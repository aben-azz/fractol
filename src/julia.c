/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:02:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/17 17:58:52 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int getss(int n, int iter_max) {
	int R,G,B;

	// Use smooth polynomials for r, g, b

	if (n == iter_max){
		R = 0;
		G = 0;
		B = 0;
	} else if (n < 64) {
		R =n * 2;
		G = 0;
		B = 0;
	} else if (n < 128) {
		R = (((n - 64) * 128) / 126) + 128;
		G = 0;
		B = 0;
	} else if (n < 256) {
		R = (((n - 128) * 62) / 127) + 193;
		G = 0;
		B = 0;
	} else if (n < 512) {
		R = 255;
		G = (((n - 256) * 62) / 255) + 1;
		B = 0;
	} else if (n < 1024) {
		R = 255;
		G = (((n - 512) * 63) / 511) + 64;
		B = 0;
	} else if (n < 2048) {
		R = 255;
		G = (((n - 1024) * 63) / 1023) + 128;
		B = 0;
	} else if (n < 4096) {
		R = 255;
		G = (((n - 2048) * 63) / 2047) + 192;
		B = 0;
	} else {
		R = 255;
		G = 255;
		B = 0;
	}

	return rgb2dec(R, G, B);
}


static void	print_julia(long double c_r, t_point xy, t_mlx *fractol)
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
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + 0.01;
		++i;
		if (i == fractol->iteration_max)
			put_pixel_img(fractol, (t_point){xy.x, xy.y},
				getss(i, fractol->iteration_max));
		else
			put_pixel_img(fractol, (t_point){xy.x, xy.y},
				getss(i, fractol->iteration_max));
	}
}

void		*draw_julia(void *data)
{
	t_mlx		*fractol;
	t_point		x;
	t_dpoint	img;
	int padding;
	int start;

	fractol = (t_mlx *)data;
	img = (t_dpoint){(fractol->y.x - fractol->x.x) * fractol->zoom,
		(fractol->y.y - fractol->x.y) * fractol->zoom};
	padding = WIN_W / THREADS;
	start = padding * get_thread(pthread_self(), (pthread_t *)fractol->thread);
	x.x = start - 1;
	while (++x.x < img.x && x.x < WIN_W && x.x < start + padding && (x.y = -1))
		while (++x.y < img.y && x.y < WIN_H)
			print_julia(fractol->julia_var, x, fractol);
	pthread_exit(NULL);
	return (NULL);
}
