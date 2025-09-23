# EDLIN - A Historical Re-creation in C
My C99 implementation of the venerable PC/MS-DOS multi-modal, line-orientated, text editor - EDLIN.

## Synopsis
EDLIN was developed in 1980 by Tim Paterson for Seattle Computer Products' QDOS 0.1. When Paterson sold the operating system to Microsoft, EDLIN was included as a temporary solution—intended to last about six months. By virtue of its sheer utility, it persisted as the standard text editor until MS-DOS 4.01, surviving for nearly 11 years until the release of MS-DOS 5.0. During that time, despite various language localizations, it was never significantly updated or overhauled.

## Why recreate EDLIN?
When I first decided to implement my own version of EDLIN, I presumed I was taking on a simple programming exercise—a chance to cut my teeth on tokenizing and parsing techniques with what I assumed would be a straightforward DOS relic. How wrong I was.

What began as a parsing challenge quickly transformed into a journey through computing history and a masterclass in elegant software design. EDLIN, Microsoft's first text editor from 1981, revealed itself to be anything but simple. Beneath its minimalist interface lay a remarkably sophisticated tool built with astonishing efficiency, shaped by the computing constraints of its era.

## The Frenzy of the First MS-DOS
The story of "Big Blue" agreeing with a scrappy young company called Microsoft to produce an operating system for its new computer, the IBM PC—before Bill Gates even had a finished product—has taken its place in computing legend. Part of that legend is EDLIN.

EDLIN had to operate within brutal constraints: 64KB of memory, 4.77MHz processors, and no modern parsing libraries. Yet it managed to deliver a powerful mulit-modal, line-editing experience with context-aware parsing, relative addressing, and a complex command syntax that would challenge any developer to implement cleanly.

Running the 86-DOS emulator on an IBM PC with DOS 3.1 as a reference, I began using EDLIN firsthand. The programming challenges emerged quickly. I dug into EDLIN's command structure—the mix of `[parameters]COMMAND` and `COMMAND[parameters]` patterns, the elegant handling of optional arguments, and the clever use of context that made it so much more than a simple editor. This wasn't just a primitive tool; it was a beautifully designed system that enabled efficient text manipulation through a concise, expressive mini-language.

## EDLIN functionality

Delving into EDLIN reveals its powerful command syntax. This wasn't a system built on a single, rigid grammar rule. Instead, it employed several distinct syntactic patterns, each elegantly matched to the prevailing use-case and task at hand — writing and editing computer programs. The command syntax enables the editor to shift between distinct modes: command input, text insertion, and interactive search/replace.

EDLIN starts up in _command mode_ waiting for input. There are simple commands, such as End (E), Quit (Q), and Help (?). However, for the core editing commands—List (L), Page (P), Delete (D), Copy (C), and Move (M)—the logic follows a natural "select, then act" flow. You first specify what to operate on with a line number range (e.g., `10,20` operates on those lines), then issue the command: `[range]COMMAND`. This structure makes perfect sense for manipulating existing lines of text and has the added efficiency quirk of being able to omit the first line number to express starting at the current line (e.g., `,20L` lists from the current line to line 20).

This workflow expands for commands that require inputting new data—like Search (S), Replace (R), or Transfer (T). Here, the syntax expands and the structure becomes: `[range][?]COMMAND[text]`.

This hybrid approach is where EDLIN's parser reveals its true sophistication. The command still terminates the parameter list, but it can be prefixed with a range and an interactive modifier (?), and suffixed with free-form text. For example:

+ `Stext` is valid — a raw search from the current line.

+ `1,10?Stext` is also valid — an _interactive mode_ search in a specific range.

+ `Rold,new` works — replace from the current position.

+ `1,100?Rold,new` also works — _interactive mode_ replace across a range.

Thus, EDLIN commands form an expandable grammar — a structural paradigm that is consistent and applicable across commands. A grammar that soon becomes second nature, allowing text to be wrangled into the desired shape with a quick flurry of commands.

Perhaps the most intersting modal change comes when entering a line number alone. This is interpreted by EDLIN as entering the _edit mode_, a mode where the user is given a mini text editor controlled by the function key 1 - 4, the insert, escape and return keys.

Thus, EDLIN is not only mutlitmodal but also it is multiparadigm.

Finally, hybrid commands like Insert (I) and Append (A) use a prefixed pattern, `[line]I`, acting as a bridge that accepts a single parameter before transitioning the editor from command mode into _insert mode_ for inputting text line by line. Exiting this mode back to command mode by pressing `Ctrl-C` or in some versions a fullstop `.` on its own line.

But it is Append that stands as a stark testament to the brutal hardware constraints of early 1980s personal computers. While `I` switches the editor into insert mode for inputting new text from the user, the `A` command reveals a time when a large text file *could not fit into memory*. In an era where 64KB was a significant amount of RAM, editing a large file required a different strategy. EDLIN would load only the initial portion of the file. The `[#lines]A` command was not for adding new typed content, but for appending the next segment of the existing file from disk into memory—transforming `A` from a simple editing verb into a memory management tool.

In an era of severe memory constraints, this elegant design is what made EDLIN not just functional, but powerful and fast—a testament to the craftsmanship of early PC software developers such as Tim Paterson.

## Implementation notes 

For this implementation of EDLIN the _command mode_ usage is slightly different, such that, the user does not have to type the control characters mandated by the original Microsoft DOS:
+ To exit from _insert mode_ rather than typing `Ctrl-C` (in the same way as the FreeDOSS version of EDLIN) the user enters a single fullstop (aka period) on an empty line and hits `Enter` - this will switch to _command mode_.
+ Using the (R)eplace command, rather than separating the search and replace text strings with `Ctrl-Z` a simple comma between them will suffice e.g. `?Rold,new`
