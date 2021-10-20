#include "fractol.h"

int		mandelbrot(t_comp c, t_comp z, t_settings *s)
{
	double		tmp;
	int			i;

	i = 0;
	while (i < s->iters)
	{
		if (z.real * z.real + z.imag * z.imag > 4)
			return (themes(s, i, z, c));
		tmp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * (z.real * z.imag) + c.imag;
		z.real = tmp;
		i++;
	}
	if (s->theme == 5)
		return (0);
		// return (themes(i, z, c));
		// s->col = 0;
	return (0);
}

int		julia(t_comp c, t_comp z, t_settings *s)
{
	static t_vec2	old_loc;
	double			tmp;
	int				i;

	i = -1;
	if (s->mouse_mode == 0)
		old_loc = s->mouse;
	c.real = (double)3 / RES_X * (old_loc.x - RES_X / 2);
	c.imag = (double)2 / RES_Y * (old_loc.y - RES_Y / 2);
	while (++i < s->iters)
	{
		if (z.real * z.real + z.imag * z.imag > 4)
			return (themes(s, i, z, c));
		tmp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = tmp;
	}
	return (0xffffff);
}

int		burning_ship(t_comp c, t_comp z, t_settings *s)
{
	double	tmp;
	int		i;
	int		out;

	i = -1;
	out = 0;
	while (++i < s->iters)
	{
		if (z.real < 0)
			z.real *= -1;
		if (z.imag < 0)
			z.imag *= -1;
		if (z.real * z.real + z.imag * z.imag > 4)
		{
			out = 1;
			break ;
		}
		tmp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * (z.real * z.imag) + c.imag;
		z.real = tmp;
	}
	if (out)
		return (themes(s, i, z, c));
	return (0);
	// if (win->theme == 5)
	// 	win->col = 0;
	// return (0);
}

