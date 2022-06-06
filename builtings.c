/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:49:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/03 19:03:17 by aherrero         ###   ########.fr       */
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

	fd = open(".history", O_RDONLY, 0000644);
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

char	*check_infile(t_data data)
{
	int		i;
	int		n;
	char	*infile;
	int		in;
	char	*str;
	t_dict	*temp;
	t_dict	**redirection;

	if (!data.redirections[0])
		return (NULL);
	redirection = data.redirections;
	i = 0;
	while (redirection[i])
		i++;
	n = 0;
	while (n <= i)
	{
		temp = redirection[n];
		while (temp)
		{
			if (ft_atoi(temp->key) == -127)
			{
				printf("");
				if (open(temp->value, O_RDONLY, 0000644) < 0)
				{
					perror("minishell: No such file or directory\n");
					infile = NULL;
					break ;
				}
				else
					infile = temp->value;
			}
			if (ft_atoi(temp->key) == -126 || data.commands->key[0] == (char)130)
			{
				data.is_redir = 1;
				str = ft_readline(data);
				in = open(".redir", O_WRONLY | O_APPEND | O_CREAT, 0000644);
				while (1)
				{
					if (ft_str_equals(str, temp->value))
						break ;
					if (in < 0)
					{
						perror("minishell: No such file or directory\n");
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
				data.is_redir = 0;
				infile = ".redir";
			}
			temp = temp->next;
		}
		n++;
	}
	return (infile);
}

int	check_outfile(t_data data)
{
	int		i;
	int		n;
	int		outfile;
	t_dict	*temp;
	t_dict	**redirection;

	if (!data.redirections[0])
		return (-1);
	redirection = data.redirections;
	i = 0;
	while (redirection[i])
		i++;
	n = 0;
	while (n <= i)
	{
		temp = redirection[n];
		while (temp)
		{
			if (ft_atoi(temp->key) == -128)
			{
				outfile = open(temp->value, O_WRONLY | O_CREAT, 0000644);
				if (outfile < 0)
				{
					perror("minishell: No such file or directory\n");
					outfile = -1;
					break ;
				}
			}
			if (ft_atoi(temp->key) == -125)
			{
				outfile = open(temp->value, O_WRONLY | O_APPEND | O_CREAT, 0000644);
				if (outfile < 0)
				{
					perror("minishell: No such file or directory\n");
					outfile = -1;
					break ;
				}
			}
			temp = temp->next;
		}
		n++;
	}
	return (outfile);
}

static void	redirections_fd(t_data data, int fd_in, int temp_out)
{
	int		fd[2];
	int		fd_out;
	int		outfile;

	dup2(fd_in, 0);
	close(fd_in);
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

void	redirections(t_data data, char *str)
{
	int		temp_in;
	int		temp_out;
	int		fd_in;
	int		pid;
	char	*infile;

	temp_in = dup(0);
	temp_out = dup(1);
	infile = check_infile(data);
	if (infile)
		fd_in = open(infile, O_RDONLY, 0000644);
	else
		fd_in = dup(temp_in);
	while (data.commands)
	{
		redirections_fd(data, fd_in, temp_out);
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
	if (open(".redir", O_RDONLY, 0000644) >= 0)
		unlink(".redir");
}
