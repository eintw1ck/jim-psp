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

 #include <stdio.h>
 #include <stdlib.h> 
 #ifdef HAVE_MALLOC_H 
 #include <malloc.h> 
 #endif 

#ifdef __BIG_ENDIAN__

 #include <machine/byte_order.h>

#endif 

 typedef struct { char signature[4]; int version; int offset[8]; } HEADER;

 char *filename[8] = { "PARAM.SFO", "ICON0.PNG", "ICON1.PMF", "UKNOWN.PNG", "PIC1.PNG", "SND0.AT3", "UNKNOWN.PSP", "UNKNOWN.PSAR" };

 int main(int argc, char *argv[]) {
  FILE *infile, *outfile; HEADER header; int loop0, total_size;

  // Check the argument count.
  if (argc != 2) { printf("USAGE: %s <filename>\n", argv[0]); return -1; }

  // Open the input file.
  infile = fopen(argv[1], "rb");
  if (infile == NULL) { printf("ERROR: Could not open the input file. (%s)\n", argv[1]); return -1; }

  // Get the input file size.
  fseek(infile, 0, SEEK_END); total_size = ftell(infile); fseek(infile, 0, SEEK_SET);
  if (total_size < 0) { printf("ERROR: Could not get the input file size.\n"); return -1; }

  // Read in the input file header.
  if (fread(&header, sizeof(HEADER), 1, infile) < 0) { printf("ERROR: Could not read the input file header.\n"); return -1; }

  // Check the input file signature.
  if (header.signature[0] != 0x00) { printf("ERROR: Input file is not a PBP file.\n"); return -1; } else
  if (header.signature[1] != 0x50) { printf("ERROR: Input file is not a PBP file.\n"); return -1; } else
  if (header.signature[2] != 0x42) { printf("ERROR: Input file is not a PBP file.\n"); return -1; } else
  if (header.signature[3] != 0x50) { printf("ERROR: Input file is not a PBP file.\n"); return -1; }

#ifdef __BIG_ENDIAN__

  // Swap the byte order for big-endian machines.
  for (loop0=0; loop0<8; loop0++) { header.offset[loop0] = NXSwapInt(header.offset[loop0]); }

#endif 

  // For each section...
  for (loop0=0; loop0<8; loop0++) { void *buffer; int size;

   // Get the size of the last section data.
   if (loop0 == 7) { size = total_size - header.offset[loop0]; }

   // Get the size of the section data.
   else { size = header.offset[loop0 + 1] - header.offset[loop0]; }

   // Allocate the section data buffer.
   buffer = malloc(size);
   if (buffer == NULL) { printf("ERROR: Could not allocate the section data buffer. (%d)\n", size); return -1; }

   // Read in the section data.
   if (fread(buffer, size, 1, infile) < 0) { printf("ERROR: Could not read in the section data.\n"); return -1; }

   // Open the output file.
   outfile = fopen(filename[loop0], "wb");
   if (outfile == NULL) { printf("ERROR: Could not open the output file. (%s)\n", filename[loop0]); return -1; }

   // Write out the section data.
   if (fwrite(buffer, size, 1, outfile) < 0) { printf("ERROR: Could not write out the section data.\n"); return -1; }

   // Close the output file.
   if (fclose(outfile) < 0) { printf("ERROR: Could not close the output file.\n"); return -1; }

   // Free the section data buffer.
   free(buffer);

   // Output the section information.
   printf("[%d] %8d bytes | %s\n", loop0, size, filename[loop0]);

  }

  // Close the input file.
  if (fclose(infile) < 0) { printf("ERROR: Could not close the input file.\n"); return -1; }

  // End program.
  return 0;

 }
