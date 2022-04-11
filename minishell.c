/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/11 17:37:11 by aherrero         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}	
	str = readline("> ");
	while (1)
	{
		if (ft_str_equals(str, "exit") == 1)
			ft_exit(str);
		else if (quotation_open(str) == 0)
			printf("Cierra las comillas: %s\n", str);
		else if (ft_str_equals(str, "pwd") == 1)
			ft_pwd();
		else
			printf("command not found: %s\n", str);
		str = readline("> ");
	}
	return (0);
}
