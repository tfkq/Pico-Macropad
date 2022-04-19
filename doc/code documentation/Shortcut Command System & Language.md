# Shortcut Command System & Language

I created my own Command Language which would be easy to parse and doesn't require line breaks. This system supports all modifier on Windows (and maybe UNIX, but I haven't tested) and special keys to be pressed and released in whatever order.

## Sending letters / text

To send plain text you just use ... plain text! For example if you want a macro typing "Hello World!" for you, you would just type it like that.

However, there are some problems when your computer is set to a keyboard-layout other than the standard English (QWERTY) one. Especially special letters (@,#,+,*,...) are problematic, and I couldn't find a way to fix this yet. 

## Commands

Generally speaking, all commands start with `$` and only contain two letters, with some exceptions. There are also two type of commands: First the modifier keys, which are toggled when using its command. The first use presses the key down, the second one releases its, and so on. Second, other special keys, like Enter/Return, Insert, Delete, etc. These are just pressed once and than you're done. Following is a list with all commands.

**One important thing: the command system is Case-Sensitive.**

### Toggled commands

1. *these are always the one on the left side of the keyboard*
2. *the keyword in the bracket is the input to the [Keyboard library](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/) (`Keyboard.print(<Keyword>);`)*
3. *as mentioned, these keys are toggled on and off, so don't forget to toggle them off at the end*

| Command | Explanation                         |
| ------- | ----------------------------------- |
| $W      | Windows / Meta key (`KEY_LEFT_GUI`) |
| $C      | Control Key (`KEY_LEFT_CTRL`)       |
| $S      | Shift Key (`KEY_LEFT_SHIFT`)        |
| $A      | Alt Key (`KEY_LEFT_ALT`)            |

### Special keys

- *these are just pressed once and will be quickly released*

| Command                                      | Explanation                                                  |
| -------------------------------------------- | ------------------------------------------------------------ |
| $E                                           | Enter / Return                                               |
| $T                                           | Tab                                                          |
| $*                                           | Escape                                                       |
| $1                                           | Home / Pos1                                                  |
| $0                                           | End                                                          |
| $I                                           | Insert                                                       |
| $D                                           | Delete                                                       |
| $$      | $ (in case you need a dollar sign) |                                                              |
| $Fxx                                         | All the F-keys your computer supports. "xx" can be replaced with a number from 1 to 24 |
| $dxxxx$                                      | This one starts a delay. The time is given in milliseconds and is limited to four digits. Please note that this stops the whole program and it waits until the time is past. You won't be able to do other things with it in the meantime. |

### Examples

- `$We$W` opens the explorer on Windows
- `$Cko$C` opens a folder in VS Code
- `$Wr$W$d250$cmd$E` starts the command palette (the delay gives Windows enough time to start Run)
- `$We$W$d500$vv$E$d250$g$E$d250$a$E$d259$r$E`: This beast starts the explorer, navigates to my folder of this project and opens the ReadMe