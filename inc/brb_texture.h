#pragma once
#include "sdl_wrapper.h"

namespace brb::sdl
{
	class Texture 
	{
	private:
		SDL_Texture* texture_;
		int texture_width_;
		int texture_height_;
		SDL_Renderer* renderer_;
		TTF_Font* font_;
		SDL_Color basecolor_; //used when clear the screen

	public:
		Texture(const WindowRenderer&, const Font&);
		~Texture();
		void set_font(const Font&);
		void set_basecolor(const SDL_Color&, Uint8);
		void clear();
#ifdef __linux__
		bool load_pic(const std::string&);
		bool load_text(const std::string&, const SDL_Color&);
#endif
#ifdef _WIN32
		bool load_pic(const std::wstring&);
		bool load_text(const std::wstring&, const SDL_Color&);
#endif //win32
		void draw(
					int x = 0,	//coordinates
					int y = 0,
					SDL_Rect* srcrect = NULL,	//square taken from texture that get drawn
					double angle = 0.0,
					SDL_Point* center = NULL,
					SDL_RendererFlip flip = SDL_FLIP_NONE
					);
		void draw_fullscreen();
		int return_width();
	};
}