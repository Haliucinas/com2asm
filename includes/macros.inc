;--------------------------------------
cmpje macro opand1, opand2, dest
    local @@exit
    cmp opand1, opand2
        jne @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
cmpjne macro opand1, opand2, dest
    local @@exit
    cmp opand1, opand2
        je @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
cmpja macro opand1, opand2, dest
    local @@exit
    cmp opand1, opand2
        jbe @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
cmpjge macro opand1, opand2, dest
    local @@exit
    cmp opand1, opand2
        jb @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
cmpjg macro opand1, opand2, dest
    local @@exit
    cmp opand1, opand2
        jbe @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
cmpjbe macro opand1, opand2, dest
    local @@exit
    cmp opand1, opand2
        jg @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
mjc macro dest
    local @@exit
        jnc @@exit
    jmp dest
@@exit:
endm
;--------------------------------------
; implementation of printf()
print macro string
    local sdb, @@skip, @@nextChar, @@exit
    push ax si
    jmp @@skip
    sdb db string, 0

@@skip:
    lea si, sdb

@@nextChar:
    mov al, cs:[si]
    cmp al, 0
        jz @@exit
    inc si
    mov ah, 02h
    mov dl, al
    int 21h
    jmp @@nextChar

@@exit:
    pop si ax
endm
;--------------------------------------
; implementation of printf() with new line
printn macro string
    local sdb, @@skip, @@nextChar, @@end
    push ax si
    jmp @@skip
    sdb db string, 0Dh, 0Ah, 0

@@skip:
    lea si, sdb

@@nextChar:
    mov al, cs:[si]
    cmpje al, 0, @@end
    inc si
    mov ah, 02h
    mov dl, al
    int 21h
    jmp @@nextChar

@@end:
    pop si ax
endm
;--------------------------------------
printString macro string
    push ax dx
    mov ah, 09h
    lea dx, string
    int 21h
    pop dx ax
endm
;--------------------------------------
printParam macro string
    local @@print, @@end
    push ax dx si
    xor si, si
@@print:
    cmpje [string][si], 0, @@end
    mov ah, 02h
    mov dl, byte ptr [string + si]
    int 21h
    inc si
    jmp @@print
@@end:
    pop si dx ax
endm
;--------------------------------------
printBuffer macro buffer
    push ax dx
    mov dx, buffer
    mov ah, 09h
    int 21h
    pop dx ax
endm
;--------------------------------------
printSymbol macro buffer
    push ax dx
    mov ah, 02h
    mov dl, buffer
    int 21h
    pop dx ax
endm
;--------------------------------------
newLine macro
    push ax dx
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    mov ah, 02h
    mov dl, 0Ah
    int 21h
    pop dx ax
endm
;--------------------------------------
exit macro
    mov ax, 4C00h
    int 21h
endm
;--------------------------------------