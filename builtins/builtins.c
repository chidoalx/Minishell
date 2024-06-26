/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:45:15 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/14 20:08:47 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_echo(t_cmd *node)
{
	int		j;
	int		n;

	j = 1;
	n = 0;
	while (node && node->data[j] && \
		!ft_strcmp(node->data[j], "-n") && ++n)
		j++;
	while (node && node->data && node->data[j])
	{
		if (node->data[j])
		{
			ft_putstr_fd(node->data[j], node->out);
			if (node->data[j + 1])
				ft_putstr_fd(" ", node->out);
		}
		j++;
	}
	if (n == 0)
		ft_putstr_fd("\n", node->out);
	return (0);
}

static int	ft_pwd(t_pars *args, t_cmd *node)
{
	char	*tmp;

	if (node && args && node->data && node->data[0])
	{
		tmp = ft_getcwd(args);
		if (!tmp)
			tmp = args->cwd;
		printf("%s\n", tmp);
	}
	return (0);
}

static int	ft_env(t_pars *arg, t_cmd *node)
{
	int		i;

	i = -1;
	if (arg && node && node->data && node->data[1])
		return (ft_builts_error("env", node->data[1], \
			"No such file or directory"), 127);
	if (node && arg && arg->envp)
	{
		while (arg->envp[++i])
		{
			if (ft_strchr(arg->envp[i], '='))
				ft_putendl_fd(arg->envp[i], node->out);
		}
	}
	return (0);
}

int	ft_builtins(t_pars *args, t_cmd *node)
{
	if (node && node->data && args)
	{
		if (!ft_strcmp(node->data[0], "export"))
			return (ft_export(args, node, node->data));
		else if (!ft_strcmp(node->data[0], "cd"))
			return (ft_cd(args, node));
		else if (!ft_strcmp(node->data[0], "pwd"))
			return (ft_pwd(args, node));
		else if (!ft_strcmp(node->data[0], "env"))
			return (ft_env(args, node));
		else if (!ft_strcmp(node->data[0], "echo"))
			return (ft_echo(node));
		else if (!ft_strcmp(node->data[0], "unset"))
			return (ft_unset(args, node->data));
		else if (!ft_strcmp(node->data[0], "exit"))
		{
			ft_putendl_fd("exit", 1);
			return (ft_exit(node));
		}
	}
	return (10);
}
