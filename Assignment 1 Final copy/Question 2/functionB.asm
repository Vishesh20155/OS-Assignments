SECTION .data
    msg: db "Inside function B", 10
    msg2: db "The number you entered from is being printed from assembly program as- "
    msg3: db 10,10,"Next up is execution of return, control will transfer to C()...", 10
    msg4: db "The ASCII string corresponding to the number entered will be- ", 10

SECTION .bss
    digit resb 64
    digitPosition resb 8
    digitASCII resb 8

SECTION .text   
    global  functionB 
    extern C      
   
functionB:
    pop r9
    push C
    mov r10, rdi
    mov [digitASCII], r10

    mov rax, 1
    mov rdi, 1
    mov rsi, msg 
    mov rdx, 18 
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, msg2 
    mov rdx, 71
    syscall

    mov rax, r10
    call _printInt

    mov rax, 1
    mov rdi, 1
    mov rsi, msg4
    mov rdx, 63
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, digitASCII
    mov rdx, 8 
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, msg3
    mov rdx, 66
    syscall

    ret 

_printInt:
    mov rcx, digit
    mov rbx, 10         ;NewLine Characeter
    mov [rcx], rbx      ;Store it in the beginning of the string as we will print in reverse order
    inc rcx
    mov [digitPosition], rcx

_loop:
    mov rdx, 0
    mov rbx, 10
    div rbx
    push rax
    add rdx, 48

    mov rcx, [digitPosition]
    mov [rcx], dl 
    inc rcx
    mov [digitPosition], rcx

    pop rax
    cmp rax, 0
    jne _loop

_print:
    mov rcx, [digitPosition]

    mov rax, 1
    mov rdi, 1
    mov rsi, rcx
    mov rdx, 1
    syscall

    mov rcx, [digitPosition]
    dec rcx
    mov [digitPosition], rcx

    cmp rcx, digit
    jge _print

    ret