/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:41:05 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/12 22:07:25 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_rand(long long n)
{
	char *string;

	if (!(string = malloc(0)))
		return (0);
	return (ft_max((unsigned int)(&string) / 200 % n, 0));
}
