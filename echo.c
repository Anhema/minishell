/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/07 20:06:47 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_stats;

char	*expand(char *str, t_data *data)
{
	char	*var;
	char	*temp;
	int		i;
	int		ii;
	int		j;
	int		jj;
	int		n;
	int		q;
	char	c;

	if (!str)
		return (NULL);
	i = 0;
	q = 0;
	while (str[i])
	{
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
		if (str[i] == '$' && c != '\'')
		{
			if (str[i + 1] == ' ')
			{
				i++;
				continue ;
			}
			temp = malloc(sizeof(char) * (i + 1));
			ii = 0;
			while (ii < i)
			{
				temp[ii] = str[ii];
				ii++;
			}
			temp[ii] = '\0';
			i++;
			j = i;
			n = j;
			var = NULL;
			while (str[j])
			{
				if (str[j] == ' '
					|| str[j] == '$'
					|| str[j] == '@'
					|| str[j] == '\''
					|| str[j] == '\"')
					break ;
				j++;
			}
			var = malloc(sizeof(char) * ((j - i) + 1));
			n = 0;
			jj = j - i;
			while (n < jj)
			{
				var[n] = str[i];
				i++;
				n++;
			}
			var[n] = '\0';
			if (get_dict_value(data->env, var))
				temp = ft_strjoin(temp, get_dict_value(data->env, var));
			else if (var[0] == '?')
				temp = ft_strjoin(temp, ft_strjoin("$", var));
			temp = ft_strreplace(temp, "$?", ft_itoa(g_stats));
			//printf("--%s--VAR = %s-- I = %d\n", temp, var, i);
			j--;
			while (str[j])
				j++;
			var = (char *)malloc(sizeof(char) * (j - i) + 1);
			ft_memset(var, 0, sizeof(char *) * ((j - i) + 1));
			jj = 0;
			ii = i;
			while (str[ii])
			{
				var[jj] = str[ii];
				jj++;
				ii++;
			}
			var[jj] = '\0';
			if (var && !ft_str_equals(var, ""))
				temp = ft_strjoin(temp, var);
			//printf("--%s--VAR = %s-- I = %d\n", temp, var, i);
			// if (get_dict_value(data.env, var))
			// 	str = ft_strreplace
			// 		(str, ft_strjoin("$", var), get_dict_value(data.env, var));
			// else if (!(ft_strstr(var, "'") || ft_strstr(var, "\"")))
			// 	str = ft_strreplace(str, ft_strjoin("$", var), "");
			//str = ft_strreplace(str, ft_strjoin("$", var), "");
			str = temp;
			i = 0;
		}
		i++;
	}
	return (str);
}

// char	*expand(t_data data)
// {
// 	char	*str;
// 	char	*var;
// 	int		i;
// 	int		j;
// 	int		n;

// 	if (!data.commands->value)
// 		return (NULL);
// 	str = data.commands->value;
// 	i = 0;
// 	while (data.commands->value[i])
// 	{
// 		if (data.commands->value[i] == '$')
// 		{
// 			i++;
// 			j = i + 1;
// 			n = j;
// 			var = NULL;
// 			while (data.commands->value[j])
// 			{
// 				if (data.commands->value[j] == ' '
// 					|| data.commands->value[j] == '$'
// 					|| data.commands->value[j] == '@'
// 					|| data.commands->value[j] == '\"')
// 					break ;
// 				j++;
// 			}
// 			var = malloc(sizeof(char) * ((j - i) + 1));
// 			n = 0;
// 			j = j - i;
// 			while (n < j)
// 			{
// 				var[n] = data.commands->value[i];
// 				i++;
// 				n++;
// 			}
// 			var[n] = '\0';
// 			if (get_dict_value(data.env, var))
// 				str = ft_strreplace
// 					(str, ft_strjoin("$", var), get_dict_value(data.env, var));
// 			else
// 				str = ft_strreplace(str, ft_strjoin("$", var), "");
// 			if (!str)
// 				str = data.commands->value;
// 			i--;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

void	ft_echo(t_data *data)
{
	char	*str;
	char	*str_temp;
	int		i;
	int		n;

	str = data->commands->value;
	g_stats = 0;
	//str = expand(data);
	if (!str)
	{
		printf("\n");
		return ;
	}
	//str = space_front_to_back(str);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		n = 0;
		while (str[i] != ' ')
		{
			if (str[i] != 'n')
			{
				n = 1;
				break ;
			}
			i++;
		}
		if (n == 1)
			printf("%s\n", str);
		else
		{
			str_temp = malloc(sizeof(char) * (ft_strlen(str) - i));
			i++;
			n = 0;
			while (str[i])
			{
				str_temp[n] = str[i];
				n++;
				i++;
			}
			str_temp[n] = '\0';
			printf("%s", str_temp);
		}
	}
	else
		printf("%s\n", str);
}
