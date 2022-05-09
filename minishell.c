/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/09 17:07:05 by aherrero         ###   ########.fr       */
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

char	*get_prompt(char *usr)
{
	char	*prompt;
	char	*s;
	int		i;

	s = getcwd(NULL, 0);
	i = 0;
	s = ft_strreplace(s, ft_strjoin("/Users/", usr), "~");
	prompt = ft_strjoin(usr, ": ");
	prompt = ft_strjoin(prompt, s);
	prompt = ft_strjoin(prompt, " % ");
	free (s);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		i;
	t_data	data;

	i = 0;
	(void)argc;
	(void)argv;
	data.env = create_env(envp);
	data.usr = get_dict_value(data.env, "USER");
	str = readline(get_prompt(data.usr));
	while (1)
	{
		ft_history(str);
		//data.commands = ft_sort(ft_split(str, '|'));
		data.commands = ft_pipe_parse(str);
		//print_dict(data.commands);
		if (data.commands)
		{
			if (ft_str_equals(str, "exit"))
				ft_exit(str);
			else if (ft_str_equals(data.commands->key, "pwd"))
				ft_pwd();
			else if (ft_str_equals(data.commands->key, "echo"))
				ft_echo(data);
			else if (ft_str_equals(data.commands->key, "env")
				&& !data.commands->value)
				print_dict(data.env);
			else if (ft_str_equals(data.commands->key, "history"))
				ft_read_file(".history", 0);
			else if (ft_str_equals(data.commands->key, "cd"))
				data = _cd(str, data.usr, data);
			else if (ft_str_equals(data.commands->key, "export"))
				data.env = ft_export(data.env, ft_split(str, ' '));
			else if (ft_str_equals(data.commands->key, "unset"))
				data.env = ft_unset(data.env, ft_split(str, ' '));
			else
				ft_execve(data);
				//printf("command not found: %s\n", str);
		}
		str = readline(get_prompt(data.usr));
	}
	return (0);
}
