# jpeg-markers
Show all the markers from a JPG file and dump all frames

Build it with "make" and run it like:

```
$ ./jpeg-markers image.jpg 
Offset:      0 - FFD8: SOI
Offset:      2 - FFE0: JFIF [V:1 U:1/1 Xd:72 Yd:72 Xt:0 Yt:0]
Offset:     14 - FFED: APP13
Offset:   223c - FFE1: EXIF
Offset:   2262 - FFE2: APP2
Offset:   2ebc - FFE1: EXIF
Offset:   448f - FFDB: Define Quantization
Offset:   44d4 - FFDB: Define Quantization
Offset:   4519 - FFC2: Start of Frame (progressive) [P:8, Y:522, X:783, Nf:3]
Offset:   452c - FFC4: Define Huffman
Offset:   454b - FFC4: Define Huffman
Offset:   4565 - FFDA: Start of Scan [NC:3] (8184 bytes)
Offset:   656b - FFC4: Define Huffman
Offset:   659f - FFDA: Start of Scan [NC:1] (21274 bytes)
Offset:   b8c3 - FFC4: Define Huffman
Offset:   b8f8 - FFDA: Start of Scan [NC:1] (1333 bytes)
Offset:   be37 - FFC4: Define Huffman
Offset:   be6b - FFDA: Start of Scan [NC:1] (1282 bytes)
Offset:   c377 - FFC4: Define Huffman
Offset:   c3cc - FFDA: Start of Scan [NC:1] (147491 bytes)
Offset:  303f9 - FFC4: Define Huffman
Offset:  30422 - FFDA: Start of Scan [NC:1] (44414 bytes)
Offset:  3b1aa - FFDA: Start of Scan [NC:3] (2426 bytes)
Offset:  3bb32 - FFC4: Define Huffman
Offset:  3bb57 - FFDA: Start of Scan [NC:1] (575 bytes)
Offset:  3bda0 - FFC4: Define Huffman
Offset:  3bdc5 - FFDA: Start of Scan [NC:1] (577 bytes)
Offset:  3c010 - FFC4: Define Huffman
Offset:  3c039 - FFDA: Start of Scan [NC:1] (48374 bytes)
Offset:  47d39 - FFD9: End of Image
Found 10 scans
```

(Fields gotten from http://www.videotechnology.com/jpeg/j1.html)

To extract the various scans, use the ```-e``` option.

```
$ ./jpeg-markers -e image.jpg 
[...]
Found 10 scans
Saving scan 0 to image-0.jpg
[...]
Saving scan 1 to image-1.jpg
[...]
Saving scan 2 to image-2.jpg
[...]
$ ls -al
total 1568
drwxr-xr-x  18 edwin  staff     576  2 Aug 15:17 .
drwx------+ 37 edwin  staff    1184  2 Aug 15:01 ..
drwxr-xr-x  13 edwin  staff     416  2 Aug 15:12 .git
-rw-r--r--   1 edwin  staff    1320  2 Aug 15:01 LICENSE
-rw-r--r--   1 edwin  staff      66  2 Aug 15:02 Makefile
-rw-r--r--   1 edwin  staff   26363  2 Aug 15:17 image-0.jpg
-rw-r--r--   1 edwin  staff   39449  2 Aug 15:17 image-1.jpg
-rw-r--r--   1 edwin  staff   19508  2 Aug 15:17 image-2.jpg
-rw-r--r--   1 edwin  staff   19457  2 Aug 15:17 image-3.jpg
-rw-r--r--   1 edwin  staff  165666  2 Aug 15:17 image-4.jpg
-rw-r--r--   1 edwin  staff   62589  2 Aug 15:17 image-5.jpg
-rw-r--r--   1 edwin  staff   20605  2 Aug 15:17 image-6.jpg
-rw-r--r--   1 edwin  staff   18750  2 Aug 15:17 image-7.jpg
-rw-r--r--   1 edwin  staff   18752  2 Aug 15:17 image-8.jpg
-rw-r--r--   1 edwin  staff   66549  2 Aug 15:17 image-9.jpg
-rw-r--r--   1 edwin  staff  294203  2 Aug 15:13 image.jpg
-rwxr-xr-x   1 edwin  staff   13476  2 Aug 15:13 jpeg-markers
-rw-r--r--   1 edwin  staff    3668  2 Aug 15:12 jpeg-markers.c
