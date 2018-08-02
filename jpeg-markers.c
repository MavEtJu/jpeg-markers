#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totalscans = 0;
int currentscan = 0;
int writeit;

void process_file(char *filename, unsigned char **data)
{
	struct stat sb;

	stat(filename, &sb);
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		perror(filename);
		exit(1);
	}

	*data = calloc(1, sb.st_size);
	fread(*data, sb.st_size, 1, f);

	fclose(f);
}

unsigned int show_markers(unsigned char *data, int scanreq)
{
writeit = 1;
	if (data[0] == 0xff && data[1] == 0xd8) {
		printf("FFD8: SOI");
		return 2;
	}
	if (data[0] == 0xff && data[1] == 0xe0) {
		printf("FFE0: JFIF [V:%d U:%d/%d Xd:%d Yd:%d Xt:%d Yt:%d]",
			256 * data[8] + data[9],
			data[10],
			data[11],
			256 * data[12] + data[13],
			256 * data[14] + data[15],
			data[16],
			data[17]);
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xdb) {
		printf("FFDB: Define Quantization");
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xc4) {
		printf("FFC4: Define Huffman");
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xc0) {
		printf("FFC0: Start of Frame (baseline)");
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xda) {
		if (scanreq != -1 && scanreq != currentscan)
			writeit = 0;
		if (scanreq == -1)
			totalscans++;
		currentscan++;
		printf("FFDA: Start of Scan [NC:%d]", data[4]);
		unsigned int headersize = 2 + data[2] * 256 + data[3];;
		unsigned int offset = headersize;
		while (1) {
			if (data[offset] == 0xff)
				if (data[offset + 1] != 0x00)
					break;
			offset++;
		}
		printf(" (%d bytes)", offset - headersize);
		return offset;
	}
	if (data[0] == 0xff && data[1] == 0xfe) {
		printf("FFFE: Comment");
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xe1) {
		printf("FFE1: EXIF");
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] >= 0xe2 && data[1] <= 0xef) {
		printf("FF%X: APP%d", data[1], data[1] - 0xe0);
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xc2) {
		printf("FFC2: Start of Frame (progressive) [P:%d, Y:%d, X:%d, Nf:%d]",
			 data[4],
			 256 * data[5] + data[6],
			 256 * data[7] + data[8],
			 data[9]);
		return 2 + data[2] * 256 + data[3];;
	}
	if (data[0] == 0xff && data[1] == 0xd9) {
		printf("FFD9: End of Image");
		return 0;
	}

	printf("Unknown: %x %x\n", data[0], data[1]);
	exit(0);
}

int main(int argc, char **argv)
{
	unsigned char *data;
	FILE *fout;

	char finname[100];
	char foutname[100];
	char export = 0;
	int argi = 1;

	if (strcmp(argv[argi], "-e") == 0) {
		export = 1;
		argi++;
	}

	stpcpy(finname, argv[argi]);
	stpcpy(foutname, argv[argi]);
	char *s = strrchr(foutname, '.');
	*s = '\0';

	process_file(finname, &data);

	unsigned int offset = 0;
	while (1) {
		unsigned int size;
		printf("Offset: %6x - ", offset);
		size = show_markers(data + offset, -1);
		//printf(" - size: %d - ", size);
		printf("\n");
		if (size == 0)
			break;
		offset += size;
	}
	printf("Found %d scans\n", totalscans);
	if (export == 0)
		return 0;
	if (totalscans == 1)
		return 0;

	for (int i = 0; i < totalscans; i++) {
		char *filename;
		asprintf(&filename, "%s-%d.jpg", foutname, i);
		fout = fopen(filename, "w");
		printf("Saving scan %d to %s\n", i, filename);
		currentscan = 0;

		unsigned int offset = 0;
		while (1) {
			unsigned int size;
			size = show_markers(data + offset, i);
			printf("\n");
			if (writeit == 1)
				fwrite(data + offset, size, 1, fout);
			if (size == 0) {
				fwrite(data + offset, 2, 1, fout);
				break;
			}
			offset += size;
		}
	}

	return 0;
}
