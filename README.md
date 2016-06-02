CLEFIA
======

CLEFIA is a proprietary block cipher algorithm, developed by Sony. 
Its name is derived from the French word clef, meaning "key". 

The **block size is 128 bits** (16 bytes) and the key size can be 128 bit, 192 bit or 256 bit. 
It is intended to be used in DRM systems. 
It is among the cryptographic techniques recommended candidate for Japanese government use by CRYPTREC revision in 2013.

### How can I use this...
1. Compile: `gcc -o clefia clefia.c`
1. Run: `./clefia <file_to_cipher> <file_destination_encrypted> <file_destination_decrypted>`
