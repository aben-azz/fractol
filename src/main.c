/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/16 19:55:44 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void			put_legend(t_mlx *fractol)
{
	int i;

	i = 10;
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i, WHITE,
	"FdF Legend: ");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"(Lshift/Rshift) + scroll  - change altitude");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"scroll                    - zoom");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"scroll click              - toggle projection");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"Space                     - reset values");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"arrow or A/D/W/S           - move");
}
//



void julia(t_mlx *fractal, long zoom, long iterations_max)
{
	double cY, cX;
	cX = ORIGINALJULIAX;
	cY = ORIGINALJULIAY;
	double moveX = 0, moveY = 0;
	double zx, zy;

	for (int x = 0; x < DRAW_W; x++)
	{
		for (int y = 0; y < WIN_H; y++)
		{
			zx = 1.5 * (x - DRAW_W / 2) / (0.5 * zoom/2 * DRAW_W) + moveX;
			zy = (y - WIN_H / 2) / (0.5 * zoom/2 * WIN_H) + moveY;
			float i = 0;
			while (zx * zx + zy * zy < 4 && i < iterations_max)
			{
				double tmp = zx * zx - zy * zy + cX;
				zy = 2.0 * zx * zy + cY;
				zx = tmp;
				i++;
			}
			if (i == iterations_max)
				put_pixel_img(fractal, (t_point){x, y}, 0xFFFFFF);
			else
			{
				if (i * 100 / iterations_max < 50)
					put_pixel_img(fractal, (t_point){x, y},
						rgb2dec(i*255/(iterations_max*0.75), 0, i*255/(iterations_max*0.75)));
				else
					put_pixel_img(fractal, (t_point){x, y},
						rgb2dec(255, i*255/iterations_max, 0));
			}
		}
	}
}
void multijulia(t_mlx *fractal, long zoom, long iterations_max, int n)
{
	double cY, cX;
	cX = ORIGINALJULIAX;
	cY = ORIGINALJULIAY;
	double moveX = 0, moveY = 0;
	double zx, zy;

	for (int x = 0; x < DRAW_W; x++)
	{
		for (int y = 0; y < WIN_H; y++)
		{
			zx = 1.5 * (x - DRAW_W / 2) / (0.5 * zoom/2 * DRAW_W) + moveX;
			zy = (y - WIN_H / 2) / (0.5 * zoom/2 * WIN_H) + moveY;
			float i = 0;
			while (zx * zx + zy * zy < 4 && i < iterations_max)
			{
				double tmp = ft_pow((zx * zx + zy * zy), (n / 2)) * cos(n * atan2(zy, zx)) + cX;
			    zy = ft_pow((zx * zx + zy * zy), (n / 2)) * sin(n * atan2(zy, zx)) + cY;
			    zx = tmp;
				// double tmp = zx * zx - zy * zy + cX;
				// zy = 2.0 * zx * zy + cY;
				// zx = tmp;
				i++;
			}
			if (i == iterations_max)
				put_pixel_img(fractal, (t_point){x, y}, 0xFFFFFF);
			else
			{
				if (i * 100 / iterations_max < 50)
					put_pixel_img(fractal, (t_point){x, y},
						rgb2dec(i*255/(iterations_max*0.75), 0, i*255/(iterations_max*0.75)));
				else
					put_pixel_img(fractal, (t_point){x, y},
						rgb2dec(255, i*255/iterations_max, 0));
			}
		}
	}
}

void mandelbrot(t_mlx *fractal) {
	double c_x, c_y , a, b, tmp;
	int i, x, y;
	for(x = 0; x < DRAW_W; x++) {

		for(y = 0; y < WIN_H; y++) {
			a = 0;
			b = 0;
			i = 0;
			c_x = ((double)x - 700) / fractal->zoom;
			c_y = ((double)y- 500) / fractal->zoom;
			while((a*a + b*b) < 4.0 && i < fractal->iteration_max) {
				tmp = a;
				a = a*a - b*b + c_x;
				b = 2*tmp*b + c_y;
				i++;
			}
			if(i == fractal->iteration_max)
				put_pixel_img(fractal, (t_point){x, y}, 0xFFFFFF);
			else {
			if(i * 100 / fractal->iteration_max < 50)
				put_pixel_img(fractal, (t_point){x, y}, rgb2dec(i*255/(fractal->iteration_max*0.75), 0, i*255/(fractal->iteration_max*0.75)));
			else
				put_pixel_img(fractal, (t_point){x, y}, rgb2dec(255, i*255/fractal->iteration_max, 0));
			}
		}
	}
}

void			draw_fractal(t_mlx *fractol)
{
	int		i;

	i = -1;
	//fractol->get_thread = -1;
	while (++i < THREADS)
		pthread_create(&fractol->thread[i], NULL, fractol->fract[fractol->type], fractol);
	i = -1;
	while (++i < THREADS)
		pthread_join(fractol->thread[i], NULL);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img->ptr, 0, 0);
}


void				process(t_mlx *fractol)
{
	mlx_clear_window(fractol->mlx, fractol->win);
	(fractol->img) && mlx_destroy_image(fractol->mlx, fractol->img->ptr);
	if (!(fractol->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fractol->img->ptr = mlx_new_image(fractol->mlx, WIN_W, WIN_H);
	if (!(fractol->img->ptr))
		exit(1);
	fractol->img->data = mlx_get_data_addr(fractol->img->ptr,
			&fractol->img->bpp, &fractol->img->sizeline, &fractol->img->endian);
	fractol->img->bpp /= 8;
	//draw(fractol);
	draw_fractal(fractol);
	put_legend(fractol);
}

t_point				put_pixel_img(t_mlx *fractol, t_point p, int clr)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fractol->img->bpp);
	color = mlx_get_color_value(fractol->mlx, clr);
	if (fractol->is_border || (p.x < DRAW_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fractol->img->data + offset) = color;
	return (p);
}

unsigned int	get_thread(pthread_t id, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < THREADS && !pthread_equal(id, threads[i]))
		;
	return (i);
}
static inline void	init_variables(t_mlx *fractol)
{
	fractol->img = NULL;
	fractol->zoom = 100;
	fractol->iteration_max = 50;
	fractol->is_border = 0;
	fractol->is_shift = 0;
	fractol->is_pressed = 0;
	fractol->fract[0] = &draw_julia;
	fractol->fract[1] = &draw_mandelbrot;
	fractol->type = 1;
	fractol->x.x = -2.9999;
	fractol->x.y = -2.9999;
	fractol->y.x = 5;
	fractol->y.y = 10;
	fractol->julia_var = 0.285;
}

static t_mlx inline	*init(void)
{
	t_mlx	*fractol;

	if (!(fractol = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(1);
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WIN_W, WIN_H, "fractol");
	mlx_hook(fractol->win, KPRESS, 0, evt_live_key_pressed, fractol);
	mlx_hook(fractol->win, MMOVE, 0, evt_live_mouse_move, fractol);
	mlx_hook(fractol->win, MCLICK, 0, evt_live_mouse_clicked, fractol);
	mlx_hook(fractol->win, MPRESS, 0, evt_live_mouse_pressed, fractol);
	mlx_hook(fractol->win, KEYRELEASE, 0, evt_live_key_released, fractol);
	init_variables(fractol);
	return (fractol);
}

int					main(int argc, char **argv)
{
	t_mlx *fractol;

	(void)argv;
	(void)argc;
	fractol = init();
	process(fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
