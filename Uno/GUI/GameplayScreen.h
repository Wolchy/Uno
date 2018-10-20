#pragma once

#include "../../Mya/Graphics/GUI/Screen.h"
#include "../../Mya/Network/Network.h"
#include "../../Mya/Mya.h"
#include "../../Mya/Graphics/Sprite.h"
#include "../../Mya/Graphics/GUI/Button.h"

#include "../utils/SplitString.h"
#include "../Game/Player.h"
#include "../Assets.h"

class GameplayScreen : public Screen {
public:
	Assets* assets;

	Network network;
	Player player;
	Card card;

	Sprite * s_bkg;
	Sprite * s_pileCard, * s_uno, * s_win;

	Button * btn_grabCard;
	TextView * tv_cards, * tv_wild;
	TextView * tv_fps, * tv_uno, * tv_winner;
	std::string str_wild = "";

	std::vector<Button*> hand;
	std::vector<Sprite*> realHand;

	bool needsmoar = false, goat = false, wild = false, winner = false, uno = false;
	bool isUno = false;

	GameplayScreen(Mya, std::string, std::string, int);

	virtual void render(Mya);
	virtual void update(Mya);
	virtual void mouseKeyUp(Mya, SDL_MouseButtonEvent&);
	virtual void keyUp(Mya, Uint8);
};