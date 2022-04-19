#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
#Singleinstance force
SetFormat, float, 0




; ### ### Context menu on Druck/Print/PrntScrn
PrintScreen::+F10

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



F24::
; get input
Input, input, , .

; search for numbers
Pos := 1
While Pos := RegExMatch(input, "(\d+)", Match, Pos + StrLen(Match)) {
	Variable%A_Index% := Match
}
Result =
(LTrim
	Variable 1 = %Variable1%
	Variable 2 = %Variable2%
)

layer := % Variable1
btn := % Variable2
;* do certain action depending on numbers
if (layer == 0){				; LAYER 0 - "MAIN"
	if (btn == 0){					; button  0 - "Micro"
	;toggle microphone mute
SoundSet, +1, MASTER, mute, 8
SoundSet, +1, MASTER, mute, 9
}
if (btn == 1){					; button  1 - "Prev"
	; spiel vorheriges lied
Send {Media_Prev}
}
if (btn == 2){					; button  2 - "Next"
	;spiele n‰chstes Lied
Send {Media_Next}
}
if (btn == 3){					; button  3 - "Lock"
	; sperrt den PC
DllCall("user32.dll\LockWorkStation")
}
if (btn == 4){					; button  4 - "Suspnd"
	; Ruhezustand mit Best‰tigung
;TODO change to Ruhezustand
MsgBox, 4,, Do you really want to suspend?
IfMsgBox Yes
    Run, rundll32.exe powrprof.dll,SetSuspendState
; nicht sicher ob dass so passt. die zeit wirds zeigen
}
if (btn == 5){					; button  5 - "Off"
	;shutdown
MsgBox, 4,, Do you really want to shutdown?
IfMsgBox Yes
    Run, Shutdown.exe -s -t 00
}
if (btn == 6){					; button  6 - ""
	
}
if (btn == 7){					; button  7 - "Explor"
	; starte windows explorer
Send #e
}
if (btn == 8){					; button  8 - "Firefx"
	; starte firefox
Run, firefox.exe
}
if (btn == 9){					; button  9 - "[PROG]"
	;reprogram macropad, isn't supposed to do ANYTHING in ahk-script
}
if (btn == 10){					; button  10 - "VsCode"
	; starte VS Code
Run, Code.exe, C:\Users\arvid\AppData\Local\Programs\Microsoft VS Code
}
if (btn == 11){					; button  11 - "Obsdn"
	; starte Obsidian
Send !{Space}
Sleep, 300
Send Vault
}

}
if (layer == 1){				; LAYER 1 - "Firefox"
	if (btn == 0){					; button  0 - "] Hist"
	;zeige Chronik sidebar
;ctrl + h
Send ^h
}
if (btn == 1){					; button  1 - "N Tab"
	;neuer tab
;ctrl + t
Send, ^t
}
if (btn == 2){					; button  2 - "N Win"
	;neues fenster
;ctrl + n
Send, ^n
}
if (btn == 3){					; button  3 - "] Fav "
	; zeige lesezeichen sidebar
;ctrl + b
Send, ^b
}
if (btn == 4){					; button  4 - "<T<"
	;vorheriger tab
;ctrl + shift + tab
Send, ^+{TAB}
}
if (btn == 5){					; button  5 - ">T>"
	; n√§chster tab
;ctrl + tab
Send, ^{TAB}
}
if (btn == 6){					; button  6 - "] dev "
	;untersuchen
;F12
Send {F12}
}
if (btn == 7){					; button  7 - ""
	
}
if (btn == 8){					; button  8 - "mute"
	;tab stummschalten
;ctrl + m
Send, ^m
}
if (btn == 9){					; button  9 - "Downl."
	;zeige downloads
;ctrl + j
Send, ^j
}
if (btn == 10){					; button  10 - ""
	
}
if (btn == 11){					; button  11 - ""
	
}

}
if (layer == 2){				; LAYER 2 - "VS Code"
	if (btn == 0){					; button  0 - "] Up  "
	;side bar go up
Send, ^+!.
}
if (btn == 1){					; button  1 - "<- [#]"
	;go to editor group ont the left
;ctrl + k, ctrl + LEFT ARROW
Send, ^k
Send, ^{Left}
}
if (btn == 2){					; button  2 - "[#] ->"
	;go to editor group on the right
;ctrl + k, ctrl + RIGHT ARROW
Send, ^k
Send, ^{Right}
}
if (btn == 3){					; button  3 - "] <-> "
	;side bar toggle
;ctrl + b
Send, ^b
}
if (btn == 4){					; button  4 - "<- #"
	;prev file
Send, ^+{Home}
}
if (btn == 5){					; button  5 - "# ->"
	;next file
Send, ^+{End}
}
if (btn == 6){					; button  6 - "] Down"
	;side bar down
Send, ^+!,
}
if (btn == 7){					; button  7 - ""
	
}
if (btn == 8){					; button  8 - "Comand"
	;command thing
;ctrl + shift + p
Send, ^+p
}
if (btn == 9){					; button  9 - ""
	
}
if (btn == 10){					; button  10 - ",--,"
	;toggle panel
;ctrl + alt + b
Send, ^!b
}
if (btn == 11){					; button  11 - ""
	
}

}
if (layer == 3){				; LAYER 3 - "Obsidian"
	if (btn == 0){					; button  0 - "] <->"
	;toggle left panel
; ctrl + b (?)
Send, ^b
}
if (btn == 1){					; button  1 - ""
	
}
if (btn == 2){					; button  2 - "<-> ["
	;toggle right panel
;ctrl + shift + b (?)
Send ^+b
}
if (btn == 3){					; button  3 - "Search"
	;search in text
Send, ^+f
}
if (btn == 4){					; button  4 - ""
	
}
if (btn == 5){					; button  5 - "Table"
	; table tools
Send, ^+d
}
if (btn == 6){					; button  6 - ""
	
}
if (btn == 7){					; button  7 - "Corect"
	; correction toggle
Send, ^.
}
if (btn == 8){					; button  8 - ""
	
}
if (btn == 9){					; button  9 - ""
	
}
if (btn == 10){					; button  10 - "PDF"
	; export as PDF
;ctrl + shift + p
Send, ^+p
}
if (btn == 11){					; button  11 - ""
	
}

}
if (layer == 4){				; LAYER 4 - "Unity"
	if (btn == 0){					; button  0 - ""
	
}
if (btn == 1){					; button  1 - ""
	
}
if (btn == 2){					; button  2 - ""
	
}
if (btn == 3){					; button  3 - ""
	
}
if (btn == 4){					; button  4 - ""
	
}
if (btn == 5){					; button  5 - ""
	
}
if (btn == 6){					; button  6 - ""
	
}
if (btn == 7){					; button  7 - ""
	
}
if (btn == 8){					; button  8 - ""
	
}
if (btn == 9){					; button  9 - ""
	
}
if (btn == 10){					; button  10 - ""
	
}
if (btn == 11){					; button  11 - ""
	
}

}
if (layer == 5){				; LAYER 5 - "Fusion 360"
	if (btn == 0){					; button  0 - ""
	
}
if (btn == 1){					; button  1 - ""
	
}
if (btn == 2){					; button  2 - ""
	
}
if (btn == 3){					; button  3 - ""
	
}
if (btn == 4){					; button  4 - ""
	
}
if (btn == 5){					; button  5 - ""
	
}
if (btn == 6){					; button  6 - ""
	
}
if (btn == 7){					; button  7 - ""
	
}
if (btn == 8){					; button  8 - ""
	
}
if (btn == 9){					; button  9 - ""
	
}
if (btn == 10){					; button  10 - ""
	
}
if (btn == 11){					; button  11 - ""
	
}

}
if (layer == 6){				; LAYER 6 - "Aseprite"
	if (btn == 0){					; button  0 - ""
	
}
if (btn == 1){					; button  1 - ""
	
}
if (btn == 2){					; button  2 - ""
	
}
if (btn == 3){					; button  3 - ""
	
}
if (btn == 4){					; button  4 - ""
	
}
if (btn == 5){					; button  5 - ""
	
}
if (btn == 6){					; button  6 - ""
	
}
if (btn == 7){					; button  7 - ""
	
}
if (btn == 8){					; button  8 - ""
	
}
if (btn == 9){					; button  9 - ""
	
}
if (btn == 10){					; button  10 - ""
	
}
if (btn == 11){					; button  11 - ""
	
}

}
