/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:37:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/20 08:43:55 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_multibrot(int *coords, long double c_r, long double c_i, \
t_mlx *fractol)
{
	double		zi;
	double		zr;
	double		t;
	long long	i;
	int			n;

	n = fractol->multi;
	zr = 0;
	zi = 0;
	i = 0;
	while (zr * zr + zi * zi < 4 && i < fractol->iteration_max)
	{
		t = pow((zr * zr + zi * zi), (n / 2)) * cos(n * atan2(zi, zr)) + c_r;
		zi = pow((zr * zr + zi * zi), (n / 2)) * sin(n * atan2(zi, zr)) + c_i;
		zr = t;
		++i;
	}
	put_pixel_img(fractol, (t_point){coords[0], coords[1]}, get(i, fractol));
}

static void	calc_multibrot(long double *xy, long double image_x, \
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
			print_multibrot((int *)coords, coords[0] / zoom[0] + \
			fractol->x.x, coords[1] / zoom[1] + fractol->x.y, fractol);
	}
}

void		*draw_multibrot(void *data)
{
	long double	xy[2];
	t_mlx		*fractol;

	fractol = (t_mlx *)data;
	xy[0] = 2;
	xy[1] = 2;
	calc_multibrot((long double *)xy, \
	(xy[0] - fractol->x.x) * fractol->zoom, \
	(xy[1] - fractol->x.y) * fractol->zoom, fractol);
	pthread_exit(NULL);
	return (NULL);
}
