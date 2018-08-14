/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 08:40:00 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/06/08 09:35:35 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp;
	char	*temp2;

	i = 0;
	if (n == 0 || dest == src)
		return (dest);
	temp = (char *)dest;
	temp2 = (char *)src;
	while (i < n)
	{
		temp[i] = temp2[i];
		i++;
	}
	dest = (void *)temp;
	return (dest);
}
