
#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

; created automatically on 2021-12-18T18:03:59.160819

input := "149#420"


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

app := % Variable1
btn := % Variable2
;* do certain action depending on numbers


if (app == 0){			; APP MAIN

	if (btn == 0){			; BTN MIC
		;-- place your script here (and remove me) --
SoundSet, +1, MASTER, mute, 5
SoundSet, +1, MASTER, mute, 6



	}

	if (btn == 1){			; BTN Lock
		;-- place your script here (and remove me) --
DllCall("user32.dll\LockWorkStation")





	}

	if (btn == 2){			; BTN StBy
		;standby
Run, psshutdown -d -t 0



	}

	if (btn == 3){			; BTN Off
		;shutdown
Run, Shutdown.exe -s -t 00


	}

	if (btn == 4){			; BTN Min
		;minimize the current window
WinMinimize, A

	}

	if (btn == 5){			; BTN Max
		;toggle between restored and maximize

WinGet, max, MinMax, A
if(max == 1){
	WinRestore, A
}
else{
	WinMaximize, A
}


	}

	if (btn == 6){			; BTN Prev
		; plays previous song
Send {Media_Prev}
	}

	if (btn == 7){			; BTN Next
		;plays next song
Send {Media_Next}


	}

	if (btn == 12){			; BTN Win1
		;-- place your script here (and remove me) --
Send, #1

	}

	if (btn == 13){			; BTN Win2
		;-- place your script here (and remove me) --
Send, #2
	}

	if (btn == 14){			; BTN Win3
		;-- place your script here (and remove me) --
Send, #3

	}

	if (btn == 15){			; BTN Win4
		;-- place your script here (and remove me) --
Send, #4
	}

}

if (app == 1){			; APP QuickStart

	if (btn == 0){			; BTN AbiV
		; open the abitur vault
Run, "D:\Documents\Programme\Pico-Macropad-AHK\Abitur - Vault.URL"



	}

	if (btn == 1){			; BTN HA_V
		; open hausaufgaben vault
Run, "D:\Documents\Programme\Pico-Macropad-AHK\Hausaufgaben - Vault.URL"

	}

	if (btn == 2){			; BTN NB_V
		; open the notebook vault
Run, "D:\Documents\Programme\Pico-Macropad-AHK\Notebook - Vault.URL"

	}

	if (btn == 3){			; BTN Obdn
		; run obsidian
Run, C:\Users\arvid\AppData\Local\Obsidian\Obsidian.exe


	}

	if (btn == 4){			; BTN Typo
		;will start typora
Run, "C:\Program Files\Typora\Typora.exe"

	}

	if (btn == 5){			; BTN Notn
		;notion

Run, "C:\Users\arvid\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Notion.lnk"


	}

	if (btn == 6){			; BTN Word
		;run ms word
Run, "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Word.lnk"


	}

	if (btn == 7){			; BTN Excl
		;run ms excel
Run, "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Excel.lnk"



	}

	if (btn == 12){			; BTN Sblm
		;run sublime text
Run, "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Sublime Text.lnk"

	}

	if (btn == 13){			; BTN VSCo
		; run VS-Code

Run, "C:\Users\arvid\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Visual Studio Code\Visual Studio Code.lnk"
	}

	if (btn == 14){			; BTN Ardu
		;run Arduino IDE
Run, "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Arduino.lnk"
	}

	if (btn == 15){			; BTN ViSt
		; run Visual Studio 2019
Run, "C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2019.lnk"
	}

}

if (app == 2){			; APP Firefox

	if (btn == 0){			; BTN NTab
		;New Tab
Send, ^t




	}

	if (btn == 1){			; BTN NWin
		;open new window
Send, ^n



	}

	if (btn == 2){			; BTN CTab
		;close current tab
Send, ^w


	}

	if (btn == 3){			; BTN CWin
		;close current window
Send, ^+w


	}

	if (btn == 4){			; BTN Srch
		;focus on the adress bar
Send, ^l


	}

	if (btn == 5){			; BTN Wiki
		;start a wikipedia search
Send, ^l
Send, @wikipedia{Space}




	}

	if (btn == 6){			; BTN Leo
		;opens leo.org in current tab
Send, ^l
Sleep, 500
Send, leo.org
Send, {Enter}



	}

	if (btn == 7){			; BTN SrPg
		;search in page
Send, ^f




	}

	if (btn == 8){			; BTN Mute
		;mute / unmute the tab
Send, ^m


	}

	if (btn == 9){			; BTN Z0
		;reset zoom
Send, ^0


	}

	if (btn == 10){			; BTN Z-
		;zoom out
Send, ^-


	}

	if (btn == 11){			; BTN Z+
		;zoom in
Send, ^{+}






	}

	if (btn == 12){			; BTN Home
		;sends you back to your homepage
Send, !{Home}


	}

	if (btn == 13){			; BTN Refr
		;reload website
Send, {F5}

	}

	if (btn == 14){			; BTN <T<
		;previous tab
Send, ^+{Tab}





	}

	if (btn == 15){			; BTN >T>
		;goes to next tab
Send, ^{Tab}



	}

}

if (app == 3){			; APP VS-Code

}

if (app == 4){			; APP Obsidian

	if (btn == 0){			; BTN Expl
		;Dateiexplorer zeigen
Send, ^1








	}

	if (btn == 1){			; BTN OFil
		;open file
Send, ^o
	}

	if (btn == 2){			; BTN Cmd
		;open command palette
Send, ^p


	}

	if (btn == 3){			; BTN Tags
		;Tag-Bereich zeigen
Send, ^2




	}

	if (btn == 4){			; BTN Srch
		;search in all files
Send, ^+F



	}

	if (btn == 5){			; BTN Mode
		;toggle mode
Send, ^e


	}

	if (btn == 7){			; BTN Outl
		;Gliederungsbereich zeigen
Send, ^3




	}

	if (btn == 8){			; BTN Grph
		;show graph view
Send, ^g




	}

	if (btn == 9){			; BTN Corr
		;correct on 
Send, ^.



	}

	if (btn == 10){			; BTN Corr
		;correction off
Send, ^+.


	}

	if (btn == 11){			; BTN Tabl
		;show table tools
Send, ^+d

	}

	if (btn == 12){			; BTN PDF
		;export to pdf
Send, ^+p



	}

	if (btn == 13){			; BTN LPan
		;show/hide left panel
Send, ^b






	}

	if (btn == 14){			; BTN RPan
		;show/hide right panel
Send, ^+b







	}

	if (btn == 15){			; BTN DayN
		;open daily note
Send, ^!d


	}

}

if (app == 5){			; APP Fusion 360

}

if (app == 6){			; APP Aseprite

}

