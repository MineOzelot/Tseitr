//
// Created by mineozelot on 8/20/18.
//

#include <cstring>
#include "Label.hpp"

Label::Label(SDL_Renderer *ren, const std::string &txt, int x, int y, TTF_Font *fnt, SDL_Color col): text(txt), font(fnt), color(col) {
	tex_rect.x = x;
	tex_rect.y = y;
	update(ren);
}

void Label::setText(const std::string &txt) {
	changed = true;
	text = txt;
}

void Label::update(SDL_Renderer *ren) {
	if(changed) {
		changed = false;
		tex = renderText(ren, font, text, color, tex_rect.w, tex_rect.h);
	}
}

void Label::draw(SDL_Renderer *ren) const {
	SDL_RenderCopy(ren, tex, nullptr, &tex_rect);
}

Label::~Label() {
	SDL_DestroyTexture(tex);
}

SDL_Texture *Label::renderText(SDL_Renderer *ren, TTF_Font *font, const std::string &text, SDL_Color color, int &w, int &h) {
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	return texture;
}
