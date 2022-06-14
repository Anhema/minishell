/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/14 17:09:55 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *str, t_data *data)
{
	int		i;
	char	c;
	char	*tmp;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		c = continue_expand(c, i, str);
		if (str[i] == '$' && c != '\'')
		{
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
			{
				i++;
				continue ;
			}
			tmp = continue_expand_two(str, i, tmp, data);
			str = tmp;
			i = 0;
		}
		i++;
	}
	return (str);
}

void	continue_echo(char *str, char *str_temp, int n, int i)
{
	while (str[i] != ' ')
	{
		if (str[i] != 'n')
		{
			n = 1;
			break ;
		}
		i++;
	}
	if (n == 1)
		printf("");
	else
	{
		str_temp = malloc(sizeof(char) * (ft_strlen(str) - i));
		i++;
		n = 0;
		while (str[i])
		{
			str_temp[n] = str[i];
			n++;
			i++;
		}
		str_temp[n] = '\0';
		printf("%s", str_temp);
	}	
}

void	ft_echo(t_data *data)
{
	char		*str;
	char		*str_temp;
	int			i;
	int			n;
	extern int	g_stats;

	str = data->commands->value;
	str_temp = NULL;
	g_stats = 0;
	if (!str)
	{
		printf("\n");
		return ;
	}
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		n = 0;
		continue_echo(str, str_temp, n, i);
	}
	else
		printf("%s\n", str);
}
