section .data
    print_byte db "%c", 10, 0
    scan_byte db "%c", 0

section .bss
    mem resb 30000
    
section .text

global main
extern printf
extern scanf

main:
    push rbp
    mov rbp, rsp

    mov rax, mem
    add rax, 15000

    mov rbx, 0
      
    ;code
    
    mov rsp, rbp
    pop rbp
    ret
