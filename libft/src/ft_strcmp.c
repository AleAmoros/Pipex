/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoros- <aamoros-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 20:26:17 by aamoros-          #+#    #+#             */
/*   Updated: 2024/09/04 17:59:14 by aamoros-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-2);
	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)(s1[i]) == (unsigned char)(s2[i]))
			i++;
		else
		{
			if ((unsigned char)(s1[i]) < (unsigned char)(s2[i]))
				return (-1);
			if ((unsigned char)(s1[i]) > (unsigned char)(s2[i]))
				return (1);
		}
	}
	return (0);
}
