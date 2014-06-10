;--------------------------------------
; checks if parameter if given,
; prints help message or saves given param.
; checks if param extension is correct.
getParam proc
    push ax dx bx si di 
    mov si, 0081h
    xor di, di
    xor dx, dx

    mov al, es:[si]
    cmpje al, 0Dh, @@emptyMsg
    lea bx, param
    inc si

@@read:
    mov al, es:[si]
    cmpjge al, 61h, @@sub
    jmp @@skip

@@sub:
    sub al, 20h

@@skip:
    cmpje al, 0Dh, @@help
    mov byte ptr [bx + di], al
    inc si
    inc di
    jmp @@read

@@emptyMsg:
    printn 'com2asm: missing file operand'
    print 'Try ''com2asm --help'' for more information.'
    exit

@@help:
    cmpjne [param], '-', @@checkExtension
    cmpjne [param][1], '-', @@checkExtension
    cmpjne [param][2], 'H', @@checkExtension
    cmpjne [param][3], 'E', @@checkExtension
    cmpjne [param][4], 'L', @@checkExtension
    cmpjne [param][5], 'P', @@checkExtension
    cmpjne [param][6], 0, @@checkExtension
    printn 'Usage: com2asm SOURCE'
    printn '     or: com2asm SOURCE > DEST'
    printn 'Disassembles SOURCE to STDOUT or DEST.'
    newLine
    print 'Report com2asm bugs to haliucinas@gmail.com'
    exit

@@checkExtension:
    push di
    cmpje dx, 0, @@skipdx
    mov di, dx

@@skipdx:
    dec di
    cmpjne [param][di], 'M', @@invalidUse
    dec di
    cmpjne [param][di], 'O', @@invalidUse
    dec di
    cmpjne [param][di], 'C', @@invalidUse
    dec di
    cmpjne [param][di], '.', @@invalidUse
    pop di
    jmp @@exit

@@invalidUse:
    printn 'Invalid use!'
    print 'Only .COM files are supported.'
    exit

@@exit:
    mov byte ptr [bx + di], 0
    pop di si bx dx ax
    ret
endp
;--------------------------------------
openFile proc
    push ax cx dx
    mov ax, 4E00h
    mov cx, 1
    lea dx, param
    int 21h
        mjc @@error2
    mov ax, 3D00h
    lea dx, param
    int 21h
        mjc @@error1
    mov fileHandle, ax
    jmp @@exit

@@error1:
    print 'Error occurred while opening source file.'
    exit

@@error2:
    print 'File does not exist: '
    printParam param
    exit

@@exit:
    pop dx cx ax
    ret
endp
;--------------------------------------
closeFile proc
  push ax bx
  mov ah, 3Eh
  mov bx, fileHandle
  int 21h
    mjc @@error
  jmp @@end

@@error:
  print 'Error occurred while closing source file.'
  exit

@@end:
  pop bx ax
  ret
endp
;--------------------------------------
printByte proc
    push dx ax
    mov dh, al
    shr al, 4
    cmpja al, 09h, @@above9
    add al, '0'
    jmp @@firstNum

@@above9:
    sub al, 10
    add al, 'A'

@@firstNum:
    mov ah, 02
    mov dl, al
    int 21h

    and dh, 0Fh
    cmpja dh, 09h, @@above9_2
    add dh, '0'
    jmp @@secNum

@@above9_2:
    sub dh, 10
    add dh, 'A'

@@secNum:
    mov ah, 02
    mov dl, dh
    int 21h
    pop ax dx
    ret
endp
;--------------------------------------
printWord proc
    push ax
    xchg ah, al
    call printByte
    mov al, ah
    call printByte
    pop ax
    ret
endp
;--------------------------------------
printCommand proc
    call clearData
    call readByte
    call getOpcodeData
    call printIP
    call setData
    call printInstruction
    ret
endp
;--------------------------------------
; zeroes data to assure that algorithms
; are correctly executed.
clearData proc
    mov [amUsed], 0
    mov [dispSize], 0
    mov [dataSize], 0
    mov [dumpLenght], 0
    ret
endp
;--------------------------------------
; reads buffer once and saves current byte
; until all bytes from buffer are used.
; Upon empty read closes file and exits program.
readByte proc
    push ax cx dx bx
    cmpjge si, di, @@fillFileBuffer
    jmp @@readByte

