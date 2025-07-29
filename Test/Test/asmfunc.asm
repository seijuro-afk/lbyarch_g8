section .data
    fmt_x db "X[%d] = %.1f",10,0
    fmt_y db "Y[%d] = %.1f",10,0
    fmt_z db "Z[%d] = %.1f",10,0

section .text
bits 64
default rel
global saxpy_asm
extern printf

saxpy_asm:
    ; Windows x64 calling convention (RCX, RDX, R8, R9 + XMM1 for float A)
    push rbp
    mov rbp, rsp
    sub rsp, 64
    
    ; Save non-volatile registers
    mov [rsp+32], rbx
    mov [rsp+40], rsi
    mov [rsp+48], rdi
    
    ; Save parameters correctly for Windows x64
    ; saxpy_asm(int n, float A, float* X, float* Y, float* Z)
    ; n=RCX, A=XMM1, X=RDX, Y=R8, Z=R9
    mov edi, ecx          ; n (save in non-volatile)
    movss [rsp+52], xmm1  ; A (float parameter is in XMM1)
    mov rsi, rdx          ; X pointer
    mov rbx, r8           ; Y pointer  
    mov r10, r9           ; Z pointer
    
    ; Initialize loop counter
    xor eax, eax          ; index = 0
    
    ;Add process here
.process:

.done:
    ; Restore non-volatile registers
    mov rbx, [rsp+32]
    mov rsi, [rsp+40] 
    mov rdi, [rsp+48]
    
    add rsp, 64
    pop rbp
    ret