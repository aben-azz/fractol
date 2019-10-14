/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/12 22:49:13 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	get_thread(pthread_t id, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < THREADS && !pthread_equal(id, threads[i]))
		;
	return (i);
}

int				error(char err, t_mlx *fractol, char mode)
{
	if (!err)
		ft_printf("Erreur:\terreur d'allocation\n\t Relancez le programme\n");
	else if (err == 2)
		ft_printf("Erreur:\tNombre de thread nul ou negatif\n\t\
		editez la macro THREADS sur includes/fractol.h (ligne.18)\n");
	else if (err == 1)
	{
		fractol->type = ft_rand(4);
		ft_printf("Attention:\tNombre d'argument invalide\n \
		Une fractale aleatoire a ete choisie au hasard: %d\n", fractol->type);
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

int				select_fractal(int argc, char **argv, t_mlx *fractol)
{
	int type;

	type = 0;
	if (!ft_strcmp(argv[1], "julia"))
		type = 0;
	else if (!ft_strcmp(argv[1], "mandelbrot"))
		type = 1;
	else if (!ft_strcmp(argv[1], "tricorn"))
		type = 2;
	else if (!ft_strcmp(argv[1], "burningship"))
		type = 3;
	else if (!ft_strcmp(argv[1], "multijulia"))
		type = 4;
	else if (!ft_strcmp(argv[1], "multibrot"))
		type = 5;
	else
		type = -1;
	if ((type == 2 || type == 3) && argc > 2)
		fractol->multi = ft_atoi(argv[2]);
	else if ((type == 2 || type == 3) && argc == 2)
		fractol->multi = ft_rand(10);
	~type || error(3, NULL, 0);
	return (type);
}

int				get(int n, t_mlx *fractol)
{
	double	o;
	int		*tabe;
	int		f;
	int		s;
	int		t;

	o = (double)n / (double)fractol->iteration_max;
	f = (15 * (1 - o) * (1 - o) * o * o * 255);
	s = (8.5 * (1 - o) * (1 - o) * (1 - o) * o * 255);
	t = (9 * (1 - o) * o * o * o * 255);
	tabe = (int[][3]){ {f, s, t}, {f, t, s}, {s, f, t}, {s, t, f}, {t, f, f},
				{t, f, f}, {f, f, f}, {f, f, f}, {t, t, t}}[fractol->color];
	return (rgb2dec(tabe[0], tabe[1], tabe[2]));
}

int				main(int ac, char **av)
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
