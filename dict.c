/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/19 16:35:45 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*dict_new(char *key, char *value)
{
	t_dict	*list;

	list = malloc(sizeof(t_dict));
	if (list == NULL)
		return (NULL);
	if (!key)
		list->key = NULL;
	else
		list->key = key;
	if (!value)
		list->value = NULL;
	else
		list->value = value;
	list->next = NULL;
	return (list);
}

t_dict	*dict_add_back(t_dict *lst, t_dict *new)
{
	t_dict	*temp;

	temp = lst;
	if (lst == NULL)
		lst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (lst);
}

t_dict	*dict_add_front(t_dict *lst, t_dict *new)
{
	if (lst == NULL)
		lst = new;
	if (lst != NULL && new != NULL)
	{
		new->next = lst;
		lst = new;
	}
	return (lst);
}

t_dict	*del_one(t_dict *dict, char	*key)
{
	t_dict	*temp;
	t_dict	*result;
	t_dict	*new;

	temp = dict;
	result = NULL;
	if (!dict)
		return (NULL);
	else
	{
		while (dict->next != NULL)
		{
			if (ft_str_equals(temp->key, key) == 0)
			{
				new = dict_new(dict->key, dict->value);
				result = dict_add_back(result, new);
			}
			temp = dict->next;
			dict = temp;
		}
	}
	return (result);
}

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
