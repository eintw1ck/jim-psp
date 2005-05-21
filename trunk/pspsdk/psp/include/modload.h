
struct load_t
{
   u32 a;   // Set to 0x14
   u32 b;   // For encrypted set to 1, else 2
   u32 c;   // ""  ""        ""  "" "  ""   ""
   u32 unused;  // Unused
   u32 d;   // Set to 0
   u32 e;   // Set to 0x01000000
};
int sceKernelLoadModule(const char *path, u32 zero, struct load_t* mod);
int sceKernelStartModule(int modid, u32 zero1, u32 zero2, u32 *status, u32 zero3);

