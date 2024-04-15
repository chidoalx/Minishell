/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:12 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/15 11:05:36 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(t_pars *arg, char *str)
{
	int		i;
	char	*tmp;
	char	**p;

	i = 0;
	while (arg && arg->envp[i])
	{
		p = ft_split(arg->envp[i], '=');
		if (ft_strcmp(p[0], str) == 0)
		{
			while (arg->envp[i + 1])
			{
				tmp = ft_strdup(arg->envp[i + 1]);
				if (!tmp)
					return (ft_free(p), -1);
				free(arg->envp[i]);
				arg->envp[i] = tmp;
				i++;
			}
			ft_free(p);
			break ;
		}
		ft_free(p);
		i++;
	}
	return (0);
}

int	check_var(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] != '_' && !ft_isalnum(p[i]))
			return (printf("unset: invalid option"), 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_pars *arg, char **p)
{
	if (p[1])
	{
		if (check_var(p[1]) == 1)
			return (1);
		if (ft_strlen(p[1]) > 256)
			return (ft_putstr_fd("Error\n", 2), 1);
		check_env(arg, p[1]);
	}
	return (0);
}