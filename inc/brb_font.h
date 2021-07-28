#pragma once
#include "sdl_wrapper.h"

namespace brb::sdl
{
	class Font {
	private:
		TTF_Font* font_;
	public:
#ifdef __linux__
		Font(std::string, int);
#endif //linux
#ifdef _WIN32
		Font(std::wstring, int);
#endif //win32
		~Font();
		TTF_Font* get_font() const;
	};
}