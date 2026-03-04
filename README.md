# pipex

_This project has been created as part of the 42 curriculum by dachin_

## Description

This project focuses on handling pipes. The pipe is an in-memory buffer that connects two processes together. File descriptors point to the pipe object, which buffers data sent to it (via a write) to be drained (via a read).

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
./pipex
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
