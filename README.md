# Minishell

Minishell is a small Unix shell written in C as part of the 42 curriculum. It provides an interactive prompt, command parsing, environment expansion, builtin commands, pipelines, redirections, heredocs, and signal handling.
This project was completed in a team of 2.

## Requirements

- macOS or another Unix-like operating system
- `cc` or another C compiler compatible with the Makefile
- `make`
- GNU Readline development files and library

On macOS with Homebrew, install Readline with:

```sh
brew install readline
```

Depending on the local installation, the compiler or linker flags in the Makefile may need to point to Homebrew's Readline directory.

## Build

From the project root:

```sh
make
```

This builds the `minishell` executable and the bundled `libft` library.

Available Make targets:

```sh
make        # Build minishell
make clean  # Remove object files
make fclean # Remove object files, libft, and the executable
make re     # Rebuild from scratch
```

## Run

```sh
./minishell
```

The shell starts with the current process environment. Press `Ctrl-D` at an empty prompt to exit.

Example:

```console
$ ./minishell
minishell> export NAME="minishell"
minishell> echo "Hello, $NAME!"
Hello, minishell!
minishell> printf '%s\n' "$PWD"
/path/to/project
minishell> exit
exit
```

## Supported syntax

- Single and double quotes
- Environment variable expansion, including `$?`
- Input redirection: `< file`
- Output redirection: `> file`
- Append redirection: `>> file`
- Here-documents: `<< delimiter`
- Pipelines: `command1 | command2`
- Signals for the interactive prompt and heredoc mode

## Builtins

The following builtin commands are implemented:

`echo` · `cd` · `pwd` · `export` · `unset` · `env` · `exit`

External programs are resolved using the shell's `PATH` environment variable.

## Project layout

```text
includes/       Public project headers
libs/libft/     Bundled libft implementation
srcs/bin/       Builtin commands and environment management
srcs/execution/ Pipelines, redirections, heredocs, and command execution
srcs/parsing/   Tokenization, quoting, expansion, and syntax checks
srcs/main.c     Interactive shell loop
```

## Cleaning up

Build artifacts are ignored by the source layout and can be removed with:

```sh
make fclean
```
