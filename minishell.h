/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbustama <cbustama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:28 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/16 20:17:56 by cbustama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <time.h>
# include <stdlib.h>
# include <pthread.h>
# include <termios.h>

typedef struct s_dict_t_struct
{
	char					*key;
	char					*value;
	struct s_dict_t_struct	*next;
}	t_dict;

typedef struct s_data
{
	t_dict					*env;
	t_dict					*commands;
	char					*usr;
	char					*str;
	char					*prompt;
	t_dict					**redirections;
	int						is_redir;
}	t_data;

int		g_stats;
char	*space_front_to_back(char *c);

t_dict	**dicta_alloc(void);
void	dict_dealloc(t_dict **dict);
void	*get_item(t_dict *dict, char *key);
void	del_item(t_dict **dict, char *key);
t_dict	*dict_new(char *key, char *value);
t_dict	*dict_add_back(t_dict *lst, t_dict *new);
t_dict	*dict_add_back_repeat(t_dict *lst, t_dict *new);
t_dict	*dict_add_front(t_dict *lst, t_dict *new);
char	*get_dict_value(t_dict *dict, char	*key);
t_dict	*del_one(t_dict *dict, char	*key);
void	delete_all(t_dict *dict);

char	*remove_spaces(char	*str);
char	*expand(char *str, t_data *data);
char	*ft_readline(t_data *data);
char	*replace_redirections(char *str);
char	*delete_redirections(char *str);

void	print_dict(t_dict *env);
t_dict	*create_env(char **str);
t_dict	*ft_export(t_data *data);
t_dict	*ft_unset(t_dict *env, char **str);
t_data	_cd(char *str, char *usr, t_data *data);
void	ft_pwd(void);
void	ft_echo(t_data *data);

t_dict	*ft_sort(char **c);
void	ft_history(char *str);
t_dict	*ft_pipe_parse(char *str);
void	ft_execve(t_data *data);
void	ft_signals(void);
void	continue_signal(void);

int		check_syntax(t_dict *commands);
t_data	get_redirections(t_data data, char *str);
t_data	*redirections(t_data *data, char *str);
t_data	*builtings(t_data *data, char *str);
void	ft_exit(char *str, t_data *data);
char	*here_doc(t_data data, t_dict *temp);
void	expand_execve(t_data *data, int status);

void	free_mem(t_data *data, char *str);

int		check_outfile(t_data data);
char	*check_infile(t_data *data);
int		redirections_fd_aux(t_data data, int temp_out);
char	*heredoc(t_data *data, t_dict *temp);
void	redirections_aux(t_data *data, int fd_in, int temp_in, int temp_out);
void	redirections_fd(t_data data, int fd_in, int temp_out);

void	continue_execve(t_data *data, char *key, char **temp);
char	**join_env(t_dict *d_env);

/*  Expand functions*/

char	*continue_expand_three(char *str, char *tmp, t_data *data, int i);
char	*continue_expand_two(char *str, int i, char *tmp, t_data *data);
char	*continue_expand_for(char *str, int i, char *tmp, char *var);
char	continue_expand(char c, int i, char *str);

void	free_split(char *temp);
void	free_split_double(char **temp);

#endif
