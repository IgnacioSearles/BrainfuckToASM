# Compiler

## Desired program

[![](https://mermaid.ink/img/pako:eNo9j8sKwjAQRX8lzCqC_kAFwfdGoViX2UyTqZbaiUwTUNR_N7Xqbu6Ze-fxAOsdQQYnwetZ7Q5Tw10sB7URz4HYJYZ6IVhzFW2jcvGp344mk1mpd3QjGRkuVZLPo2-Iu6fVOUr34UP8P3KBthmQ7QNOL9N6tSUmweD7gOs56Xmx_6ZhDC1Ji7VLZz4MK2UgnKklA1kqHVUYL8GA4VeyxqvDQGtXp2mQVXjpaAwYgy_ubCELEulnWtXY__F1vd4z2VwQ)](https://mermaid.live/edit#pako:eNo9j8sKwjAQRX8lzCqC_kAFwfdGoViX2UyTqZbaiUwTUNR_N7Xqbu6Ze-fxAOsdQQYnwetZ7Q5Tw10sB7URz4HYJYZ6IVhzFW2jcvGp344mk1mpd3QjGRkuVZLPo2-Iu6fVOUr34UP8P3KBthmQ7QNOL9N6tSUmweD7gOs56Xmx_6ZhDC1Ji7VLZz4MK2UgnKklA1kqHVUYL8GA4VeyxqvDQGtXp2mQVXjpaAwYgy_ubCELEulnWtXY__F1vd4z2VwQ)

## Brainfuck boiler plate

- 30.000 bytes of memory.
- Pointer that starts in the middle.

## Brainfuck instructions

| Symbol | Action | C equivalent |
| --- | --- | --- |
| +   | Increment value at pointer. | (*pointer)++; |
| -   | Decrement value at pointer. | (*pointer)--; |
| >   | Increment pointer. | pointer++; |
| <   | Decrement pointer. | pointer--; |
| \[  | Jump to matching " \] " if value at pointer equals 0. | while (*pointer) { |
| \]  | Jump to matching " \[ ". | }   |
| .   | Print value at pointer as char. | printf("%c", *pointer); |
| ,   | Save byte at pointer. | scanf("%c", pointer); |

## Assembly Conversion

### Register use

- rax -> pointer
- rbx -> operation register (+, -). Value at pointer.

### Boiler plate code

```
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
      
    ;code goes here
    
    mov rsp, rbp
    pop rbp
    ret
```

### Translating into NASM

- **+**

```
    inc rbx
```

- **-**

```
    dec rbx
```

- **<**

```
    dec rax
```

- **>**

```
    inc rax
```

- **\[**

```
ltagID:
    cmp rbx, 0
    je ltagIDend
```

- **\]**

```
    jmp ltagID
ltagIDend:
```

- **.**

```
    mov rdx, 0
    mov dl, bl
    mov rcx, print_byte
    call printf
```

- **,**

```
    mov rdx, rax
    mov rcx, scan_byte
    call scanf
```

- **+ or - followed by < or >**

```
    mov [rel rax], bl
```

- **+ or - followed by [ or ]**

```
    mov [rel rax], bl
```

- **[ or ] not followed by [ and ]**

```
    mov bl, byte [rel rax]
```
## Compiler

### Lexer

**Task:** create tokens from input text. Ignore whitespace and newlines.

**Tokens:**

| SYMBOL | TOKEN |
| --- | --- |
| +   | ADD |
| -   | SUBTRACT |
| <   | PTR_LEFT |
| >   | PTR_RIGHT |
| \[  | START_LOOP |
| \]  | END_LOOP |
| .   | PRINT |
| ,   | SCAN |

**Lexer definitions file:**

This file defines which regex will correspond to which token.

```text
\+ || ADD
\- || SUBTRACT
\< || PTR_LEFT
\> || PTR_RIGHT
\[ || START_LOOP
\] || END_LOOP
\. || PRINT
\, || SCAN
```

Represented in code as:

[![](https://mermaid.ink/img/pako:eNo1js0KwjAQhF8l7CmF9gUieNKbJ-sxlzXZpsHmh7gBpfTdTUVvwzcfw6xgkiVQ4ArmWVyuBx1RBsydGIajuMuRi49OFHL06vbyy428pQfFHUAPgUpAb9vKqqMQGnimQBpUi5YmrAtr0HFras0Wmc7WcyqgJlye1ANWTuM7GlBcKv2lk8d2Kvys7QMp8zh_)](https://mermaid.live/edit#pako:eNo1js0KwjAQhF8l7CmF9gUieNKbJ-sxlzXZpsHmh7gBpfTdTUVvwzcfw6xgkiVQ4ArmWVyuBx1RBsydGIajuMuRi49OFHL06vbyy428pQfFHUAPgUpAb9vKqqMQGnimQBpUi5YmrAtr0HFras0Wmc7WcyqgJlye1ANWTuM7GlBcKv2lk8d2Kvys7QMp8zh_)

### Parser

**Task:** organize and interpret tokens. Identify code blocks (from loops), must correctly ID every loop to later create ASM tags.

**Parser definitions file:**

This file defines how different token combinations will translate into ASM code.

```text
ADD || inc rbx\n
SUBTRACT || dec rbx\n
PTR_LEFT || dec rax\n
PTR_RIGHT || inc rax\n
START_LOOP || ltagID:\ncmp rbx, 0\nje ltagIDend\n
END_LOOP || jmp ltagID\nltagIDend:\n
PRINT || mov rdx, 0\nmov dl, bl\nmov rcx, print_byte\ncall printf\n
SCAN || mov rdx, rax\nmov rcx, scan_byte\ncall scanf\n
ADD|SUBTRACT,PTR_RIGHT|PTR_LEFT || mov [rel rax], bl\n
ADD|SUBTRACT,START_LOOP|END_LOOP || mov [rel rax], bl\n
```

Represented in code as:

[![](https://mermaid.ink/img/pako:eNo9j7GuwjAMRX_F8gw_UCQm2BiegK1hcBuXRjROlTgDQvz78yuvbNY5Z7h-YZ88Y4P3TPMIp_POSdf-UC6cwfMQJGhIUm6w3e6hX02uE5ebpQv2bdEc5A5CJRrtF8oW_7WaHizli4e2S2kCEn9dBS9ibBcA-iXhk3YGcIORc6TgbevLCYBDHTmyw8ZOW0p1UodO3pbW2ZPy0QdNGZuBpsIbpKrp8pQeG82V1-gQyF6P_9X7F17lXRE)](https://mermaid.live/edit#pako:eNo9j7GuwjAMRX_F8gw_UCQm2BiegK1hcBuXRjROlTgDQvz78yuvbNY5Z7h-YZ88Y4P3TPMIp_POSdf-UC6cwfMQJGhIUm6w3e6hX02uE5ebpQv2bdEc5A5CJRrtF8oW_7WaHizli4e2S2kCEn9dBS9ibBcA-iXhk3YGcIORc6TgbevLCYBDHTmyw8ZOW0p1UodO3pbW2ZPy0QdNGZuBpsIbpKrp8pQeG82V1-gQyF6P_9X7F17lXRE)

The program can lookahead several tokens.

### Code Generator

**Task:** create the final ASM file.

## Example

The following example adds two numbers. The compiler is given a input code written in *Brainfuck* and a output file is generated. The output of the compiler is NASM Assembly which then must be linked using gcc.

- Input (Brainfuck)

```text
++
>+++

[
< +
> -
]

++++ ++++
[
< +++ +++
> -
]
< .
```

- Output (NASM)

```
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
``` 
