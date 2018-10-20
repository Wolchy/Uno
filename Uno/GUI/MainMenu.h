#pragma once

#include "../../Mya/Graphics/GUI/Screen.h"
#include "../../Mya/Mya.h"
#include "../../Mya/Graphics/GUI/Button.h"

#include "../Assets.h"
#include "ServerScreen.h"
#include "ConnectScreen.h"

class MainMenu : public Screen {
public:
	Assets* assets;

	Button *btn_host, *btn_connect;

	MainMenu(Mya);

	virtual void render(Mya);
	virtual void mouseKeyUp(Mya, SDL_MouseButtonEvent&);
};