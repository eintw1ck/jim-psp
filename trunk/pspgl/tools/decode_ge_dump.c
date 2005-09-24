#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>


static inline
uint32_t swap32 (uint32_t x)
{
	return  ((x >> 24) & 0x000000ff) |
		((x >> 8)  & 0x0000ff00) |
		((x << 8)  & 0x00ff0000) |
		((x << 24) & 0xff000000);
}


#if defined(__BIG_ENDIAN__)
#define be32_to_cpu(x) (x)
#define le32_to_cpu(x) swap32(x)
#elif defined(__LITTLE_ENDIAN__)
#define le32_to_cpu(x) (x)
#define be32_to_cpu(x) swap32(x)
#else
#error unknown endianess!!
#endif


enum pspgl_dump_tag {
        PSPGL_GE_DUMP_MATRIX    = 1,
        PSPGL_GE_DUMP_REGISTERS = 2,
        PSPGL_GE_DUMP_DLIST     = 3
};


#define DUMP(x...) do { printf(x); } while (0)


static
float float32 (uint32_t i)
{
	i <<= 8;
	return *(float *) &i;
}


static const char *test_function [] = {
	"NEVER", "ALWAYS", "EQUAL", "NOTEQUAL", "LESS", "LEQUAL", "GREATER", "GEQUAL"
};


