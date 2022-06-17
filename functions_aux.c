/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:35:35 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/16 22:36:00 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arguments(char	*str)
{
	int		i;
	int		j;
	int		n;
	char	c;
	char	*temp;

	i = -1;
	n = 0;
	while (str[++i])
	{
		n = aux_aux(n, &c, str, i);
		if (str[i] == ' ')
		{
			if (n == 0)
			{
				j = -1;
				i++;
				temp = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
				while (++j <= (int)(ft_strlen(str) - i))
					temp[j] = str[j + i];
				return (temp);
			}
		}
	}
	return (NULL);
}

char	*remove_spaces(char	*str)
{
	int		i;
	int		n;
	char	c;

	c = 0;
	i = 0;
	n = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		n = aux_aux(n, &c, str, i);
		if (str[i] == ' ' && n == 0)
		{
			if (str[i + 1] == ' ')
			{
				str = remove_spaces_aux(str, i);
				i = 0;
			}
		}
		i++;
	}
	return (str);
}

t_dict	*ft_pipe_parse(char *str)
{
	int		i;
	int		last;
	char	c;
	int		n;
	t_dict	*commands;

	i = -1;
	last = 0;
	n = 0;
	commands = NULL;
	while (str[++i] != '\0')
	{
		n = aux_aux(n, &c, str, i);
		if (str[i] == '|' && n == 0)
			commands = ft_pipe_parse_add(str, &last, commands, i);
	}
	if (n == 0)
		commands = ft_pipe_parse_end(str, last, commands, i);
	else
	{
		printf("minishell: syntax error unclosed quotes\n");
		commands = NULL;
	}
	return (commands);
}

char	*check_quotes(char *str)
{
	int		i;
	int		n;
	char	c;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		n = aux_aux(n, &c, str, i);
		i++;
	}
	if (n > 0)
	{
		printf("minishell: syntax error unclosed quotes\n");
		return (NULL);
	}
	return (str);
}
