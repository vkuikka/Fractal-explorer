/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:12:55 by vkuikka           #+#    #+#             */
/*   Updated: 2020/01/09 20:38:37 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_stop(int code)
{
	if (code != 3)
		ft_putstr("error: ");
	if (code == 0)
		ft_putstr("memory allocation error\n");
	if (code == 1)
		ft_putstr("failed to open new window\n");
	if (code == 2)
		ft_putstr("failed to create image\n");
	if (code == 3)
		ft_putstr("valid fractals:\n\tmandelbrot\n\tjulia\n\tburning_ship\n");
	exit(1);
}

int		*ft_save_mode(void)
{
	static int	*mode = NULL;

	if (!mode)
	{
		if (!(mode = (int *)malloc(sizeof(int) * 1)))
			ft_stop(0);
		*mode = 0;
	}
	return (mode);
}

int		main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	**params;

	if (ac != 2 || ((ft_strcmp(av[1], "mandelbrot")) &&
					(ft_strcmp(av[1], "julia")) &&
					(ft_strcmp(av[1], "burning_ship"))))
		ft_stop(3);
	if (!(params = (void **)malloc(sizeof(void*) * 4)))
		ft_stop(0);
	if (!(mlx_ptr = mlx_init()))
		ft_stop(1);
	if (!(win_ptr = mlx_new_window(mlx_ptr, 1500, 1000, "fractol")))
		ft_stop(1);
	params[0] = mlx_ptr;
	params[1] = win_ptr;
	params[2] = av[1];
	params[3] = ft_save_mode();
	mlx_hook(win_ptr, 2, 0, ft_deal_key, params);
	mlx_hook(win_ptr, 4, 0, ft_deal_button, params);
	mlx_hook(win_ptr, 5, 0, ft_deal_button, params);
	mlx_hook(win_ptr, 6, 0, ft_deal_mouse, params);
	main_fractal(0, params, 1500 / 2, 1000 / 2);
	mlx_loop(mlx_ptr);
	return (0);
}
