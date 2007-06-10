
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	uint32_t fsize;
	int lcount;
	uint8_t c;

	FILE *fp;
	FILE *ofp;

	if(argc<4)
	{
		printf("bin2c inputfile outputfile recordname\n");
		exit(0);
	}

	ofp = fopen(argv[2], "wt");
	if(ofp != NULL)
	{
		fp = fopen(argv[1], "rb");
		if(fp!=NULL)
		{
			fseek(fp, 0x0L, SEEK_END);
			fsize = ftell(fp);
			fseek(fp, 0x0L, SEEK_SET);

			lcount = 0;

			fprintf(ofp, "unsigned long size_%s=%i;\n", argv[3], fsize);
			fprintf(ofp, "unsigned char %s[]=\n{\n\t", argv[3]);

			while(ftell(fp) < fsize)
			{
				c = fgetc(fp);

				if(lcount > 0)
					fprintf(ofp, ", ");

				fprintf(ofp, "0x%02X", c);

				lcount++;
				if(lcount == 10)
				{
					lcount = 0;
					fprintf(ofp, ", \n\t");
				}
			}
			fclose(fp);
			fprintf(ofp, "\n};\n");
			fclose(ofp);
		}
		else
		{
			fprintf(stderr, "Could not open file\n");
		}
	}
	else
	{
		fprintf(stderr, "Could not open output file\n");
	}

	return 0;
}

