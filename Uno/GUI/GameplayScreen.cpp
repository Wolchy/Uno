#include "GameplayScreen.h"

GameplayScreen::GameplayScreen(Mya mya, std::string name, std::string ip, int port) : Screen::Screen("gameplayScreen")
{
	network.isServer = false;
	network.serverName = ip;
	network.PORT = port;
	network.init();
	network.sendMessage("regPlayer|" + name);

	assets = new Assets(mya);
	std::string base = SDL_GetBasePath();
	assets->registerTexture(base + "assets\\uno\\background.png", "bkg");

	for (int i = 0; i < 4; i++) {
		std::string color = "null";
		if (i == 1)
			color = "blue";
		if (i == 2)
			color = "red";
		if (i == 3)
			color = "green";
		if (i == 0)
			color = "yellow";
		for (int ii = 0; ii < 10; ii++)
			assets->registerTexture(base + "assets\\uno\\" + color + "\\card" + std::to_string(ii) + ".png", "card" + std::to_string(ii) + color);
		assets->registerTexture(base + "assets\\uno\\" + color + "\\cardBlock.png", "cardBlock" + color);
		assets->registerTexture(base + "assets\\uno\\" + color + "\\cardReverse.png", "cardReverse" + color);
		assets->registerTexture(base + "assets\\uno\\" + color + "\\cardPlusTwo.png", "cardPlusTwo" + color);
	}
	assets->registerTexture(base + "assets\\uno\\cardWild.png", "cardWildnull");
	assets->registerTexture(base + "assets\\uno\\cardWild4.png", "cardWild4null");
	assets->registerTexture(base + "assets\\uno\\uno.png", "uno");
	assets->registerTexture(base + "assets\\uno\\winner.png", "winner");
	assets->init(mya.getRenderer());

	s_bkg = new Sprite(assets->getTexture("bkg"));
	s_pileCard = new Sprite(assets->getTexture("cardWildNull"));
	btn_grabCard = new Button("Grab Card", *assets->font, mya.getRenderer(), mya.SCREEN_WIDTH / 2, mya.SCREEN_HEIGHT / 2);
	tv_cards = new TextView(*assets->font, "Cards: 0", 5, 35, mya.getRenderer());
	tv_wild = new TextView(*assets->font, "1 = red. 2 = green. 3 = blue. 4 = yellow.", 0, mya.SCREEN_HEIGHT / 2, mya.getRenderer());
	tv_fps = new TextView(*assets->font, "FPS: ", 5, 5, mya.getRenderer());
	s_uno = new Sprite(assets->getTexture("uno"));
	s_win = new Sprite(assets->getTexture("winner"));
	tv_uno = new TextView(*assets->font, "UNO!", 0, 0, mya.getRenderer());
	tv_winner = new TextView(*assets->font, "Winner!", 0, 0, mya.getRenderer());
}

void GameplayScreen::render(Mya mya)
{
	s_bkg->bounds.w = mya.SCREEN_WIDTH;
	s_bkg->bounds.h = mya.SCREEN_HEIGHT;
	s_bkg->bounds.x = 0;
	s_bkg->bounds.y = 0;
	s_bkg->renderWithBounds(mya.getRenderer());

	s_pileCard->bounds.w = 85;
	s_pileCard->bounds.h = 135;
	s_pileCard->bounds.x = (mya.SCREEN_WIDTH / 2) - (s_pileCard->bounds.w / 2);
	s_pileCard->bounds.y = (mya.SCREEN_HEIGHT / 8);
	s_pileCard->renderWithBounds(mya.getRenderer());

	tv_cards->render(mya.getRenderer());

	if(needsmoar == false && goat && !winner)
		for (Sprite * s : hand) {
			s->renderWithBounds(mya.getRenderer());
		}
	if (needsmoar && !winner) {
		btn_grabCard->x = (mya.SCREEN_WIDTH / 2) - (btn_grabCard->tv->tex.w / 2);
		btn_grabCard->renderButton(mya.getRenderer());
	}
	if (wild && !winner)
		tv_wild->render(mya.getRenderer());

	for (Sprite * s : realHand) {
		s->renderWithBounds(mya.getRenderer());
	}

	tv_fps->setText("FPS: " + std::to_string(mya.fps.fps), mya.getRenderer());
	tv_fps->render(mya.getRenderer());

	if (isUno) {
		SDL_Delay(2000);
		isUno = false;
	}

	if (uno) {
		s_uno->bounds.w = (mya.SCREEN_WIDTH / 3) * 2;
		s_uno->bounds.x = mya.SCREEN_WIDTH / 6;
		s_uno->bounds.h = (mya.SCREEN_HEIGHT / 3) * 2;
		s_uno->bounds.y = mya.SCREEN_HEIGHT / 6;
		s_uno->renderWithBounds(mya.getRenderer());

		tv_uno->x = (mya.SCREEN_WIDTH / 2) - tv_uno->tex.w / 2;
		tv_uno->y = 5;
		tv_uno->render(mya.getRenderer());

		isUno = true;
		uno = false;
	}

	if (winner) {
		s_win->bounds.w = (mya.SCREEN_WIDTH / 3) * 2;
		s_win->bounds.x = mya.SCREEN_WIDTH / 6;
		s_win->bounds.h = (mya.SCREEN_HEIGHT / 3) * 2;
		s_win->bounds.y = mya.SCREEN_HEIGHT / 6;
		s_win->renderWithBounds(mya.getRenderer());

		tv_winner->x = (mya.SCREEN_WIDTH / 2) - tv_winner->tex.w / 2;
		tv_winner->y = 5;
		tv_winner->render(mya.getRenderer());
	}
}

