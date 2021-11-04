/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 22:06:27 by vkuikka           #+#    #+#             */
/*   Updated: 2021/11/04 23:51:41 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "SDL2/SDL.h"
# include <fcntl.h>
# include <math.h>

# define R_HEX(x) ((int)(x) << (8 * 2))
# define G_HEX(x) ((int)(x) << (8 * 1))
# define B_HEX(x) ((int)(x) << (8 * 0))
# define R_VAL(x) (x << (8 * 0)) >> (8 * 2)
# define G_VAL(x) (x << (8 * 1)) >> (8 * 2)
# define B_VAL(x) (x << (8 * 2)) >> (8 * 2)

# define TRUE 1
# define FALSE 0

# define THREAD_AMOUNT 4
# define RES_X 800
# define RES_Y (int)(RES_X * (2 / 3.0))

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
	unsigned int	inside_color;
	unsigned int	thread_amount;
	unsigned int	mouse_mode;
	unsigned int	iters;
	unsigned int	theme;
	unsigned int	color;
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
