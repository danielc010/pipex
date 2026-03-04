#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/resource.h>

void example_perror(void)
{
	int fd = open("non_existent_file.txt", O_RDONLY);
	if (fd == -1)
	{
		// Automatically prints: "Open failed: No such file or directory\n" to stderr
		perror("Open failed");
	}
}

void example_strerror(void)
{
	int fd = open("non_existent_file.txt", O_RDONLY);
	if (fd == -1)
	{
		// strerror returns the string, we must print it ourselves
		char *error_msg = strerror(errno);
		printf("My custom error message: %s\n", error_msg);
		printf("Errno: %d\n", errno);
	}
}

void	example_access(void)
{
	// Checks R_OK (Read) OR'd with W_OK (Write)
	if (access("pipex.pdf", R_OK | W_OK) == 0)
	{
		printf("You have both read and write permissions.\n");
	}
	if (access("pipex.pdf", F_OK) == 0)
		printf("File exists\n");
	if (access("pipex.pdf", X_OK) == 0)
		printf("File is executable\n");

	// Mode 7 is equivalent to R_OK | W_OK | X_OK (4 | 2 | 1)
	if (access("pipex.pdf", 7) == 0)
		printf("You have Read, Write, AND Execute permissions.\n");

}

void example_unlink(void)
{
	printf("\n--- Unlink Example ---\n");
	// 1. Create a temporary file
	int fd = open("temp_file.txt", O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		perror("Error creating file");
		return;
	}
	printf("Created 'temp_file.txt'\n");

	// 2. Unlink it immediately
	if (unlink("temp_file.txt") == 0)
		printf("Unlinked 'temp_file.txt'\n");
	else
		perror("Unlink failed");

	// 3. We can still write to it because we have the fd open!
	write(fd, "Hidden data", 11);

	// 4. Once we close it, the data is lost forever because the name is gone
	close(fd);

	if (access("temp_file.txt", F_OK) == -1)
		printf("Confirmed: 'temp_file.txt' is gone from the filesystem.\n");
}

void example_wait(void)
{
	printf("\n--- Wait Example ---\n");
	pid_t pid = fork();

	if (pid == 0)
	{
		// Child Process
		printf("Child: I am running... and now I will exit with code 42.\n");
		exit(42);
	}
	else
	{
		// Parent Process
		int status;

		// Wait blocks until the child finishes.
		// The OS stores the exit details in 'status'.
		wait(&status);

		if (WIFEXITED(status))
			printf("Parent: Child finished. Exit code was: %d\n", WEXITSTATUS(status));
	}
}

void example_rusage(void)
{
	printf("\n--- Rusage Example (wait4) ---\n");
	// Note: wait4 is often not allowed in 42 projects, but this demonstrates rusage.
	pid_t pid = fork();

	if (pid == 0)
	{
		// Child: Do some work to consume CPU time
		int i = 0;
		while (i < 10000000)
			i++;
		exit(0);
	}
	else
	{
		int status;
		struct rusage usage;

		// wait4 allows us to pass a 'usage' struct to get statistics
		wait4(pid, &status, 0, &usage);

		if (WIFEXITED(status))
		{
			printf("Child finished.\n");
			printf("CPU time used: %ld.%06ld sec\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
		}
	}
}

void example_fork(void)
{
	printf("\n--- Fork Example ---\n");
	// fork() creates a duplicate process
	pid_t pid = fork();


	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}
	printf("Test (outside) - what is pid? %d\n", pid);
	if (pid == 0)
	{
		// This block is executed ONLY by the Child
		printf("CHILD: I am the child process.\n");
		printf("CHILD: My PID is %d.\n", getpid());
		printf("CHILD: My Parent's PID is %d.\n", getppid());
		printf("Test (CHILD Block) - what is pid? %d\n", pid);
		exit(0); // Child exits here
	}
	else
	{
		// This block is executed ONLY by the Parent
		printf("PARENT: I am the parent process.\n");
		printf("PARENT: My PID is %d.\n", getpid());
		printf("PARENT: I created a child with PID %d.\n", pid);
		wait(NULL); // Wait for child to finish
	}
}

void example_pipe(void)
{
	printf("\n--- Pipe Example ---\n");
	int fd[2];
	pid_t pid;
	char buffer[100];

	// 1. Create the pipe
	// fd[0] will be the READ end
	// fd[1] will be the WRITE end
	if (pipe(fd) == -1)
	{
		perror("Pipe failed");
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}

	if (pid == 0)
	{
		// Child Process: Reader
		close(fd[1]); // Close unused write end

		// Read from the pipe
		int bytes_read = read(fd[0], buffer, sizeof(buffer));
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0'; // Null-terminate string
			printf("Child received: %s\n", buffer);
		}
		close(fd[0]); // Close read end
		exit(0);
	}
	else
	{
		// Parent Process: Writer
		close(fd[0]); // Close unused read end

		char *msg = "Hello from parent!";
		write(fd[1], msg, strlen(msg));
		printf("Parent sent: %s\n", msg);

		close(fd[1]); // Close write end (sends EOF to reader)
		wait(NULL);   // Wait for child
	}
}

void example_dup2(void)
{
	printf("\n--- Dup2 Example ---\n");
	int fd = open("dup2_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open failed");
		return;
	}

	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process
		// Redirect Standard Output (1) to our file (fd)
		// 1. dup2 closes STDOUT_FILENO (1) if it's open (it usually is).
		// 2. It duplicates 'fd' to slot 1.
		dup2(fd, STDOUT_FILENO);

		// We don't need the original 'fd' anymore, slot 1 is enough.
		close(fd);

		// Now, anything printed to stdout goes to the file.
		printf("This message is printed to stdout, but ends up in the file!\n");

		// Even system commands executed here would write to the file.
		exit(0);
	}
	else
	{
		// Parent process
		close(fd); // Parent doesn't need this fd
		wait(NULL); // Wait for child to finish writing

		printf("Child finished. Reading file content:\n");

		// Verify content
		char buffer[100];
		fd = open("dup2_test.txt", O_RDONLY);
		int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			printf("File contained: \"%s\"\n", buffer);
		}
		close(fd);
		unlink("dup2_test.txt");
	}
}

int main(void)
{
	// printf("%d\n", access("project_plan.txt", 0));
	// printf("%d\n", errno);
	// printf("%s\n", strerror(errno));

	example_perror();
	example_strerror();
	example_access();
	example_unlink();
	example_wait();
	example_rusage();
	example_fork();
	example_pipe();
	example_dup2();

	return 0;
}
