/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:26:30 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/22 21:44:32 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_path(char *_path, char *command)
{
	char	**paths;
	int		i;
	char	*path;
	char	*tmp;
	char	*aux;

	paths = ft_split(_path, 58);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		aux = ft_strjoin(tmp, command);
		free(paths[i]);
		paths[i] = aux;
		free(tmp);
		free (aux);
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
			path = paths[i];
		i++;
	}
	free(paths);
	return (path);
}

char	*str_aux(char *str)
{
	char	*aux;
	char	*temp;
	char	*tmp;
	//char	*_aux;

	/*s1 = ft_itoa(-125);
	s2 = ft_itoa(-126);
	s3 = ft_itoa(-127);
	_aux = ft_itoa(-128);*/
	/*
	str = ft_strreplace(str, aux, "<");
	str = ft_strreplace(str, temp, "<<");
	str = ft_strreplace(str, tmp, ">");
	str = ft_strreplace(str, _aux, ">>");*/
	aux = ft_strreplace(str, "-125", "<");
	temp = ft_strreplace(aux, "-126", "<<");
	tmp = ft_strreplace(temp, "-127", ">");
	str = ft_strreplace(tmp, "-128", ">>");
	free (aux);
	free (temp);
	free (tmp);
	/*free (_aux);
	free (s1);
	free(s2);
	free (s3);*/
	return (str);
}

void	print_error(t_data *data)
{
	//t_dict		*env;
	char		*str;
	char		*temp;
	extern int	g_stats;
	char		*aux;
	//env = data->env;
	str = data->commands->key;
	/*while (env)
	{
		temp = ft_strjoin("$", env->key);
		str = ft_strreplace(str, temp, env->value);
		env = env->next;
		free(temp);
	}*/
	/*
	str = ft_strreplace(str, ft_itoa(-125), "<");
	str = ft_strreplace(str, ft_itoa(-126), "<<");
	str = ft_strreplace(str, ft_itoa(-127), ">");
	str = ft_strreplace(str, ft_itoa(-128), ">>");*/
	aux = str_aux(str);
	temp = ft_strstr(data->commands->key, "/");
	if (temp)
		printf("minishell: %s: No such file or directory\n",
			data->commands->key);
	else
	{
		g_stats = 127;
		printf("minishell: %s: command not found\n", str);
	}
	//delete_all(env);
	//free(temp);
	free(aux);
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
