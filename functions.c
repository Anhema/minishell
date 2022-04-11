/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:19:32 by cbustama          #+#    #+#             */
/*   Updated: 2022/04/11 17:35:04 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sort(char *c)
{
	char	*s;

	s = *ft_split(c, ' ');
	return (*&s);
}
// enum	e_builtins
// {
// 	echo = 1,
// 	cd = 2,
// 	pwd = 3,
// 	export = 4,
// 	unset = 5,
// 	env = 6,
// 	_exit = 7,
// }builtins;

char	*ft_enum(int c)
{
	if (c == 1)
		return ("echo");
	if (c == 2)
		return ("cd");
	if (c == 3)
		return ("pwd");
	if (c == 4)
		return ("export");
	if (c == 5)
		return ("unset");
	if (c == 6)
		return ("env");
	if (c == 7)
		return ("exit");
	else
		return ("NULL");
}

int main (int argc, char **argv)
{
	(void)argc;
	
	printf("%s\n",ft_sort(argv[1]));
	printf("%d\n",n_exit);
	return (0);
}