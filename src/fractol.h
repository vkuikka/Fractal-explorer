/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 22:06:27 by vkuikka           #+#    #+#             */
/*   Updated: 2021/10/31 22:57:30 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
# define R_VAL(x) ((x) / 65536)
# define G_VAL(x) (((x) - ((x) / 65536) * 65536) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)
# define THREAD_AMOUNT 4
# define RES_X 800
# define RES_Y (int)(RES_X * (2 / 3.0))
# include "libft.h"
# include "SDL2/SDL.h"
# include <fcntl.h>
# include <math.h>

typedef enum e_mode
{
	MANDELBROT = 0,
	JULIA,
	BURNING_SHIP
}			t_mode;


typedef struct	s_comp
{
	double		real;
	double		imag;
}				t_comp;

typedef struct		s_vec2
{
	long double		x;
	long double		y;
}					t_vec2;

typedef struct		s_settings
{
	unsigned int	mouse_mode;
	unsigned int	iters;
	unsigned int	theme;
	float			scale;
	t_vec2			mouse;
	t_vec2			pos;
	t_mode			mode;
}					t_settings;

typedef struct		s_window
{
	SDL_Renderer	*SDLrenderer;
	SDL_Window		*SDLwindow;
	SDL_Texture		*texture;
	unsigned int	*frame_buffer;
}					t_window;

typedef struct s_rthread
{
	int					id;
	t_settings			*settings;
	t_window			*window;
}						t_rthread;

int			mandelbrot(t_comp c, t_comp z, t_settings *s);
int			julia(t_comp c, t_comp z, t_settings *s);
int			burning_ship(t_comp c, t_comp z, t_settings *s);

int			themes(t_settings *s, int i, t_comp x, t_comp y);
int			fractal_thread(void *data_pointer);

void		input(t_window *window, t_settings *settings);
void		init_settings(t_settings *settings);
void		init_window(t_window **window);

#endif
