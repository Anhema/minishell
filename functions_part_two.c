/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_part_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 22:33:04 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/20 18:43:17 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*add_command(char *line, t_dict *command)
{
	//char	*built;
	char	*arguments;

	line = space_front_to_back(line);
	//built = get_builting(line);
	arguments = get_arguments(line);
	//built = remove_quotes(built);
	arguments = remove_quotes(arguments);
	if (!arguments)
		command = dict_add_back(command, dict_new(ft_strdup(remove_quotes(get_builting(line))), NULL));
	else
		command = dict_add_back
			(command, dict_new(remove_quotes(get_builting(line)), ft_strdup(arguments)));
	// if (built)
	// 	free(built);
	// if (arguments)
	// 	free(arguments);
	// printf("--%s--\n", built);
	// printf("--%s--\n", arguments);
	if (line)
		free (line);
	return (command);
}

char	*remove_spaces_aux(char	*str, int i)
{
	int		j;
	int		jj;
	char	*temp;
	char	*aux;

	j = i;
	jj = 0;
	while (str[j] == ' ')
	{
		j++;
		jj++;
	}
	jj = i + jj;
	temp = remove_spaces_aux_temp(str, i);
	aux = remove_spaces_aux_aux(str, jj);
	str = ft_strjoin(temp, " ");
	str = ft_strjoin(str, aux);
	free(temp);
	free(aux);
	return (str);
}

char	*remove_spaces_aux_aux(char *str, int jj)
{
	char	*aux;
	int		j;

	aux = (char *)calloc((int)ft_strlen(str) - jj, sizeof(char));
	aux = ft_memset(aux, 0, (int)ft_strlen(str) - jj);
	j = 0;
	while (str[jj])
	{
		aux[j] = str[jj];
		j++;
		jj++;
	}	
	return (aux);
}

char	*remove_spaces_aux_temp(char *str, int i)
{
	char	*temp;
	int		j;

	temp = (char *)calloc(i + 1, sizeof(char));
	temp = ft_memset(temp, 0, i + 1);
	j = 0;
	while (j < i)
	{
		temp[j] = str[j];
		j++;
	}
	return (temp);
}
