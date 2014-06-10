%title 'com2asm project'
model small
assume ss:stekas, ds:duomenys, cs:kodas
;--------------------------------------
stekas segment para stack 'stack'
	db 100h dup (0)
stekas ends
;--------------------------------------
duomenys segment para public 'data'
	include includes\opmap.inc
	include includes\data.inc
duomenys ends
;--------------------------------------
kodas segment para public 'code'
locals
include includes\macros.inc
include includes\tools.inc
;--------------------------------------
start:
	mov ax, seg duomenys
	mov ds, ax

	call getParam
	call openFile

@@read:
	call printCommand
	jmp @@read
kodas ends
end start