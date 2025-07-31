global asmhello
section .text

asmhello:
    ; Windows x64 calling convention:
    ; RCX = Z (float*)
    ; RDX = n (int) 
    ; XMM2 = A (float)
    ; R9 = X (float*)
    ; [RSP+40] = Y (float*) - 5th parameter on stack
    
    ; Load Y from stack into R8
    mov r8, [rsp + 40]      ; Y is the 5th parameter, located at RSP+40
    
.loop:
    test rdx, rdx           ; Check if n == 0
    jz .done                ; Jump to done if n == 0
    
    movss xmm0, [r9]        ; Load X[i] into xmm0
    mulss xmm0, xmm2        ; xmm0 = A * X[i]
    addss xmm0, [r8]        ; xmm0 = A * X[i] + Y[i]
    movss [rcx], xmm0       ; Store result in Z[i]
    
    add r9, 4               ; Advance X pointer (float = 4 bytes)
    add r8, 4               ; Advance Y pointer
    add rcx, 4              ; Advance Z pointer
    dec rdx                 ; Decrement counter
    jmp .loop               ; Continue loop
    
.done:
    ret