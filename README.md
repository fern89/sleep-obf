# Sleep Obfuscation
A simple gargoyle-style sleep with memory encryption, implemented for x86 in pure ROP, no APCs involved. Useful to bypass runtime scanners such as PE-sieve and moneta.

We implement a ROP chain consisting of VirtualProtect(to RW) -> RtlEncryptMemory -> Sleep -> RtlDecryptMemory -> VirtualProtect (to RX) in garg.s, read it from bottom-up as that's how the stack (FIFO data) is used.

Compiled with mingw-gcc using `i686-w64-mingw32-gcc garg.c garg.s -masm=intel`

Do note that scanners may also look out for the DOS header present in first 4kb section of the PE image, but hiding that is out of scope for this project.
