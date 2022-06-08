/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:08:01 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/06 20:27:16 by cbustama         ###   ########.fr       */
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

t_data	get_redirections(t_data *data, char *str)
{
	t_dict	*temp;
	t_dict	*new;
	t_dict	**result;
	int		i;
	int		j;
	int		k;
	int		kk;
	int		n;
	int		result_count;
	char	*value;

	(void)str;
	temp = data->commands;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	result = (t_dict **)malloc(sizeof(t_dict *) * (i + 1));
	if (!result)
		return (*data);
	ft_memset(result, 0, sizeof(t_dict *) * (i + 1));
	result_count = 0;
	temp = data->commands;
	while (temp)
	{
		if (temp->key[0] == -128 || temp->key[0] == -125
			|| temp->key[0] == -126 || temp->key[0] == -127)
		{
			temp->value = space_front_to_back(temp->value);
			k = 0;
			while (temp->value[k] != '\0' && temp->value[k] != ' '
				&& temp->value[k] != -128 && temp->value[k] != -125
				&& temp->value[k] != -126 && temp->value[k] != -127)
				k++;
			value = (char *)malloc(sizeof(char) * (k));
			i = k;
			n = 0;
			while (i > 0)
			{
				value[n] = temp->value[n];
				n++;
				i--;
			}
			value[n] = '\0';
			printf("--%s--\n", value);
			new = dict_new(ft_itoa(temp->key[0]), value);
			result[result_count]
				= dict_add_back_repeat(result[result_count], new);
			value = ft_strstr(temp->value, value);
			value = ft_strreplace(temp->value, value, "");
			temp->value = value;
			j = 0;
		}
		if (temp->value)
		{
			j = 0;
			while (temp->value[j])
			{
				if (temp->value[j] == -128 || temp->value[j] == -125
					|| temp->value[j] == -126 || temp->value[j] == -127)
				{
					kk = j + 1;
					while (temp->value[kk] == ' ')
						kk++;
					k = kk + 1;
					while (temp->value[k] != '\0' && temp->value[k] != ' '
						&& temp->value[k] != -128 && temp->value[k] != -125
						&& temp->value[k] != -126 && temp->value[k] != -127)
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
					result[result_count]
						= dict_add_back_repeat(result[result_count], new);
					value = malloc(sizeof(char) * ((k - j)));
					kk = 0;
					i = j;
					while (kk < (k - j))
					{
						value[kk] = temp->value[i];
						kk++;
						i++;
					}
					value = ft_strstr(temp->value, value);
					value = ft_strreplace(temp->value, value, "");
					temp->value = value;
					j--;
				}
				j++;
			}
		}
		result_count++;
		temp = temp->next;
	}
	data->redirections = result;
	return (*data);
}