static
void process_insn (uint32_t insn)
{
	uint8_t opcode = insn >> 24;
	uint32_t arg = insn & 0x00ffffff;

	switch (opcode) {
	case 0x00:
		DUMP("NOP");
		break;
	case 0x01:
		DUMP("Vertex Address (BASE) + 0x%08x", arg);
		break;
	case 0x02:
		DUMP("Index Address (BASE) + 0x%08x", arg);
		break;
	case 0x04:
		DUMP("Primitive Kick: %d vertices, type %d", arg & 0xffff, arg >> 16);
		break;
	case 0x05:
		DUMP("Bezier Patch Kick: count: %d in U, %d in V-direction", arg & 0xff, arg >> 8);
		break;
	case 0x06:
		DUMP("Spline Kick: count: %d in U, %d in V-direction, u_f %d, v_f %d",
			arg & 0xff, arg >> 8, (arg >> 16) & 0x03, (arg >> 18) & 0x03);
		break;
	case 0x07:
		DUMP("Bounding Box: count: %d", arg);
		break;
	case 0x08:
		DUMP("Jump to Address (BASE) + 0x%08x", arg);
		break;
	case 0x09:
		DUMP("Conditional Jump to Address (BASE) + 0x%08x", arg);
		break;
	case 0x0a:
		DUMP("Call Display List at address (BASE) + 0x%08x", arg);
		break;
	case 0x0b:
		DUMP("Return from Display List Call");
		break;
	case 0x0c:
		DUMP("END");
		break;
	case 0x0e:
		DUMP("Raise Signal Interrupt");
		break;
	case 0x0f:
		DUMP("FINISH");
		break;
	case 0x10:
		DUMP("BASE Address 0x%08x", (arg << 8) & 0xff000000);
		break;
	case 0x12:
		DUMP("Vertex Type 0x%08x", arg);
		break;
	case 0x13:
		DUMP("Offset Address 0x%08x", arg);
		break;
	case 0x14:
		DUMP("Origin Address 0x%08x", arg);
		break;
	case 0x15:
		DUMP("Draw Region Start x %d, y %d", arg & 0x3ff, arg >> 10);
		break;
	case 0x16:
		DUMP("Draw Region End x %d, y %d", arg & 0x3ff, arg >> 10);
		break;
	case 0x17:
		DUMP("Enable Lighting = %d", arg);
		break;
	case 0x18:
		DUMP("Enable Light 0 = %d", arg);
		break;
	case 0x19:
		DUMP("Enable Light 1 = %d", arg);
		break;
	case 0x1a:
		DUMP("Enable Light 2 = %d", arg);
		break;
	case 0x1b:
		DUMP("Enable Light 3 = %d", arg);
		break;
	case 0x1c:
		DUMP("Enable Clipping = %d", arg);
		break;
	case 0x1d:
		DUMP("Enable Culling = %d", arg);
		break;
	case 0x1e:
		DUMP("Enable Texture2D = %d", arg);
		break;
	case 0x1f:
		DUMP("Enable Fog = %d", arg);
		break;
	case 0x20:
		DUMP("Enable Dither = %d", arg);
		break;
	case 0x21:
		DUMP("Enable Alpha Blending = %d", arg);
		break;
	case 0x22:
		DUMP("Enable Alpha Test = %d", arg);
		break;
	case 0x23:
		DUMP("Enable Depth Test = %d", arg);
		break;
	case 0x24:
		DUMP("Enable Stencil Test = %d", arg);
		break;
	case 0x25:
		DUMP("Enable Antialiasing = %d", arg);
		break;
	case 0x26:
		DUMP("Enable Patch Culling = %d", arg);
		break;
	case 0x27:
		DUMP("Enable Color Test = %d", arg);
		break;
	case 0x28:
		DUMP("Enable Color LogicOp = %d", arg);
		break;
	case 0x2a:
		DUMP("Bone Matrix Offset = %d", arg);
		break;
	case 0x2b:
		DUMP("Bone Matrix Value = %1.5f", float32(arg));
		break;
	case 0x2c ... 0x33:
		DUMP("Morph Weight %d = %1.5f", opcode - 0x2c, float32(arg));
		break;
	case 0x36:
		DUMP("Patch Divide (S/T) %d/%d", arg & 0xff, arg >> 8);
		break;
	case 0x37:
		DUMP("Patch Primitive Type %d (%s)", arg, arg == 0 ? "TRIANGLES" : arg == 1 ? "LINES" : arg == 2 ? "POINTS" : "???");
		break;
	case 0x38:
		DUMP("Patch Front Face Orientation = %d (%s)", arg, arg == 0 ? "CW" : arg == 1 ? "CCW" : "???");
		break;
	case 0x3a:
		DUMP("Model Matrix Select = %d", arg);
		break;
	case 0x3b:
		DUMP("Model Matrix Upload %1.5f", float32(arg));
		break;
	case 0x3c:
		DUMP("View Matrix Select = %d", arg);
		break;
	case 0x3d:
		DUMP("View Matrix Upload %1.5f", float32(arg));
		break;
	case 0x3e:
		DUMP("Projection Matrix Select = %d", arg);
		break;
	case 0x3f:
		DUMP("Projection Matrix Upload %1.5f", float32(arg));
		break;
	case 0x40:
		DUMP("Texture Matrix Select = %d", arg);
		break;
	case 0x41:
		DUMP("Texture Matrix Upload %1.5f", float32(arg));
		break;
	case 0x42:
		DUMP("Viewport Size X %1.5f", float32(arg));
		break;
	case 0x43:
		DUMP("Viewport Size Y %1.5f", float32(arg));
		break;
	case 0x44:
		DUMP("Viewport Size Z / Depth Range %1.5f", float32(arg));
		break;
	case 0x45:
		DUMP("Viewport Offset X %1.5f", float32(arg));
		break;
	case 0x46:
		DUMP("Viewport Offset Y %1.5f", float32(arg));
		break;
	case 0x47:
		DUMP("Viewport Offset Z / Depth Offset %1.5f", float32(arg));
		break;
	case 0x48:
		DUMP("Texture Scale S %1.5f", float32(arg));
		break;
	case 0x49:
		DUMP("Texture Scale T %1.5f", float32(arg));
		break;
	case 0x4a:
		DUMP("Texture Offset S %1.5f", float32(arg));
		break;
	case 0x4b:
		DUMP("Texture Offset T %1.5f", float32(arg));
		break;
	case 0x4c:
		DUMP("Viewport/Screen Offset X %d", arg >> 4);
		break;
	case 0x4d:
		DUMP("Viewport/Screen Offset Y %d", arg >> 4);
		break;
	case 0x4e:
		/* ??? */
		break;
	case 0x4f:
		/* ??? */
		break;
	case 0x50:
		DUMP("Shading = %d (%s)", arg, arg == 0 ? "FLAT" : arg == 1 ? "SMOOTH" : "???");
		break;
	case 0x51:
		DUMP("Enable Normal Reverse = %d", arg);
		break;
	case 0x53:
		DUMP("Update Material %d/%d/%d - specular %s, diffuse %s, ambient %s",
		     (arg >> 16) & 0xff, (arg >> 8) & 0xff, arg & 0xff, 
		     (arg >> 16) & 0xff ? "yes" : "no", (arg >> 8) & 0xff ? "yes" : "no", arg & 0xff ? "yes" : "no");
		break;
	case 0x54:
		DUMP("Color Material Emissive 0x%06x", arg);
		break;
	case 0x55:
		DUMP("Color Material Ambient 0x%06x", arg);
		break;
	case 0x56:
		DUMP("Color Material Diffuse 0x%06x", arg);
		break;
	case 0x57:
		DUMP("Color Material Specular 0x%06x", arg);
		break;
	case 0x58:
		DUMP("Color Material Ambient Alpha 0x%02x", arg);
		break;
	case 0x59:
		/* ??? */
		break;
	case 0x5a:
		/* ??? */
		break;
	case 0x5b:
		DUMP("Specular Power %1.5f", float32(arg));
		break;
	case 0x5c:
		DUMP("Ambient LightModel Color 0x%06x", arg);
		break;
	case 0x5d:
		DUMP("Ambient LightModel Alpha 0x%02x", arg);
		break;
	case 0x5e:
		DUMP("Light Mode %d (%s)",
		     arg, arg == 0 ? "single color" : arg == 1 ? "seperate specular color" : "??");
		break;
	case 0x5f ... 0x62:
		DUMP("(Light %d) Type %d (%s), %s/%s/%s", opcode - 0x5f,
		     (arg >> 8), (arg >> 8) == 0 ? "parallel" : (arg >> 8) == 1 ? "point" : (arg >> 8) == 2 ? "spot" : "??",
		     arg & 0x01 ? "ambient" : "-", arg & 0x02 ? "diffuse" : "-", arg & 0x04 ? "specular" : "-");
		break;
	case 0x63 ... 0x6e:
		DUMP("(Light %d) Position %c %1.5f", (opcode - 0x63) / 3, (opcode - 0x63) % 3 + 'X', float32(arg));
		break;
	case 0x6f ... 0x7a:
		DUMP("(Light %d) Direction %c %1.5f", (opcode - 0x6f) / 3, (opcode - 0x6f) % 3 + 'X', float32(arg));
		break;
	case 0x7b ... 0x86:
		DUMP("(Light %d) Attentuation Coefficient %c %1.5f", (opcode - 0x7b) / 3, (opcode - 0x7b) % 3 + 'A', float32(arg));
		break;
	case 0x87 ... 0x8a:
		DUMP("(Light %d) Spotlight Cutoff %1.5f", opcode - 0x87, float32(arg));
		break;
	case 0x8b ... 0x8e:
		DUMP("(Light %d) Spotlight Cone Attentuation %1.5f", opcode - 0x8b, float32(arg));
		break;
	case 0x8f ... 0x9a:
		DUMP("(Light %d) Light Color %s 0x%06x",
		     (opcode - 0x8f) / 3, ((opcode - 0x8f) % 3) == 0 ? "Ambient" : ((opcode - 0x8f) % 3 == 1) ? "Diffuse" : "Specular", arg);
		break;
	case 0x9b:
		DUMP("Front Face Orientation = %d (%s)", arg, arg == 0 ? "CW" : arg == 1 ? "CCW" : "???");
		break;
	case 0x9c:
		DUMP("Frame Buffer Pointer [23-0] 0x%08x", arg);
		break;
	case 0x9d:
		DUMP("Frame Buffer Stride %d. Frame Buffer Pointer [32-24] 0x%08x", arg & 0xffff, (arg << 8) & 0xff000000);
		break;
	case 0x9e:
		DUMP("Depth Buffer Pointer [23-0] 0x%08x", arg);
		break;
	case 0x9f:
		DUMP("Depth Buffer Stride %d. Frame Buffer Pointer [32-24] 0x%08x", arg & 0xffff, (arg << 8) & 0xff000000);
		break;
	case 0xa0 ... 0xa7:
		DUMP("(Mipmap Level %d) Texture Pointer [23-0] 0x%08x", opcode - 0xa0, arg);
		break;
	case 0xa8 ... 0xaf:
		DUMP("(Mipmap Level %d) Texture Stride %d. Texture Pointer [32-24] 0x%08x", opcode - 0xa8, arg & 0xffff, (arg << 8) & 0xff000000);
		break;
	case 0xb0:
		DUMP("CLUT Pointer [23-0] 0x%08x", arg);
		break;
	case 0xb1:
		DUMP("CLUT Pointer [32-24] 0x%08x", arg << 8);
		break;
	case 0xb8 ... 0xbf:
		DUMP("(Mipmap Level %d) Texture Width 2^%d, Height 2^%d", opcode - 0xb8, arg & 0xff, arg >> 8);
		break;
	case 0xc4:
		DUMP("CLUT size %d", arg);
		break;
	case 0xc7:
		DUMP("Texture Wrap Mode S %d (%s), T %d (%s)", arg & 0xff, (arg & 0xff) ? "clamp" : "repeat", arg >> 8, (arg >> 8) ? "clamp" : "repeat");
		break;
	case 0xca:
		DUMP("TextureEnv Color 0x%06x", arg);
		break;
	case 0xcb:
		DUMP("Texture Flush");
		break;
	case 0xcc:
		DUMP("Texture Sync");
		break;
	case 0xcd:
		DUMP("Fog End %1.5f", float32(arg));
		break;
	case 0xce:
		DUMP("Fog Range %1.5f", float32(arg));
		break;
	case 0xcf:
		DUMP("Fog Color 0x%06x", arg);
		break;
	case 0xd0:
		DUMP("Texture Slope %1.5f", float32(arg));
		break;
	case 0xd2:
		DUMP("Pixel Format %d (%s)", arg, arg == 0 ? "RGB565" : arg == 1 ? "RGBA551" : arg == 2 ? "RGBA4444" : arg == 3 ? "RGBA8888" : "???");
		break;
	case 0xd3:
		DUMP("Clear Enable = %d, Flags (%s|%s|%s)", (arg & 1),
			(arg & (1 << 8)) ? "CLEAR_COLOR" : "-",
			(arg & (1 << 9)) ? "CLEAR_ALPHA/STENCIL" : "-",
			(arg & (1 << 10)) ? "CLEAR_DEPTH" : "-");
		break;
	case 0xd4:
		DUMP("Scissor Lower Left %d/%d", arg & 0x3ff, arg >> 10);
		break;
	case 0xd5:
		DUMP("Scissor Upper Right %d/%d", arg & 0x3ff, arg >> 10);
		break;
	case 0xd6:
		DUMP("Near Depth Plane %d / %f", arg, float32(arg));
		break;
	case 0xd7:
		DUMP("Far Depth Plane %d / %f", arg, float32(arg));
		break;
	case 0xd8:
		DUMP("Color Test Function %d (%s)", arg, (arg < sizeof(test_function)/sizeof(test_function[0])) ? test_function[arg] : "???");
		break;
	case 0xd9:
		DUMP("Color Test Reference 0x%06x", arg);
		break;
	case 0xda:
		DUMP("Color Test Mask 0x%06x", arg);
		break;
	case 0xdb:
		DUMP("Alpha Test Function %d (%s), Reference 0x%02x, Mask 0x%02x", 
		     arg & 0xff, ((arg & 0xff) < sizeof(test_function)/sizeof(test_function[0])) ? test_function[arg & 0xff] : "???",
		     (arg >> 8) & 0xff, (arg >> 16) & 0xff);
		break;
	case 0xdc:
		DUMP("Stencil Test Function %d (%s), Reference 0x%02x, Mask 0x%02x", 
		     arg & 0xff, ((arg & 0xff) < sizeof(test_function)/sizeof(test_function[0])) ? test_function[arg & 0xff] : "???",
		     (arg >> 8) & 0xff, (arg >> 16) & 0xff);
		break;
	case 0xde:
		DUMP("Depth Test Function %d (%s)", arg, (arg < sizeof(test_function)/sizeof(test_function[0])) ? test_function[arg] : "???");
		break;
	case 0xe2 ... 0xe5:
		DUMP("Dither Matrix %d", opcode - 0xe2);
		break;
	case 0xe7:
		DUMP("Depth Mask 0x%04x", arg);
		break;
	case 0xe8:
		DUMP("Pixel Mask Color 0x%06x", arg);
		break;
	case 0xe9:
		DUMP("Pixel Mask Alpha 0x%02x", arg);
		break;
	default:
		;
	}
}