@@fillFileBuffer:
    mov ah, 3Fh
    mov cx, 64
    lea dx, fileBuffer
    mov bx, fileHandle
    int 21h
    xor si, si
    mov di, ax
    cmpjne di, 0, @@readByte
    call closeFile
    exit

@@readByte:
    mov al, [fileBuffer + si]
    mov [currentByte], al
    inc si
    inc [countIP]
    xor bx, bx
    mov bl, [dumpLenght]
    mov byte ptr [hexDump + bx], al
    inc [dumpLenght]

@@exit:
    pop bx dx cx ax
    ret
endp
;--------------------------------------
; gathers data from opcode map.
getOpcodeData proc
    push ax dx bx
    mov al, size opcode
    mov dl, [currentByte]
    mul dl
    lea bx, opcodeMap
    add bx, ax
    mov al, [bx].opType
    mov [tmp].opType, al
    mov ax, [bx].mnemonic
    mov [tmp].mnemonic, ax
    mov al, [bx].operand1
    mov [tmp].operand1, al
    mov al, [bx].operand2
    mov [tmp].operand2, al
    pop bx dx ax
    ret
endp
;--------------------------------------
printIP proc
    push ax
    cmpje [nl], 1, @@newLine
    mov [nl], 1
    jmp @@skip
@@newLine:
    newLine
@@skip:
    mov ax, [countIP]
    call printWord
    printSymbol ':'
    printSymbol ' '
    pop ax
    ret
endp
;--------------------------------------
; gets instruction length, saves needed bytes,
; stores hex dump and puts neccesary spaces
setData proc
    push ax
    cmpje [tmp].opType, SegPrefix, @@pExit
    cmpjne [tmp].opType, Extension, @@continue
    call getExtensionOpcode

@@continue:
    cmpjbe [tmp].operand1, 22, @@nextByte
    cmpjbe [tmp].operand1, 30, @@setImm1
    call getAddrMode
    call getDispSize
    jmp @@nextByte

@@setImm1:
    mov al, [tmp].operand1
    call getDataSize
    jmp @@exit

@@nextByte:
    cmpjbe [tmp].operand2, 22, @@exit
    cmpjbe [tmp].operand2, 30, @@setImm2
    call getAddrMode
    call getDispSize
    jmp @@exit

@@setImm2:
    mov al, [tmp].operand2
    call getDataSize

@@exit:
    call fillBuffers
@@pExit:
    call printHexDump
    call printSpaces
    pop ax
    ret
endp
;--------------------------------------
; if extension, finds which mnemonic used.
getExtensionOpcode proc
    push ax bx
    mov al, [currentByte]
    call getAddrMode
    mov bl, [regByte]
    shl bl, 1
    cmpje al, 0FFh, @@extensionFF
    cmpje al, 0FEh, @@extensionFE
    cmpje al, 0F7h, @@extensionF7
    cmpje al, 0F6h, @@extensionF6
    cmpjge al, 0D0h, @@extensionD0D3

    mov bx, [GRP1 + bx]
    mov [tmp].mnemonic, bx
    jmp @@exit

@@extensionD0D3:
    mov bx, [GRP2 + bx]
    mov [tmp].mnemonic, bx
    jmp @@exit

@@extensionF6:
    mov bx, [GRP3a + bx]
    mov [tmp].mnemonic, bx
    ; test command has second operand as byte immediate
    cmpjne bx, 00ADh, @@skipIb
    mov [tmp].operand2, Ib
@@skipIb:
    jmp @@exit

@@extensionF7:
    mov bx, [GRP3b + bx]
    mov [tmp].mnemonic, bx
    ; test command has second operand as word immediate
    cmpjne bx, 00ADh, @@skipIw
    mov [tmp].operand2, Iw
@@skipIw:
    jmp @@exit

@@extensionFE:
    mov bx, [GRP4 + bx]
    mov [tmp].mnemonic, bx
    jmp @@exit

@@extensionFF:
    mov bx, [GRP5 + bx]
    mov [tmp].mnemonic, bx

@@exit:
    pop bx ax
    ret
endp
;--------------------------------------
getAddrMode proc
    push ax dx
    cmpje [amUsed], 1, @@exit
    mov [amUsed], 1
    call readByte
    xor ax, ax
    mov al, [currentByte]
    mov dl, 40h
    div dl
    mov [modByte], al
    xchg al, ah
    xor ah, ah
    mov dl, 8h
    div dl
    mov [regByte], al
    mov [rmByte], ah

@@exit:
    pop dx ax
    ret
