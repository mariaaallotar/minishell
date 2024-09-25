
#include "../../includes/minishell.h"

void	update_variable(t_main *main, char *var)
{
	t_list	*node;
	char	*malloced_content;

	node = find_node(main, var);
	free(node->content);
	malloced_content = ft_strdup(var);
	if (malloced_content == NULL)
	{
		//TODO error
		free_environment(&(main->env_list));
		ft_free_split(&(main->split_input));
	}
	node->content = malloced_content;
}

int	existing_key(t_main *main, char *var)
{
	if (find_node(main, var) != NULL)
		return (1);
	return (0);
}

int	forbidden_key(char *var)
{
	int	i;

	if (ft_isdigit(var[0]) || !ft_isalpha(var[0]) || var[0] != '_')
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
		printf("Forbidden key: ");
		while (*var != '=' && *var)
		{
			printf("%c", *var);
			var++;
		}
		printf("\n");
		return ;
	}
	if (existing_key(main, var))
		update_variable(main, var);
	else
		add_variable(main, var);
}

void	unset(t_main *main, char *var_key)
{
	t_list	*node;
	char	*joined_str;

	if (ft_strchr(var_key, '=') != NULL)
	{
		printf("invalid parameter name\n");
		return ;
	}
	joined_str = ft_strjoin(var_key, "=");
	if (joined_str == NULL)
	{
		//error;	TODO
		exit(1);
	}
	node = find_node(main, joined_str);
	if (node == NULL)
		return ;
	remove_variable(main, joined_str);
	free(joined_str);
}
