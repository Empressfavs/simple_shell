This README provides an overview of the "Simple Shell" project, including its purpose, functionalities, and implementation details.

Table of Contents:

Overview: #overview
Functionalities: #functionalities
Implementation Details: #implementation-details
Build Instructions: #build-instructions
Testing: #testing
Contributing: #contributing
License: #license
Overview
The "Simple Shell" project aims to create a basic command-line interpreter similar to the standard Unix shell. This project serves as a learning exercise to understand the fundamentals of shell programming and system calls.

Functionalities
The implemented functionalities of the simple shell include:

Prompting the user for commands
Parsing and interpreting commands
Executing built-in commands
Creating child processes for external commands
Handling command arguments
Supporting basic I/O redirection (e.g., >, <)
Implementing pipes for command chaining (e.g., ls | grep file)
Handling background processes (e.g., command &)
Reporting errors and displaying appropriate messages
Implementation Details
The simple shell is implemented in C language and utilizes various system calls to interact with the operating system. It employs a command-line parser to break down the user input into recognizable tokens and a process management system to create and control child processes. The shell also utilizes memory management techniques to allocate and free resources efficiently.

Key design choices:

Modular design with separate functions for different functionalities
Emphasis on code clarity and maintainability
Efficient memory management to avoid memory leaks
Extensive error handling with informative messages
Build Instructions
To build the simple shell project, you will need the following:

C compiler
Makefile
Build steps:

Open a terminal in the project directory.
Enter the following command:
make
This command will compile the source code and generate the executable file named simple_shell.

Testing
To test the functionality of the simple shell, you can run it in the terminal and execute various commands. You can also write test scripts to verify specific functionalities.

Here are some examples of commands you can test:

Built-in commands:
exit
pwd
cd
echo
External commands:
ls
cat
grep
wc
Command chaining with pipes:
ls | grep file
ps | grep process_name
Background processes:
make clean &
sleep 10 &
This is a simple shell project done by Avwopiabro Favour and Eweje Kabiru
