/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:34:11 by aherrero          #+#    #+#             */
/*   Updated: 2022/04/19 18:20:52 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free (s);
}

void	ft_exit(char *str)
{
	free(str);
	exit(0);
}

char	*get_prompt(char *usr)
{
	char	*prompt;
	char	*s;
	int		i;

	s = getcwd(NULL, 0);
	i = 0;
	s = ft_strreplace(s, ft_strjoin("/Users/", usr), "~");
	prompt = ft_strjoin(usr, ": ");
	prompt = ft_strjoin(prompt, s);
	prompt = ft_strjoin(prompt, " % ");
	free (s);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*usr;
	int		i;
	t_dict	*env;
	char	**built;

	i = 0;
	(void)argc;
	(void)argv;
	env = create_env(envp);
	usr = get_dict_value(env, "USER");
	str = readline(get_prompt(usr));
	while (1)
	{
		built = ft_sort(str);
		if (ft_str_equals(str, "exit") == 1)
			ft_exit(str);
		else if (quotation_open(str) == 0)
			printf("Cierra las comillas: %s\n", str);
		else if (ft_str_equals(str, "pwd") == 1)
			ft_pwd();
		else if (ft_str_equals(str, "env") == 1)
			print_env(env);
		else if (ft_str_equals(built[0], "export") == 1)
			env = ft_export(env, built);
		else if (ft_str_equals(built[0], "unset") == 1)
			env = ft_unset(env, built);
		else
			printf("command not found: %s\n", str);
		str = readline(get_prompt(usr));
	}
	return (0);
}
