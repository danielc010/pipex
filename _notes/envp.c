#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;  // ← Tell compiler you know it's unused
	(void)argv;  // ← Tell compiler you know it's unused

	int	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		++i;
	}
	return 0;
}
