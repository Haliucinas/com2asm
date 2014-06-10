; opcode structure
opcode struc
	opType db 0
	mnemonic dw 0
	operand1 db 0
	operand2 db 0
ends

; possible types
Implemented equ 0
SegPrefix equ 1
Extension equ 2
Unsupported equ 3

; available mnemonics
mneAdd db "add $"
mnePush db "push $"
mnePop db "pop $"
mneOr db "or $"
mneAdc db "adc $"
mneSbb db "sbb $"
mneAnd db "and $"
mneEs db "es: $"
mneDaa db "daa $"
mneSub db "sub $"
mneCs db "cs: $"
mneDas db "das $"
mneXor db "xor $"
mneSs db "ss: $"
mneAaa db "aaa $"
mneCmp db "cmp $"
mneDs db "ds: $"
mneAas db "aas $"
mneInc db "inc $"
mneDec db "dec $"
mneJo db "jo $"
mneJno db "jno $"
mneJb db "jb $"
mneJnb db "jnb $"
mneJz db "jz $"
mneJnz db "jnz $"
mneJbe db "jbe $"
mneJa db "ja $"
mneJs db "js $"
mneJns db "jns $"
mneJpe db "jpe $"
mneJpo db "jpo $"
mneJl db "jl $"
mneJge db "jge $"
mneJle db "jle $"
mneJg db "jg $"
mneTest db "test $"
mneXchg db "xchg $"
mneMov db "mov $"
mneNop db "nop $"
mneCall db "call $"
mnePushf db "pushf $"
mnePopf db "popf $"
mneRet db "ret $"
mneRetf db "retf $"
mneInt db "int $"
mneInto db "into $"
mneIret db "iret $"
mneRol db "rol $"
mneRor db "ror $"
mneRcl db "rcl $"
mneRcr db "rcr $"
mneShl db "shl $"
mneShr db "shr $"
mneSar db "sar $"
mneAam db "aam $"
mneAad db "aad $"
mneLoopnz db "loopnz $"
mneLoopz db "loopz $"
mneLoop db "loop $"
mneJcxz db "jcxz $"
mneJmp db "jmp $"
mneCmc db "cmc $"
mneNot db "not $"
mneNeg db "neg $"
mneMul db "mul $"
mneImul db "imul $"
mneDiv db "div $"
mneIdiv db "idiv $"
mneClc db "clc $"
mneStc db "stc $"
mneCli db "cli $"
mneSti db "sti $"
mneCld db "cld $"
mneStd db "std $"

; possible operands
argAL equ 1
argCL equ 2
argDL equ 3
argBL equ 4
argAH equ 5
argCH equ 6
argDH equ 7
argBH equ 8
argAX equ 9
argCX equ 10
argDX equ 11
argBX equ 12
argSP equ 13
argBP equ 14
argSI equ 15
argDI equ 16
argES equ 17
argCS equ 18
argSS equ 19
argDS equ 20
C1 equ 21		; const 1
C3 equ 22		; const 3
I0 equ 23		; suppressed immediate
Ib equ 24		; immediate byte
Jpb equ 25		; jump short, relative, displacement relative to next instruction
Ob equ 26		; offset byte
Iw equ 27		; immediate word
Jw equ 28		; jump near, relative, displacement relative to next instruction
Ow equ 29		; offset word
Ap equ 30		; jump far, absolute, address given in operand
Eb equ 31		; modr/m byte
Ew equ 32		; modr/m word
Gb equ 33		; reg byte
Gw equ 34		; reg word
Sw equ 35		; seg word
; dummy args. needed only for correct reading and are never really used.
M equ 36
Mp equ 37

