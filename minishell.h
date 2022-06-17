/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:28 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/16 22:38:11 by aherrero         ###   ########.fr       */
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
	t_dict					**redirections;
	int						is_redir;
	int						fd_aux;
	int						fd[2];
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
char	*syntax_redirections(char *str);
char	*check_quotes(char *str);
char	*get_path(char *_path, char *command);
void	print_error(t_data *data);

t_dict	*ft_sort(char **c);
char	*ft_history(char *str);
t_dict	*ft_pipe_parse(char *str);
void	ft_execve(t_data *data);
void	ft_signals(void);
void	continue_signal(void);

int		check_syntax(t_dict *commands);
t_data	*get_redirections(t_data *data, char *str);
t_data	*redirections(t_data *data, char *str);
t_data	*builtings(t_data *data, char *str);
void	ft_exit(char *str, t_data *data);
char	*here_doc(t_data data, t_dict *temp);
void	expand_execve(t_data *data, int status);

void	free_mem(t_data data, char *str);

int		check_outfile(t_data *data, int j);
char	*check_infile(t_data *data, int j);
int		redirections_fd_aux(t_data *data, int temp_out);
char	*heredoc(t_data *data, t_dict *temp);
void	redirections_aux(t_data *data, int fd_in, int temp_in, int temp_out);
t_data	*redirections_fd(t_data *data, int fd_in, int temp_out, int j);

char	**continue_execve(t_data *data, char **temp, char **argv, char *key);
void	_execve_print(t_data *data);
char	*modify_str(char *str, int j);
char	aux(char p, int n);
int		aux_aux(int n, char *c, char *str, int j);
char	**join_env(t_dict *d_env);

/*  Expand functions*/

char	*continue_expand_three(char *str, char *tmp, t_data *data, int i);
char	*continue_expand_two(char *str, int i, char *tmp, t_data *data);
char	*continue_expand_for(char *str, int i, char *tmp, char *var);
char	continue_expand(char c, int i, char *str);

char	*space_front_to_back_aux(char *c, int i, int j, int fill);
char	remove_quotes_aux(char *str, char *temp, int *i, int j);
char	remove_quotes_get_c(char *str, int *n, char c, int i);
t_dict	*ft_pipe_parse_add(char *str, int *last, t_dict *commands, int i);
t_dict	*ft_pipe_parse_end(char *str, int last, t_dict *commands, int i);
t_dict	*add_command(char *line, t_dict *command);
char	*remove_spaces_aux(char	*str, int i);
char	*remove_spaces_aux_aux(char *str, int jj);
char	*remove_spaces_aux_temp(char *str, int i);

char	*get_arguments(char	*str);
char	*remove_spaces(char	*str);
t_dict	*ft_pipe_parse(char *str);
char	*check_quotes(char *str);
char	*remove_quotes(char *str);
char	*get_builting(char	*str);

#endif
