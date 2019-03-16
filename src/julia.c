/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:02:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/16 19:55:40 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	print_julia(long double c_r, int x, int y, t_mlx *fractol)
{
	long double tmp;
	long double z_r;
	long double z_i;
	long double i;

	z_r = x / fractol->zoom + fractol->x.x;
	z_i = y / fractol->zoom + fractol->x.y;
	i = 0;
	while (i < fractol->iteration_max && z_r * z_r + z_i * z_i < 4)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + 0.01;
		++i;
		if (i == fractol->iteration_max)
			put_pixel_img(fractol, (t_point){x, y}, rgb2dec(i*255/(fractol->iteration_max*0.75), 0, i*255/(fractol->iteration_max*0.75)));
		else
			put_pixel_img(fractol, (t_point){x, y}, rgb2dec(255, i*255/fractol->iteration_max, 0));
	}
}

static void	calc_julia(long double image_x, long double image_y, t_mlx *fractol)
{
	int	x;
	int	y;
	int	padding;
	int	start;

	padding = DRAW_W / THREADS;
	start = padding * get_thread(pthread_self(), (pthread_t *)fractol->thread);
	x = start - 1;
	while (++x < image_x && x < DRAW_W && x < start + padding)
	{
		y = -1;
		while (++y < image_y && y < WIN_H)
			print_julia(fractol->julia_var, x, y, fractol);
	}
}

void		*draw_julia(void *data)
{
	long double	image_x;
	long double	image_y;
	t_mlx		*fractol;

	fractol = (t_mlx *)data;
	image_x = (fractol->y.x - fractol->x.x) * fractol->zoom;
	image_y = (fractol->y.y - fractol->x.y) * fractol->zoom;
	calc_julia(image_x, image_y, fractol);
	pthread_exit(NULL);
	return (NULL);
}
