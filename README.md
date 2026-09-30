# Pipex

A C implementation of the pipex project from 42 School. Recreates the behavior of shell pipes (`|`) by executing commands with input/output redirections using `fork`, `pipe`, `dup2`, and `execve`.

## How it works

The program takes an input file, two commands, and an output file. It executes the first command with the input file as stdin, pipes its output to the second command, and writes the final output to the output file.

```
./pipex input.txt "grep foo" "wc -l" output.txt
```

Equivalent to: `< input.txt grep foo | wc -l > output.txt`

## Building

```bash
make        # Compile mandatory part
make bonus  # Compile with bonus (multiple pipes + here_doc)
```

Requires `cc` (C compiler) and the shared libraries (libft, gnl, printf) from the parent repository.

## Usage

### Mandatory

```bash
./pipex input.txt "cmd1" "cmd2" output.txt
```

### Bonus (multiple commands + here_doc)

```bash
./pipex input.txt "cmd1" "cmd2" "cmd3" "cmd4" output.txt
./pipex here_doc LIMITER "cmd1" "cmd2" output.txt
```

The `here_doc` feature reads from stdin until the limiter string is encountered, then uses that as input.

## Project structure

```
pipex/
├── src/
│   ├── main.c              # Mandatory entry point
│   ├── main_bonus.c        # Bonus entry point
│   ├── find_executable.c   # PATH resolution
│   ├── child_process.c     # Fork and exec logic
│   ├── utils.c             # File ops, here_doc, error handling
│   ├── pipe_utils.c        # Pipe creation and setup (bonus)
│   ├── process.c           # Multi-process management (bonus)
│   └── free_array2.c       # Utility function
├── inc/
│   └── pipex.h             # Unified header
└── Makefile
```

## Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove binary and object files
make re       # Recompile
```
