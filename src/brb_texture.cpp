#include "pch.h"

namespace brb::sdl
{
	Texture::Texture(const WindowRenderer& wr, const Font& f) :
		texture_(nullptr),
		texture_width_(0),
		texture_height_(0),
		renderer_(wr.get_renderer()),
		font_(f.get_font()),
		basecolor_(brb::sdl::col::basics::black)
	{
		basecolor_.a = 0xff;
		SDL_SetRenderDrawColor(renderer_, basecolor_.r, basecolor_.g, basecolor_.b, basecolor_.a);
		brb::log("texture created", texture_);
	}

	Texture::~Texture()
	{
		if (texture_ != nullptr) {
			SDL_DestroyTexture(texture_);
			brb::log("texture destroyed", texture_);
		}
	}

	void Texture::set_font(const Font& f) {
		font_ = f.get_font();
		brb::log("texture font changed", texture_);
	}

	void Texture::set_basecolor(const SDL_Color& c, Uint8 alpha) {
		basecolor_ = c;
		basecolor_.a = alpha;
		SDL_SetRenderDrawColor(renderer_, basecolor_.r, basecolor_.g, basecolor_.b, basecolor_.a);
		brb::log("texture basecolor changed", texture_);
	}

	void Texture::clear() {
		SDL_RenderClear(renderer_);
	}

#ifdef __linux__
	bool Texture::load_pic(const std::string& fname)
	{
		try
		{	
			if (texture_) {
				SDL_DestroyTexture(texture_);
				texture_ = nullptr;
			}

			SDL_Surface* surface(IMG_Load(fname.c_str()));
			if (!surface) {
				throw(std::runtime_error("Image load, " + fname));
			}

			SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 255, 255, 255));

			texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
			if (!texture_)
				throw(std::runtime_error("SDL_CreateTextureFromSurface" + fname));

			texture_width_ = surface->w;
			texture_height_ = surface->h;
			SDL_FreeSurface(surface);

			brb::log("Image loaded", fname, Mode::all);
		}
		catch (const std::exception& e) {
			brb::err("brb::sdl::load_pic", e.what());
			return false;
		}
		return texture_ != nullptr;
	}
#endif //linux

#ifdef _WIN32
	bool Texture::load_pic(const std::wstring& wfname)
	{
		try
		{	
			if (texture_) {
				SDL_DestroyTexture(texture_);
				texture_ = nullptr;
			}

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::string fname{ converter.to_bytes(wfname) };
			SDL_Surface* surface(IMG_Load(fname.c_str()));
			if (!surface) {
				throw(std::runtime_error("Image load, " + fname + std::string(SDL_GetError())));
			}

			SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 255, 255, 255));

			texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
			if (!texture_)
				throw(std::runtime_error("SDL_CreateTextureFromSurface" + fname));

			texture_width_ = surface->w;
			texture_height_ = surface->h;
			SDL_FreeSurface(surface);

			brb::log("Image loaded", fname, Mode::all);
		}
		catch (const std::exception& e) {
			brb::err("brb::sdl::load_pic", e.what());
			return false;
		}
		return texture_ != nullptr;
	}
#endif //win32
	
#ifdef __linux__
	bool Texture::load_text(const std::string& text, const SDL_Color& col)
	{
		typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;
		try {
			if (text.empty()) {
				return false;
			}

			if (texture_) {
			SDL_DestroyTexture(texture_);
			texture_ = nullptr;
			}

			u16string utext(text.begin(), text.end());
			SDL_Surface* surface(TTF_RenderUNICODE_Blended(font_, utext.c_str(), col));
			if (!surface) {
				throw std::runtime_error("TTF_RenderUNICODE_Blended: " + std::string(TTF_GetError()));
			}
	
			texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
			if (!texture_) {
				throw std::runtime_error("SDL_CreateTextureFromSurface: " + std::string(SDL_GetError()));
			}

			texture_width_ = surface->w;
			texture_height_ = surface->h;
			
			SDL_FreeSurface(surface);
		}
		catch (const std::exception& e) {
			brb::err("brb::sdl::load_text", e.what());
			return false;
		}
		return texture_ != nullptr;
	}
#endif //linux

#ifdef _WIN23
	bool Texture::load_text(const std::wstring& text, const SDL_Color& col)
	{
		typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;
		try {
			if (text.empty()) {
				return false;
			}

			if (texture_) {
			SDL_DestroyTexture(texture_);
			texture_ = nullptr;
			}

			u16string utext(text.begin(), text.end());

			SDL_Surface* surface(TTF_RenderUNICODE_Blended(font_, utext.c_str(), col));
			if (!surface) {
				throw std::runtime_error("TTF_RenderUNICODE_Blended: " + std::string(TTF_GetError()));
			}

			texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
			if (!texture_) {
				throw std::runtime_error("SDL_CreateTextureFromSurface: " + std::string(SDL_GetError()));
			}

			texture_width_ = surface->w;
			texture_height_ = surface->h;

			SDL_FreeSurface(surface);
		}
		catch (const std::exception& e) {
			brb::err("brb::sdl::load_text", e.what());
			return false;
		}
		return texture_ != nullptr;
	}
#endif //win32

	void Texture::draw(
		int x,
		int y,
		SDL_Rect* srcrect,
		double angle,
		SDL_Point* center,
		SDL_RendererFlip flip)
	{
		//draw to render
		//srcrect: witch part of the texture gets drawn, NULL whole pic
		//dstrect: where the picture will be drawn, NULL stretch to whole screen
		SDL_Rect dstrect = { x, y, texture_width_, texture_height_ };

		if (srcrect != NULL) {
			dstrect.w = srcrect->w;
			dstrect.h = srcrect->h;
		}
		SDL_RenderCopyEx(renderer_, texture_, srcrect, &dstrect, angle, center, flip);
	}

	void Texture::draw_fullscreen()
	{
        SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    }

	int Texture::return_width()
	{
		return texture_width_;
	}
}