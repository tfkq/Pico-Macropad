#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
#Singleinstance force
SetFormat, float, 0




input := "149#420"
output := "50"

; ### ### ROTARY ENCODER 1 - SOUND
F20::				; Play / Pause
	Send {Media_Play_Pause}
return

F21::				; Volume DOWN
	Send {Volume_Down}

return

F22::				; Volume UP
	Send {Volume_Up}
return