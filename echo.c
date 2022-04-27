/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:11:20 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/27 18:37:30 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data data)
{
	char	**temp;
	char	*str;
	char	*var;
	int		i;
	int		j;
	int		n;

	i = 0;
	temp = ft_split(data.commands->value, ' ');
	if (ft_str_equals(temp[0], "-n"))
	{
		str = ft_strreplace(data.commands->value, "-n ", "");
		printf("%s", str);
	}
	else
	{
		str = data.commands->value;
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
				if (!str)
					str = data.commands->value;
				i--;
			}
			i++;
		}
		printf("%s\n", str);
	}
}