/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/05/10 18:47:15 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse(t_data data)
{
	char	*str;
	char	*var;
	int		i;
	int		j;
	int		n;

	str = data.commands->value;
	i = 0;
	while (data.commands->value[i])
	{
		if (data.commands->value[i] == '$')
		{
			i++;
			j = i + 1;
			n = j;
			var = NULL;
			while (data.commands->value[j])
			{
				if (data.commands->value[j] == ' ' || data.commands->value[j] == '$')
					break ;
				j++;
			}
			var = malloc(sizeof(char) * ((j - i) + 1));
			n = 0;
			j = j - i;
			while (n < j)
			{
				var[n] = data.commands->value[i];
				i++;
				n++;
			}
			var[n] = '\0';
			if (get_dict_value(data.env, var))
				str = ft_strreplace(str, ft_strjoin("$", var), get_dict_value(data.env, var));
			else
				str = ft_strreplace(str, ft_strjoin("$", var), "");
			if (!str)
				str = data.commands->value;
			i--;
		}
		i++;
	}
	return (str);
}

void	ft_echo(t_data data)
{
	char	*str;
	char	*str_temp;
	int		i;
	int		n;


	str = parse(data);
	str = space_front_to_back(str);
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
