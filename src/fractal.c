/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:22:53 by vkuikka           #+#    #+#             */
/*   Updated: 2021/10/21 02:05:44by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_comp	fractal_loc(t_comp *min, t_comp *max, t_settings *s)
{
	static t_vec2	mouse_loc = {0, 0};
	double			tmp;
	t_comp			factor;

	// if (location)
		// mouse_loc = s->location;
	// s->mouse = mouse_loc;
	tmp = (double)3 / RES_X * (s->mouse.x * s->scale - RES_X / 2) / s->scale;
	min[0].real = -2 + tmp;
	max[0].real = 1 + tmp;
	tmp = (double)2 / RES_Y * (s->mouse.y * s->scale - RES_Y / 2) / s->scale;
	min[0].imag = -1 - tmp;
	max[0].imag = 1 - tmp;
	factor.real = (max[0].real - min[0].real) / (RES_X * s->scale);
	factor.imag = (max[0].imag - min[0].imag) / (RES_Y * s->scale);
	return (factor);
}

int		choose_fractal(t_comp c, t_comp z, t_settings *settings)
{
	if (settings->mode == MANDELBROT)
		return (mandelbrot(c, z, settings));
	else if (settings->mode == JULIA)
		return (julia(c, z, settings));
	else if (settings->mode == BURNING_SHIP)
		return (burning_ship(c, z, settings));
	return (0);
}

void	fractal(t_window *window, t_settings *settings)
{
	t_comp	z;
	t_comp	c;
	t_comp	min;
	t_comp	max;
	t_comp	factor;
	t_vec2	i;
	int		color;

	factor = fractal_loc(&min, &max, settings);
	i.y = 0;
	while (i.y < RES_Y)
	{
		c.imag = max.imag - i.y * factor.imag;
		i.x = 0;
		while (i.x < RES_X)
		{
			c.real = min.real + i.x * factor.real;
			z.real = c.real;
			z.imag = c.imag;
			color = choose_fractal(c, z, settings);
			if (settings->theme == 5)
				window->frame_buffer[(int)(i.x + i.y * RES_X)] += color;
			else
				window->frame_buffer[(int)(i.x + i.y * RES_X)] = color;
			i.x++;
		}
		i.y++;
	}
}