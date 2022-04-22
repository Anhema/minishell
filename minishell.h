/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:28 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/21 18:10:41 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
#include <fcntl.h>
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
}	builtins;

typedef struct dict_t_struct
{
	char					*key;
	char					*value;
	struct dict_t_struct	*next;
}	t_dict;

t_dict	**dicta_alloc(void);
void	dict_dealloc(t_dict **dict);
void	*get_item(t_dict *dict, char *key);
void	del_item(t_dict **dict, char *key);
t_dict	*dict_new(char *key, char *value);
t_dict	*dict_add_back(t_dict *lst, t_dict *new);
t_dict	*dict_add_front(t_dict *lst, t_dict *new);
char	*get_dict_value(t_dict *dict, char	*key);
t_dict	*del_one(t_dict *dict, char	*key);
char	*quotation_open(char *str);
void	print_env(t_dict *env);
t_dict	*create_env(char **str);
t_dict	*ft_export(t_dict *env, char **str);
t_dict	*ft_unset(t_dict *env, char **str);

char	**ft_sort(char *c);
char	*ft_history(char *str);


#endif
