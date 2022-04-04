/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/04 18:49:29 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free (s);
}
void	ft_exit(char *str)
{
		free(str);
		exit(0);
}

int main(void)
{
	char	*str;

	str = readline("> ");
	while (1)
	{
		if (ft_str_equals(str, "exit") == 1)
			ft_exit(str);
		else if (ft_str_equals(str, "pwd") == 1)
			ft_pwd();
		else
			printf("command not found: %s\n", str);
		
		str = readline("> ");
			
	}
	return (0);
}
