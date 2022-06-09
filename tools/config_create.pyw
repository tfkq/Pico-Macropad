"""
this script provides a simple gui to create a config for the macropad

created: 15.04.2022, Arvid Randow
"""

# * MODULES
import os
import PySimpleGUI as sg
import json
from tkinter.colorchooser import askcolor

# * VARIABLES AND OBJECTS

MAX_TITLE_LENGTH = 20
MAX_SHORT_LENGTH = 6

data: dict


file_layout = 	[
					[sg.Text("Config Creator", size=(50, 1), justification='center')],
			   		[
						sg.Text("Chosen Config: "),
						sg.In("D:/GitHub/Pico-Macropad/config2.json", size=(50, 1), enable_events=True, key="-CONFIG_PATH-"),
						sg.FileBrowse("select config", key="-SELECT_CONFIG-"),
			   			sg.Button("Create folder", k="-CREATE_FOLDER-"),
						sg.Button("Create AHK-Script", k="-CREATE_AHK-"),
						sg.Button("Write to JSON", k="-WRITE_JSON-")
			   		]
				]

menu_edit_layout = 	[
						[sg.Text("Select Layers here")],
						[sg.Listbox(values=[], enable_events=True, size=(30, 20), key="-LAYER_LIST-")],
						[
							sg.In("new layer", k="-ADD_LAYER_TEXT-", size=(15,1)),
							sg.Button("add Layer", key="-ADD_LAYER-"),
							sg.Button("▲", k="-LAYER_UP-"),
							sg.Button("▼", k="-LAYER_DOWN-")
						]
					]

btn_size = (6,3)
btn_font = ("Consolas", 10)

layer_edit_layout = [
						[sg.Text("Edit Layers here")],
						[sg.Text("edit title:"), sg.In(enable_events=True, key="-LAYER_EDIT_TITLE-", size=(15,1))],
						[sg.Text("edit short:"), sg.In(enable_events=True, key="-LAYER_EDIT_SHORT-", size=(10,1))],
						[sg.Text("edit color:"), sg.In(enable_events=True, key="-LAYER_EDIT_COLOR-", size=(10,1)), sg.Button("choose color", k="-LAYER_EDIT_COLOR_BTN-")],

						[
							sg.Button("0", key="-LAYER_BTN_0-", size=btn_size, font=btn_font),
						 	sg.Button("1", key="-LAYER_BTN_1-", size=btn_size, font=btn_font),
							sg.Button("2", key="-LAYER_BTN_2-", size=btn_size, font=btn_font)
						],
						[
							sg.Button("3", key="-LAYER_BTN_3-", size=btn_size, font=btn_font),
						 	sg.Button("4", key="-LAYER_BTN_4-", size=btn_size, font=btn_font),
							sg.Button("5", key="-LAYER_BTN_5-", size=btn_size, font=btn_font)
						],
						[
							sg.Button("6", key="-LAYER_BTN_6-", size=btn_size, font=btn_font),
						 	sg.Button("7", key="-LAYER_BTN_7-", size=btn_size, font=btn_font),
							sg.Button("8", key="-LAYER_BTN_8-", size=btn_size, font=btn_font)
						],
						[
							sg.Button("9", key="-LAYER_BTN_9-", size=btn_size, font=btn_font),
						 	sg.Button("10", key="-LAYER_BTN_10-", size=btn_size, font=btn_font),
						 	sg.Button("11", key="-LAYER_BTN_11-", size=btn_size, font=btn_font)
						],

						[sg.Button("delete Layer", key="-DELETE_LAYER-")]
					]

button_edit_layout = 	[
							[sg.Text("Edit Buttons here")],
							[sg.Text("edit name:"), sg.In(enable_events=True, key="-BTN_EDIT_NAME-", size=(10,1))],
							[sg.Text("edit color:"), sg.In(enable_events=True, k="-BTN_EDIT_COLOR_TEXT-", size=(10,1)), sg.Button("choose color", key="-BTN_EDIT_COLOR-")],
							[sg.Text("edit command:"), sg.Multiline(enable_events=True, key="-BTN_EDIT_COMMAND-", size=(60,25), expand_x=True, expand_y=True, font=("Consolas", 11))],
						]

