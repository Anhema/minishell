/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/09 18:26:58 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_data *data)
{
	char	*prompt;
	char	*s;
	int		i;

	if (data->is_redir)
	{
		prompt = "> ";
		return (prompt);
	}
	s = get_dict_value(data->env, "PWD");
	i = 0;
	s = ft_strreplace(s, ft_strjoin("/Users/", data->usr), "~");
	prompt = ft_strjoin(data->usr, ": ");
	prompt = ft_strjoin(prompt, s);
	prompt = ft_strjoin(prompt, " % ");
	free (s);
	return (prompt);
}

void	free_mem(t_data data, char *str)
{
	int	i;

	i = 0;
	free (str);
	if (data.str)
		free (data.str);
	free (data.usr);
	delete_all(data.env);
}

char	*ft_readline(t_data *data)
{
	char			*str;
	struct termios	term;
	struct termios	term_old;
	char			*count;

	tcgetattr(STDIN_FILENO, &term_old);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	ft_signals();
	str = readline(get_prompt(data));
	if (!str)
	{
		count = getcwd(NULL, 0);
		printf("\033[1A");
		printf("\033[%zuC", ft_strlen(count) - 2);
		printf(" exit\n");
		free (count);
		exit(0);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term_old);
	return (str);
}

char	*cd_exit_syntax(t_data *data, char *str)
{
	if (check_syntax(data->commands))
	{
		str = ft_readline(data);
		return (str);
	}
	if (ft_str_equals(data->commands->key, "exit") && !data->commands->next)
		ft_exit(str, data);
	if (ft_str_equals(data->commands->key, "cd") && !data->commands->next)
	{
		*data = _cd(data->commands->value, data->usr, data);
		str = ft_readline(data);
		return (str);
	}
	if (ft_str_equals(data->commands->key, "export") && !data->commands->next)
	{
		data->env = ft_export(data);
		return (ft_readline(data));
	}
	if (ft_str_equals(data->commands->key, "unset") && !data->commands->next)
	{
		data->env = ft_unset(data->env, ft_split(data->commands->value, ' '));
		str = ft_readline(data);
		return (str);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	extern int	g_stats;
	char		*str;
	t_data		*data;

	(void)argc;
	(void)argv;
	g_stats = 0;
	data = malloc(sizeof(t_data));
	data->env = create_env(envp);
	data->usr = get_dict_value(data->env, "USER");
	data->is_redir = 0;
	data->str = NULL;
	str = ft_readline(data);
	while (1)
	{
		ft_history(str);
		str = remove_spaces(str);
		str = replace_redirections(str);
		if (!str || ft_str_equals(str, ""))
		{
			str = ft_readline(data);
			continue ;
		}
		*data = get_redirections(*data, str);
		str = data->str;
		data->commands = ft_pipe_parse(str);
		if (data->commands)
		{
			str = cd_exit_syntax(data, str);
			if (str)
				continue ;
		}
		data = redirections(data, str);
		str = ft_readline(data);
	}
	return (0);
}
