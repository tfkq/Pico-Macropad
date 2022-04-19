#!/usr/bin/python
"""
this script creates the ahk-script for the pc out of a config json file

created: 10.04.2022, Arvid Randow
"""

# * modules
import os
import sys
import rich
import json
from rich.console import Console
from rich.markdown import Markdown

# * global variables and presets

ahk_init = """#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.
#Singleinstance force
SetFormat, float, 0
"""

ahk_processing = """F24::
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
"""

# 0: layer number
# 1: layer name
# 2: button code
ahk_if_layer = """if (layer == {0}){{				; LAYER {0} - "{1}"
	{2}
}}
"""

# 0: button number
# 1: button name
# 2: button code
ahk_if_button = """if (btn == {0}){{					; button  {0} - "{1}"
	{2}
}}
"""


# * MAIN SCRIPT

console = Console()

console.print(Markdown("## checking parameters"))
console.print('Number of arguments:', len(sys.argv), 'arguments.')
console.print('Argument List:', str(sys.argv))


if len(sys.argv) != 3:
    console.print("[red][X] 0. incorrect number of parameters")
    console.print(
        "[red]        give to paths: 1. the config file; 2. the file to write the ahk-script to as parameters")
    console.print("[red]        ... EXITING")
    exit()
else:
    console.print("[green][✔] 0. parameters ok, going on")


# * get data

console.print(Markdown("## loading data"))

file = open(sys.argv[1], 'r')
data = json.loads(file.read())
file.close()

console.print("[green][✔] 1. json file found and read")

# * prepare text

console.print(Markdown("## prepare script"))

text = ahk_init + "\n\n\n\n" + \
    data["script_extra"] + "\n\n\n\n" + ahk_processing

layer_c = 0
for layer in data["layers"]:

    button_text = ""
    button_c = 0
    for button in layer["buttons"]:

        name = button["name"]
        command = button["command"]

        button_text += ahk_if_button.format(str(button_c), name, command)

        button_c += 1

    text += ahk_if_layer.format(str(layer_c), layer["title"], button_text)

    layer_c += 1


for i in text.split("\n"):
    console.print("\t[italic white]" + i)

console.print("[green][✔] 2. script generated")


# * write it

console.print(Markdown("## write the script"))

file = open(sys.argv[2], 'w')

file.write(text)

console.print("[green][✔] 3. script written")


console.print(Markdown("# DONE."))