lower_half_layout = 	[
							sg.Column(menu_edit_layout), sg.VSeparator(), sg.Column(layer_edit_layout), sg.VSeparator(), sg.Column(button_edit_layout)
						]

root_layout = 	[
					file_layout,
					[
						sg.HSeparator()
					],
					lower_half_layout
				]

window = sg.Window("Config Creator - Main Page", root_layout)

selected_layer = -1
selected_btn = -1
# * FUNCTIONS

#* helper functions
def rgb_to_hex(rgb: list):
	return "#{0:02x}{1:02x}{2:02x}".format(rgb[0], rgb[1], rgb[2])

#* data update and load
def data_load(path):
	global data
	file = open(path, "r")
	data = json.loads(file.read())
	file.close()

def write_json(path):
	global data
	file = open(path, "w")
	file.truncate(0)
	file.write(json.dumps(data))
	file.close()
	print ("### JSON FILE WRITTEN ###")

def data_add_layer(title: str):

	# check for maximum length
	if(len(title) > MAX_TITLE_LENGTH):
		title = title[0:MAX_TITLE_LENGTH]

	# check if already existant
	for i in data["layers"]:
		if i["title"] == title:
			print("layer already exists")
			return 1

	# create empty layer and add it to the data
	layer = {
		"title": title,
		"short": "",
		"color": [0,0,0],
		"buttons": [
			{
				"name": "",
				"command": "",
				"color": [0,0,0]
			}
		]*12
	}
	data["layers"].append(layer)

#* gui update
def reload_layer_list():
	layers = []
	for i in data["layers"]:
		layers.append(i["title"])

	window["-LAYER_LIST-"].update(layers)

def load_layer_edit(layer_title):
	global selected_layer

	# get layer number
	for idx, val in enumerate(data["layers"]):
		if val["title"] == layer_title:
			selected_layer = idx
			break

	# update data of layer
	# print(data["layers"][selected_layer]["color"])
	window["-LAYER_EDIT_TITLE-"].update(data["layers"][selected_layer]["title"])
	window["-LAYER_EDIT_SHORT-"].update(data["layers"][selected_layer]["short"])
	window["-LAYER_EDIT_COLOR-"].update(rgb_to_hex(data["layers"][selected_layer]["color"]))
	window["-LAYER_EDIT_COLOR_BTN-"].update(button_color=rgb_to_hex(data["layers"][selected_layer]["color"]))

	# update button color
	for idx, val in enumerate(data["layers"][selected_layer]["buttons"]):
		key = "-LAYER_BTN_{0}-".format(idx)
		window[key].update(button_color=rgb_to_hex(val["color"]))
		window[key].update(data["layers"][selected_layer]["buttons"][idx]["name"])
		window[key].Widget.config(fg='Black')


def load_btn_edit(btn_number):
	window["-BTN_EDIT_NAME-"].update(data["layers"][selected_layer]["buttons"][btn_number]["name"])
	window["-BTN_EDIT_COLOR_TEXT-"].update(rgb_to_hex(data["layers"][selected_layer]["buttons"][btn_number]["color"]))
	window["-BTN_EDIT_COLOR-"].update(button_color=rgb_to_hex(data["layers"][selected_layer]["buttons"][btn_number]["color"]))
	window["-BTN_EDIT_COMMAND-"].update(data["layers"][selected_layer]["buttons"][btn_number]["command"])

# * MAIN PART

event, values = window.read()
data_load(values["-CONFIG_PATH-"])
reload_layer_list()

