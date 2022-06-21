/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:58:19 by cbustama          #+#    #+#             */
/*   Updated: 2022/06/21 21:18:48 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	continue_expand(char c, int i, char *str)
{
	int	q;

	q = 0;
	if (q == 0)
	{
		if (str[i] == '\"')
		{
			c = '\"';
			q++;
		}
		if (str[i] == '\'')
		{
			c = '\'';
			q++;
		}
	}
	else if (c && str[i] == c)
	{
		if (q > 0)
			q--;
		else
			q++;
	}
	return (c);
}

static int	get_j(char *str, int j)
{
	int	n;

	n = j;
	while (str[j])
	{
		if (str[j] == ' ' || str[j] == '$' || str[j] == '@'
			|| str[j] == '\'' || str[j] == '\"')
			break ;
		j++;
		n++;
	}
	return (n);
}

char	*continue_expand_two(char *str, int i, char *tmp, t_data *data)
{
	int		ii;
	int		j;
	char	*result;

	ii = -1;
	tmp = malloc(sizeof(char) * (i + 1));
	while (++ii < i)
		tmp[ii] = str[ii];
	tmp[ii] = '\0';
	i++;
	j = i;
	result = continue_expand_three(str, tmp, data, i);
	return (result);
}

char	*continue_expand_three(char *str, char *tmp, t_data *data, int i)
{
	int		n;
	int		jj;
	int		j;
	char	*var;
	char	*var_two;
	char	*aux;
	char	*result;
	char	*result_temp;
	char	*temp;

	j = get_j(str, i);
	var = malloc(sizeof(char) * ((j - i) + 1));
	n = -1;
	jj = j - i;
	while (++n < jj)
		var[n] = str[i++];
	var[n] = '\0';
	if (get_dict_value(data->env, var))
		aux = ft_strjoin(tmp, get_dict_value(data->env, var));
	else if (var[0] == '?')
		aux = ft_strjoin(tmp, ft_strjoin("$", var));
	else
		aux = NULL;
	temp = ft_itoa(g_stats);
	if (aux)
		result_temp = ft_strreplace(aux, "$?", temp);
	else
		result_temp = ft_strreplace(tmp, "$?", temp);
	j--;
	while (str[j])
		j++;
	var_two = NULL;
	var_two = (char *)malloc(sizeof(char) * (j - i) + 1);
	ft_memset(var_two, 0, sizeof(char) * (j - i));
	result = continue_expand_for(str, i, result_temp, var_two);
	free (var);
	free (var_two);
	free (aux);
	free (tmp);
	free (temp);
	free (result_temp);
	return (result);
}

char	*continue_expand_for(char *str, int i, char *tmp, char *var)
{
	int		jj;
	int		ii;
	char	*result;

	jj = -1;
	ii = i -1;
	result = NULL;
	while (str[++ii])
		var[++jj] = str[ii];
	var[jj + 1] = '\0';
	if (var && !ft_str_equals(var, ""))
		result = ft_strjoin(tmp, var);
	else
		result = ft_strdup(tmp);
	free(str);
	//free(var);
	//free(tmp);
	return (result);
}