void GameplayScreen::update(Mya mya)
{
	network.client_update();

	if (network.hasNewMessage) {
		SplitString ss;

		for (std::string s : network._buffer) {
			std::vector<std::string> fix1 = ss.split(s, "]");

			if (fix1[0] == "fix1") {
				std::vector<std::string> awd = ss.split(fix1[1], "^");

				for (std::string asd : awd) {
					std::vector<std::string> b = ss.split(s, "|");

					if (b[0] == "heresanude") {
						Card c;
						c.type = b[1];
						c.color = b[2];
						player.takeCard(c);
						std::cout << "New Card: t: " << c.type << ", c: " << c.color << "!" << std::endl;
						tv_cards->setText("Cards: " + std::to_string(player.cards.size()), mya.getRenderer());

						int mathw = (mya.SCREEN_WIDTH / 3) * 2;
						int mathx = 5;
						int mathh = mya.SCREEN_HEIGHT / 7;
						int mathy = mya.SCREEN_HEIGHT / 4 * 3;
						realHand.clear();

						for (Card cc : player.cards) {
							SDL_Rect r;
							r.h = mathh;
							r.y = mathy;
							r.w = mathw / 12;
							if (r.w > 135)
								r.w = 13;
							r.x = mathx;
							mathx += r.w + 5;

							Button* b = new Button(assets->getTexture(cc.type + cc.color), r);
							b->data = cc.type + "|" + cc.color;
							realHand.push_back(b);

							std::cout << "t: " << cc.type << ", c: " << cc.color << std::endl;
						}
					}
				}
			}
			else if (fix1[0] == "gaeboi") {
				std::vector<std::string> awd = ss.split(fix1[1], "^");

				for (std::string asd : awd) {
					std::vector<std::string> b = ss.split(s, "|");

					if (b[0] == "playa") {
						
					}
				}
			}
			else {
				std::vector<std::string> b = ss.split(s, "|");
				if (b[0] == "regPlayer") {
					player.name = b[1];
					std::cout << "Im in!" << std::endl;
				}
				if (b[0] == "heresanude") {
					Card c;
					c.type = b[1];
					c.color = b[2];
					player.takeCard(c);
					std::cout << "New Card: t: " << c.type << ", c: " << c.color << "!" << std::endl;
					tv_cards->setText("Cards: " + std::to_string(player.cards.size()), mya.getRenderer());

					int mathw = (mya.SCREEN_WIDTH / 3) * 2;
					int mathx = 5;
					int mathh = mya.SCREEN_HEIGHT / 7;
					int mathy = mya.SCREEN_HEIGHT / 4 * 3;
					realHand.clear();

					for (Card cc : player.cards) {
						SDL_Rect r;
						r.h = mathh;
						r.y = mathy;
						r.w = mathw / 12;
						if (r.w > 135)
							r.w = 13;
						r.x = mathx;
						mathx += r.w + 5;

						Button* b = new Button(assets->getTexture(cc.type + cc.color), r);
						b->data = cc.type + "|" + cc.color;
						realHand.push_back(b);

						std::cout << "t: " << cc.type << ", c: " << cc.color << std::endl;
					}
				}
				if (b[0] == "urturnsir") {
					Card c;
					c.type = b[1];
					c.color = b[2];
					if (b[1] == "cardWild" || b[1] == "cardWild4")
						s_pileCard = new Sprite(assets->getTexture(c.type + "null"));
					else
						s_pileCard = new Sprite(assets->getTexture(c.type + c.color));

					std::cout << "is my turn and heres the cards I can use:" << std::endl;
					std::cout << "current card on play: t: " << c.type << ", c: " << c.color << std::endl;
					std::vector<Card> ccards = player.getUsableCards(c);
					if (ccards.size() == 0) {
						needsmoar = true;
						std::cout << "No cards available, I need moar" << std::endl;
					}
					else {
						int mathw = (mya.SCREEN_WIDTH / 3) * 2;
						int mathx = (mya.SCREEN_WIDTH / 2) - (mathw / 2);
						int mathh = mya.SCREEN_HEIGHT / 7;
						int mathy = mya.SCREEN_HEIGHT / 4 * 2;
						hand.clear();
						goat = true;

						for (Card cc : ccards) {
							SDL_Rect r;
							r.h = mathh;
							r.y = mathy;
							r.w = mathw / 12;
							if (r.w > 135)
								r.w = 13;
							r.x = mathx;
							mathx += r.w + 5;


							Button* b = new Button(assets->getTexture(cc.type + cc.color), r);
							b->data = cc.type + "|" + cc.color;
							hand.push_back(b);

							std::cout << "t: " << cc.type << ", c: " << cc.color << std::endl;
						}
					}
				}
				if (b[0] == "clean") {
					goat = false;
					needsmoar = false;
					wild = false;
					winner = false;
					uno = false;
					player.cards.clear();
					card = Card();

					int mathw = (mya.SCREEN_WIDTH / 3) * 2;
					int mathx = 5;
					int mathh = mya.SCREEN_HEIGHT / 7;
					int mathy = mya.SCREEN_HEIGHT / 4 * 3;
					realHand.clear();

					for (Card cc : player.cards) {
						SDL_Rect r;
						r.h = mathh;
						r.y = mathy;
						r.w = mathw / 12;
						if (r.w > 135)
							r.w = 13;
						r.x = mathx;
						mathx += r.w + 5;

						Button* b = new Button(assets->getTexture(cc.type + cc.color), r);
						b->data = cc.type + "|" + cc.color;
						realHand.push_back(b);

						std::cout << "t: " << cc.type << ", c: " << cc.color << std::endl;
					}
				}
				if (b[0] == "UNO") {
					uno = true;
					tv_uno->setText(b[1], mya.getRenderer());
				}
				if (b[0] == "WINNER") {
					winner = true;
					tv_winner->setText(b[1], mya.getRenderer());
				}
			}
		}

		network._buffer.clear();
		network.hasNewMessage = false;
	}
}

