# Simple Shell

This project is an implementation of a simple Unix shell in C. The shell serves as the interface for users to interact with the operating system by entering commands. It reads and executes commands from either a file or the terminal, providing a way for users to communicate with the operating system.

## Learning Objectives

- Understand the design and implementation of the original Unix operating system.
- Recognize key figures involved in the development of Unix, including creators of the first Unix shell and the B programming language.
- Comprehend the working principles of a shell and differentiate between a function and a system call.
- Manipulate the environment of the current process and create new processes.
- Utilize system calls, such as `fork`, `execve`, and `wait`, to manage processes.
- Understand the concept of a process ID (PID) and parent process ID (PPID).
- Implement a basic shell that can execute commands and manage environment variables.

## Requirements

### General

- Allowed editors: vi, vim, emacs
- Compiled on Ubuntu 20.04 LTS using gcc with options -Wall -Werror -Wextra -pedantic -std=gnu89
- Code follows the Betty style and passes checks with betty-style.pl and betty-doc.pl
- No memory leaks in the shell
- No more than 5 functions per file
- All header files include guards
- Use system calls only when necessary

### GitHub

- One project repository per group, with collaborators added
- Follow the specified structure for the project repository

### Output

- Shell produces the exact same output and error output as `/bin/sh`

## List of Allowed Functions and System Calls

- [List of Allowed Functions and System Calls](#list-of-allowed-functions-and-system-calls)

## Compilation

Compile the shell using the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## How to add Author file
`Bash script for generating the list of authors in git repo`
```
#!/bin/sh

git shortlog -se \
  | perl -spe 's/^\s+\d+\s+//' \
  | sed -e '/^CommitSyncScript.*$/d' \
  > AUTHORS
  ```Ammar Ashour
