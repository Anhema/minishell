/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:28 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/11 17:42:24 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <time.h>
# include <stdlib.h>
# include <pthread.h>

enum	e_builtins
{
	none = 0,
	echo = 1,
	cd = 2,
	pwd = 3,
	export = 4,
	unset = 5,
	env = 6,
	e_exit = 7,
}builtins;

char	*quotation_open(char *str);

#endif
