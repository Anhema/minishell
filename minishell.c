/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/04 18:30:46 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *str)
{
	if (ft_str_equals(str, "exit") == 1)
	{
		free(str);
		exit(0);
	}
	else
	{
		printf("command not found: %s\n", str);
		str = readline("> ");
	}
}

int main(void)
{
	char	*str;

	str = readline("> ");
	while (1)
	{
		ft_exit(str);
	}
	return (0);
}
