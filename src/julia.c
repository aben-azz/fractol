/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:02:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/10 19:03:09 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	print_julia(t_point xy, t_mlx *fractol)
{
	long double tmp;
	long double z_r;
	long double z_i;
	long double i;

	z_r = xy.x / fractol->zoom + fractol->x.x;
	z_i = xy.y / fractol->zoom + fractol->x.y;
	i = 0;
	while (i < fractol->iteration_max && z_r * z_r + z_i * z_i < 4)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + fractol->julia_var;
		z_i = (z_i + z_i) * tmp + fractol->julia_var2;
		++i;
		if (i == fractol->iteration_max)
			put_pixel_img(fractol, (t_point){xy.x, xy.y},
				get(i, fractol->iteration_max));
		else
			put_pixel_img(fractol, (t_point){xy.x, xy.y},
				get(i, fractol->iteration_max));
	}
}

void		*draw_julia(void *data)
{
	t_mlx		*fractol;
	t_point		x;
	t_dpoint	img;
	int			padding;
	int			start;

	fractol = (t_mlx *)data;
	img = (t_dpoint){(fractol->y.x - fractol->x.x) * fractol->zoom,
		(fractol->y.y - fractol->x.y) * fractol->zoom};
	padding = DRAW_W / (THREADS ? THREADS : 1);
	start = padding * get_thread(pthread_self(), (pthread_t *)fractol->thread);
	x.x = start - 1;
	while (++x.x < img.x && x.x < DRAW_W && x.x < start + padding && (x.y = -1))
		while (++x.y < img.y && x.y < WIN_H)
			print_julia(x, fractol);
	pthread_exit(NULL);
	return (NULL);
}
