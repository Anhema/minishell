/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/25 17:11:24 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_data	_cd(char *str, char *usr, t_data data)
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
		temp = data.env;
		temp = cd_aux(temp, old_path);
		return (data);
	}
	else
		printf("minishell: cd: %s: No such file or directory\n", path);
	return (data);
}
