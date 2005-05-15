/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |     ___|    ____| |    \    PSPDEV Open Source Project.
#-----------------------------------------------------------------------
# (c) 2005 Dan Peori <peori@oopo.net>
# Licenced under Academic Free License version 2.0
# Review pspsdk README & LICENSE files for further details.
#
*/

#ifdef __BIG_ENDIAN__

 #include <machine/byte_order.h>

#endif

 #include <stdio.h>
 #include <string.h>
 #include <malloc.h>

 struct { char signature[4]; char version[4]; int offset[8]; } header =
  { { 0x00, 0x50, 0x42, 0x50 }, { 0x00, 0x00, 0x01, 0x00 }, { 40, 0, 0, 0, 0, 0, 0, 0 } };

 int main(int argc, char *argv[]) { int loop0, result;
  FILE *infile, *outfile; void *filedata[8]; int filesize[8];

  // Check the argument count.
  if (argc != 10) { printf("USAGE: %s <output.pbp> <param.sfo> <icon.png> <icon1.pmf> <unknown.png> <pic1.png> <snd0.at3> <unknown.psp> <unknown.psar>\n", argv[0]); return -1; }

  // For each file...
  for (loop0=0;loop0<8;loop0++) {

   // If the specificed filename is NULL, skip the file.
   if (strncmp(argv[2 + loop0], "NULL", 4) == 0) { filesize[loop0] = 0; } else {

    // Open the file.
    infile = fopen(argv[2 + loop0], "rb");
    if (infile == NULL) { printf("ERROR: Could not open the file. (%s)\n", argv[2 + loop0]); return -1; }

    // Read in the file size.
    fseek(infile, 0, SEEK_END); filesize[loop0] = ftell(infile); fseek(infile, 0, SEEK_SET);
    if (filesize[loop0] < 0) { printf("ERROR: Could not read in the file size. (%s)\n", argv[2 + loop0]); return -1; }

    // Allocate the file data space.
    filedata[loop0] = malloc(filesize[loop0]);
    if (filedata[loop0] == NULL) { printf("ERROR: Could not allocate the file data space. (%s)\n", argv[2 + loop0]); return -1; }

    // Read in the file data.
    result = fread(filedata[loop0], filesize[loop0], 1, infile);
    if (result < 0) { printf("ERROR: Could not read in the file data. (%s)\n", argv[2 + loop0]); return -1; }

    // Close the file.
    result = fclose(infile);
    if (result < 0) { printf("ERROR: Could not close the file. (%s)\n", argv[2 + loop0]); return -1; }

   }

  }

  // Set the header offset values.
  for (loop0=1;loop0<8;loop0++) { header.offset[loop0] = header.offset[loop0 - 1] + filesize[loop0 - 1]; }

#ifdef __BIG_ENDIAN__

  // Swap the byte order for big-endian machines.
  for (loop0=0;loop0<8;loop0++) { header.offset[loop0] = NXSwapInt(header.offset[loop0]); }

#endif 

  // Open the output file.
  outfile = fopen(argv[1], "wb");
  if (outfile == NULL) { printf("ERROR: Could not open the output file. (%s)\n", argv[1]); return -1; }

  // Write out the header.
  result = fwrite(&header, sizeof(header), 1, outfile);
  if (result < 0) { printf("ERROR: Could not write out the file header. (%s)\n", argv[1]); return -1; }

  // For each file...
  for (loop0=0; loop0<8; loop0++) {// void *buffer; int size;

   // Write out the file data.
   result = fwrite(filedata[loop0], filesize[loop0], 1, outfile);
   if (result < 0) { printf("ERROR: Could not write out the file data. (%s)\n", argv[1]); return -1; }

   // Free the file data space.
   if (filesize[loop0] > 0) { free(filedata[loop0]); }

  }

  // Close the output file.
  result = fclose(outfile);
  if (result < 0) { printf("ERROR: Could not close the output file. (%s)\n", argv[1]); return -1; }

  // End program.
  return 0;

 }
