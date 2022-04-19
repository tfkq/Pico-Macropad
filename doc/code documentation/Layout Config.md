# Layout Config

This file describes the format of the config files found in `/data`.

> Example of config file:
> ````
> MAIN	255	0	0
> Micro	$F240#0.	255	255	0
> Prev	$F240#1.	255	191	0
> Next	$F240#2.	255	191	0
> Lock	$F240#3.	255	127	0
> StandBy	$F240#4.	255	64	0
> ShutDn	$F240#5.	255	0	0
> -
> -
> -
> ~PROGRA
> -
> -
> ````

**Layout Name and Color**

The first line contains the Layout name (max. 6 chars.) and color as RGB (0-255)

**Buttons**

The Buttons are given in the following lines, each line for one button.'
These lines also contain the name for the button (max. 6 chars.), then the macros (max. 63 chars.), then the color as RGB (0-255)

**Formatting**

The different fields are always seperated by `TABs`, so that Spaces can still be used if wanted to.

**Special Signs**

| Sign    |                                                              |
| ------- | ------------------------------------------------------------ |
| **`-`** | empty field. this button will not perform any action and will be turned off |
| **`~`** | special functions. there will no macros performed on these buttons. Instead a function will be called.<br />Names for these fields can be given after the `~` (max. 6 char.; without  `~`) |

*Sign `~`:*

- `~PROG`: change the selected layout



