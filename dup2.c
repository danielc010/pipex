#include <unistd.h>
#include <fcntl.h>

int main(int ac, char *av[], char *env[])
{
    (void) ac;
    (void) av;
    int in;
    int out;
    char *grep_args[] = {"grep", "Lausanne", NULL};

    // open input and output files (assuming both files exist)
    in = open("in", O_RDONLY);
    out = open("out", O_WRONLY);

    // replace standard input with input file
    dup2(in, 0);
    // close unused file descriptors
    close(in);
    close(out);

    // execute grep
    execve("grep", grep_args, env);
}
