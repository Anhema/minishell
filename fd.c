/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:00:01 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/13 17:02:00 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc(t_data *data, t_dict *temp)
{
	int		in;
	char	*str;

	data->is_redir = 1;
	str = ft_readline(data);
	in = open(".redir", O_WRONLY | O_APPEND | O_CREAT, 0000644);
	while (1)
	{
		if (ft_str_equals(str, temp->value))
			break ;
		if (in < 0)
		{
			perror("minishell:");
			break ;
		}
		else
		{
			ft_putstr_fd(str, in);
			ft_putstr_fd("\n", in);
			str = ft_readline(data);
		}
	}
	close(in);
	data->is_redir = 0;
	return (".redir");
}

void	redirections_fd(t_data data, int fd_in, int temp_out)
{
	int		fd[2];
	int		fd_out;
	int		outfile;

	dup2(fd_in, 0);
	close(fd_in);
	if (redirections_fd_aux(data, temp_out))
		return ;
	if (!data.commands->next)
	{
		outfile = check_outfile(data);
		if (outfile >= 0)
			fd_out = outfile;
		else
			fd_out = dup(temp_out);
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

void	redirections_aux(t_data *data, int fd_in, int temp_in, int temp_out)
{
	int		status;
	int		pid;

	if (!data->commands)
		redirections_fd(*data, fd_in, temp_in);
	while (data->commands)
	{
		redirections_fd(*data, fd_in, temp_out);
		continue_signal();
		pid = fork();
		if (pid == 0)
		{
			data = builtings(data, data->str);
			exit (g_stats);
		}
		data->commands = data->commands->next;
	}
	dup2(temp_in, 0);
	dup2(temp_out, 1);
	close(temp_out);
	close(temp_in);
	waitpid(pid, &status, 0);
	expand_execve(data, status);
	if (open(".redir", O_RDONLY, 0000644) >= 0)
		unlink(".redir");
}
