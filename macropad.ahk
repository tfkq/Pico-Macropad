#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


global timing

; ### ### global variables
T_LONG_PRESS = 250
T_DOUBLE_PRESS = 300


; ### ### ROTARY ENCODER 1 - SOUND
F22::				; Play / Pause
Send {Media_Play_Pause}
return

F23::				; Volume DOWN
Send {Volume_Down}
return

F24::				; Volume UP
Send {Volume_Up}
return