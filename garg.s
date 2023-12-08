.intel_syntax noprefix
.globl _ropsled
fin:
    pop ebp
    ret
_ropsled:
    push ebp
    mov ebp, esp
    lea eax, fin
    push eax
    
    //make rx again
    push DWORD PTR [ebp+28]
    push 0x20
    push DWORD PTR [ebp+24]
    push DWORD PTR [ebp+36]
    push DWORD PTR [ebp+32]
    push DWORD PTR [ebp+8]
    
    //dec data
    push 0
    push DWORD PTR [ebp+24]
    push DWORD PTR [ebp+36]
    push DWORD PTR [ebp+32]
    push DWORD PTR [ebp+20]
    
    //sleep
    push DWORD PTR [ebp+40]
    push DWORD PTR [ebp+32]
    push DWORD PTR [ebp+12]
    
    //enc data
    push 0
    push DWORD PTR [ebp+24]
    push DWORD PTR [ebp+36]
    push DWORD PTR [ebp+32]
    push DWORD PTR [ebp+16]
    
    //make rw
    push DWORD PTR [ebp+28]
    push 0x4
    push DWORD PTR [ebp+24]
    push DWORD PTR [ebp+36]
    push DWORD PTR [ebp+32]
    push DWORD PTR [ebp+8]
    ret
