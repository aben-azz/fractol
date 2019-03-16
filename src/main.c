/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/16 20:54:49 by aben-azz         ###   ########.fr       */
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
	fractol->type = 0;
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

int error(char err, t_mlx *fractol, char mode)
{
	if (!err)
		ft_printf("Erreur:\terreur d'allocation\n\t Relancez le programme\n");
	else if (err == 2)
		ft_printf("Erreur:\tNombre de thread nul ou negatif\n\t\
		editez la macro THREADS sur includes/fractol.h (ligne.18)\n");
	else if (err == 1)
	{

		fractol->type = max((unsigned int)(&fractol->mlx) / 200 % 1, 0);
		ft_printf("Attention:\tNombre d'argument invalide\n \
		Une fractale aleatoire a ete choisie au hasard\n");
		error(3, NULL, 1);
	}
	else
	{
		!mode ? ft_printf("Erreur:\tparametre incorrect") : 0;
		ft_printf("\nListe des fractales:\n\t\t[0] julia\n\t\t[1] mandelbrot\n \
		[2] tricorn \n\t\t[3] burningship\n");
		!mode ? exit(1) : NULL;
	}
	(err == 2 || !err) ? exit(1) : NULL;
	return (0);
}
int				main(int ac, char **av)
{
	t_mlx *fractol;

	fractol = init();
	if (!fractol)
		error(0, NULL, 0);
	else if (ac == 1)
		error(1, fractol, 0);
	else if (THREADS < 1)
		error(2, NULL, 0);
	else
	{
		if (!ft_strcmp(av[1], "julia"))
			fractol->type = 0;
		else if (!ft_strcmp(av[1], "mandelbrot"))
			fractol->type = 1;
		else if (!ft_strcmp(av[1], "tricorn"))
			fractol->type = 2;
		else if (!ft_strcmp(av[1], "burningship"))
			fractol->type = 3;
		else
			error(3, NULL, 0);
	}
	process(fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