void GameplayScreen::mouseKeyUp(Mya mya, SDL_MouseButtonEvent & k)
{
	if (k.button == SDL_BUTTON_LEFT) {
		if (btn_grabCard->wasPressed(mouseX, mouseY) && needsmoar && !winner) {
			goat = false;
			needsmoar = false;
			network.sendMessage("sendnudes");
		}

		for (Button* b : hand) {
			if (b->wasPressed(mouseX, mouseY) && !winner) {
				SplitString ss;
				std::vector<std::string> s = ss.split(b->data, "|");
				Card c;
				c.type = s[0];
				c.color = s[1];
				if (s[0] == "cardWild" || s[0] == "cardWild4") {
					wild = true;
					goat = false;
					str_wild = c.type;
				}
				else {
					network.sendMessage("ichewyou|" + s[0] + "|" + s[1]);
					card = c;
					player.useCard(c);
					goat = false;

					int mathw = (mya.SCREEN_WIDTH / 3) * 2;
					int mathx = 5;
					int mathh = mya.SCREEN_HEIGHT / 7;
					int mathy = mya.SCREEN_HEIGHT / 4 * 3;
					realHand.clear();

					for (Card cc : player.cards) {
						SDL_Rect r;
						r.h = mathh;
						r.y = mathy;
						r.w = mathw / 12;
						if (r.w > 135)
							r.w = 13;
						r.x = mathx;
						mathx += r.w + 5;

						Button* b = new Button(assets->getTexture(cc.type + cc.color), r);
						b->data = cc.type + "|" + cc.color;
						realHand.push_back(b);

						std::cout << "t: " << cc.type << ", c: " << cc.color << std::endl;
					}

					tv_cards->setText("Cards: " + std::to_string(player.cards.size()), mya.getRenderer());
				}
			}
		}
	}
}

void GameplayScreen::keyUp(Mya mya, Uint8 k)
{
	if (wild && !winner) {
		if (k == SDLK_1 || k == SDLK_2 || k == SDLK_3 || k == SDLK_4) {
			std::string ccolor = "null";
			if (k == SDLK_1) {
				ccolor = "red";
			}
			if (k == SDLK_2) {
				ccolor = "green";
			}
			if (k == SDLK_3) {
				ccolor = "blue";
			}
			if (k == SDLK_4) {
				ccolor = "yellow";
			}
			Card c;
			c.type = str_wild;

			network.sendMessage("ichewyou|" + c.type + "|" + ccolor);
			card = c;
			player.useCard(c);
			goat = false;
			wild = false;

			int mathw = (mya.SCREEN_WIDTH / 3) * 2;
			int mathx = 5;
			int mathh = mya.SCREEN_HEIGHT / 7;
			int mathy = mya.SCREEN_HEIGHT / 4 * 3;
			realHand.clear();

			for (Card cc : player.cards) {
				SDL_Rect r;
				r.h = mathh;
				r.y = mathy;
				r.w = mathw / 12;
				if (r.w > 135)
					r.w = 13;
				r.x = mathx;
				mathx += r.w + 5;

				Button* b = new Button(assets->getTexture(cc.type + cc.color), r);
				b->data = cc.type + "|" + cc.color;
				realHand.push_back(b);

				std::cout << "t: " << cc.type << ", c: " << cc.color << std::endl;
			}

			tv_cards->setText("Cards: " + std::to_string(player.cards.size()), mya.getRenderer());
		}
	}
}
