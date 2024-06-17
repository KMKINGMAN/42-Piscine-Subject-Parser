# 42 Piscine Subject Parser

The Piscine Subject Parser is a utility that parses `42 Piscine` subject PDF files to extract "Turn-in directory" and "Files to turn in" information. It then creates directories and placeholder files accordingly, facilitating the setup required for Piscine projects.

## Features:
- **PDF Parsing**: Extracts relevant information from 42 Piscine subject PDF files using C (using `Poppler` library) or Python (using `PyPDF2` library).
- **Directory and File Creation**: Automatically creates directory structures and placeholder files based on extracted information.
- **Cross-platform**: Supports both C and Python versions for flexibility in different environments.
- **Command-line Interface**: Takes the PDF file path as a command-line argument for easy integration into scripts or workflows.

## C Version:
The C version utilizes the Poppler library for PDF parsing and system calls for directory and file creation. It ensures robust handling of PDF contents and file system operations.

## Python Version:
The Python version uses the PyPDF2 library for PDF parsing and standard Python functions for directory and file creation. It provides similar functionality to the C version with Python's ease of use and cross-platform compatibility.

## Setup and Usage:
### C Version:
1. Ensure the necessary libraries (like Poppler) are installed on your system.
2. Compile the C code using a C compiler (`cc`) with appropriate flags.
3. Run the compiled executable with the path to the Piscine subject PDF file as an argument.

### Python Version:
1. Install Python on your system if not already installed.
2. Install the PyPDF2 library using `pip3 install PyPDF2`.
3. Run the Python script with the path to the Piscine subject PDF file as an argument (`python3 main.py path/to/42_piscine_subject.pdf`).

## Example Usage:
```bash
# C Version
$ ./create_dirs_files en.subject.pdf

# Python Version
$ python3 main.py en.subject.pdf
```
## install C version

```bash
$ git clone https://github.com/KMKINGMAN/42-Piscine-Subject-Parser.git ~/42-Piscine-Subject-Parser
$ cd ~/42-Piscine-Subject-Parser
$ chmod +x ./build/install-libs.sh
$ sudo sh ./build/install-libs.sh
$ chmod +x ./build/build.sh
$ sh ./build/build.sh
$ echo "alias 42parse='./42-Piscine-Subject-Parser/create_dirs_files'" >> ~/.zshrc && source ~/.zshrc
```

## install Python Version version

```bash
$ git clone https://github.com/KMKINGMAN/42-Piscine-Subject-Parser.git ~/42-Piscine-Subject-Parser
$ cd ~/42-Piscine-Subject-Parser
$ chmod +x ./build/python-req.sh
$ sh ./build/python-req.sh
echo "alias 42parse='python3 ~/42-Piscine-Subject-Parser/main.py'" >> ~/.zshrc && source ~/.zshrc
```

