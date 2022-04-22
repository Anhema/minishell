/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:32 by cbustama          #+#    #+#             */
/*   Updated: 2022/04/21 18:10:28 by cbustama         ###   ########.fr       */
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

char	**ft_sort(char *c)
{
	char	**s;

	if (!c)
		return (NULL);
	s = ft_split(space_front_to_back(c), ' ');
	return (s);
}

char	*ft_history(char *str)
{
	int		i;
	int		fd;
	//char	*s;
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

