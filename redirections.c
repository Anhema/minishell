/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:01 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/09 17:15:38 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_dict *commands)
{
	char	*str;
	t_dict	*temp;
	int		n;

	temp = commands;
	while (temp)
	{
		str = ft_strjoin(temp->key, " ");
		if (temp->value)
			str = ft_strjoin(str, temp->value);
		n = str[ft_strlen(str) - 1];
		if (n == -128 || n == -125 || n == -127 || n == -126)
		{
			if (temp->next)
				printf("minishell: syntax error near unexpected token `|'\n");
			else
				printf(
					"minishell: syntax error near unexpected token `newline'\n");
			free(str);
			return (1);
		}
		temp = temp->next;
	}
	free (str);
	return (0);
}

t_dict	**get_n_commands(char *str)
{
	int		i;
	int		j;
	int		n;
	t_dict	**result;
	char	c;

	j = 1;
	n = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
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
				j++;
		}
		i++;
	}
	result = (t_dict **)malloc(sizeof(t_dict *) * (j + 1));
	ft_memset(result, 0, sizeof(t_dict *) * (j + 1));
	return (result);
}

char	*replace_redirections(char *str)
{
	char	*temp;
	int		i;
	int		j;
	int		n;
	char	c;

	i = 0;
	j = 0;
	n = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_memset(temp, 0, sizeof(char) * (ft_strlen(str) + 1));
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
		if (n == 0)
		{
			if (str[i] == '>' && str[i + 1] == '<' && n == 0)
			{
				printf("minishell: syntax error near unexpected token `<'\n");
				return (NULL);
			}
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
		else
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	return (temp);
}

t_data	get_redirections(t_data data, char *str)
{
	t_dict	*new;
	t_dict	**result;
	int		i;
	int		j;
	int		k;
	int		kk;
	int		closed;
	int		n;
	int		result_count;
	char	*value;
	char	*value_aux;
	char	c;

	result = get_n_commands(str);
	j = 0;
	i = 0;
	closed = 0;
	n = 0;
	result_count = 0;
	while (str[j])
	{
		if (closed == 0)
		{
			if (str[j] == '\"')
			{
				c = '\"';
				n++;
			}
			if (str[j] == '\'')
			{
				c = '\'';
				n++;
			}
		}
		else if (c && str[i] == c)
		{
			if (closed > 0)
				closed--;
			else
				closed++;
		}
		if (n == 0 && str[j] == '|')
			result_count++;
		if (str[j] == -128 || str[j] == -125
			|| str[j] == -126 || str[j] == -127)
		{
			kk = j + 1;
			while (str[kk] == ' ')
				kk++;
			k = kk;
			while (str[k] != '\0' && str[k] != ' '
				&& str[k] != -128 && str[k] != -125
				&& str[k] != -126 && str[k] != -127)
				k++;
			value = (char *)malloc(sizeof(char) * (k - kk) + 1);
			i = (k - kk);
			k = kk;
			n = 0;
			while (i > 0)
			{
				value[n] = str[k];
				n++;
				k++;
				i--;
			}
			value[n] = '\0';
			new = dict_new(ft_itoa(str[j]), value);
			result[result_count]
				= dict_add_back_repeat(result[result_count], new);
			if (j == 0)
			{
				if (!str[k])
				{
					str = "";
					break ;
				}
				value_aux = malloc(sizeof(char) * ((int)ft_strlen(str) - k) + 1);
				ft_memset(value_aux, 0, sizeof(char) * ((int)ft_strlen(str) - k) + 1);
				kk = 0;
				while (str[k])
				{
					value_aux[kk] = str[k];
					kk++;
					k++;
				}
				str = value_aux;
				j = 0;
			}
			else
			{
				value = malloc(sizeof(char) * (j + 1));
				ft_memset(value, 0, sizeof(char) * (j + 1));
				kk = 0;
				while (kk < j)
				{
					value[kk] = str[kk];
					kk++;
				}
				value_aux = malloc(sizeof(char) * ((int)ft_strlen(str) - k) + 1);
				ft_memset(value_aux, 0, sizeof(char) * ((int)ft_strlen(str) - k) + 1);
				kk = 0;
				while (str[k])
				{
					value_aux[kk] = str[k];
					kk++;
					k++;
				}
				str = ft_strjoin(value, value_aux);
				j = 0;
			}
		}
		j++;
	}
	data.redirections = result;
	data.str = str;
	return (data);
}