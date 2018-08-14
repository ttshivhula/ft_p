/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 11:35:22 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/05/30 15:46:23 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*te;
	char	*tem;
	size_t	i;

	te = (char *)s1;
	tem = (char *)s2;
	i = 0;
	while (i < n && te[i] == tem[i])
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)te[i] - (unsigned char)tem[i]);
}
