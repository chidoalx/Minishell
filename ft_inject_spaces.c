/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inject_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:06:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/07 09:54:24 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_operator(char *s, int i)
{
	if (s)
	{
		if ((s[i] == '|' && s[i + 1] == '|') || \
			(s[i] == '&' && s[i + 1] == '&') || \
			(s[i] == '>' && s[i + 1] == '>') || \
			(s[i] == '<' && s[i + 1] == '<'))
			return (2);
		else if (s[i] == '|' || s[i] == '<' || \
			s[i] == '>')
			return (1);
	}
	return (0);
}

static int	ft_word_len(char *s, int *i)
{
	int			l;

	if ((l = ft_is_operator(s, *i)) == 0)
	{
		l = *i;
		while (s && s[*i])
		{
			if (s[*i] == '\'' || s[*i] == '\"')
				*i = ft_scape_quotes(s, *i);
			else if (ft_is_operator(s, *i))
				break ;
			else
				(*i)++;
		}
		return (*i - l);
	}
	*i += l;
	return (l);
}

char	*ft_inject_space(char *input)
{
	int			i;
	int			j;
	int			w_len;
	char		*str;

	j = 0;
	i = 0;
	str = ft_strdup("");
	while (input && input[i])
	{
		w_len = ft_word_len(input, &i);
		if (w_len)
		{
			str = ft_strs_join(str, ft_substr(input, j, w_len));
			str = ft_strs_join(str, ft_strdup(" "));
			j += w_len;
		}
	}
	return (free (input), str);
}