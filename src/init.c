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

void	init_window(t_window **window)
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

void	init_settings(t_settings *settings)
{
	settings->mouse.x = 0;
	settings->mouse.y = 0;

	settings->theme = 2;
	settings->mode = MANDELBROT;
	settings->scale = 1;
	settings->iters = 10;

	settings->pos.x = RES_X / 2;
	settings->pos.y = RES_Y / 2;
}
