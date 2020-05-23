#ifndef TEST

#include "App.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Rect.h"
#include "Point.h"
#include "Size.h"

namespace ii887522::Calculator
{
	App::App() : window{ SDL_CreateWindow("Calcuator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 480, 0u) },
		ico{ IMG_Load("res/main/calculator.png") }, renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE) },
		button{ renderer, Rect{ Point{ 0, 0 }, Size{ 41, 41 } } }
	{
		SDL_SetWindowIcon(window, ico);
	}

	void App::renderBackground()
	{
		SDL_SetRenderDrawColor(renderer, 192u, 192u, 192u, 255u);
		SDL_RenderClear(renderer);
	}

	void App::render()
	{
		renderBackground();
		button.render(renderer);
	}

	void App::show()
	{
		render();
		SDL_RenderPresent(renderer);
	}

	App::~App()
	{
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(ico);
		SDL_DestroyWindow(window);
	}
}

#endif