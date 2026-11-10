*This project has been created as part of the 42 curriculum by `mohalaou`, `saamouss`.*

# Minishell

## Description

Minishell is a simple Unix shell written in C, inspired by Bash. The goal of the project is to understand how a shell works internally: how it reads a command line, parses it, manages processes and file descriptors, and executes programs.

The project covers key Unix concepts such as processes (`fork`, `execve`, `waitpid`), pipes, file descriptor redirection, environment variables and signal handling.

### Features

- Interactive prompt with command history
- Execution of commands using the `PATH` variable, or a relative / absolute path
- Single quotes `'` (no interpretation) and double quotes `"` (only `$` is interpreted)
- Environment variable expansion (`$VAR`) and exit status expansion (`$?`)
- Redirections:
  - `<` redirect input
  - `>` redirect output
  - `>>` redirect output in append mode
  - `<<` heredoc (reads input until a given delimiter)
- Pipes `|` to connect the output of one command to the input of the next
- Signal handling: `Ctrl-C`, `Ctrl-D` and `Ctrl-\` behave like in Bash
- Built-in commands:

| Built-in | Description |
|----------|-------------|
| `echo` | Prints text, with the `-n` option |
| `cd` | Changes directory (relative or absolute path) |
| `pwd` | Prints the current working directory |
| `export` | Sets environment variables |
| `unset` | Removes environment variables |
| `env` | Prints the environment |
| `exit` | Exits the shell |

## Instructions

### Requirements

- A C compiler (`cc`)
- `make`
- The `readline` library

On Debian / Ubuntu, install it with:

```bash
sudo apt-get install libreadline-dev
```

### Compilation

```bash
make        # build the minishell executable
make clean  # remove object files
make fclean # remove object files and the executable
make re     # rebuild everything
```

### Execution

```bash
./minishell
```

### Usage examples

```bash
minishell$ echo "Hello World"
Hello World
minishell$ export NAME=42
minishell$ echo $NAME
42
minishell$ ls -l | grep minishell > result.txt
minishell$ cat << EOF
> some text
> EOF
some text
minishell$ cat < result.txt | wc -l
1
minishell$ echo $?
0
```

## Project Structure

*Adjust this section to match your own repository.*

```
.
├── Makefile
├── includes/
│   └── minishell.h
├── srcs/
│   ├── main.c
│   ├── parser.c     # Command parsing and pipeline structuring
│   ├── tokenize.c   # Lexical analysis and input tokenization
│   ├── quotes.c     # Quote parsing and removal logic
│   ├── utilis.c     # General helper and utility functions
│   └── ...     
└── libft/
```

## Resources

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — reference behavior for the shell
- [GNU Readline documentation](https://tiswww.cwru.edu/php/chet/readline/rltop.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Linux man pages](https://man7.org/linux/man-pages/) — `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `sigaction`, `readline`

### AI usage

AI tools were utilized during the development of this project as an efficient engineering assistant. The workflow focused on leveraging AI for specific development phases while maintaining strict oversight of core architecture and code implementation:

* **Fast Documentation & Reference:** Used AI to quickly search, synthesize, and look up standard library functions, configuration syntax, and system manual descriptions.
* **Architecture Refactoring & Structure:** Consulted AI for structural advice and best practices when organizing directories, setting up custom headers, and refactoring modular C source files.
* **Debugging Assistance:** Leveraged AI diagnostics to help parse compilation errors, trace linker flags, and resolve header path issues.
