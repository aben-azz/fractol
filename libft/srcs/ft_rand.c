/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:41:05 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/20 10:07:31 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_rand(long long n)
{
	char		*string;
	long long	a;

	if (!(string = malloc(0)))
		return (0);
	a = ft_max((unsigned int)(&string) / 200 % n, 0);
	ft_strdel(&string);
	return (a);
}
