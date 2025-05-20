# Minishell

A simple bash-like shell. This is the first pair project of the 42 curiculum. [Ethan Berkowitz](https://github.com/ethan-berkowitz) focused on user input, parsing and variable expansion. I focused on everything else.

## Features

- built-in commands:
  - echo with option -n   
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
- execute any program based on PATH variable as well as relative or absolute path
- handle single and double quotes
- redirections
- pipes
- environment variables
- signals:
  - ctrl-C, ctrl-D and ctrl-\
- history

## Screenshots

![image](https://github.com/user-attachments/assets/7be6e04a-f44c-4670-9b89-2ed0441e7f54)   

## Allowed external functions

- readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history   
- printf, malloc, free, write   
- access, open, read, close   
- fork, wait, waitpid, wait3, wait4   
- signal, sigaction, sigemptyset, sigaddset, kill, exit   
- getcwd, chdir, stat, lstat, fstat, unlink   
- execve, dup, dup2, pipe, opendir, readdir, closedir   
- strerror, perror, isatty, ttyname, ttyslot, ioctl   
- getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

## Technologies Used

- `C`, `Makefile`, `Git`

## What I learned

- project planing, management and teamwork
- to use `Git` for a shared project   
  - branches
  - pull requests
  - merging
- error handling
- project structure
