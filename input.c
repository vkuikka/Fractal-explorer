/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:57:40 by vkuikka           #+#    #+#             */
/*   Updated: 2020/01/22 15:57:42 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_print_cross(void **params, int key)
{
	static int	toggle = 0;
	int			i;

	i = -1;
	if (key == 49)
		toggle = toggle ? 0 : 1;
	if (toggle)
		while (++i < 1500)
		{
			mlx_pixel_put(params[0], params[1], i, 1000 / 2, 0x004400);
			mlx_pixel_put(params[0], params[1], 1500 / 2, i, 0x004400);
		}
}

int		ft_deal_mouse(int x, int y, void **params)
{
	static int	oldx = 0;
	static int	oldy = 0;
	int			*mode;

	mode = ft_save_mode();
	params[3] = mode;
	if (*mode != -1 && (*mode != 0 || !ft_strcmp(params[2], "julia")))
		mlx_clear_window(params[0], params[1]);
	*mode = *mode == -1 ? 0 : *mode;
	oldx = *mode == 0 ? 0 : oldx;
	oldy = *mode == 0 ? 0 : oldy;
	if (!*mode && !ft_strcmp(params[2], "julia"))
		if (!(main_fractal(-1, params, x, y)))
			ft_stop(4);
	if (*mode == 2)
		if (!(main_fractal(-1, params, x, y)))
			ft_stop(4);
	if (*mode == 1)
		if (!(main_fractal(-1, params, oldx - x, oldy - y)))
			ft_stop(4);
	oldx = x;
	oldy = y;
	ft_print_cross(params, 0);
	return (1);
}

int		ft_deal_button(int key, int x, int y, void **params)
{
	static int	pressed = 0;
	int			*mode;

	mode = ft_save_mode();
	if (key == 1 || key == 2)
		pressed = pressed ? 0 : 1;
	if (pressed && key == 2)
		*mode = 2;
	if (pressed && key == 1)
		*mode = 1;
	params[3] = mode;
	if (key != 1)
	{
		mlx_clear_window(params[0], params[1]);
		if (!(main_fractal(key, params, x, y)))
			ft_stop(4);
	}
	if (!pressed)
		*mode = 0;
	ft_print_cross(params, 0);
	return (1);
}

int		ft_deal_key(int key, void **params)
{
	int		*mode;
	int		i;

	i = -1;
	mlx_clear_window(params[0], params[1]);
	mode = ft_save_mode();
	*mode = -1;
	params[3] = mode;
	if (!(main_fractal(key, params, 0, 0)))
		ft_stop(4);
	ft_print_cross(params, key);
	return (1);
}
