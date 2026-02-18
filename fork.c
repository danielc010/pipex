/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/18 09:26:17 by dachin        #+#    #+#                 */
/*   Updated: 2026/02/18 11:59:45 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// int main(void)
// {
//     pid_t pid = fork();  // Creates a NEW process

//     if (pid == 0) {
//         // Child process
//         printf("I'm the child, PID: %d\n", getpid());
//     } else {
//         // Parent process
//         printf("I'm the parent, PID: %d\n", getpid());
//     }
// }
int main(void)
{
    // pid_t is the DATA TYPE for storing PIDs
    pid_t pid;           // Variable named 'pid'
    pid_t my_process;    // Variable named 'my_process'
    pid_t child;         // Variable named 'child'

    // getpid() returns your process's PID (the actual number)
    pid = getpid();                    // Get MY PID
    printf("My PID is: %d\n", pid);    // e.g., "My PID is: 1234"

    // fork() returns the CHILD's PID to parent
    child = fork();

    if (child == 0) {
        // I'm the child process
        printf("Child PID: %d\n", getpid());      // My actual PID
        printf("Parent PID: %d\n", getppid());    // My parent's PID
    } else {
        // I'm the parent process
        printf("Parent PID: %d\n", getpid());     // My actual PID
        printf("Child PID: %d\n", child);         // Child's PID (stored in variable)
		wait(NULL);
    }
}