endp
;--------------------------------------
getDispSize proc
    cmpje [modByte], 11b, @@exit
    cmpje [modByte], 01b, @@01mod
    cmpje [modByte], 10b, @@10mod

    cmpje [rmByte], 110b, @@10mod
    jmp @@exit

@@01mod:
    mov [dispSize], 1
    jmp @@exit

@@10mod:
    mov [dispSize], 2

@@exit:
    ret
endp
;--------------------------------------
getDataSize proc
    cmpjbe al, 25, @@1bData
    cmpjbe al, 29, @@2bData

    mov [dataSize], 4
    jmp @@exit

@@1bData:
    mov [dataSize], 1
    jmp @@exit

@@2bData:
    mov [dataSize], 2

@@exit:
    ret 
endp
;--------------------------------------
fillBuffers proc
    push ax
    cmpje [dispSize], 1, @@1bDisp
    cmpje [dispSize], 2, @@2bDisp
    jmp @@setData

@@1bDisp:
    call readByte
    mov al, [currentByte]
    mov [disp + 1], al
    jmp @@setData

@@2bDisp:
    call readByte
    mov al, [currentByte]
    call readByte
    mov ah, [currentByte]
    mov word ptr [disp], ax

@@setData:
    cmpje [dataSize], 1, @@1bData
    cmpjge [dataSize], 2, @@2bData
    jmp @@exit

@@1bData:
    call readByte
    mov al, [currentByte]
    mov [data + 1], al
    jmp @@exit

@@2bData:
    call readByte
    mov al, [currentByte]
    call readByte
    mov ah, [currentByte]
    mov word ptr [data], ax
    cmpjbe [dataSize], 2, @@exit

@@4bData:
    call readByte
    mov al, [currentByte]
    call readByte
    mov ah, [currentByte]
    mov word ptr [data + 2], ax

@@exit:
    pop ax
    ret
endp
;--------------------------------------
printHexDump proc
    push ax cx bx
    xor cx, cx
    mov cl, [dumpLenght]
@@loopy:
    mov al, [hexDump + bx]
    inc bx
    call printByte
    loop @@loopy
    pop bx cx ax
    ret
endp
;--------------------------------------
printSpaces proc
    push cx
    mov cl, 7
    sub cl, [dumpLenght]
    shl cl, 1

@@loopy:
    printSymbol ' '
    loop @@loopy
    pop cx
    ret
endp
;--------------------------------------
printInstruction proc
    push bx
    cmpjne [tmp].opType, Unsupported, @@skip
    printString unsupportedMsg
    jmp @@exit
@@skip:
    printBuffer [tmp].mnemonic
    cmpje [tmp].operand1, 0, @@exit
    cmpje [hexDump], 90h, @@exit 
    mov al, [tmp].operand1
    call writeOperandValue
    cmpje [tmp].operand2, 0, @@exit
    printSymbol ','
    printSymbol ' '
    mov al, [tmp].operand2
    call writeOperandValue

@@exit:
    pop bx
    ret
endp
;--------------------------------------
writeOperandValue proc
    push ax dx
    mov dl, 3
    cmpjbe al, 8, @@w0Reg
    cmpjbe al, 16, @@w1Reg
    cmpjbe al, 20, @@sReg
    cmpjbe al, C3, @@const
    cmpje al, I0, @@I0
    cmpje al, Ib, @@data
    cmpje al, Jpb, @@relative
    cmpje al, Ob, @@offset
    cmpje al, Iw, @@data
    cmpje al, Jw, @@relative
    cmpje al, Ow, @@offset
    cmpje al, Ap, @@relative
    cmpjbe al, Ew, @@rm
    cmpjbe al, Gw, @@reg
    cmpje al, Sw, @@seg
    jmp @@exit

@@w0Reg:
    dec al
    mul dl
    add ax, w0List
    printBuffer ax
    jmp @@exit

@@w1Reg:
    sub al, 9
    mul dl
    add ax, w1List
    printBuffer ax
    jmp @@exit

@@sReg:
    sub al, 17
    mul dl
    add ax, sList
    printBuffer ax
    jmp @@exit

@@const:
    cmpjne al, C1, @@const3
    printSymbol '1'
    jmp @@exit
@@const3:
    printSymbol '3'
    jmp @@exit

@@I0:
    cmpje [data][1], 0Ah, @@exit
@@data:
    call printData
    jmp @@exit

@@relative:
    call printRel
    jmp @@exit

