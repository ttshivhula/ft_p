/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 15:51:35 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/05/31 09:25:03 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *haystack, int c)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	len = ft_strlen(haystack) + 1;
	while (len)
	{
		if (haystack[i] == (char)c)
		{
			temp = (char *)(haystack + i);
			return ((char *)temp);
		}
		len--;
		i++;
	}
	return (NULL);
}
