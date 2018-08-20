//
// Created by mineozelot on 8/20/18.
//

#ifndef TSEITR_LABEL_HPP
#define TSEITR_LABEL_HPP

#include <SDL_render.h>
#include <SDL_ttf.h>
#include "Game.hpp"

class Label {
	std::string text;
	bool changed = true;
	SDL_Texture *tex;
	SDL_Rect tex_rect{};
	TTF_Font *font;
	SDL_Color color{};
public:
	Label(SDL_Renderer *ren, const std::string &txt, int x, int y, TTF_Font *fnt, SDL_Color col = Game::TEXT_COLOR);

	void setText(const std::string &txt);

	void update(SDL_Renderer *ren);

	void draw(SDL_Renderer *ren) const;

	void setX(int x) {
		tex_rect.x = x;
	}
	void setY(int y) {
		tex_rect.y = y;
	}

	int getMinX() const {
		return tex_rect.x;
	}
	int getMinY() const {
		return tex_rect.y;
	}
	int getMaxX() const {
		return tex_rect.x + tex_rect.w;
	}
	int getMaxY() const {
		return tex_rect.y + tex_rect.h;
	}

	int getWidth() const {
		return tex_rect.w;
	}
	int getHeight() const {
		return tex_rect.h;
	}

	virtual ~Label();

	static SDL_Texture *renderText(SDL_Renderer *ren, TTF_Font *font, const std::string &text, SDL_Color color, int &w, int &h);
};

#endif //TSEITR_LABEL_HPP
