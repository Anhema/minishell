/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:49:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/26 17:44:28 by aherrero         ###   ########.fr       */
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

void	ft_exit(char *str)
{
	int	fd;

	fd = open(".history", O_RDONLY);
	unlink(".history");
	close (fd);
	free(str);
	exit(0);
}

void	builtings(t_data data, char *str)
{
	if (ft_str_equals(data.commands->key, "pwd"))
		ft_pwd();
	else if (ft_str_equals(data.commands->key, "echo"))
		ft_echo(data);
	else if (ft_str_equals(data.commands->key, "env")
		&& !data.commands->value)
		print_dict(data.env);
	else if (ft_str_equals(data.commands->key, "history"))
		ft_read_file(".history", 0);
	else if (ft_str_equals(data.commands->key, "cd"))
		printf("");
	else if (ft_str_equals(data.commands->key, "export"))
		data.env = ft_export(data);
	else if (ft_str_equals(data.commands->key, "unset"))
		data.env = ft_unset(data.env, ft_split(str, ' '));
	else
	{
		continue_signal();
		ft_execve(data);
	}
}

static void	redirections_fd(t_data data, int fd_in, int temp_in)
{
	int	fd[2];
	int	fd_out;

	dup2(fd_in, 0);
	close(fd_in);
	if (!data.commands->next)
	{
		fd_out = dup(temp_in);
	}
	else
	{
		pipe(fd);
		fd_out = fd[1];
		fd_in = fd[0];
	}
	dup2(fd_out, 1);
	close(fd_out);
}

void	redirections(t_data data, char *str)
{
	int	temp_in;
	int	temp_out;
	int	fd_in;
	int	pid;

	temp_in = dup(0);
	temp_out = dup(1);
	fd_in = dup(temp_in);
	while (data.commands)
	{
		redirections_fd(data, fd_in, temp_in);
		pid = fork();
		if (pid == 0)
		{
			builtings(data, str);
			exit (1);
		}
		data.commands = data.commands->next;			
	}
	dup2(temp_in, 0);
	dup2(temp_out, 1);
	close(temp_out);
	close(temp_in);
	waitpid(pid, NULL, 0);
}
