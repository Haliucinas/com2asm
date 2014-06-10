; buffers
param db 64 dup (?)
fileHandle dw ?
fileBuffer db 64 dup (?)
hexDump db 7 dup (?)
disp db 2 dup (?)
data db 4 dup (?)

; messages
unsupportedMsg db 'Unsupported command.$'
wordPtr db 'word ptr $'
bytePtr db 'byte ptr $'
farPtr db 'far $'

; data
tmp opcode <>
currentByte db 0
dumpLenght db 0
modByte db 0
regByte db 0
rmByte db 0
countIP dw 00FFh ; intensionally for correct address output
dispSize db 0
dataSize db 0

; flags
amUsed db 0
nl db 0

; lists
w0Al db "al$"
w0Cl db "cl$"
w0Dl db "dl$"
w0Bl db "bl$"
w0Ah db "ah$"
w0Ch db "ch$"
w0Dh db "dh$"
w0Bh db "bh$"

label w0List word
	dw w0Al, w0Cl, w0Dl, w0Bl, w0Ah, w0Ch, w0Dh, w0Bh

w1Ax db "ax$"
w1Cx db "cx$"
w1Dx db "dx$"
w1Bx db "bx$"
w1Sp db "sp$"
w1Bp db "bp$"
w1Si db "si$"
w1Di db "di$"

label w1List word
	dw w1Ax, w1Cx, w1Dx, w1Bx, w1Sp, w1Bp, w1Si, w1Di

sEs db "es$"
sCs db "cs$"
sSs db "ss$"
sDs db "ds$"

label sList word
	dw sEs, sCs, sSs, sDs

rmBxsi db "bx+si$"
rmBxdi db "bx+di$"
rmBpsi db "bp+si$"
rmBpdi db "bp+di$"

label rmList word
	dw rmBxsi, rmBxdi, rmBpsi, rmBpdi, w1Si, w1Di, w1Bp, w1Bx