/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:41:22 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/25 18:04:27 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**join_env(t_dict *d_env)
{
	char	**env;
	int		i;
	int		j;
	t_dict	*temp;

	temp = d_env;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * i);
	temp = d_env;
	j = 0;
	while (temp)
	{
		env[j] = ft_strjoin(temp->key, "=");
		env[j] = ft_strjoin(env[j], temp->value);
		temp = temp->next;
		j++;
	}
	return (env);
}

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

static void	print_error(t_data data)
{
	t_dict	*env;
	char	*str;

	env = data.env;
	str = data.commands->key;
	while (env)
	{
		str = ft_strreplace(str, ft_strjoin("$", env->key), env->value);
		env = env->next;
	}
	printf("minishell: %s: command not found\n", str);
}

void	ft_execve(t_data data)
{
	pid_t	pid;
	int		i;
	int		j;
	char	**temp;
	char	**argv;
	char	**env;
	int		status;
	char	*path;

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
	}
	else
	{
		argv = malloc(sizeof(char *) * 3);
		argv[0] = data.commands->key;
		argv[1] = data.commands->value;
		argv[2] = NULL;
	}
	env = join_env(data.env);
	if (!get_dict_value(data.env, "PATH"))
	{
		printf("minishell: %s: No such file or directory\n", data.commands->key);
		return ;
	}
	path = get_path(get_dict_value(data.env, "PATH"), data.commands->key);
	argv[0] = path;
	pid = fork();
	if ((pid) == -1)
		perror("fork error");
	else if (pid == 0)
	{
		if (execve(path, argv, env) < 0)
			print_error(data);
	}
	waitpid(pid, &status, 0);
}
