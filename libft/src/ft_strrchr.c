/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:05:48 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:58:10 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*ptr;

	i = -1;
	ptr = 0;
	while (str[++i])
	{
		if (str[i] == (char)c)
			ptr = &((char *)str)[i];
	}
	if (str[i] == (char)c)
		ptr = &((char *)str)[i];
	if (!c)
		ptr = &((char *)str)[i];
	return (ptr);
}
