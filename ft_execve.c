/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:41:22 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/06 19:42:52 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data data)
{
	pid_t	pid;
	int		i;
	int		j;
	char	**temp;
	char	**argv;
	char	**env;
	int		status;

	temp = ft_split(data.commands->value, ' ');
	i = 0;
	if (temp)
	{
		while (temp[i])
			i++;
	}
	if (!temp)
	{
		argv = malloc(sizeof(char *) * 2);
		argv[0] = data.commands->key;
		argv[1] = NULL;	
	}
	else if (i > 1)
	{
		argv = malloc(sizeof(char *) * (i + 2));
		argv[0] = data.commands->key;
		i = 1;
		j = 0;
		while (temp[j])
		{
			argv[i] = temp[j];
			i++;
			j++;
		}
		argv[i] = NULL;	
		// printf ("--%s--", argv[i]);
	}
	else
	{
		argv = malloc(sizeof(char *) * 3);
		argv[0] = data.commands->key;
		argv[1] = data.commands->value;	
		argv[2] = NULL;
	}
	// i = 0;
	// while (argv[i])
	// {
	// 	printf("\n--%s--\n", argv[i]);
	// 	i++;
	// }
	if ((pid = fork()) == -1)
		perror("fork error");
	else if (pid == 0) 
		execve(ft_strjoin("/bin/", data.commands->key), argv, env);
	waitpid(pid, &status, 0);
}
