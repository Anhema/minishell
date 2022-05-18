/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/18 18:42:01 by aherrero         ###   ########.fr       */
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

char	*get_prompt(t_data data)
{
	char	*prompt;
	char	*s;
	int		i;

	s = get_dict_value(data.env, "PWD");
	i = 0;
	s = ft_strreplace(s, ft_strjoin("/Users/", data.usr), "~");
	prompt = ft_strjoin(data.usr, ": ");
	prompt = ft_strjoin(prompt, s);
	prompt = ft_strjoin(prompt, " % ");
	free (s);
	return (prompt);
}

char	*ft_readline(t_data data)
{
	char			*str;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	ft_signals();
	str = readline(get_prompt(data));
	if (!str)
	{
		// printf("\033[1A");
		// printf("\033[10C");
		printf("\rexit\n");
		exit(-1);
	}
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		i;
	int		fd[3];
	t_data	data;
	pid_t	pid;

	i = 0;
	(void)argc;
	(void)argv;
	data.env = create_env(envp);
	data.usr = get_dict_value(data.env, "USER");
	str = ft_readline(data);
	while (1)
	{
		ft_history(str);
		data.commands = ft_pipe_parse(str);
		// print_dict(data.commands);
		//printf("--%c--\n", 128);
		if (!data.commands)
		{
			str = ft_readline(data);
			continue ;
		}
		if (ft_str_equals(str, "exit"))
			ft_exit(str);
		if (ft_str_equals(data.commands->key, "cd") && data.commands->next == NULL)
		{
			data = _cd(data.commands->value, data.usr, data);
			str = ft_readline(data);
			continue ;
		}
		if (check_syntax(data.commands))
		{
			str = ft_readline(data);
			continue ;
		}
		data.redirections = get_redirections(data);
		i = 0;
		while (data.redirections[i] && data.redirections)
		{
			print_dict(data.redirections[i]);
			printf("---\n");
			i++;
		}
		while (data.commands)
		{
			if ((pid = fork()) == -1)
				perror("fork error");
			else if (pid == 0)
			{
				if (pipe(fd) == -1)
					break ;
				if (data.commands->next)
				{
					dup2(fd[1], STDOUT_FILENO);
					dup2(fd[0], STDIN_FILENO);
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
						data.env = ft_export(data.env, ft_split(str, ' '));
					else if (ft_str_equals(data.commands->key, "unset"))
						data.env = ft_unset(data.env, ft_split(str, ' '));
					else
						ft_execve(data);
					close(fd[0]);
					close(fd[1]);
				}
				else
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
						data = _cd(data.commands->value, data.usr, data);
					else if (ft_str_equals(data.commands->key, "export"))
						data.env = ft_export(data.env, ft_split(str, ' '));
					else if (ft_str_equals(data.commands->key, "unset"))
						data.env = ft_unset(data.env, ft_split(str, ' '));
					else
						ft_execve(data);
				}
				return (0);
			}
			waitpid(pid, NULL, 0);
			data.commands = data.commands->next;
		}
		str = ft_readline(data);
	}
	return (0);
}
