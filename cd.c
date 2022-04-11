/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/11 17:29:14 by aherrero         ###   ########.fr       */
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

char	*get_path(char *str)
{
	char	**command;
	char	*path;
	int		i;

	command = ft_split(str, ' ');
	path = malloc(sizeof(char) * ft_strlen(command[1]));
	if (!path)
		return (NULL);
	
	path = command[1];
	printf("PATH: %s\n", path);
	printf("ENV: %s\n", getenv());
	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
	return (path);
}

void	cd(char *str)
{
	char	*path;

	path = get_path(str);
	if (!path)
	{
		path = ft_strjoin("/Users/", getenv("USER"));
	}
	if (chdir(path) == 0)
		ft_pwd();
	else
		printf("cd: no such file or directory: %s\n", path);
	free(path);
}

int main (void)
{
	cd("cd /~/");
	return (0);
}