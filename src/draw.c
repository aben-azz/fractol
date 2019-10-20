/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:57:18 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/20 10:06:18 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			draw_fractal(t_mlx *m)
{
	int		i;

	i = -1;
	while (++i < THREADS)
		pthread_create(&m->thread[i], NULL, m->fract[m->type], m);
	i = -1;
	while (++i < THREADS)
		pthread_join(m->thread[i], NULL);
	mlx_put_image_to_window(m->mlx, m->win, m->img->ptr, 0, 0);
}

void			process(t_mlx *fractol)
{
	mlx_clear_window(fractol->mlx, fractol->win);
	if (fractol->img)
		mlx_destroy_image(fractol->mlx, fractol->img->ptr);
	if (fractol->img)
		free(fractol->img);
	if (!(fractol->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fractol->img->ptr = mlx_new_image(fractol->mlx, WIN_W, WIN_H);
	if (!(fractol->img->ptr))
		exit(1);
	fractol->img->data = mlx_get_data_addr(fractol->img->ptr,
			&fractol->img->bpp, &fractol->img->sizeline, &fractol->img->endian);
	fractol->img->bpp /= 8;
	draw_fractal(fractol);
}

t_point			put_pixel_img(t_mlx *fractol, t_point p, int clr)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fractol->img->bpp);
	color = mlx_get_color_value(fractol->mlx, clr);
	if ((p.x < WIN_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fractol->img->data + offset) = color;
	return (p);
}