static
void process_chunk (uint32_t tag, uint32_t *buf, unsigned long len)
{
	uint32_t adr, i;

	printf("\ngot chunk (tag 0x%08x, len %lu bytes)\n", tag, len);

	switch (tag) {
	case PSPGL_GE_DUMP_MATRIX:
		for (i=0; i<12; i++) {
			uint32_t *m = &buf[16*i];
			int j, k;
			int rows = (i==10) ? 4 : 3;
			printf("\n");
			for (j=0; j<rows; j++) {
				printf("matrix %d [ ", i);
				for (k=0; k<4; k++) {
					printf("% 2.4f ", float32(le32_to_cpu(m[rows*k+j])));
				}
				printf("]\n");
			}
		}
		break;
	case PSPGL_GE_DUMP_DLIST:
		adr = le32_to_cpu(buf[0]);
		len -= 4;
		buf++;
		for (i=0; i<len/4; i++) {
			uint32_t insn = le32_to_cpu(buf[i]);
			printf("dlist 0x%08x: 0x%08x    ", adr+4*i, insn);
			process_insn(insn);
			printf("\n");
		}
		break;
	case PSPGL_GE_DUMP_REGISTERS:
		for (i=0; i<len/4; i++)
			printf("reg 0x%02x: 0x%08x\n", i, le32_to_cpu(buf[i]));
		break;
	default:
		fprintf(stderr, "**** unknown tag! ****\n");
	}
}


int main (int argc, char **argv)
{
	unsigned long flen, fpos;
	uint32_t *fptr;
	int fd;

	if (argc != 2) {
		fprintf(stderr, "\n\tusage: %s <dump.ge>\n\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDONLY, 0);
	flen = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	fptr = (uint32_t*) mmap(NULL, flen, PROT_READ, MAP_PRIVATE, fd, 0);

	fpos = 0;
	flen /= 4;

	while (fpos<flen-2) {
		uint32_t tag = le32_to_cpu(fptr[fpos]);
		uint32_t len = le32_to_cpu(fptr[fpos+1]);

		if (fpos+len/4 > flen) {
			fprintf(stderr, "**** unexpected end of file! ****\n");
			break;
		}

		if (len == 0)
			break;

		process_chunk(tag, &fptr[fpos+2], len-2*4);
		fpos += len/4;
	}

	munmap((void*) fptr, flen);
	close(fd);

	return 0;
}