@@offset:
    call printOffset
    jmp @@exit

@@rm:
    call printRm
    jmp @@exit

@@reg:
    cmpjne al, Gb, @@Gw
    mov al, [regByte]
    mul dl
    add ax, w0List
    printBuffer ax
    jmp @@exit
@@Gw:
    mov al, [regByte]
    mul dl
    add ax, w1List
    printBuffer ax
    jmp @@exit

@@seg:
    mov al, [regByte]
    mul dl
    add ax, sList
    printBuffer ax

@@exit:
    pop dx ax
    ret
endp
;--------------------------------------
printData proc
    push ax bx
    cmpje al, Iw, @@Iw

    mov al, [data + 1]
    call printByte
    jmp @@exit

@@Iw:
    mov ax, word ptr [data]
    call printWord

@@exit:
    pop bx ax
    ret
endp
;--------------------------------------
printRel proc
    push ax
    cmpje al, Jpb, @@relShort
    cmpje al, Jw, @@relNear

    mov ax, word ptr [data + 2]
    call printWord
    printSymbol ':'
    mov ax, word ptr [data]
    call printWord
    jmp @@exit

@@relShort:
    mov al, [data + 1]
    cbw
    add ax, [countIP]
    inc ax
    call printWord
    jmp @@exit

@@relNear:
    mov ax, word ptr [data]
    add ax, [countIP]
    inc ax
    call printWord

@@exit:
    pop ax
    ret
endp
;--------------------------------------
printOffset proc
    push ax
    mov ax, word ptr [data]
    cmpjne al, Ob, @@Ow

    call ptrStr
    printSymbol '['
    call printWord
    printSymbol ']'
    jmp @@exit

@@Ow:
    call ptrStr
    printSymbol '['
    call printWord
    printSymbol ']'

@@exit:
    pop ax
    ret
endp
;--------------------------------------
ptrStr proc
    cmpje [tmp].operand2, Ib, @@bytePtr
    cmpje [tmp].operand2, C1, @@bytePtr
    cmpje [tmp].operand2, argCL, @@bytePtr
    cmpje [hexDump], 0f6h, @@bytePtr
    cmpje [hexDump], 0feh, @@bytePtr
    cmpje [tmp].operand2, Iw, @@wordPtr
    cmpje [hexDump], 0f7h, @@wordPtr
    cmpje [hexDump], 0ffh, @@farPtr
    jmp @@exit

@@bytePtr:
    cmpje [hexDump], 83h, @@wordPtr
    cmpje [hexDump], 0d1h, @@wordPtr
    cmpje [hexDump], 0d3h, @@wordPtr
    printString bytePtr
    jmp @@exit

@@wordPtr:
    printString wordPtr
    jmp @@exit

@@farPtr:
    cmpjge [hexDump][1], 18h, @@next
    jmp @@wordPtr
@@next:
    cmpjbe [hexDump][1], 1Fh, @@print
    cmpjge [hexDump][1], 28h, @@next1
    jmp @@wordPtr
@@next1:
    cmpjbe [hexDump][1], 2Fh, @@print
    jmp @@wordPtr
@@print:
    printString farPtr

@@exit:
    ret
endp
;--------------------------------------
printRm proc
    push ax bx
    cmpje [modByte], 11b, @@11b
    cmpjge [modByte], 01b, @@01b

    call ptrStr
    printSymbol '['
    mov bl, [rmByte]
    cmpje [rmByte], 110b, @@110b
    shl bl, 1
    mov bx, [rmList + bx]
    printBuffer bx
    printSymbol ']'
    jmp @@exit

@@01b:
    call ptrStr
    printSymbol '['
    mov bl, [rmByte]
    shl bl, 1
    mov bx, [rmList + bx]
    printBuffer bx
    printSymbol '+'
    cmpje [dispSize], 2, @@110b
    mov al, [disp + 1]
    call printByte
    printSymbol ']'
    jmp @@exit

@@11b:
    cmpjne al, Eb, @@w1
    mov bl, [rmByte]
    shl bl, 1
    mov bx, [w0List + bx]
    printBuffer bx
    jmp @@exit

@@w1:
    mov bl, [rmByte]
    shl bl, 1
    mov bx, [w1List + bx]
    printBuffer bx
    jmp @@exit

@@110b:
    mov ax, word ptr [disp]
    call printWord
    printSymbol ']'

@@exit:
    pop bx ax
    ret
endp
;--------------------------------------