/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipedemo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 13:47:18 by dachin        #+#    #+#                 */
/*   Updated: 2026/02/18 13:47:20 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void pipe_size_demo(void)
{
    printf("\n--- Pipe Size Demo ---\n");
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {
        // Child: Read slowly
        close(fd[1]);

        sleep(2);  // Wait before reading

        char buffer[100];
        int bytes = read(fd[0], buffer, sizeof(buffer));
        buffer[bytes] = '\0';
        printf("Child read: %s\n", buffer);

        close(fd[0]);
        exit(0);
    }
    else {
        // Parent: Write immediately
        close(fd[0]);

        printf("Parent writing to pipe...\n");
        write(fd[1], "Data is waiting in kernel buffer!", 33);
        printf("Parent wrote! Data is now sitting in pipe memory.\n");
        printf("Parent will close write end and wait...\n");

        close(fd[1]);  // This sends EOF
        wait(NULL);

        printf("Parent: Child finished reading.\n");
    }
}

int main(void)
{
    pipe_size_demo();
    return 0;
}
