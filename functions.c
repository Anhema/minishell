/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:32 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/09 17:18:52 by aherrero         ###   ########.fr       */
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
		str = "";
		temp = ft_split(space_front_to_back(c[j]), ' ');
		i = 1;
		while (temp[i])
		{
			str = ft_strjoin(str, temp[i]);
			str = ft_strjoin(str, " ");
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
	int			i;
	int			fd;
	char		*dst;
	extern int	g_stats;

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

char	*get_builting(char	*str)
{
	int		i;
	int		j;
	int		n;
	char	c;
	char	*temp;

	c = 0;
	i = 0;
	n = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (n == 0)
		{
			if (str[i] == '\"')
			{
				c = '\"';
				n++;
			}
			if (str[i] == '\'')
			{
				c = '\'';
				n++;
			}
		}
		else if (c && str[i] == c)
		{
			if (n > 0)
				n--;
			else
				n++;
		}
		if (str[i] == ' ')
		{
			if (n == 0)
			{
				j = 0;
				temp = malloc(sizeof(char) * (i + 1));
				while (j < i)
				{
					temp[j] = str[j];
					j++;
				}
				temp[j] = '\0';
				return (temp);
			}
		}
		i++;
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

	c = 0;
	i = 0;
	n = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (n == 0)
		{
			if (str[i] == '\"')
			{
				c = '\"';
				n++;
			}
			if (str[i] == '\'')
			{
				c = '\'';
				n++;
			}
		}
		else if (c && str[i] == c)
		{
			if (n > 0)
				n--;
			else
				n++;
		}
		if (str[i] != c)
		{
			if (str[i] == '>' && str[i + 1] != '>' && n == 0)
				temp[j] = (unsigned char)128;
			else if (str[i] == '<' && str[i + 1] != '<' && n == 0)
				temp[j] = (unsigned char)129;
			else if (str[i] == '<' && str[i + 1] == '<' && n == 0)
			{
				temp[j] = (unsigned char)130;
				i++;
			}
			else if (str[i] == '>' && str[i + 1] == '>' && n == 0)
			{
				temp[j] = (unsigned char)131;
				i++;
			}
			else
				temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*get_arguments(char	*str)
{
	int		i;
	int		j;
	int		n;
	char	c;
	char	*temp;

	c = 0;
	i = 0;
	n = 0;
	while (str[i])
	{
		if (n == 0)
		{
			if (str[i] == '\"')
			{
				c = '\"';
				n++;
			}
			if (str[i] == '\'')
			{
				c = '\'';
				n++;
			}
		}
		else if (c && str[i] == c)
		{
			if (n > 0)
				n--;
			else
				n++;
		}
		if (str[i] == ' ')
		{
			if (n == 0)
			{
				j = 0;
				i++;
				temp = malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
				while (j <= (int)(ft_strlen(str) - i))
				{
					temp[j] = str[j + i];
					j++;
				}
				return (temp);
			}
		}
		i++;
	}
	return (NULL);
}

char	*remove_spaces(char	*str)
{
	int		i;
	int		j;
	int		jj;
	int		n;
	char	c;
	char	*temp;
	char	*aux;

	c = 0;
	i = 0;
	n = 0;
	while (str[i])
	{
		if (n == 0)
		{
			if (str[i] == '\"')
			{
				c = '\"';
				n++;
			}
			if (str[i] == '\'')
			{
				c = '\'';
				n++;
			}
		}
		else if (c && str[i] == c)
		{
			if (n > 0)
				n--;
			else
				n++;
		}
		if (str[i] == ' ' && n == 0)
		{
			if (str[i + 1] == ' ')
			{
				j = i;
				jj = 0;
				while (str[j] == ' ')
				{
					j++;
					jj++;
				}
				jj = i + jj;
				temp = (char *)calloc(i + 1, sizeof(char));
				temp = ft_memset(temp, 0, i + 1);
				aux = (char *)calloc((int)ft_strlen(str) - jj, sizeof(char));
				aux = ft_memset(aux, 0, (int)ft_strlen(str) - jj);
				j = 0;
				while (j < i)
				{
					temp[j] = str[j];
					j++;
				}
				j = 0;
				while (str[jj])
				{
					aux[j] = str[jj];
					j++;
					jj++;
				}		
				str = ft_strjoin(temp, " ");
				str = ft_strjoin(str, aux);
				i = 0;
			}
		}
		i++;
	}
	return (str);
}

t_dict	*add_command(char *line, t_dict *command)
{
	char	*built;
	char	*arguments;
	t_dict	*new;

	line = space_front_to_back(line);
	built = get_builting(line);
	if (!built)
		return (NULL);
	arguments = get_arguments(line);
	built = remove_quotes(built);
	if (arguments)
		arguments = remove_quotes(arguments);
	new = dict_new(built, arguments);
	command = dict_add_back(command, new);
	return (command);
}

t_dict	*ft_pipe_parse(char *str)
{
	int		i;
	int		j;
	int		jj;
	int		last;
	char	c;
	int		n;
	char	*temp;
	t_dict	*commands;

	i = 0;
	last = 0;
	n = 0;
	c = 0;
	commands = NULL;
	while (str[i] != '\0')
	{
		if (n == 0)
		{
			if (str[i] == '\"')
			{
				c = '\"';
				n++;
			}
			if (str[i] == '\'')
			{
				c = '\'';
				n++;
			}
		}
		else if (c && str[i] == c)
		{
			if (n > 0)
				n--;
			else
				n++;
		}
		if (str[i] == '|')
		{
			if (n == 0)
			{
				j = last;
				temp = malloc(sizeof(char) * (i - last) + 1);
				jj = 0;
				while (j < i)
				{
					temp[jj] = str[j];
					j++;
					jj++;
				}
				temp[jj] = '\0';
				last = i + 1;
				commands = add_command(temp, commands);
			}
		}
		i++;
	}
	if (n == 0)
	{
		j = 0;
		temp = malloc(sizeof(char) * (i - last) + 1);
		while (j < i - last)
		{
			temp[j] = str[j + last];
			j++;
		}
		temp[j] = '\0';
		commands = add_command(temp, commands);
	}
	else
	{
		printf("minishell: syntax error unclosed quotes\n");
		commands = NULL;
	}
	return (commands);
}
