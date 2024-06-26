/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:26:38 by bramzil           #+#    #+#             */
/*   Updated: 2024/01/18 12:43:01 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchar(char *s, char c)
{
	if (!s)
		return (0);
	while (*s && (*s != c))
		s++;
	if (*s && *s == c)
		return (1);
	return (0);
}
