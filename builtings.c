/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:49:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/13 17:00:46 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	extern int	g_stats;
	char		*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	g_stats = 0;
	free (s);
}

int	ft_magic_nbr(int n, t_data *data)
{
	n = ft_atoi(data->commands->value);
	if (n > 256)
		n = n - 256 ;
	else if (n < 0)
		n = 256 + n;
	else if (n >= 500)
		n = n - 512;
	else if (n == 256 || n == 512)
		n = 0;
	return (n);
}

void	ft_exit(char *str, t_data *data)
{
	int	n;
	int	i;

	i = -1;
	n = 0;
	if (data->commands->value)
	{
		while (data->commands->value[++i])
		{
			if (data->commands->value[i] == '-')
				continue ;
			if (data->commands->value[i] < 47
				|| data->commands->value[i] > 57)
			{
				printf("exit: %s: numeric argument required\n",
					data->commands->value);
				exit(255);
			}
		}
		n = ft_magic_nbr(n, data);
	}
	g_stats = n;
	free(str);
	exit(n);
}

t_data	*builtings(t_data *data, char *str)
{
	(void)str;
	if (ft_str_equals(data->commands->key, "pwd"))
		ft_pwd();
	else if (ft_str_equals(data->commands->key, "echo"))
		ft_echo(data);
	else if (ft_str_equals(data->commands->key, "env")
		&& !data->commands->value)
		print_dict(data->env);
	else if (ft_str_equals(data->commands->key, "history"))
		ft_read_file(".history", 0);
	else if (ft_str_equals(data->commands->key, "cd"))
		printf("");
	else
		ft_execve(data);
	return (data);
}

t_data	*redirections(t_data *data, char *str)
{
	int		temp_in;
	int		temp_out;
	int		fd_in;
	char	*infile;

	(void)str;
	temp_in = dup(0);
	temp_out = dup(1);
	infile = check_infile(data);
	if (infile)
	{
		if (ft_str_equals(infile, "1_"))
			return (data);
		else
			fd_in = open(infile, O_RDONLY, 0000644);
	}
	else
		fd_in = dup(temp_in);
	printf("");
	redirections_aux(data, fd_in, temp_in, temp_out);
	return (data);
}