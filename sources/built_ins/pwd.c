
#include "../../includes/minishell.h"

void	pwd(void)
{						//TODO is it the responsibility of the builtins to check that they do not have any flags or options?
	char	*buf;
	size_t	size;

	size = 10;
	while (1)
	{
		buf = malloc (size);
		if (buf == NULL)
		{
			printf("Malloc failed\n");
			//error();
			exit(1);
		}
		buf = getcwd(buf, size);
		if (buf == NULL)
			size *= 2;
		else
			break ;
	}
	printf("%s\n", buf);
	free(buf);
}