/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/22 18:07:51 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_exit_syntax(t_data *data, char *str)
{
	char	**_unset;

	if (ft_str_equals(data->commands->key, "exit") && !data->commands->next)
		ft_exit(str, data);
	if (ft_str_equals(data->commands->key, "cd") && !data->commands->next)
	{
		data = _cd(data->commands->value, data->usr, data);
		return (ft_readline(data));
	}
	if (ft_str_equals(data->commands->key, "export") && !data->commands->next)
	{
		data->env = ft_export(data);
		return (ft_readline(data));
	}
	if (ft_str_equals(data->commands->key, "unset") && !data->commands->next)
	{
		_unset = NULL;
		if (data->commands->value)
			_unset = ft_split(data->commands->value, ' ');
		data->env = ft_unset(data->env, _unset);
		if (_unset)
			free_split_double(_unset);
		str = ft_readline(data);
		return (str);
	}
	return (NULL);
}

char	*minishell_loop(t_data *data, char *str)
{
	ft_history(str);
	str = replace_redirections
		(syntax_redirections(remove_spaces(check_quotes(str))));
	if (!str || ft_str_equals(str, ""))
	{
		free (str);
		str = ft_readline(data);
		return (str);
	}
	data = get_redirections(data, str);
	data->str = expand(data);
	str = data->str;
	// if (!data->str || ft_str_equals(data->str, ""))
	// {
	// 	str = ft_readline(data);
	// 	return (str);
	// }
	data->commands = ft_pipe_parse(data->str);
	if (data->commands)
	{
		data->str = cd_exit_syntax(data, data->str);
		if (data->str)
			return (data->str);
	}
	data = redirections(data);
	if (str)
		free(str);
	str = ft_readline(data);
	return (str);
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
	data->usr = ft_strdup(get_dict_value(data->env, "USER"));
	data->is_redir = 0;
	data->commands = NULL;
	data->prompt = NULL;
	data->redirections = NULL;
	data->str = NULL;
	data->fd[0] = 0;
	data->fd[1] = 1;
	str = ft_readline(data);
	while (1)
		str = minishell_loop(data, str);
	return (0);
}
