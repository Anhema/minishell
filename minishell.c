/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/26 18:01:18 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	struct termios	term_old;

	tcgetattr(STDIN_FILENO, &term_old);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	ft_signals();
	str = readline(get_prompt(data));
	if (!str)
	{
		printf("\033[1A");
		printf("\033[40C");
		printf(" exit\n");
		exit(-1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term_old);
	return (str);
}

char	*cd_exit_syntax(t_data data, char *str)
{
	if (ft_str_equals(str, "exit"))
		ft_exit(str);
	if (ft_str_equals(data.commands->key, "cd") && !data.commands->next)
	{
		data = _cd(data.commands->value, data.usr, data);
		str = ft_readline(data);
		return (str);
	}
	if (check_syntax(data.commands))
	{
		str = ft_readline(data);
		return (str);
	}
	if (ft_str_equals(data.commands->key, "export") && !data.commands->next)
	{
		data.env = ft_export(data);
		str = ft_readline(data);
		return (str);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = create_env(envp);
	data.usr = get_dict_value(data.env, "USER");
	str = ft_readline(data);
	while (1)
	{
		ft_history(str);
		data.commands = ft_pipe_parse(str);
		if (!data.commands)
		{
			str = ft_readline(data);
			continue ;
		}
		str = cd_exit_syntax(data, str);
		if (str)
			continue ;
		data = get_redirections(data);
		redirections(data, str);
		str = ft_readline(data);
	}
	return (0);
}
