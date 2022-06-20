/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:01 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/20 17:40:49 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	aux(char p, int n)
{
	char	c;

	c = 0;
	if (n == 0)
	{
		if (p == '\"' || p == '\'')
		{
			c = p;
			n++;
		}
	}
	else if (c && p == c)
	{
		if (n > 0)
		{
			c = 0;
			n--;
		}
		else
			n++;
	}
	return (c);
}

int	check_syntax(t_dict *commands)
{
	char	*str;
	char	*str_temp;
	t_dict	*temp;
	int		n;

	temp = commands;
	while (temp)
	{
		str_temp = ft_strjoin(temp->key, " ");
		if (temp->value)
			str = ft_strjoin(str_temp, temp->value);
		n = str[ft_strlen(str) - 1];
		if (n == -128 || n == -125 || n == -127 || n == -126)
		{
			if (temp->next)
				printf("minishell: syntax error near unexpected token `|'\n");
			else
				printf(
					"minishell: syntax error near unexpected token `newline'\n");
			// free (str);
			// free (str_temp);
			return (1);
		}
		temp = temp->next;
	}
	// if (str)
	// 	free (str);
	// if (str_temp)
	// 	free (str_temp);
	return (0);
}

t_dict	**get_n_commands(char *str)
{
	int		i;
	int		j;
	char	c;
	int		n;
	t_dict	**result;

	j = 1;
	n = 0;
	c = 0;
	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '|')
			j++;
		i++;
	}
	result = (t_dict **)malloc(sizeof(t_dict *) * (j + 1));
	ft_memset(result, 0, sizeof(t_dict *) * (j + 1));
	return (result);
}

t_dict	**add_to_dict(t_dict **result, int j, int count, char *str)
{
	char	*value;
	int		i;
	int		n;
	int		k;
	int		kk;

	kk = j + 1;
	while (str[kk] == ' ')
		kk++;
	k = kk;
	while (str[k] != '\0' && str[k] != ' ' && str[k] != -128 && str[k] != -125
		&& str[k] != -126 && str[k] != -127 && str[k] != '|')
		k++;
	value = (char *)malloc(sizeof(char) * (k - kk) + 1);
	i = (k - kk);
	k = kk;
	n = 0;
	while (i-- > 0)
		value[n++] = str[k++];
	value[n] = '\0';
	result[count] = dict_add_back_repeat
		(result[count], dict_new(ft_itoa(str[j]), ft_strdup(value)));
	free(value);
	return (result);
}

t_data	*get_redirections(t_data *data, char *str)
{
	int		j;
	int		n;
	char	c;
	int		count;

	data->redirections = get_n_commands(str);
	j = -1;
	count = 0;
	n = 0;
	while (str[++j] && !ft_str_equals(str, ""))
	{
		n = aux_aux(n, &c, str, j);
		if (n == 0 && str[j] == '|')
			count++;
		if (str[j] == -128 || str[j] == -125
			|| str[j] == -126 || str[j] == -127)
		{
			data->redirections = add_to_dict(data->redirections, j, count, str);
			str = modify_str(str, j);
			j = 0;
		}
	}
	data->str = ft_strdup(str);
	free(str);
	return (data);
}
