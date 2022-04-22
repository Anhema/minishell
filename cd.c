/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/22 17:19:02 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *str)
{
	char	**command;
	char	*path;

	command = ft_split(str, ' ');
	if (!command[1] || ft_str_equals(command[1], "~") == 1)
		return (NULL);
	path = malloc(sizeof(char) * ft_strlen(command[1]));
	if (!path)
		return (NULL);
	path = command[1];
	free(command);
	return (path);
}

void	_cd(char *str, char *usr)
{
	char	*path;

	path = get_path(str);
	(void)env;
	if (!path)
	{
		path = ft_strjoin("/Users/", usr);
		if (chdir(path) == 0)
		{
			free(path);
			return ;
		}
		else
			printf("cd: no such file or directory: %s\n", path);
	}
	else
	{
		if (chdir(path) == 0)
		{
			free(path);
			return ;
		}
		else
			printf("cd: %s: No such file or directory\n", path);
	}
	free(path);
}
