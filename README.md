# 🎵 MP3 Tag Reader & Editor

A command-line based **MP3 Tag Reader and Editor** developed in **C**.
This project reads and modifies **ID3v2.3 metadata** stored inside MP3 files using C file handling, string manipulation, command-line arguments, and bitwise operations.

---

## 📌 Project Overview

MP3 files contain metadata such as:

* 🎵 Title
* 👤 Artist
* 💿 Album
* 📅 Year
* 🎼 Genre
* 💬 Comment

This project allows users to **view existing MP3 tag information** and **edit individual metadata fields** directly from the terminal.

The project works with MP3 files in binary mode and processes ID3 frame headers and frame data.

---

## ✨ Features

### 📖 View MP3 Tags

Display the metadata stored in an MP3 file.

```bash
./a.out -v <filename>
```

Example:

```bash
./a.out -v temp.mp3
```

---

### ✏️ Edit MP3 Tags

The project supports editing the following ID3 frames:

| Option | ID3 Frame | Description |
| ------ | --------- | ----------- |
| `-t`   | `TIT2`    | Title       |
| `-a`   | `TPE1`    | Artist      |
| `-A`   | `TALB`    | Album       |
| `-y`   | `TYER`    | Year        |
| `-g`   | `TCON`    | Genre       |
| `-c`   | `COMM`    | Comment     |

Example:

```bash
./a.out -e -t "Manohari"
```

```bash
./a.out -e -a "Mohana Bhogaraju, Revanth"
```

```bash
./a.out -e -A "Baahubali - The Beginning"
```

```bash
./a.out -e -y 2015
```

```bash
./a.out -e -g "Telugu Film Music"
```

```bash
./a.out -e -c "Baahubali - The Beginning"
```

---

## 📂 Fresh Editing

Before editing, an MP3 file can be copied to a temporary file so that the original file remains unchanged.

```bash
./a.out -copy temp.mp3 sample.mp3
```

Here:

```text
temp.mp3   → Destination / working file
sample.mp3 → Original source file
```

After copying, edits can be performed on `temp.mp3`.

---

## 🆘 Help

Display the available commands:

```bash
./a.out -help
```

The help menu shows the available viewing, editing, and copying operations.

---

## 🛠️ Technologies Used

* **C Programming**
* **GCC**
* **File Handling**
* **Binary File Processing**
* **Command-Line Arguments**
* **String Manipulation**
* **Dynamic Memory Allocation**
* **Pointers**
* **Bitwise Operations**
* **ID3v2.3 MP3 Metadata**

---

## 🧠 C Concepts Used

This project helped implement and understand several important C concepts:

### File Handling

Functions such as:

```c
fopen()
fread()
fwrite()
fseek()
ftell()
fclose()
```

are used to read and modify MP3 binary data.

### Command-Line Arguments

The program uses:

```c
int main(int argc, char *argv[])
```

to process commands supplied through the terminal.

### Bitwise Operations

Bitwise operations are used while processing ID3 tag sizes and frame sizes.

For example:

```c
tag_size = ((header[6] & 0x7F) << 21) |
           ((header[7] & 0x7F) << 14) |
           ((header[8] & 0x7F) << 7)  |
            (header[9] & 0x7F);
```

This converts the ID3 tag's synchsafe size representation into an integer.

### Dynamic Memory Allocation

Memory is dynamically allocated for frame data based on the frame size:

```c
frame_data = malloc(frame_size);
```

---

## 🏗️ ID3v2.3 Frame Structure

The project works with the ID3v2.3 frame format.

A frame contains:

```text
+----------------------+
| Frame ID   - 4 bytes |
+----------------------+
| Size       - 4 bytes |
+----------------------+
| Flags      - 2 bytes |
+----------------------+
| Frame Data           |
+----------------------+
```

Examples:

```text
TIT2 → Title
TPE1 → Artist
TALB → Album
TYER → Year
TCON → Genre
COMM → Comment
```

---

## 🔄 How Editing Works

The editing process follows these steps:

```text
             MP3 File
                |
                v
        Read ID3 Header
                |
                v
          Find Frame ID
                |
                v
       Read Existing Size
                |
                v
         Replace Data
                |
                v
       Create Temporary File
                |
                v
        Write Updated Frame
                |
                v
       Copy Remaining Data
                |
                v
          temp.mp3
```

The updated data is written to a temporary file and then used as the new working MP3 file.

---

## 🖥️ Example

### View

```bash
./a.out -v temp.mp3
```

Example output:

```text
========== MP3 TAG INFORMATION ==========

ID3 Tag    : Found
Version    : 3

Title      : Manohari
Artist     : Mohana Bhogaraju, Revanth
Album      : Baahubali - The Beginning
Year       : 2015
Genre      : Telugu Film Music
Comment    : Baahubali - The Beginning

==========================================
```

---

## 🚀 Build and Run

Compile the project using GCC.

```bash
gcc main.c view.c edit.c -o mp3tag
```

Run the application:

```bash
./mp3tag -help
```

> Use the actual source-file names present in the repository when compiling.

---

## 📋 Command Reference

| Command                         | Purpose                    |
| ------------------------------- | -------------------------- |
| `./a.out -help`                 | Display help               |
| `./a.out -copy <dest> <source>` | Copy MP3 for fresh editing |
| `./a.out -v <file>`             | View MP3 tags              |
| `./a.out -o <file>`             | View MP3 information       |
| `./a.out -e -t <title>`         | Edit title                 |
| `./a.out -e -a <artist>`        | Edit artist                |
| `./a.out -e -A <album>`         | Edit album                 |
| `./a.out -e -y <year>`          | Edit year                  |
| `./a.out -e -g <genre>`         | Edit genre                 |
| `./a.out -e -c <comment>`       | Edit comment               |

---

## 📚 Learning Outcomes

Through this project, I gained practical experience with:

* Reading and writing binary files
* Understanding MP3 ID3 metadata
* Working with ID3v2.3 frame structures
* Command-line argument handling
* File pointers and random file access
* Dynamic memory allocation
* Pointer manipulation
* String handling
* Bitwise operations
* Big-endian and synchsafe integer processing
* Modular C programming
* Debugging file-processing applications

---

## 🔮 Future Enhancements

Possible improvements include:

* Support for more ID3 frames
* Better handling of `COMM` frame structure
* Support for ID3v1
* Album artwork support
* Improved error handling
* Input validation
* Support for more MP3 metadata fields
* Cross-platform testing

---

## 👨‍💻 Author

**Sreenath Yellutla**

Electronics and Communication Engineering

GitHub:
https://github.com/SreenathYellutla

---

## ⭐ Project

If you find this project useful for learning C programming, file handling, and MP3 metadata processing, feel free to explore the repository and provide feedback.
