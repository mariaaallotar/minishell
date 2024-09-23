
#include "../../includes/minishell.h"

void	unset()
{

}

int	existing_key(char *var)
{
	if (find_key() != 0)
		return (1);
	return (0);
}

int	forbidden_key(char *var)
{
	int	i;

	if (ft_isdigit(var[0]) || !ft_isprint(var[0]))
		return (1);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) || var[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

void	export(t_main *main, char *var)
{
	if (forbidden_key(var))
	{
		//TODO what error to print
		//error();
		return ;
	}
	if (existing_key(var))
		update_variable(main, var);
	add_variable(main, var);
}
