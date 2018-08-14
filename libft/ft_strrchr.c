/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:08:23 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/06/02 12:07:36 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *haystack, int c)
{
	int len;
	int i;

	len = ft_strlen(haystack) + 1;
	i = len - 1;
	while (i >= 0)
	{
		if (haystack[i] == c)
			return ((char *)(haystack + i));
		i--;
	}
	return (NULL);
}
