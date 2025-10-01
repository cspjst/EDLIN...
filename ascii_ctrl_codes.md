# ASCII Control Characters

| Char    | Decimal | Hex | Name & Historical/Common Usage |
| :-------| :------ | :-- | :------------------------------ |
| ctrl-@  | 0       | 00  | **NUL** (Null) - Used for padding, often signifies end of a string in C. |
| ctrl-A  | 1       | 01  | **SOH** (Start of Header) - Start of a header in a data transmission. |
| ctrl-B  | 2       | 02  | **STX** (Start of Text) - Start of the text in a transmission. |
| ctrl-C  | 3       | 03  | **ETX** (End of Text) - End of the text. **Commonly used as an interrupt signal.** |
| ctrl-D  | 4       | 04  | **EOT** (End of Transmission) - End of a transmission. **On Unix, sends EOF.** |
| ctrl-E  | 5       | 05  | **ENQ** (Enquiry) - A request for a response from the other end. |
| ctrl-F  | 6       | 06  | **ACK** (Acknowledge) - A positive acknowledgment of a message. |
| ctrl-G  | 7       | 07  | **BEL** (Bell) - **Causes an audible beep or visual flash.** |
| ctrl-H  | 8       | 08  | **BS** (Backspace) - Moves the cursor back one space. |
| ctrl-I  | 9       | 09  | **TAB** (Horizontal Tab) - Moves the cursor to the next tab stop. |
| ctrl-J  | 10      | 0A  | **LF** (Line Feed) - Moves the cursor to the next line. **In Unix, this is a newline.** |
| ctrl-K  | 11      | 0B  | **VT** (Vertical Tab) - Moves the cursor down to the next vertical tab stop. |
| ctrl-L  | 12      | 0C  | **FF** (Form Feed) - Advances to the next page. **Often clears the terminal screen.** |
| ctrl-M  | 13      | 0D  | **CR** (Carriage Return) - Moves the cursor to the start of the line.|
| ctrl-N  | 14      | 0E  | **SO** (Shift Out) - Switch to an alternative character set. |
| ctrl-O  | 15      | 0F  | **SI** (Shift In) - Switch back to the standard character set. |
| ctrl-P  | 16      | 10  | **DLE** (Data Link Escape) - Alters the meaning of the following characters. |
| ctrl-Q  | 17      | 11  | **DC1** (Device Control 1) - Often used as **XON** to resume transmission. |
| ctrl-R  | 18      | 12  | **DC2** (Device Control 2) |
| ctrl-S  | 19      | 13  | **DC3** (Device Control 3) - Often used as **XOFF** to pause transmission. |
| ctrl-T  | 20      | 14  | **DC4** (Device Control 4) |
| ctrl-U  | 21      | 15  | **NAK** (Negative Acknowledge) - A negative response to a message. |
| ctrl-V  | 22      | 16  | **SYN** (Synchronize) - Used for synchronization in data transmission. |
| ctrl-W  | 23      | 17  | **ETB** (End of Transmission Block) - End of a block of data. |
| ctrl-X  | 24      | 18  | **CAN** (Cancel) - Indicates that the previous data should be ignored. |
| ctrl-Y  | 25      | 19  | **EM** (End of Medium) - Signifies the end of the storage medium. |
| ctrl-Z  | 26      | 1A  | **SUB** (Substitute) - **Historically used as End-of-File in DOS/CPM (e.g., EDLIN).** |
| ctrl-[  | 27      | 1B  | **ESC** (Escape) - **Starts an escape sequence, e.g., for terminal control.** |
| ctrl-\  | 28      | 1C  | **FS** (File Separator) - Used as a field delimiter in data. |
| ctrl-]  | 29      | 1D  | **GS** (Group Separator) |
| ctrl-^  | 30      | 1E  | **RS** (Record Separator) |
| ctrl-_  | 31      | 1F  | **US** (Unit Separator) |

## Common Modern Uses

*   **Ctrl+C**: **Interrupt/Kill** a running process.
*   **Ctrl+D**: **End-of-File (EOF)** signal, logs you out of a shell.
*   **Ctrl+G**: **Bell** (makes a sound).
*   **Ctrl+H**: **Backspace**.
*   **Ctrl+I**: **Tab**.
*   **Ctrl+J**: **Newline** (hitting 'Enter' in a terminal often sends this).
*   **Ctrl+L**: **Clear** the terminal screen.
*   **Ctrl+Z**: **Suspend** a process (or EOF in Windows).
*   **Ctrl+[**: **Escape** key, used in Vim and terminal control sequences.

## Historical Context

### SUB (Ctrl-Z) - The DOS/CPM End-of-File Marker
In CP/M and early DOS, the file system tracked file sizes only in blocks, not bytes. To mark where the *actual* text ended within the last block, the **SUB** character (0x1A) was placed right after the last real character. Text editors and commands (like `TYPE`) would stop reading the file when they encountered this character. This legacy is why Ctrl-Z still works as an EOF marker in the Windows Command Prompt today.

### ETX (Ctrl-C) vs SUB (Ctrl-Z)
While both are "end" markers in protocol terms, they took different practical roles:
- **ETX (Ctrl-C)**: Became the powerful "break everything now" interrupt signal in interactive systems
- **SUB (Ctrl-Z)**: Served as the pragmatic end-of-text marker for files in the DOS/CPM world

This historical division of labor explains why we have two different "end" controls that behave differently across operating systems.