; http://www.mlsite.net/8086/
label opcodeMap opcode
	opcode <Implemented, mneAdd, Eb, Gb>			;00
	opcode <Implemented, mneAdd, Ew, Gw>			;01
	opcode <Implemented, mneAdd, Gb, Eb>			;02
	opcode <Implemented, mneAdd, Gw, Ew>			;03
	opcode <Implemented, mneAdd, argAL, Ib>			;04
	opcode <Implemented, mneAdd, argAX, Iw>			;05
	opcode <Implemented, mnePush, argES, 0>			;06
	opcode <Implemented, mnePop, argES, 0>			;07
	opcode <Implemented, mneOr, Eb, Gb>				;08
	opcode <Implemented, mneOr, Ew, Gw>				;09
	opcode <Implemented, mneOr, Gb, Eb>				;0A
	opcode <Implemented, mneOr, Gw, Ew>				;0B
	opcode <Implemented, mneOr, argAL, Ib>			;0C
	opcode <Implemented, mneOr, argAX, Iw>			;0D
	opcode <Implemented, mnePush, argCS, 0>			;0E
	opcode <Unsupported, mnemonic, 0, 0>			;0F
	opcode <Implemented, mneAdc, Eb, Gb>			;10
	opcode <Implemented, mneAdc, Ew, Gw>			;11
	opcode <Implemented, mneAdc, Gb, Eb>			;12
	opcode <Implemented, mneAdc, Gw, Ew>			;13
	opcode <Implemented, mneAdc, argAL, Ib>			;14
	opcode <Implemented, mneAdc, argAX, Iw>			;15
	opcode <Implemented, mnePush, argSS, 0>			;16
	opcode <Implemented, mnePop, argSS, 0>			;17
	opcode <Implemented, mneSbb, Eb, Gb>			;18
	opcode <Implemented, mneSbb, Ew, Gw>			;19
	opcode <Implemented, mneSbb, Gb, Eb>			;1A
	opcode <Implemented, mneSbb, Gw, Ew>			;1B
	opcode <Implemented, mneSbb, argAL, Ib>			;1C
	opcode <Implemented, mneSbb, argAX, Iw>			;1D
	opcode <Implemented, mnePush, argDS, 0>			;1E
	opcode <Implemented, mnePop, argDS, 0>			;1F
	opcode <Implemented, mneAnd, Eb, Gb>			;20
	opcode <Implemented, mneAnd, Ew, Gw>			;21	
	opcode <Implemented, mneAnd, Gb, Eb>			;22
	opcode <Implemented, mneAnd, Gw, Ew>			;23
	opcode <Implemented, mneAnd, argAL, Ib>			;24
	opcode <Implemented, mneAnd, argAX, Iw>			;25
	opcode <SegPrefix, mneEs, 0, 0>					;26
	opcode <Implemented, mneDaa, 0, 0>				;27
	opcode <Implemented, mneSub, Eb, Gb>			;28
	opcode <Implemented, mneSub, Ew, Gw>			;29
	opcode <Implemented, mneSub, Gb, Eb>			;2A
	opcode <Implemented, mneSub, Gw, Ew>			;2B
	opcode <Implemented, mneSub, argAL, Ib>			;2C
	opcode <Implemented, mneSub, argAX, Iw>			;2D
	opcode <SegPrefix, mneCs, 0, 0>					;2E
	opcode <Implemented, mneDas, 0, 0>				;2F
	opcode <Implemented, mneXor, Eb, Gb>			;30
	opcode <Implemented, mneXor, Ew, Gw>			;31
	opcode <Implemented, mneXor, Gb, Eb>			;32
	opcode <Implemented, mneXor, Gw, Ew>			;33
	opcode <Implemented, mneXor, argAL, Ib>			;34
	opcode <Implemented, mneXor, argAX, Iw>			;35
	opcode <Implemented, mneSs, 0, 0>				;36
	opcode <Implemented, mneAaa, 0, 0>				;37
	opcode <Implemented, mneCmp, Eb, Gb>			;38
	opcode <Implemented, mneCmp, Ew, Gw>			;39
	opcode <Implemented, mneCmp, Gb, Eb>			;3A
	opcode <Implemented, mneCmp, Gw, Ew>			;3B
	opcode <Implemented, mneCmp, argAL, Ib>			;3C
	opcode <Implemented, mneCmp, argAX, Iw>			;3D
	opcode <SegPrefix, mneDs, 0, 0>					;3E
	opcode <Implemented, mneAas, 0, 0>				;3F
	opcode <Implemented, mneInc, argAX, 0>			;40
	opcode <Implemented, mneInc, argCX, 0>			;41
	opcode <Implemented, mneInc, argDX, 0>			;42
	opcode <Implemented, mneInc, argBX, 0>			;43
	opcode <Implemented, mneInc, argSP, 0>			;44
	opcode <Implemented, mneInc, argBP, 0>			;45
	opcode <Implemented, mneInc, argSI, 0>			;46
	opcode <Implemented, mneInc, argDI, 0>			;47
	opcode <Implemented, mneDec, argAX, 0>			;48
	opcode <Implemented, mneDec, argCX, 0>			;49
	opcode <Implemented, mneDec, argDX, 0>			;4A
	opcode <Implemented, mneDec, argBX, 0>			;4B
	opcode <Implemented, mneDec, argSP, 0>			;4C
	opcode <Implemented, mneDec, argBP, 0>			;4D
	opcode <Implemented, mneDec, argSI, 0>			;4E
	opcode <Implemented, mneDec, argDI, 0>			;4F
	opcode <Implemented, mnePush, argAX, 0>			;50
	opcode <Implemented, mnePush, argCX, 0>			;51
	opcode <Implemented, mnePush, argDX, 0>			;52
	opcode <Implemented, mnePush, argBX, 0>			;53
	opcode <Implemented, mnePush, argSP, 0>			;54
	opcode <Implemented, mnePush, argBP, 0>			;55
	opcode <Implemented, mnePush, argSI, 0>			;56
	opcode <Implemented, mnePush, argDI, 0>			;57
	opcode <Implemented, mnePop, argAX, 0>			;58
	opcode <Implemented, mnePop, argCX, 0>			;59
	opcode <Implemented, mnePop, argDX, 0>			;5A
	opcode <Implemented, mnePop, argBX, 0>			;5B
	opcode <Implemented, mnePop, argSP, 0>			;5C
	opcode <Implemented, mnePop, argBP, 0>			;5D
	opcode <Implemented, mnePop, argSI, 0>			;5E
	opcode <Implemented, mnePop, argDI, 0>			;5F
	opcode <Unsupported, mnemonic, 0, 0>			;60
	opcode <Unsupported, mnemonic, 0, 0>			;61
	opcode <Unsupported, mnemonic, 0, 0>			;62
	opcode <Unsupported, mnemonic, 0, 0>			;63
	opcode <Unsupported, mnemonic, 0, 0>			;64
	opcode <Unsupported, mnemonic, 0, 0>			;65
	opcode <Unsupported, mnemonic, 0, 0>			;66
	opcode <Unsupported, mnemonic, 0, 0>			;67
	opcode <Unsupported, mnemonic, 0, 0>			;68
	opcode <Unsupported, mnemonic, 0, 0>			;69
	opcode <Unsupported, mnemonic, 0, 0>			;6A
	opcode <Unsupported, mnemonic, 0, 0>			;6B
	opcode <Unsupported, mnemonic, 0, 0>			;6C
	opcode <Unsupported, mnemonic, 0, 0>			;6D
	opcode <Unsupported, mnemonic, 0, 0>			;6E
	opcode <Unsupported, mnemonic, 0, 0>			;6F
	opcode <Implemented, mneJo, Jpb, 0>				;70
	opcode <Implemented, mneJno, Jpb, 0>			;71
	opcode <Implemented, mneJb, Jpb, 0>				;72
	opcode <Implemented, mneJnb, Jpb, 0>			;73
	opcode <Implemented, mneJz, Jpb, 0>				;74
	opcode <Implemented, mneJnz, Jpb, 0>			;75
	opcode <Implemented, mneJbe, Jpb, 0>			;76
	opcode <Implemented, mneJa, Jpb, 0>				;77
	opcode <Implemented, mneJs, Jpb, 0>				;78
	opcode <Implemented, mneJns, Jpb, 0>			;79
	opcode <Implemented, mneJpe, Jpb, 0>			;7A
	opcode <Implemented, mneJpo, Jpb, 0>			;7B
	opcode <Implemented, mneJl, Jpb, 0>				;7C
	opcode <Implemented, mneJge, Jpb, 0>			;7D
	opcode <Implemented, mneJle, Jpb, 0>			;7E
	opcode <Implemented, mneJg, Jpb, 0>				;7F
	opcode <Extension, mnemonic, Eb, Ib>			;80
	opcode <Extension, mnemonic, Ew, Iw>			;81
	opcode <Extension, mnemonic, Eb, Ib>			;82
	opcode <Extension, mnemonic, Ew, Ib>			;83
	opcode <Implemented, mneTest, Eb, Gb>			;84
	opcode <Implemented, mneTest, Ew, Gw>			;85
	opcode <Implemented, mneXchg, Gb, Eb>			;86
	opcode <Implemented, mneXchg, Gw, Ew>			;87
	opcode <Implemented, mneMov, Eb, Gb>			;88
	opcode <Implemented, mneMov, Ew, Gw>			;89
	opcode <Implemented, mneMov, Gb, Eb>			;8A
	opcode <Implemented, mneMov, Gw, Ew>			;8B
	opcode <Implemented, mneMov, Ew, Sw>			;8C
	opcode <Unsupported, mnemonic, Gw, M>			;8D
	opcode <Implemented, mneMov, Sw, Ew>			;8E
	opcode <Implemented, mnePop, Ew, 0>				;8F
	opcode <Implemented, mneNop, argAX, argAX>		;90
	opcode <Implemented, mneXchg, argCX, argAX>		;91
	opcode <Implemented, mneXchg, argDX, argAX>		;92
	opcode <Implemented, mneXchg, argBX, argAX>		;93
	opcode <Implemented, mneXchg, argSP, argAX>		;94
	opcode <Implemented, mneXchg, argBP, argAX>		;95
	opcode <Implemented, mneXchg, argSI, argAX>		;96
	opcode <Implemented, mneXchg, argDI, argAX>		;97
	opcode <Unsupported, mnemonic, 0, 0>			;98
	opcode <Unsupported, mnemonic, 0, 0>			;99
	opcode <Implemented, mneCall, Ap, 0>			;9A
	opcode <Unsupported, mnemonic, 0, 0>			;9B
	opcode <Implemented, mnePushf, 0, 0>			;9C
	opcode <Implemented, mnePopf, 0, 0>				;9D
	opcode <Unsupported, mnemonic, 0, 0>			;9E
	opcode <Unsupported, mnemonic, 0, 0>			;9F
	opcode <Implemented, mneMov, argAL, Ob>			;A0
	opcode <Implemented, mneMov, argAX, Ow>			;A1
	opcode <Implemented, mneMov, Ob, argAL>			;A2
	opcode <Implemented, mneMov, Ow, argAX>			;A3
	opcode <Unsupported, mnemonic, 0, 0>			;A4
	opcode <Unsupported, mnemonic, 0, 0>			;A5
	opcode <Unsupported, mnemonic, 0, 0>			;A6
	opcode <Unsupported, mnemonic, 0, 0>			;A7
	opcode <Implemented, mneTest, argAL, Ib>		;A8
	opcode <Implemented, mneTest, argAX, Iw>		;A9
	opcode <Unsupported, mnemonic, 0, 0>			;AA
	opcode <Unsupported, mnemonic, 0, 0>			;AB
	opcode <Unsupported, mnemonic, 0, 0>			;AC
	opcode <Unsupported, mnemonic, 0, 0>			;AD
	opcode <Unsupported, mnemonic, 0, 0>			;AE
	opcode <Unsupported, mnemonic, 0, 0>			;AF
	opcode <Implemented, mneMov, argAL, Ib>			;B0
	opcode <Implemented, mneMov, argCL, Ib>			;B1
	opcode <Implemented, mneMov, argDL, Ib>			;B2
	opcode <Implemented, mneMov, argBL, Ib>			;B3
	opcode <Implemented, mneMov, argAH, Ib>			;B4
	opcode <Implemented, mneMov, argCH, Ib>			;B5
	opcode <Implemented, mneMov, argDH, Ib>			;B6
	opcode <Implemented, mneMov, argBH, Ib>			;B7
	opcode <Implemented, mneMov, argAX, Iw>			;B8
	opcode <Implemented, mneMov, argCX, Iw>			;B9
	opcode <Implemented, mneMov, argDX, Iw>			;BA
	opcode <Implemented, mneMov, argBX, Iw>			;BB
	opcode <Implemented, mneMov, argSP, Iw>			;BC
	opcode <Implemented, mneMov, argBP, Iw>			;BD
	opcode <Implemented, mneMov, argSI, Iw>			;BE
	opcode <Implemented, mneMov, argDI, Iw>			;BF
	opcode <Unsupported, mnemonic, 0, 0>			;C0
	opcode <Unsupported, mnemonic, 0, 0>			;C1
	opcode <Implemented, mneRet, Iw, 0>				;C2
	opcode <Implemented, mneRet, 0, 0>				;C3
	opcode <Unsupported, mnemonic, Gw, Mp>			;C4
	opcode <Unsupported, mnemonic, Gw, Mp>			;C5
	opcode <Implemented, mneMov, Eb, Ib>			;C6
	opcode <Implemented, mneMov, Ew, Iw>			;C7
	opcode <Unsupported, mnemonic, 0, 0>			;C8
	opcode <Unsupported, mnemonic, 0, 0>			;C9
	opcode <Implemented, mneRetf, Iw, 0>			;CA
	opcode <Implemented, mneRetf, 0, 0>				;CB
	opcode <Implemented, mneInt, C3, 0>				;CC
	opcode <Implemented, mneInt, Ib, 0>				;CD
	opcode <Implemented, mneInto, 0, 0>				;CE
	opcode <Implemented, mneIret, 0, 0>				;CF
	opcode <Extension, mnemonic, Eb, C1>			;D0
	opcode <Extension, mnemonic, Ew, C1>			;D1
	opcode <Extension, mnemonic, Eb, argCL>			;D2
	opcode <Extension, mnemonic, Ew, argCL>			;D3
	opcode <Implemented, mneAam, I0, 0>				;D4
	opcode <Implemented, mneAad, I0, 0>				;D5
	opcode <Unsupported, mnemonic, 0, 0>			;D6
	opcode <Unsupported, mnemonic, 0, 0>			;D7
	opcode <Unsupported, mnemonic, 0, 0>			;D8
	opcode <Unsupported, mnemonic, 0, 0>			;D9
	opcode <Unsupported, mnemonic, 0, 0>			;DA
	opcode <Unsupported, mnemonic, 0, 0>			;DB
	opcode <Unsupported, mnemonic, 0, 0>			;DC
	opcode <Unsupported, mnemonic, 0, 0>			;DD
	opcode <Unsupported, mnemonic, 0, 0>			;DE
	opcode <Unsupported, mnemonic, 0, 0>			;DF
	opcode <Implemented, mneLoopnz, Jpb, 0>			;E0
	opcode <Implemented, mneLoopz, Jpb, 0>			;E1
	opcode <Implemented, mneLoop, Jpb, 0>			;E2
	opcode <Implemented, mneJcxz, Jpb, 0>			;E3
	opcode <Unsupported, mnemonic, argAL, Ib>		;E4
	opcode <Unsupported, mnemonic, argAX, Ib>		;E5
	opcode <Unsupported, mnemonic, Ib, argAL>		;E6
	opcode <Unsupported, mnemonic, Ib, argAX>		;E7
	opcode <Implemented, mneCall, Jw, 0>			;E8
	opcode <Implemented, mneJmp, Jw, 0>				;E9
	opcode <Implemented, mneJmp, Ap, 0>				;EA
	opcode <Implemented, mneJmp, Jpb, 0>			;EB
	opcode <Unsupported, mnemonic, argAL, argDX>	;EC
	opcode <Unsupported, mnemonic, argAX, argDX>	;ED
	opcode <Unsupported, mnemonic, argDX, argAL>	;EE
	opcode <Unsupported, mnemonic, argDX, argAX>	;EF
	opcode <Unsupported, mnemonic, 0, 0>			;F0
	opcode <Unsupported, mnemonic, 0, 0>			;F1
	opcode <Unsupported, mnemonic, 0, 0>			;F2
	opcode <Unsupported, mnemonic, 0, 0>			;F3
	opcode <Unsupported, mnemonic, 0, 0>			;F4
	opcode <Implemented, mneCmc, 0, 0>				;F5
	opcode <Extension, mnemonic, Eb, 0>				;F6
	opcode <Extension, mnemonic, Ew, 0>				;F7
	opcode <Implemented, mneClc, 0, 0>				;F8
	opcode <Implemented, mneStc, 0, 0>				;F9
	opcode <Implemented, mneCli, 0, 0>				;FA
	opcode <Implemented, mneSti, 0, 0>				;FB
	opcode <Implemented, mneCld, 0, 0>				;FC
	opcode <Implemented, mneStd, 0, 0>				;FD
	opcode <Extension, mnemonic, Eb, 0>				;FE
	opcode <Extension, mnemonic, Ew, 0>				;FF

label GRP1 word
	dw mneAdd, mneOr, mneAdc, mneSbb, mneAnd, mneSub, mneXor, mneCmp

label GRP2 word
	dw mneRol, mneRor, mneRcl, mneRcr, mneShl, mneShr, mnemonic, mneSar

label GRP3a word
	dw mneTest, mnemonic, mneNot, mneNeg, mneMul, mneImul, mneDiv, mneIdiv

label GRP3b word
	dw mneTest, mnemonic, mneNot, mneNeg, mneMul, mneImul, mneDiv, mneIdiv

label GRP4 word
	dw mneInc, mneDec

label GRP5 word
	dw mneInc, mneDec, mneCall, mneCall, mneJmp, mneJmp, mnePush