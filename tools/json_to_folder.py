#!/usr/bin/python
"""
this script creates the data folder for the pico out of a config json file

created: 10.04.2022, Arvid Randow
"""

import os
import sys
import rich
import json
from rich.console import Console
from rich.markdown import Markdown

console = Console()


console.print(Markdown("## checking parameters"))
console.print('Number of arguments:', len(sys.argv), 'arguments.')
console.print('Argument List:', str(sys.argv))


if len(sys.argv) != 3:
	console.print("[red][X] 0. incorrect number of parameters")
	console.print(
		"[red]        give to paths: 1. the config file; 2. the folder to write the data to as parameters")
	console.print("[red]        ... EXITING")
	exit()
else:
	console.print("[green][✔] 0. parameters ok, going on")


# * LOOK IF FILE AND FOLDER EXIST
console.print(Markdown("## open file and check folder"))

# json file
try:
	file = open(sys.argv[1], 'r')
except FileNotFoundError:
	console.print("[red][X] 1. json file not found ... EXITING")
	exit()

data = json.loads(file.read())

file.close()

console.print("[green][✔] 1. json file found and read")


# folder
folder_path = sys.argv[2]
if (os.path.isdir(folder_path)):
	console.print("[green][✔] 2. folder found")

	# check if empty
	if(len(os.listdir(folder_path)) == 0):
		console.print("[green][✔] \t2.1. folder is empty")
	else:
		console.print(
			"[yellow][ ] \t2.1. folder is not empty, attempting to clearing it")
		for i in os.listdir(folder_path):
			os.remove(folder_path + "/" + i)
			console.print("\t\t\t deleted " + i)
		console.print("[green][✔] \t2.1. folder is now empty")


else:
	console.print(
		"[red][X] 2. folder not found. Please create an empty folder beforehand. ... EXITING")
	exit()


# * CREATE FILES
console.print(Markdown("## create data files"))

counter = 0
for layer in data["layers"]:
	console.print("[bold]layer " + str(counter))

	text: str = ""

	text += layer["title"]
	for color in layer["color"]:
		text += "\t" + str(color)

	text += "\n"

	btn_counter = 0
	for button in layer["buttons"]:

		ahk_hotkey = "$F24{0}#{1}.".format(str(counter), str(btn_counter))

		text += button["name"] + "\t" + ahk_hotkey
		for color in button["color"]:
			text += "\t" + str(color)

		text += "\n"
		btn_counter += 1

	for i in text.split("\n"):
		console.print("\t[italic white]" + i)

	console.print("\t[yellow][ ] attempting to write file " + folder_path + "/" + str(counter))
	try:
		file = open(folder_path + "/" + str(counter), 'w')
		file.write(text)
		file.close()
	except Exception as e:
		console.print("\t[red][X] writing failed")
		print(e)
		exit()
	console.print("\t[green][✔] file successfully written")

	counter += 1


#* create SEL file

console.print(Markdown("## create standard sel file"))
text = ""

for i in data["sel"]:

	text += str(i) + "\n"

for i in text.split("\n"):
	console.print("\t[italic white]" + i)

console.print("\t[yellow][ ] attempting to write file " + folder_path + "/sel")
try:
	file = open(folder_path + "/sel", 'w')
	file.write(text)
	file.close()
except Exception as e:
	console.print("\t[red][X] writing failed")
	print(e)
	exit()
console.print("\t[green][✔] file successfully written")


console.print(Markdown("# DONE."))
