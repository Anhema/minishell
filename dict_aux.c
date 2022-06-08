/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/08 17:35:39 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dict_value(t_dict *dict, char	*key)
{
	t_dict	*temp;

	temp = dict;
	if (!dict)
		return (NULL);
	else
	{
		while (dict != NULL)
		{
			if (ft_str_equals(temp->key, key) == 1)
				return (temp->value);
			temp = dict->next;
			dict = temp;
		}
	}
	return (NULL);
}

void	delete_all(t_dict *dict)
{
	if (!dict->next)
		delete_all(dict->next);
	free(dict);
}
