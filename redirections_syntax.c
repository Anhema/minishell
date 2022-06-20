/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:09:05 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/20 18:43:58 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_redirections_aux(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (0);
	}
	if (i > 0 && (str[i] == '>' && str[i + 1] == '>' && str[i - 1] == '>'))
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		return (0);
	}
	if (i > 0)
	{
		if (str[i] == '>' && str[i + 1] == '>' && str[i - 1] == '>')
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			return (0);
		}
		if (str[i] == '<' && str[i + 1] == '<' && str[i - 1] == '<')
		{
			printf("minishell: syntax error near unexpected token `<'\n");
			return (0);
		}				
	}
	return (1);
}

char	*syntax_redirections(char *str)
{
	int		i;
	int		n;
	char	c;

	i = -1;
	n = 0;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		n = aux_aux(n, &c, str, i);
		if (n == 0)
		{
			if (!syntax_redirections_aux(str, i))
				return (NULL);
		}
	}
	return (str);
}

char	replace_char(char *str, int i, int n)
{
	char	c;

	if (str[i] == '>' && str[i + 1] != '>' && n == 0)
		c = (unsigned char)128;
	else if (str[i] == '<' && str[i + 1] != '<' && n == 0)
		c = (unsigned char)129;
	else if (str[i] == '<' && str[i + 1] == '<' && n == 0)
	{
		c = (unsigned char)130;
		i++;
	}
	else if (str[i] == '>' && str[i + 1] == '>' && n == 0)
	{
		c = (unsigned char)131;
		i++;
	}
	else
		c = str[i];
	return (c);
}

int	replace_aux(int n, char *c, char *str, int j)
{
	if (n == 0)
	{
		if (str[j] == '\"')
		{
			*c = '\"';
			n++;
		}
		if (str[j] == '\'')
		{
			*c = '\'';
			n++;
		}
	}
	else if (*c && str[j] == *c)
	{
		if (n > 0)
			n--;
		else
			n++;
	}	
	return (n);
}

char	*replace_redirections(char *str)
{
	char	*temp;
	int		i;
	int		j;
	char	c;
	int		n;

	j = 0;
	n = 0;
	i = -1;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_memset(temp, 0, sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i])
	{
		n = replace_aux(n, &c, str, j);
		if (n == 0)
		{
			temp[j] = replace_char(str, i, n);
			if (temp[j] == -126 || temp[j] == -125)
				i++;
		}
		else
			temp[j] = str[i];
		j++;
	}
	if (ft_str_equals(temp, "") || !temp)
	{
		free (temp);
		return (str);
	}
	free (str);
	return (temp);
}
