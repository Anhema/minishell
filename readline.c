/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:01:00 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/09 19:06:12 by aherrero         ###   ########.fr       */
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
