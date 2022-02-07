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
inc rbx
inc rbx
mov [rel rax], bl
inc rax
mov bl, byte [rel rax]
inc rbx
inc rbx
inc rbx
mov [rel rax], bl
ltag0:
cmp rbx, 0
je ltag0end
dec rax
mov bl, byte [rel rax]
inc rbx
mov [rel rax], bl
inc rax
mov bl, byte [rel rax]
dec rbx
mov [rel rax], bl
jmp ltag0
ltag0end:
inc rbx
inc rbx
inc rbx
inc rbx
inc rbx
inc rbx
inc rbx
inc rbx
mov [rel rax], bl
ltag1:
cmp rbx, 0
je ltag1end
dec rax
mov bl, byte [rel rax]
inc rbx
inc rbx
inc rbx
inc rbx
inc rbx
inc rbx
mov [rel rax], bl
inc rax
mov bl, byte [rel rax]
dec rbx
mov [rel rax], bl
jmp ltag1
ltag1end:
dec rax
mov bl, byte [rel rax]
mov rdx, 0
mov dl, bl
mov rcx, print_byte
call printf
    
    mov rsp, rbp
    pop rbp
    ret
