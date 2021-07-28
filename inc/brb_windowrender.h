#pragma once
#include "sdl_wrapper.h"

namespace brb::sdl
{
	class WindowRenderer {
	private:
		SDL_Window* window_;
		SDL_Renderer* renderer_;
	public:
#ifdef __linux__
		WindowRenderer(std::string);
#endif
#ifdef _WIN32
		WindowRenderer(std::wstring);
#endif
		~WindowRenderer();
		void present();
		SDL_Renderer* get_renderer()const;
	};
}