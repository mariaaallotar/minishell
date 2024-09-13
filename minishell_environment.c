/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:13:14 by maheleni          #+#    #+#             */
/*   Updated: 2024/09/13 10:20:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//when a (normal) shell is opened from minishell it gets its env automatically
//but when minishell is opened from a shell it will get that shells env via envp
//do we want to have a set env that minishell always has when opened (but without
//the unset things? Does that work even after unseting, in the same way

/**
 * so when we run any program from minishell we will give it the changed environ
 */

/**
 * if i export some variable in minishell and open bash, how does bash get it? We
 * need to actually edit the file that holds the esported variables for that to
 * work? I suppose we could hardcode it to do export but I don't think that is correct.
 */


//Code example of how access environment variables
extern char **environ;

void print_environ() {
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

int main() {
    print_environ(); // Accesses the global `environ` variable
    return 0;
}
/**
 * is environ the exact same thing as envp
 */
