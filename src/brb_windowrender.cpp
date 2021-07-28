#include "pch.h"

namespace brb::sdl
{
#ifdef __linux__
	WindowRenderer::WindowRenderer(std::string window_name) : 
		window_(nullptr),
		renderer_(nullptr)
	{
		try {
#endif //linux
#ifdef _WIN32
	WindowRenderer::WindowRenderer(std::wstring wname) : 
		window_(nullptr),
		renderer_(nullptr)
	{
		try {
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string window_name{ converter.to_bytes(wname) };
#endif //_win32
			window_ = SDL_CreateWindow(
				window_name.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				640,
				480,
				SDL_WINDOW_MAXIMIZED |
				SDL_WINDOW_RESIZABLE
			);
			if (!window_)
				throw std::runtime_error("window creation failure\n");
			else
				brb::log("window creation success", window_);

			renderer_ = SDL_CreateRenderer(
				window_,
				-1,
				SDL_RENDERER_ACCELERATED |
				SDL_RENDERER_PRESENTVSYNC
			);
			if (!renderer_) {
				throw std::runtime_error("renderer creation failure\n");
			}
			else {
				brb::log("renderer creation success", renderer_);
				SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
				SDL_RenderSetLogicalSize(renderer_, 1280, 720);
			}
		}
		catch (std::exception& e) {
			brb::err("brb::sdl::WindowRenderer", e.what());
			exit(1);
		}
	}

	WindowRenderer::~WindowRenderer()
	{
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
		brb::log("renderer destroyed", renderer_);
		brb::log("Window destroyed", window_);
	}

	void WindowRenderer::present()
	{
		SDL_RenderPresent(renderer_);
	}

	SDL_Renderer* WindowRenderer::get_renderer()const {
		return renderer_;
	}
}