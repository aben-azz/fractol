/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/17 20:01:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"
static void		put_legend(t_mlx *fdf)
{
	int i;

	i = 10;
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i, WHITE,
	"Fract'ol Legend: ");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"scroll                 - Zoom");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"+/-                    - Change max iterations");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"Space                  - Toggle variation (Julia)");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"arrow or A/D/W/S       - move");
}

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
	draw_fractal(fractol);
	put_legend(fractol);
}

t_point				put_pixel_img(t_mlx *fractol, t_point p, int clr)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fractol->img->bpp);
	color = mlx_get_color_value(fractol->mlx, clr);
	if ((p.x < WIN_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fractol->img->data + offset) = color;
	return (p);
}

int				mouse_position(int x, int y, void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (x < WIN_W && x > 0 && mlx->is_var)
	{
		if (y < WIN_H && y > 0)
		{
			mlx->julia_var = (((float)x / 2 * (float)y / 2) / 1000);
		}
	}
	return (0);
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
	fractol->zoom = 300.0;
	fractol->iteration_max = 50;
	fractol->is_shift = 0;
	fractol->is_pressed = 0;
	fractol->fract[0] = &draw_julia;
	fractol->fract[1] = &draw_mandelbrot;
	fractol->fract[2] = &draw_multijulia;
	fractol->fract[3] = &draw_multibrot;
	fractol->fract[4] = &draw_tricorn;
	fractol->fract[5] = &draw_bship;
	fractol->x.x = -1.9999;
	fractol->x.y = -1.9999;
	fractol->y.x = 5;
	fractol->y.y = 5;
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
	if (fractol->type == 0)
		mlx_hook(fractol->win, 6, (1L << 6), mouse_position, fractol);
	init_variables(fractol);
	return (fractol);
}

int		error(char err, t_mlx *fractol, char mode)
{
	if (!err)
		ft_printf("Erreur:\terreur d'allocation\n\t Relancez le programme\n");
	else if (err == 2)
		ft_printf("Erreur:\tNombre de thread nul ou negatif\n\t\
		editez la macro THREADS sur includes/fractol.h (ligne.18)\n");
	else if (err == 1)
	{
		fractol->type = ft_rand(2);
		ft_printf("Attention:\tNombre d'argument invalide\n \
		Une fractale aleatoire a ete choisie au hasard\n");
		error(3, NULL, 1);
	}
	else
	{
		!mode ? ft_printf("Erreur:\tparametre incorrect") : 0;
		ft_printf("\nListe des fractales:\n\t\tJulia\n\t\tMandelbrot\n \
		Multibrot n \n\t\tMultijulia n \n\t\tTricorn \n\t\tBurningship\n");
		!mode ? exit(1) : NULL;
	}
	(err == 2 || !err) ? exit(1) : NULL;
	return (0);
}

int		select_fractal(int argc, char **argv, t_mlx *fractol)
{
	int type;

	type = 0;
	if (!ft_strcmp(argv[1], "julia"))
		type = 0;
	else if (!ft_strcmp(argv[1], "mandelbrot"))
		type = 1;
	else if (!ft_strcmp(argv[1], "multijulia"))
		type = 2;
	else if (!ft_strcmp(argv[1], "multibrot"))
		type = 3;
	else if (!ft_strcmp(argv[1], "tricorn"))
		type = 4;
	else if (!ft_strcmp(argv[1], "burningship"))
		type = 5;
	else
		type = -1;
	if ((type == 2 || type == 3) && argc > 2)
		fractol->multi = ft_atoi(argv[2]);
	else if ((type == 2 || type == 3) && argc == 2)
		fractol->multi = ft_rand(20);
	~type || error(3, NULL, 0);
	return (type);
}

int		get(int n, int iter_max)
{
	double t;

	t = (double)n / (double)iter_max;
	return (rgb2dec((int)(9 * (1 - t) * t * t * t * 255),
					(int)(15 * (1 - t) * (1 - t) * t * t * 255),
					(int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255)));
}

int		main(int ac, char **av)
{
	t_mlx *fractol;

	if (THREADS < 1)
		error(2, NULL, 0);
	if (!(fractol = init()))
		error(0, NULL, 0);
	else if (ac == 1)
		error(1, fractol, 0);
	else
		fractol->type = select_fractal(ac, av, fractol);
	process(fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
