# minishell 💻

## Overview 📝

`minishell` is a simple shell implementation written in C. The goal of this project is to replicate the basic functionalities of a shell, such as interpreting user commands, executing programs, handling piping, input/output redirection, and more, while learning how shells work at a low level.

The program parses the user's input, executes commands, and manages processes, supporting common shell operations like piping and redirection. The focus is on building a small, efficient, and functional shell that behaves similarly to `bash` or `sh`.

## Features 🌟

- **Command Parsing**: The shell can parse commands entered by the user.
- **Process Execution**: Executes external programs with `execve()`.
- **Redirection**: Supports input and output redirection (`<`, `>`, `<<`, `>>`).
- **Piping**: Implements piping between commands (`|`).
- **Built-in Commands**: Includes support for built-in commands such as `echo`, `cd`, `exit`, and `pwd`.
- **Environment Variables**: Handles environment variables and allows users to view and modify them.
- **Error Handling**: Provides basic error handling for invalid commands and system errors.
