/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 17:37:33 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int		evt_live_mouse_move(int x, int y, t_mlx *m)
{
	(void)x;
	(void)y;
	if (m->is_pressed)
	{
		process(m);
	}
	return (0);
}

int		evt_live_key_pressed(int key, t_mlx *m)
{
	if (key == ESC_KEY)
		exit(0);
	else if (key == RIGHT_KEY || key == D_KEY)
		;
	else if (key == LEFT_KEY || key == A_KEY)
		;
	else if (key == UP_KEY || key == W_KEY)
		;
	else if (key == DOWN_KEY || key == S_KEY)
		;
	else if (key == LSFT_KEY || key == RSFT_KEY)
		;
	else if (49 == key)
	{
		;
	}
	process(m);
	return (0);
}

int		evt_live_key_released(int key, t_mlx *m)
{
	if (key == LSFT_KEY)
		;//m->is_shift = 0;
	process(m);
	return (0);
}

int		evt_live_mouse_clicked(int x, int y, int z, t_mlx *m)
{
	(void)x;
	(void)y;
	(void)z;
	if (m->is_shift)
	{
		if (x == 6)
			;
		else if (x == 7)
			;
	}
	else
	{
		if (x == WHEELUP)
			;
		else if (x == WHEELDOWN)
			;
		else if (x == BUT1_KEY)
			;
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
		m->zoom++;
	else if (x == WHEELDOWN)
		m->zoom--;
	else if (x == BUT1_KEY)
		;
	process(m);
	return (0);
}
