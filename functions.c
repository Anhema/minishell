/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:32 by cbustama          #+#    #+#             */
/*   Updated: 2022/04/26 16:51:49 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_front_to_back(char *c)
{
	int		i;
	int		j;
	char	*str;
	int		fill;

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
	str = (char *)malloc(sizeof(char) * (j + 1));
	j--;
	while (j >= 0)
	{
		str[j] = c[fill];
		j--;
		i++;
		fill--;
	}
	str[i] = '\0';
	return (str);
}

t_dict	*ft_sort(char **c)
{
	t_dict	*command;
	t_dict	*new;
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
		str = NULL;
		temp = ft_split(space_front_to_back(c[j]), ' ');
		i = 1;
		while (temp[i])
		{
			str = ft_strjoin(str, temp[i]);
			i++;
		}
		new = dict_new(temp[0], str);
		command = dict_add_back(command, new);
		j++;
	}
	return (command);
}

char	*ft_history(char *str)
{
	int		i;
	int		fd;
	char	*dst;

	i = -1;
	if (str)
		add_history(str);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!dst)
		return (NULL);
	while (str[++i])
		dst[i] = str[i];
	dst[i] = '\n';
	dst[++i] = '\0';
	fd = open(".history", O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	write(fd, dst, ft_strlen(dst));
	close (fd);
	return (dst);
}

