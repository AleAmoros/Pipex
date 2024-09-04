/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:05:31 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:58:10 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char			*src2;
	char			*dst2;

	src2 = (char *)src;
	dst2 = (char *)dst;
	if (!dst2 && !src2)
		return (0);
	if (src2 < dst2)
	{
		while (n--)
			dst2[n] = src2[n];
	}
	else
		ft_memcpy(dst2, src2, n);
	return (dst2);
}
