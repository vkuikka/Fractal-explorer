#include "fractol.h"

static SDL_Texture	*empty_texture(SDL_Renderer *renderer)
{
	SDL_Texture	*texture;

	texture = NULL;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, RES_X, RES_Y);
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	return (texture);
}

static void	init_window(t_window **window)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		ft_error("could not initialize SDL\n");
	*window = (t_window *)malloc(sizeof(t_window));
	if (!*window)
		ft_error("memory allocation failed\n");
	window[0]->SDLwindow = SDL_CreateWindow("SIM",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			RES_X, RES_Y, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!window[0]->SDLwindow)
		ft_error("could not create window");
	window[0]->SDLrenderer
		= SDL_CreateRenderer(window[0]->SDLwindow, -1, 0);
	if (!window[0]->SDLrenderer)
		ft_error("could not create renderer");
	window[0]->texture = empty_texture(window[0]->SDLrenderer);
	window[0]->frame_buffer = NULL;
}

static void	init_settings(t_settings *settings)
{
	settings->mouse_mode = 1;
	settings->mouse.x = 0;
	settings->mouse.y = 0;

	settings->theme = 2;
	settings->mode = MANDELBROT;
	settings->scale = 1;
	settings->iters = 10;
}

void	render(t_window *window, t_settings *settings)
{
	if (SDL_LockTexture(window->texture, NULL,
			(void **)&window->frame_buffer, &(int){0}) != 0)
		ft_error("failed to lock texture\n");
	ft_memset(window->frame_buffer, 0, RES_X * RES_Y * sizeof(int));

	fractal(window, settings);

	SDL_UnlockTexture(window->texture);
	SDL_RenderCopy(window->SDLrenderer, window->texture, NULL, NULL);
	SDL_RenderPresent(window->SDLrenderer);
	SDL_RenderClear(window->SDLrenderer);
}

void		input(t_window *window, t_settings *settings)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEMOTION)
		{
			settings->mouse.x = event.motion.x;
			settings->mouse.y = event.motion.y;
		}
		else if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			exit(1);
		else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_M)
				settings->mouse_mode = !settings->mouse_mode;
			else if (event.key.keysym.scancode == SDL_SCANCODE_EQUALS)
				settings->iters++;
			else if (event.key.keysym.scancode == SDL_SCANCODE_MINUS && settings->iters > 0)
				settings->iters--;
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				settings->scale++;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET && settings->scale > 1)
				settings->scale--;
			else if (event.key.keysym.scancode == SDL_SCANCODE_1)
				settings->mode = MANDELBROT;
			else if (event.key.keysym.scancode == SDL_SCANCODE_2)
				settings->mode = JULIA;
			else if (event.key.keysym.scancode == SDL_SCANCODE_3)
				settings->mode = BURNING_SHIP;
			else if (event.key.keysym.scancode == SDL_SCANCODE_COMMA && settings->theme > 2)
				settings->theme--;
			else if (event.key.keysym.scancode == SDL_SCANCODE_PERIOD && settings->theme < 10)
				settings->theme++;
		}
	}
	render(window, settings);
}

int			main()
{
	t_window	*window;
	t_settings	settings;

	init_window(&window);
	init_settings(&settings);
	while (1)
	{
		input(window, &settings);
	}
}
