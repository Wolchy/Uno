#include "ServerScreen.h"

ServerScreen::ServerScreen(Mya mya) : Screen::Screen("screenServer")
{
	assets = new Assets(mya);

	tv_port = new TextView(*assets->font, "Port: ", 5, 5, mya.getRenderer());
	et_port = new EditText("9998", *assets->font, mya.getRenderer(), tv_port->tex.w + 5, 5);
	btn_host = new Button("Host", *assets->font, mya.getRenderer(), 5, 35);

	tv_player = new TextView(*assets->font, "Players: ", 5, 35, mya.getRenderer());
	btn_startRound = new Button("Start Round", *assets->font, mya.getRenderer(), 5, 5);

	network.isServer = true;
}

void ServerScreen::render(Mya mya)
{
	if (!isOn) {
		tv_port->render(mya.getRenderer());
		et_port->butt->renderButton(mya.getRenderer());
		btn_host->renderButton(mya.getRenderer());
	}
	else {
		btn_startRound->renderButton(mya.getRenderer());
		tv_player->render(mya.getRenderer());
		for (TextView* tv : tv_players)
			tv->render(mya.getRenderer());
	}
}

void ServerScreen::update(Mya mya)
{
	if (isOn) {
		network.server_update();

		if (network.hasNewMessage) {
			SplitString ss;

			for (std::string s : network._buffer) {
				std::cout << s << std::endl;
				std::vector<std::string> abba = ss.split(s, "&");
				int id = std::stoi(abba[0]);
				std::string o = abba[1];

				std::vector<std::string> b = ss.split(o, "|");
				if (b[0] == "regPlayer") {
					Player p;
					p.user = id;
					p.name = b[1];
					board.players.push_back(p);
					tv_players.push_back(new TextView(*assets->font, p.name, 25, 65 + (tv_players.size() * 30), mya.getRenderer()));
				}
				if (b[0] == "ichewyou") {
					Card c;
					c.type = b[1];
					c.color = b[2];
					board.pile.deck.push_back(c);
					bool aboola = false;
					if (b[1] == "cardWild" || b[1] == "cardWild4") {
						c.color = "null";
						aboola = true;
					}
					if (b[1] == "cardPlusTwo") {
						board.cycleUser();
						std::string s = "fix1]";
						for (int i = 0; i < 2; i++) {
							SDL_Delay(20);
							Card wah = board.deck.grabCard();
							board.players[board.user].takeCard(wah);
							s = s + "heresanude|" + c.type + "|" + c.color + "^";
						}
						network.server_sendMessage(board.user, s);
					}
					if (b[1] == "cardWild4") {
						board.cycleUser();
						std::string s = "fix1]";
						for (int i = 0; i < 4; i++) {
							SDL_Delay(20);
							Card wah = board.deck.grabCard();
							board.players[board.user].takeCard(wah);
							s = s + "heresanude|" + c.type + "|" + c.color + "^";
						}
						network.server_sendMessage(board.user, s);
					}
					board.players[id].useCard(c);
					if(!aboola)
						board.pile.deck.push_back(c);
					board.useCard(c);

					//UNO check
					if (board.players[id].cards.size() == 1)
						network.sendMessage("UNO|" + board.players[id].name);
					if (board.players[id].cards.size() == 0) {
						network.sendMessage("WINNER|" + board.players[id].name);
					}

					board.cycleUser();
					Card ncard = board.pile.deck[board.pile.deck.size()-1];//not what it looks like
					SDL_Delay(20);
					std::cout << std::to_string(board.user) << std::endl;
					network.server_sendMessage(board.user, "urturnsir|" + ncard.type + "|" + ncard.color);
				}
				if (b[0] == "sendnudes") {
					Card c = board.deck.grabCard();
					board.players[id].takeCard(c);
					SDL_Delay(20);
					network.server_sendMessage(id, "heresanude|" + c.type + "|" + c.color);
					board.cycleUser();
					Card ncard = board.pile.deck[board.pile.deck.size() - 1];//not what it looks like
					SDL_Delay(20);
					std::cout << std::to_string(board.user) << std::endl;
					network.server_sendMessage(board.user, "urturnsir|" + ncard.type + "|" + ncard.color);
				}
			}

			network._buffer.clear();
			network.hasNewMessage = false;
		}
	}
}

void ServerScreen::mouseKeyUp(Mya mya, SDL_MouseButtonEvent & k)
{
	if (k.button == SDL_BUTTON_LEFT) {
		if (!isOn) {
			et_port->wasPressed(mouseX, mouseY);
			if (btn_host->wasPressed(mouseX, mouseY)) {
				isOn = true;

				network.PORT = std::stoi(et_port->butt->tv->getText());

				network.init();
			}
		}
		else {
			if (btn_startRound->wasPressed(mouseX, mouseY)) {
				board.isThisRealLife = true;
				board.start();
				network.sendMessage("clean");
				for (int i = 0; i < board.players.size(); i++) {
					std::string s = "fix1]";
					for (Card c : board.players[i].cards) {
						s = s + "heresanude|" + c.type + "|" + c.color + "^";
					}
					SDL_Delay(25);
					network.server_sendMessage(board.players[i].user, s);
				}
				SDL_Delay(25);
				Card ncard = board.pile.deck[board.pile.deck.size() - 1];//not what it looks like
				network.server_sendMessage(board.user, "urturnsir|" + ncard.type + "|" + ncard.color);
			}
		}
	}
}

void ServerScreen::keyUp(Mya mya, Uint8 k)
{
	if (!isOn)
		et_port->handleKey(k, mya.getRenderer());
}
