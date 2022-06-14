/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:26:30 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/09 20:17:01 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	*get_path(char *_path, char *command)
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

static void	print_error(t_data *data)
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

void	continue_execve_two(t_data *data, char **temp, char **argv, char *key)
{
	int	i;
	int	j;

	i = 0;
	if (!temp || ft_str_equals(data->commands->value, ""))
	{
		argv = malloc(sizeof(char *) * 2);
		argv[0] = key;
		argv[1] = NULL;
	}
	else if (i > 1)
	{
		argv = malloc(sizeof(char *) * (i + 2));
		argv[0] = key;
		i = 1;
		j = 0;
		while (temp[j])
		{
			argv[i] = temp[j];
			i++;
			j++;
		}
		argv[i] = NULL;
	}
}

void	ft_execve(t_data *data)
{
	char	**temp;
	char	**argv ;
	char	**env;
	char	*path;
	char	*key;

	argv = NULL;
	temp = NULL;
	key = data->commands->key;
	continue_execve(data, key, temp);
	continue_execve_two(data, temp, argv, key);
	if (!temp)
	{
		argv = malloc(sizeof(char *) * 3);
		argv[0] = key;
		argv[1] = data->commands->value;
		argv[2] = NULL;
	}
	env = join_env(data->env);
	_execve_print(data);
	path = get_path(get_dict_value(data->env, "PATH"), key);
	argv[0] = path;
	if (execve(path, argv, env) < 0)
		print_error(data);
}
