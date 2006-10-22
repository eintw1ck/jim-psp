/*
 * PSPLINK
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPLINK root for details.
 *
 * parse_args.c - PSPLINK argument parser code
 *
 * Copyright (c) 2005 James F <tyranid@gmail.com>
 *
 * $HeadURL: svn://svn.pspdev.org/psp/branches/psplinkusb/psplink/parse_args.c $
 * $Id: parse_args.c 2026 2006-10-14 13:09:48Z tyranid $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parse_args.h"

int hex_to_int(char ch)
{
	ch = toupper(ch);
	if((ch >= '0') && (ch <= '9'))
	{
		return ch-'0';
	}
	else if((ch >= 'A') && (ch <= 'F'))
	{
		return ch-'A';
	}
	
	return 0;
}

int oct_to_int(char ch)
{
	if((ch >= '0') && (ch < '8'))
	{
		return ch-'0';
	}

	return 0;
}

int isodigit(char ch)
{
	if((ch >= '0') && (ch < '8'))
	{
		return 1;
	}

	return 0;
}

int decode_hex(const char *str, unsigned char *ch)
{
	int i;

	*ch = 0;
	for(i = 0; i < 2; i++)
	{
		if(!isxdigit(str[i]))
		{
			break;
		}
		*ch = *ch << 4;
		*ch = *ch | hex_to_int(str[i]);
	}
	if(i == 0)
	{
		printf("Missing following hex characters\n");
		return 0;
	}
	if(*ch == 0)
	{
		printf("Invalid hex character (not allowed NULs)\n");
		return 0;
	}

	return i;
}

int decode_oct(const char *str, unsigned char *ch)
{
	int i;

	*ch = 0;
	for(i = 0; i < 4; i++)
	{
		if(!isodigit(str[i]))
		{
			break;
		}
		*ch = *ch << 3;
		*ch = *ch | oct_to_int(str[i]);
	}
	if(i == 0)
	{
		printf("Missing following octal characters\n");
		return 0;
	}
	if(*ch == 0)
	{
		printf("Invalid octal character (not allowed NULs)\n");
		return 0;
	}

	return i;
}

int parse_cli(const char *in, char *out, int *argc, char **argv, int max_args)
{
	char in_quote = 0;
	char *outstart = out;

	if((in == NULL) || (out == NULL) || (argc == NULL) || (argv == NULL) || (max_args <= 0))
	{
		printf("Error in parse_args, invalid arguments\n");
		return 0;
	}

	*argc = 0;

	/* Skip any leading white space */
	while(isspace(*in))
	{
		in++;
	}

	/* Check this isn't an empty string */
	if(*in == 0)
	{
		return 0;
	}

	/* Set first arg */
	argv[0] = out;
	*argc += 1;

	while((*in != 0) && (*argc < (max_args)))
	{
		/* Escape character */
		if(*in == '\\')
		{
			/* Skip the escape */
			in++;
			switch(*in)
			{
				case 'n': *out++ = 10;
						  in++;
						  break;
				case 'r': *out++ = 13;
						  in++;
						  break;
				case '0': /* Octal */
						  {
							  int i;
							  unsigned char ch;
							  in++;
							  i = decode_oct(in, &ch);
							  if((i == 0) || (i == 1))
							  {
								  return 0;
							  }
							  in += i;
							  *out++ = ch;
						  }
						  break;
				case 'x': /* Hexadecimal */
						  {
							  int i;
							  unsigned char ch;
							  in++;
							  i = decode_hex(in, &ch);
							  if((i == 0) || (i == 1))
							  {
								  return 0;
							  }
							  in += i;
							  *out++ = ch;
						  }
						  break;
				case 0  : break; /* End of string */
				default : *out++ = *in++;
						  break;
			};
		}
		else
		{
			if((isspace(*in)) && (in_quote == 0))
			{
				while(isspace(*in))
				{
					in++;
				}
				if(*in != 0)
				{
					*out++ = 0;
					argv[*argc] = out;
					*argc += 1;
				}
			}
			else if((*in == '"') || (*in == '\''))
			{
				if(in_quote)
				{
					if(*in == in_quote)
					{
						in_quote = 0;
						in++;
					}
					else
					{
						*out++ = *in++;
					}
				}
				else
				{
					in_quote = *in;
					in++;
				}
			}
			else
			{
				*out++ = *in++;
			}
		}
	}

	if(in_quote)
	{
		printf("Missing matching quote %c\n", in_quote);
		return 0;
	}

	argv[*argc] = NULL;
	*out++ = 0;
	/* A command ends with a 1 */
	*out++ = 1;

	return out-outstart;
}
