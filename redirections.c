/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:01 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/18 18:38:48 by aherrero         ###   ########.fr       */
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
		str = ft_strjoin(str, temp->value);
		n = str[ft_strlen(str) - 1];
		if (n == -128 || n == -125 || n == -127 || n == -126)
		{
			if (temp->next)
				printf("minishell: syntax error near unexpected token `|'\n");
			else
				printf("minishell: syntax error near unexpected token `newline'\n");
			free(str);
			return (1);
		}
		temp = temp->next;
	}
	free (str);
	return (0);
}

t_dict	**get_redirections(t_data data)
{
	t_dict	*temp;
	t_dict	*new;
	t_dict	**result;
	int		i;
	int		j;
	int		k;
	int		kk;
	int		n;
	int		result_count;;
	char	*value;

	temp = data.commands;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	result = (t_dict **)malloc(sizeof(t_dict *) * (i + 1));
	if (!result)
		return (NULL);
	ft_memset(result, 0, sizeof(t_dict *) * (i + 1));
	result_count = 0;
	temp = data.commands;
	while (temp)
	{
		j = 0;
		while (temp->value[j])
		{
			if (temp->value[j] == -128 || temp->value[j] == -125 || temp->value[j] == -126 || temp->value[j] == -127)
			{
				kk = j + 1;
				while (temp->value[kk] == ' ')
					kk++;
				k = kk + 1;
				while (temp->value[k] && temp->value[k] != ' ' && temp->value[k] != -128 && temp->value[k] != -125 && temp->value[k] != -126 && temp->value[k] != -127)
					k++;
				value = (char *)malloc(sizeof(char) * (k - kk) + 1);
				i = (k - kk);
				k = kk;
				n = 0;
				while (i > 0)
				{
					value[n] = temp->value[k];
					n++;
					k++;
					i--;
				}
				value[n] = '\0';
				new = dict_new(ft_itoa(temp->value[j]), value);
				result[result_count] = dict_add_back_repeat(result[result_count], new);
			}
			j++;
		}
		temp = temp->next;
		result_count++;
	}
	return (result);
}