/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/20 11:29:33 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		evt_live_key_pressed(int key, t_mlx *m)
{
	if (key == ESC_KEY)
		exit(0);
	else if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 1;
	else if (key == RIGHT_KEY || key == D_KEY)
		m->x.x -= 10 / m->zoom;
	else if (key == LEFT_KEY || key == A_KEY)
		m->x.x += 10 / m->zoom;
	else if (key == UP_KEY || key == W_KEY)
		m->x.y += 10 / m->zoom;
	else if (key == DOWN_KEY || key == S_KEY)
		m->x.y -= 10 / m->zoom;
	else if (key == SP_KEY)
		m->is_var = 1;
	else if (key == 69)
		m->iteration_max += 5;
	else if (key == 78)
		m->iteration_max -= 5;
	if (key != SP_KEY)
		process(m);
	return (0);
}

int		evt_live_key_released(int key, t_mlx *m)
{
	if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 0;
	else if (key == SP_KEY)
		m->is_var = 0;
	return (0);
}

int		evt_live_mouse_clicked(int keycode, int x, int y, t_mlx *m)
{
	int a;

	a = WIN_W - WIN_W;
	if ((keycode == 1 || keycode == 5) && y >= 0)
	{
		m->x.x += (((float)x + (-a + ((-a) / 2)) - (WIN_W / 2)) / m->zoom);
		m->x.y += (((float)y - (WIN_H / 2)) / m->zoom);
		m->zoom *= 1.2;
	}
	else if ((keycode == 2 || keycode == 4) && y >= 0)
	{
		m->x.x += (((float)x + (-a + ((-a) / 2)) - (WIN_W / 2)) / m->zoom);
		m->x.y += (((float)y - (WIN_H / 2)) / m->zoom);
		m->zoom *= 0.9;
	}
	process(m);
	return (0);
}

int		mouse_position(int x, int y, void *param)
{
	t_mlx	*mlx;
	double	dy;
	double	dx;

	dx = x;
	dy = y;
	mlx = (t_mlx *)param;
	if (x < WIN_W && x > 0 && mlx->is_var && y < WIN_H && y > 0)
	{
		mlx->julia_var2 = (((MAXJ - MINJ) / ((double)WIN_W - 0.0)) *
															(dx - 0.0)) + MINJ;
		mlx->julia_var = (((MAXJ - MINJ) / ((double)WIN_H - 0.0)) *
															(dy - 0.0)) + MINJ;
		process(mlx);
	}
	return (0);
}
