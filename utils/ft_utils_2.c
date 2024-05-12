/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:34:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/12 01:55:21 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_error(char *s)
{
	char		*tmp;

	ft_get_status(0, NULL, 1, 2);
	tmp = ft_strs_join(ft_strdup(s), \
		ft_strdup(": ambiguous redirect"));
	if (!tmp)
		return (-1);
	ft_putendl_fd(tmp, 2);
	return (free(tmp), -1);
}

int	last_arg(t_pars *args, t_cmd *node, char **tab, int ind)
{
	int			i;
	char		**tmp_1;

	i = -1;
	tmp_1 = ft_split("export _=", ' ');
	while (tmp_1 && tab && tab[++i])
	{
		if (!tab[i + 1])
		{
			if (ind == 1)
				tmp_1[1] = ft_strs_join(tmp_1[1], \
					ft_strdup(tab[i]));
			ft_export(args, node, tmp_1);
		}
	}
	return (ft_free_2_dm(tmp_1), 0);
}

int	ft_is_builtin(char **tab)
{
	char		*ref;

	ref = "cd unset exit env pwd echo export";
	if (tab && tab[0])
	{
		if (ft_strstr(ref, tab[0]) || \
			!ft_strcmp(tab[0], "export"))
			return (1);
	}
	return (0);
}

int	ft_strcmp(char *s_1, char *s_2)
{
	int			i;

	i = 0;
	if (!s_1 || !s_2)
		return (-1);
	while (s_1[i] && s_2[i] && (s_1[i] == s_2[i]))
		i++;
	return (s_1[i] - s_2[i]);
}

char	*ft_getenv(char **envp, char *name)
{
	int			i;
	char		*vl;
	char		*var;

	i = -1;
	while (envp && name && envp[++i])
	{
		var = ft_substr(envp[i], 0, \
			ft_var_len(envp[i]));
		if (!ft_strcmp(var, name))
		{
			vl = ft_substr(envp[i], (ft_strlen(var) + 1), \
				ft_strlen(envp[i]));
			free(var);
			return (free(name), vl);
		}
		free(var);
	}
	return (free(name), NULL);
}
