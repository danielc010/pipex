# pipex

_This project has been created as part of the 42 curriculum by dachin_

## Description

This project focuses on handling pipes. The pipe is an in-memory buffer that connects two processes together. File descriptors point to the pipe object, which buffers data sent to it (via a write) to be drained (via a read).
We recreate this behaviour c< file1 cmd1 | cmd2 > file2`.
Bonus:
1) Support multiple pipes `< file1 cmd1 | cmd2 ... | cmdn > file2`.
2) Support << >> when the first parameter is "here_doc".
	`cmd1 << LIMITER | cmd2 >> file`


## Instructions
``` bash
# Compile the project
make

# Compile with bonus (if applicable)
make bonus

# Clean object files
make clean

# Full clean (remove executable)
make fclean

# Recompile everything
make re

# Running the program
## Normal pipe
./pipex file1 cmd1 cmd2 ... cmdn file2

## heredoc pipe
./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file

# Useful valgrind check for open fds
valgrind --track-fds=yes

```

## Resources & Credits
Man Pages:
- man 2 pipe
- man 2 fork
- man 2 dup2
- man 2 execve
- man 2 waitpid
- man 3 access

Useful Links:
- Understanding fork: https://www.geeksforgeeks.org/fork-system-call/
- Understanding pipes: https://www.geeksforgeeks.org/pipe-system-call/
- File descriptors: https://www.bottomupcs.com/file_descriptors.xhtml
- Shell command language: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
