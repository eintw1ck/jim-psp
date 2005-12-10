This sample uses the sceChnnlsv module directly to do savegame
encryption.  It currently works only on firmware 2.0 under the TIFF
exploit.  It can handle both old and new format saves (SaveParam
structure sizes 0x5c8, 0x5dc, 0x600).  New saves require a
game-specific encryption key which can only be found inside the game
code.
