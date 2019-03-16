/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:38:07 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/16 19:55:25 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/fractol.h"

static void	print_mandelbrot(int *coords, long double c_r, long double c_i, \
t_dna *dna)
{
	long double tmp;
	long double z_i;
	long double z_r;
	long long	i;

	z_r = 0;
	z_i = 0;
	i = 0;
	while (z_r * z_r + z_i * z_i < 4 && i < dna->bonus->iteration_max)
	{
		tmp = z_r;
		z_r = (dna->bonus->perspective && dna->fractale == 1) ? \
		pow(z_r * z_r - z_i * z_i + c_r, (dna->bonus->var * 1)) :\
		z_r * z_r - z_i * z_i + c_r;
		if (dna->fractale == 3)
			z_i = 2 * fabsl(z_i * tmp) + c_i;
		else
			z_i = 2 * z_i * tmp + c_i;
		++i;
	}
	if (i == dna->bonus->iteration_max)
		mlx_pixel_put_to_image(dna, &coords[0], &coords[1], 0x122440);
	else if (i > 1)
		mlx_pixel_put_to_image(dna, &coords[0], &coords[1], 0x122440 * i);
}

static void	calc_mandelbrot(long double *xy, long double image_x, \
long double image_y, t_dna *dna)
{
	long double	zoom[2];
	int			coords[2];
	int			padding;
	int			start;

	zoom[0] = image_x / (xy[0] - dna->coords->x1);
	zoom[1] = image_y / (xy[1] - dna->coords->y1);
	padding = WIDTH / THREADS;
	start = padding * get_thread(pthread_self(), (pthread_t *)dna->core);
	coords[0] = start - 1;
	while (++coords[0] < image_x && coords[0] <= WIDTH && \
		coords[0] < start + padding)
	{
		coords[1] = -1;
		while (++coords[1] < image_y && coords[1] <= HEIGHT)
			print_mandelbrot((int *)coords, coords[0] / zoom[0] + \
			dna->coords->x1, coords[1] / zoom[1] + dna->coords->y1, dna);
	}
}

void		*draw_mandelbrot(void *data)
{
	long double	xy[2];
	t_dna		*dna;

	dna = (t_dna *)data;
	xy[0] = 2;
	xy[1] = 2;
	calc_mandelbrot((long double *)xy, \
	(xy[0] - dna->coords->x1) * dna->bonus->zoom, \
	(xy[1] - dna->coords->y1) * dna->bonus->zoom, dna);
	return (NULL);
}
