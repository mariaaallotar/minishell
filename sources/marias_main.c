/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marias_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:21:42 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/12 11:54:03 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int execute(commands)
{

}

int main (argv, envp)
{
    s_env this_env = copy_env(envp);    //what datastructure is our env
    create_signals();
    while (true)
    {
        line = readline("prompt: ");    //does readline only live in that function?
        binary_tree commands = tokenize(argv);
        execute(commands);
    }
}
