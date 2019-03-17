/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/17 19:42:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;
	if (m->is_pressed)
	{
		//process(m);
	}
	return (0);
}

int		evt_live_key_pressed(int key, t_mlx *m)
{
	if (key == ESC_KEY)
		exit(0);
	else if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 1;
	else if (key == RIGHT_KEY || key == D_KEY)
		m->x.x -= 0.1;
	else if (key == LEFT_KEY || key == A_KEY)
		m->x.x += 0.1;
	else if (key == UP_KEY || key == W_KEY)
		m->x.y += 0.1;
	else if (key == DOWN_KEY || key == S_KEY)
		m->x.y -= 0.1;
	else if (key == SP_KEY)
		m->is_var = 1;
	else if (key == 69)
		m->iteration_max += 5;
	else if (key == 78)
		m->iteration_max -= 5;
	//ft_printf("keycode: %d\n", key);
	(void)m;
	process(m);
	return (0);
}

int		evt_live_key_released(int key, t_mlx *m)
{
	if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 0;
	else if (key == SP_KEY)
		m->is_var = 0;
	(void)m;
	//process(m);
	return (0);
}

int		evt_live_mouse_clicked(int keycode, int x, int y, t_mlx *m)
{
	(void)x;
	int a;

	a = WIN_W - DRAW_W;
	if ((keycode == 1 || keycode == 5) && y >= 0)
	{
		m->x.x += (((float)x + ((-a) + (((-a)) / 2)) - (DRAW_W / 2)) / m->zoom);
		m->x.y += (((float)y - (WIN_H / 2)) / m->zoom);
		m->zoom *= 1.2;
	}
	else if ((keycode == 2 || keycode == 4) && y >= 0)
	{
		m->x.x += (((float)x + ((-a) + (((-a)) / 2)) - (DRAW_W / 2)) / m->zoom);
		m->x.y += (((float)y - (WIN_H / 2)) / m->zoom);
		m->zoom *= 0.9;
	}
	process(m);
	return (0);
}

int		evt_live_mouse_pressed(int x, int y, int z, t_mlx *m)
{
	(void)y;
	(void)z;
	(void)m;
	if (x == WHEELUP)
		;//m->zoom++;
	else if (x == WHEELDOWN)
		;//m->zoom--;
	else if (x == BUT1_KEY)
		;
	//process(m);
	return (0);
}
