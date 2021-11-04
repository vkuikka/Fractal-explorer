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
	double			tmp;
	t_comp			factor;

	tmp = (double)3 / RES_X * (s->pos.x * s->scale - RES_X / 2) / s->scale;
	min[0].real = -2 + tmp;
	max[0].real = 1 + tmp;
	tmp = (double)2 / RES_Y * (s->pos.y * s->scale - RES_Y / 2) / s->scale;
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

static void	fractal(t_window *window, t_settings *settings, int thread)
{
	t_comp	z;
	t_comp	c;
	t_comp	min;
	t_comp	max;
	t_comp	factor;
	t_vec2	i;
	int		color;

	factor = fractal_loc(&min, &max, settings);
	i.y = thread;
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
			if (color)
				window->frame_buffer[(int)(i.x + i.y * RES_X)] = color;
			else
			{
				window->frame_buffer[(int)(i.x + i.y * RES_X)] = settings->inside_color;
				settings->color = 0;
			}
			i.x++;
		}
		i.y += settings->thread_amount;
	}
}

int	fractal_thread(void *data_pointer)
{
	t_rthread	*thread;

	thread = data_pointer;
	fractal(thread->window, thread->settings, thread->id);
	return (1);
}

