/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:26:30 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/14 19:11:54 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_path(char *_path, char *command)
{
	char	**paths;
	int		i;
	char	*path;

	paths = ft_split(_path, 58);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], command);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
			path = paths[i];
		i++;
	}
	return (path);
}

void	print_error(t_data *data)
{
	t_dict		*env;
	char		*str;
	extern int	g_stats;

	env = data->env;
	str = data->commands->key;
	while (env)
	{
		str = ft_strreplace(str, ft_strjoin("$", env->key), env->value);
		env = env->next;
	}
	str = ft_strreplace(str, ft_itoa(-125), "<");
	str = ft_strreplace(str, ft_itoa(-126), "<<");
	str = ft_strreplace(str, ft_itoa(-127), ">");
	str = ft_strreplace(str, ft_itoa(-128), ">>");
	if (ft_strstr(data->commands->key, "/"))
		printf("minishell: %s: No such file or directory\n",
			data->commands->key);
	else
	{
		g_stats = 127;
		printf("minishell: %s: command not found\n", str);
	}
}

void	_execve_print(t_data *data)
{
	if (!get_dict_value(data->env, "PATH"))
	{
		printf("minishell: %s: No such file or directory\n",
			data->commands->key);
		return ;
	}
}

char	**continue_execve(t_data *data,
	char **temp, char **argv, char *key)
{
	int	i;
	int	j;

	i = 0;
	(void)data;
	while (temp[i])
		i++;
	if (i >= 1)
	{
		argv = malloc(sizeof(char *) * (i + 2));
		argv[0] = key;
		i = 1;
		j = -1;
		while (temp[++j])
		{
			argv[i] = temp[j];
			i++;
		}
		argv[i] = NULL;
	}
	return (argv);
}
