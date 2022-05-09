/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/09 17:36:37 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *str)
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

t_data	_cd(char *str, char *usr, t_data data)
{
	char	*path;
	char	*old_path;

	path = get_path(str);
	old_path = getcwd(NULL, 0);
	if (!path)
		path = ft_strjoin("/Users/", usr);
	if (ft_str_equals(old_path, "/Users") && ft_str_equals(path, ".."))
		path = "/";
	if (chdir(path) == 0)
	{
		data.env = dict_add_back(data.env, dict_new("PWD", getcwd(NULL, 0)));
		data.env = dict_add_back(data.env, dict_new("OLDPWD", old_path));
		return (data);
	}
	else
		printf("cd: %s: No such file or directory\n", path);
	return (data);
}
