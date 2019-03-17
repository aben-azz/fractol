/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multijulia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:02:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/17 19:16:37 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	print_multijulia(long double c_r, t_point xy, t_mlx *fractol, int n)
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
		tmp = pow((z_r * z_r + z_i * z_i), (n / 2)) * cos(n * atan2(z_i, z_r)) + c_r;
		z_i = pow((z_r * z_r + z_i * z_i), (n / 2)) * sin(n * atan2(z_i, z_r)) + 0.01;
		z_r = tmp;
		++i;
		if (i == fractol->iteration_max)
			put_pixel_img(fractol, (t_point){xy.x, xy.y},
				rgb2dec(i * 255 / (fractol->iteration_max * 0.75), 0,
					i * 255 / (fractol->iteration_max * 0.75)));
		else
			put_pixel_img(fractol, (t_point){xy.x, xy.y},
				rgb2dec(255, i * 255 / fractol->iteration_max, 0));
	}
}

void		*draw_multijulia(void *data)
{
	t_mlx		*fractol;
	t_point		x;
	t_dpoint	img;
	int padding;
	int start;

	fractol = (t_mlx *)data;
	img = (t_dpoint){(fractol->y.x - fractol->x.x) * fractol->zoom,
		(fractol->y.y - fractol->x.y) * fractol->zoom};
	padding = WIN_W / (THREADS ? THREADS : 1);
	start = padding * get_thread(pthread_self(), (pthread_t *)fractol->thread);
	x.x = start - 1;
	while (++x.x < img.x && x.x < WIN_W && x.x < start + padding && (x.y = -1))
		while (++x.y < img.y && x.y < WIN_H)
			print_multijulia(fractol->julia_var, x, fractol, fractol->multi);
	pthread_exit(NULL);
	return (NULL);
}
