/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 08:58:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/14 18:03:47 by aben-azz         ###   ########.fr       */
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
	(void)m;
	//process(m);
	return (0);
}

int		evt_live_key_released(int key, t_mlx *m)
{
	if (key == LSFT_KEY || key == RSFT_KEY)
		m->is_shift = 0;
	(void)m;
	//process(m);
	return (0);
}

int		evt_live_mouse_clicked(int x, int y, int z, t_mlx *m)
{
	(void)x;
	(void)y;
	(void)z;

	if (m->is_shift)
	{
		if (x == 6){
			m->zoom += 5;
		}
		else if (x == 7){
			m->zoom -= 5;
		}
		ft_printf("zoom: %ld\n", m->zoom);
	}
	else
	{
		if (x == 5){
			m->iteration_max += 5;
		}
		else if (x == 4){
			m->iteration_max -= 5;
		}
		ft_printf("iter: %ld\n", m->iteration_max);
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
