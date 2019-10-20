/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:58:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/20 08:37:08 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void	init_variables(t_mlx *fractol)
{
	fractol->img = NULL;
	fractol->zoom = 300.0;
	fractol->iteration_max = 70;
	fractol->is_shift = 0;
	fractol->is_var = 0;
	fractol->is_pressed = 0;
	fractol->fract[0] = &draw_julia;
	fractol->fract[1] = &draw_mandelbrot;
	fractol->fract[2] = &draw_tricorn;
	fractol->fract[3] = &draw_bship;
	fractol->fract[4] = &draw_multijulia;
	fractol->fract[5] = &draw_multibrot;
	fractol->x.x = -2.3;
	fractol->x.y = -1.45;
	fractol->y.x = 5;
	fractol->y.y = 5;
	fractol->julia_var = 0.285;
	fractol->julia_var2 = -0.7;
	fractol->color = ft_rand(9);
}

t_mlx				*init(void)
{
	t_mlx	*fractol;

	if (!(fractol = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(1);
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WIN_W, WIN_H, "fractol");
	mlx_hook(fractol->win, KPRESS, 0, evt_live_key_pressed, fractol);
	mlx_hook(fractol->win, MCLICK, 0, evt_live_mouse_clicked, fractol);
	mlx_hook(fractol->win, KEYRELEASE, 0, evt_live_key_released, fractol);
	if (fractol->type == 0)
		mlx_hook(fractol->win, 6, (1L << 6), mouse_position, fractol);
	init_variables(fractol);
	return (fractol);
}
