/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrero <aherrero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:54:19 by aherrero          #+#    #+#             */
/*   Updated: 2022/06/13 16:57:47 by aherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections_fd_aux(t_data data, int temp_out)
{
	int		fd_out;
	int		outfile;

	if (!data.commands)
	{
		outfile = check_outfile(data);
		if (outfile >= 0)
			fd_out = outfile;
		else
			fd_out = dup(temp_out);
		return (1);
	}
	return (0);
}

char	*check_infile_aux(t_data *data, t_dict *temp, char *infile)
{
	char	*str;

	while (temp)
	{
		if (ft_atoi(temp->key) == -127)
		{
			if (open(temp->value, O_RDONLY, 0000644) < 0)
			{
				str = ft_strjoin("minishell: ", temp->value);
				perror(str);
				return ("1_");
			}
			else
				infile = temp->value;
		}
		if (ft_atoi(temp->key) == -126)
			infile = heredoc(data, temp);
		temp = temp->next;
	}
	return (infile);
}

char	*check_infile(t_data *data)
{
	int		i;
	int		n;
	char	*infile;
	t_dict	*temp;
	t_dict	**redirection;

	if (!data->redirections[0])
		return (NULL);
	redirection = data->redirections;
	i = 0;
	while (redirection[i])
		i++;
	n = 0;
	infile = "";
	while (n <= i)
	{
		temp = redirection[n];
		infile = check_infile_aux(data, temp, infile);
		n++;
	}
	return (infile);
}

int	check_outfile_aux(t_dict *temp, int outfile)
{
	while (temp)
	{
		if (ft_atoi(temp->key) == -128)
		{
			outfile = open(temp->value, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
			if (outfile < 0)
			{
				perror("minishell:");
				outfile = -1;
				break ;
			}
		}
		if (ft_atoi(temp->key) == -125)
		{
			outfile = open(temp->value, O_WRONLY | O_APPEND | O_CREAT, 0000644);
			if (outfile < 0)
			{
				perror("minishell:");
				outfile = -1;
				break ;
			}
		}
		temp = temp->next;
	}
	return (outfile);
}

int	check_outfile(t_data data)
{
	int		i;
	int		n;
	int		outfile;
	t_dict	*temp;
	t_dict	**redirection;

	if (!data.redirections[0])
		return (-1);
	redirection = data.redirections;
	i = 0;
	while (redirection[i])
		i++;
	n = 0;
	while (n <= i)
	{
		temp = redirection[n];
		outfile = check_outfile_aux(temp, outfile);
		n++;
	}
	return (outfile);
}
