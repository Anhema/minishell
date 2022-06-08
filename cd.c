/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/07 20:10:11 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stats;

static t_dict	*cd_aux(t_dict *temp, char *old_path)
{
	while (temp->next)
	{
		if (ft_str_equals(temp->next->key, "PWD") == 1)
			temp->next->value = getcwd(NULL, 0);
		if (ft_str_equals(temp->next->key, "OLDPWD") == 1)
			temp->next->value = old_path;
		temp = temp->next;
	}
	return (temp);
}

t_data	_cd(char *str, char *usr, t_data *data)
{
	char	*path;
	char	*old_path;
	t_dict	*temp;

	path = str;
	old_path = getcwd(NULL, 0);
	if (!path)
		path = ft_strjoin("/Users/", usr);
	if (ft_str_equals(old_path, "/Users") && ft_str_equals(path, ".."))
		path = "/";
	if (chdir(path) == 0)
	{
		temp = data->env;
		temp = cd_aux(temp, old_path);
		return (*data);
	}
	else
	{
		 g_stats = 1;
		printf("minishell: cd: %s: No such file or directory\n", path);
	}
	g_stats = 0;
	return (*data);
}
