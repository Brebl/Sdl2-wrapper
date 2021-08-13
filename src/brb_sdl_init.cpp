#include "pch.h"

namespace brb::sdl
{
	bool init()
	{
		try{
			//SDL startup
			if (SDL_Init(SDL_INIT_EVERYTHING))
				throw std::runtime_error("sdl init failure\n");

			//Image startup
			int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
			if (!(IMG_Init(flags) & flags))
				throw std::runtime_error("img init failure\n");

			//TTF startup
			if (TTF_Init())
				throw std::runtime_error("ttf init failure\n");

		} catch (std::exception& e){
			brb::err("brb::sdl::init", e.what());
			return false;
		}
		brb::log("brb::sdl::init", "success");

		//Texture filter
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			brb::log("WARNING", "Texture hint not set.\n Uses nearest pixel sampling");
		return true;
	}

	void shutdown()
	{
		//SDL system shutdown
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		brb::log("brb::sdl::shutdown", "success");
	}
}