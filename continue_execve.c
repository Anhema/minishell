/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:26:30 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/23 17:40:59 by cbustama         ###   ########.fr       */
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

	path = NULL;
	paths = ft_split(_path, 58);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		aux = ft_strjoin(tmp, command);
		free(paths[i]);
		paths[i] = NULL;
		paths[i] = ft_strdup(aux);
		free(tmp);
		free (aux);
		i++;
	}
	path = aux_get_path(paths, path);
	if (path)
		return (path);
	free_split_double(paths);
	return (path);
}

char	*str_aux(char *str)
{
	char	*aux;
	char	*temp;
	char	*tmp;

	aux = ft_strreplace(str, "-125", "<");
	temp = ft_strreplace(aux, "-126", "<<");
	tmp = ft_strreplace(temp, "-127", ">");
	str = ft_strreplace(tmp, "-128", ">>");
	free (aux);
	free (temp);
	free (tmp);
	return (str);
}

void	print_error(t_data *data)
{
	char		*str;
	char		*temp;
	extern int	g_stats;
	char		*aux;

	str = data->commands->key;
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
