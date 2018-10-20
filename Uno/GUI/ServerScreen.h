#pragma once

#include <vector>

#include "../../Mya/Graphics/GUI/Screen.h"
#include "../../Mya/Mya.h"
#include "../../Mya/Graphics/GUI/Button.h"
#include "../../Mya/Graphics/GUI/EditText.h"
#include "../../Mya/Graphics/GUI/TextView.h"
#include "../../Mya/Network/Network.h"

#include "../Assets.h"
#include "../Game/Board.h"
#include "../utils/SplitString.h"

class ServerScreen : public Screen {
public:
	Assets * assets;
	Network network;

	TextView* tv_port;
	EditText* et_port;
	Button* btn_host;

	TextView* tv_player;
	std::vector<TextView*> tv_players;
	Button* btn_startRound;

	bool isOn = false;
	Board board;

	ServerScreen(Mya);

	virtual void render(Mya);
	virtual void update(Mya);
	virtual void mouseKeyUp(Mya, SDL_MouseButtonEvent&);
	virtual void keyUp(Mya, Uint8);
};