/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:49:58 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/07 21:30:20 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_stats;

void	ft_pwd(void)
{
	char	*s;

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
	printf("%s vaue\n", data->commands->value);
	if (data->commands->value)
	{
		while (data->commands->value[++i])
		{
			if (data->commands->value[i] == '-')
				continue ;
			if (data->commands->value[i] < 47
				|| data->commands->value[i] > 57)
			{
				printf("exit: %s: numeric argument required\n", data->commands->value);
				g_stats = 255;
				exit(255);
			}
		}
		n = ft_magic_nbr(n, data);
		/*if (n > 256)
			n = n - 256 ;
		if (n < 0)
			n = 256 + n;
		else if (n == 256)
			n = 0;*/
		free(str);
		printf("esto es n  ==== %d\n", n);
		g_stats = n;
		exit (n);

	}
	g_stats = 0;
	free(str);
	exit(0);
}

void	builtings(t_data *data, char *str)
{
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
	else if (ft_str_equals(data->commands->key, "export"))
		data->env = ft_export(data);
	else if (ft_str_equals(data->commands->key, "unset"))
		data->env = ft_unset(data->env, ft_split(str, ' '));
	else
	{
		continue_signal();
		ft_execve(data);
	}
}

char	*check_infile(t_data *data)
{
	int		i;
	int		n;
	char	*infile;
	int		in;
	char	*str;
	t_dict	*temp;
	t_dict	**redirection;

	if (!data->redirections[0])
		return (NULL);
	redirection = data->redirections;
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
					perror("minishell:");
					infile = NULL;
					break ;
				}
				else
					infile = temp->value;
			}
			if (ft_atoi(temp->key) == -126 || data->commands->key[0] == (char)130)
			{
				data->is_redir = 1;
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
				data->is_redir = 0;
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

void	redirections(t_data *data, char *str)
{
	int		temp_in;
	int		temp_out;
	int		fd_in;
	int		pid;
	char	*infile;
	int		status;

	temp_in = dup(0);
	temp_out = dup(1);
	infile = check_infile(data);
	if (infile)
		fd_in = open(infile, O_RDONLY, 0000644);
	else
		fd_in = dup(temp_in);
	while (data->commands)
	{
		redirections_fd(*data, fd_in, temp_out);
		pid = fork();
		if (pid == 0)
		{
			builtings(data, str);
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
