/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:37:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/17 19:16:35 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	print_bship(int *coords, long double c_r, long double c_i, \
t_mlx *fractol)
{
	long double tmp;
	long double z_i;
	long double z_r;
	long long	i;

	z_r = 0;
	z_i = 0;
	i = 0;
	while (z_r * z_r + z_i * z_i < 4 && i < fractol->iteration_max)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		++i;
	}
	if (i == fractol->iteration_max)
		put_pixel_img(fractol, (t_point){coords[0], coords[1]},
			rgb2dec(i * 255 / (fractol->iteration_max * 0.75), 0,
				i * 255 / (fractol->iteration_max * 0.75)));
	else
		put_pixel_img(fractol, (t_point){coords[0], coords[1]},
			rgb2dec(255, i * 255 / fractol->iteration_max, 0));
}

static void	calc_bship(long double *xy, long double image_x, \
long double image_y, t_mlx *fractol)
{
	long double	zoom[2];
	int			coords[2];
	int			padding;
	int			start;

	zoom[0] = image_x / (xy[0] - fractol->x.x);
	zoom[1] = image_y / (xy[1] - fractol->x.y);
	padding = WIN_W / (THREADS ? THREADS : 1);
	start = padding * get_thread(pthread_self(), (pthread_t *)fractol->thread);
	coords[0] = start - 1;
	while (++coords[0] < image_x && coords[0] <= WIN_W && \
		coords[0] < start + padding)
	{
		coords[1] = -1;
		while (++coords[1] < image_y && coords[1] <= WIN_H)
			print_bship((int *)coords, coords[0] / zoom[0] + \
			fractol->x.x, coords[1] / zoom[1] + fractol->x.y, fractol);
	}
}

void		*draw_bship(void *data)
{
	long double	xy[2];
	t_mlx		*fractol;

	fractol = (t_mlx *)data;
	xy[0] = 2;
	xy[1] = 2;
	calc_bship((long double *)xy, \
	(xy[0] - fractol->x.x) * fractol->zoom, \
	(xy[1] - fractol->x.y) * fractol->zoom, fractol);
	pthread_exit(NULL);
	return (NULL);
}
