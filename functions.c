/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:32 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/17 16:14:12 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_front_to_back(char *c)
{
	int		i;
	int		j;
	int		fill;
	char	*str;

	if (!c)
		return (NULL);
	i = 0;
	while (c[i] == 32)
		i++;
	j = ft_strlen(c);
	while (j > 0 && c[j - 1] == ' ')
		j--;
	if (j == 0)
		return (NULL);
	fill = j - 1;
	j = (j - i);
	i = 0;
	str = space_front_to_back_aux(c, i, j, fill);
	free (c);
	return (str);
}

t_dict	*ft_sort(char **c)
{
	t_dict	*command;
	char	**temp;
	char	*str;
	int		i;
	int		j;

	if (!c)
		return (NULL);
	command = NULL;
	j = 0;
	while (c[j])
	{
		str = "";
		temp = ft_split(space_front_to_back(c[j]), ' ');
		i = 1;
		while (temp[i])
		{
			str = ft_strjoin(str, temp[i]);
			str = ft_strjoin(str, " ");
			i++;
		}
		command = dict_add_back(command, dict_new(temp[0], str));
		j++;
	}
	return (command);
}

void	ft_history(char *str)
{
	extern int	g_stats;

	if (str)
		add_history(str);
}

char	*get_builting(char	*str)
{
	int		i;
	int		j;
	int		n;
	char	c;
	char	*temp;

	i = -1;
	n = 0;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		n = aux_aux(n, &c, str, i);
		if (str[i] == ' ' && n == 0)
		{
			j = -1;
			temp = malloc(sizeof(char) * (i + 1));
			while (++j < i)
				temp[j] = str[j];
			temp[j] = '\0';
			return (temp);
		}
	}
	return (str);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		n;
	char	c;
	char	*temp;

	i = -1;
	n = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i])
	{
		c = remove_quotes_get_c(str, &n, c, i);
		if (str[i] != c)
		{
			if ((str[i] == '>' || str[i] == '<') && n == 0)
				remove_quotes_aux(str, temp, &i, j);
			else
				temp[j] = str[i];
			j++;
		}
	}
	temp[j] = '\0';
	free (str);
	return (temp);
}
