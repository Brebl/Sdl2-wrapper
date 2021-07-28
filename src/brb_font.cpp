#include "pch.h"

namespace brb::sdl
{
#ifdef __linux__
	Font::Font(std::string name, int size) :
		font_(nullptr)
	{
		try {
			font_ = TTF_OpenFont(name.c_str(), size);
			if (!font_) {
				throw std::runtime_error(std::string("TTF_OpenFont : " + name));
			}
			else {
				brb::log("font creation success", font_);
			}
		}
		catch (std::exception& e) {
			brb::err("brb::sdl::Font", e.what());
			exit(1);
		}
	}
#endif //linux
#ifdef _WIN32
	Font::Font(std::wstring wname, int size) :
		font_(nullptr)
	{
		try {
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string name{ converter.to_bytes(wname) };
			font_ = TTF_OpenFont(name.c_str(), size);
			if (!font_) {
				throw std::runtime_error(std::string("TTF_OpenFont : " + name));
			}
			else {
				brb::log("font creation success", font_);
			}
		}
		catch (std::exception& e) {
			brb::err("brb::sdl::Font", e.what());
			exit(1);
		}
	}
#endif //win32

	Font::~Font()
	{
		TTF_CloseFont(font_);
		brb::log("font destroyed", font_);
	}

	TTF_Font* Font::get_font() const{	
		return font_;
	}
}