active = True
while active:
	event, values = window.read()

	# end program
	if event == sg.WIN_CLOSED:
		active = False
		break

	# * file management part
	if event == "-CONFIG_PATH-":
		data_load(values["-CONFIG_PATH-"])
		reload_layer_list()

	if event == "-CREATE_FOLDER-":
		write_json(values["-CONFIG_PATH-"])
		os.system("python ./json_to_folder.py " + values["-CONFIG_PATH-"] + " " + data["path_to_folder"])

	if event == "-CREATE_AHK-":
		write_json(values["-CONFIG_PATH-"])
		os.system("python ./json_to_ahk.py " + values["-CONFIG_PATH-"] + " " + data["path_to_ahk-script"])
		
	if event == "-WRITE_JSON-":
		write_json(values["-CONFIG_PATH-"])

	#* layer selection management part
	if event == "-LAYER_LIST-":
		load_layer_edit(values["-LAYER_LIST-"][0])
	
	if event == "-ADD_LAYER-":
		data_add_layer(values["-ADD_LAYER_TEXT-"])
		reload_layer_list()

	if event == "-LAYER_UP-":
		if not selected_layer <= 1:		# not the first two layers
			layer = data["layers"].pop(selected_layer)
			selected_layer -= 1
			data["layers"].insert(selected_layer, layer)
			reload_layer_list()

	if event == "-LAYER_DOWN-":
		if not (selected_layer >= len(data["layers"]) or selected_layer <= 0):		# not the last and not the first
			layer = data["layers"].pop(selected_layer)
			selected_layer += 1
			data["layers"].insert(selected_layer, layer)
			reload_layer_list()

	#* layer edit management part
	if event == "-LAYER_EDIT_TITLE-":
		title = values["-LAYER_EDIT_TITLE-"]

		# check for maximum length
		if(len(title) > MAX_TITLE_LENGTH):
			title = title[0:MAX_TITLE_LENGTH]

		# check if already existent
		err = False
		for i in data["layers"]:
			if i["title"] == title:
				print("layer already exists")
				err = True
		if not err:
			data["layers"][selected_layer]["title"] = title
			reload_layer_list()
		window["-LAYER_EDIT_TITLE-"].update(data["layers"][selected_layer]["title"])
	
	if event == "-LAYER_EDIT_SHORT-":
		short = values["-LAYER_EDIT_SHORT-"]

		# check for maximum length
		if(len(short) > MAX_SHORT_LENGTH):
			short = short[0:MAX_SHORT_LENGTH]

		# check if already existent
		err = False
		for i in data["layers"]:
			if i["short"] == short and not short == "":
				print("short already exists")
				err = True
		if not err:
			data["layers"][selected_layer]["short"] = short
			reload_layer_list()
		window["-LAYER_EDIT_SHORT-"].update(data["layers"][selected_layer]["short"])
	
	if event == "-LAYER_EDIT_COLOR_BTN-":
		color = rgb_to_hex(data["layers"][selected_layer]["color"])
		rgb, hex = askcolor(color=color)
		if not rgb == None:
			data["layers"][selected_layer]["color"] = rgb
			window["-LAYER_EDIT_COLOR-"].update(hex)
			window["-LAYER_EDIT_COLOR_BTN-"].update(button_color = hex)
	
	for i in range(12):
		key = "-LAYER_BTN_{0}-".format(i)
		if event == key:
			selected_btn = i
			load_btn_edit(i)

	if event == "-DELETE_LAYER-":
		data["layers"].pop(selected_layer)
		selected_layer = -1
		selected_btn = -1
		reload_layer_list()
	
	#* button edit management part
	if event == "-BTN_EDIT_NAME-":
		name = values["-BTN_EDIT_NAME-"]

		# check for maximum length
		if(len(name) > MAX_SHORT_LENGTH):
			name = name[0:MAX_SHORT_LENGTH]

		# check if already existent
		err = False
		for i in data["layers"][selected_layer]["buttons"]:
			if i["name"] == name and not name == "":
				print("name already exists")
				err = True
		if not err:
			data["layers"][selected_layer]["buttons"][selected_btn]["name"] = name
			reload_layer_list()
		window["-BTN_EDIT_NAME-"].update(data["layers"][selected_layer]["buttons"][selected_btn]["name"])

	if event == "-BTN_EDIT_COLOR-":
		color = rgb_to_hex(data["layers"][selected_layer]["buttons"][selected_btn]["color"])
		rgb, hex = askcolor(color=color)
		if not rgb == None:
			data["layers"][selected_layer]["buttons"][selected_btn]["color"] = rgb
			window["-BTN_EDIT_COLOR_TEXT-"].update(hex)
			window["-BTN_EDIT_COLOR-"].update(button_color = hex)
			load_layer_edit(data["layers"][selected_layer]["title"])

	if event == "-BTN_EDIT_COMMAND-":
		data["layers"][selected_layer]["buttons"][selected_btn]["command"] = values["-BTN_EDIT_COMMAND-"]
