//
// Created by mineozelot on 8/11/18.
//

#include "StartScreen.hpp"
#include "GameScreen.hpp"

const char *TEXT_STARTGAME = "Start Game";const char *TEXT_LEADERBOARD = "Leaderboard";
const char *TEXT_EXIT = "Exit";

void StartScreen::init(Game *game) {
	label_startgame = new Label(game->getRenderer(), TEXT_STARTGAME, 0, 0, game->getFont24());
	label_startgame->centerAt(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	label_leaderboard = new Label(game->getRenderer(), TEXT_LEADERBOARD, 0, 0, game->getFont24());
	label_leaderboard->centerAt(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	label_exit = new Label(game->getRenderer(), TEXT_EXIT, 0, 0, game->getFont24());
	label_exit->centerAt(WIN_WIDTH / 2, WIN_HEIGHT / 2);

	label_startgame->setY(label_startgame->getMinY() - 32);
	selections[0] = SDL_Rect{label_startgame->getMinX(), label_startgame->getMaxY(), label_startgame->getWidth(), 2};
	label_leaderboard->setY(label_leaderboard->getMinY());
	selections[1] = SDL_Rect{label_leaderboard->getMinX(), label_leaderboard->getMaxY(), label_leaderboard->getWidth(), 2};
	label_exit->setY(label_exit->getMinY() + 32);
	selections[2] = SDL_Rect{label_exit->getMinX(), label_exit->getMaxY(), label_exit->getWidth(), 2};
}

void StartScreen::handle(Game *game, const SDL_Event &event) {
	switch(event.type) {
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					selection = (selection - 1) % 3;
					if(selection == -1) selection = 2;
					break;
				case SDL_SCANCODE_DOWN:
					selection = (selection + 1) % 3;
					break;
				case SDL_SCANCODE_RETURN:
					select(game);
					break;
				default: break;
			}
			break;
		case SDL_MOUSEMOTION: {
				SDL_Point mouse{event.motion.x, event.motion.y};
				if(SDL_PointInRect(&mouse, &label_startgame->getRect())) {
					selection = 0;
				} else if(SDL_PointInRect(&mouse, &label_leaderboard->getRect())) {
					selection = 1;
				} else if(SDL_PointInRect(&mouse, &label_exit->getRect())) {
					selection = 2;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN: {
			SDL_Point mouse{event.button.x, event.button.y};
			bool flag = false;
			if(SDL_PointInRect(&mouse, &label_startgame->getRect())) {
				selection = 0;
				flag = true;
			} else if(SDL_PointInRect(&mouse, &label_leaderboard->getRect())) {
				selection = 1;
				flag = true;
			} else if(SDL_PointInRect(&mouse, &label_exit->getRect())) {
				selection = 2;
				flag = true;
			}
			if(flag) select(game);
		}
		default: break;
	}
}

void StartScreen::select(Game *game) {
	switch(selection) {
		case 0:
			game->setScreen(std::make_shared<GameScreen>());
			break;
		case 1:
			break;
		case 2:
			game->stop();
			break;
		default: break;
	}
}

void StartScreen::update(Game *game) {}

void StartScreen::render(Game *game) {
	SDL_SetRenderDrawColor(game->getRenderer(), 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(game->getRenderer());

	label_startgame->draw(game->getRenderer());
	label_leaderboard->draw(game->getRenderer());
	label_exit->draw(game->getRenderer());

	SDL_SetRenderDrawColor(game->getRenderer(), 0x00, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(game->getRenderer(), &selections[selection]);

	SDL_RenderPresent(game->getRenderer());
}

void StartScreen::dispose() {
	delete label_startgame;
	delete label_leaderboard;
	delete label_exit;
}
