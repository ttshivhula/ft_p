/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 08:52:58 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/05/30 16:08:14 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	*temp2;

	i = 0;
	temp = (unsigned char *)dest;
	temp2 = (unsigned char *)src;
	while (i < n)
	{
		temp[i] = temp2[i];
		if (temp[i] == (unsigned char)c)
			return (dest + 1 + i);
		i++;
	}
	return (NULL);
}
