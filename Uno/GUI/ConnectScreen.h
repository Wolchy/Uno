#pragma once

#include "../../Mya/Graphics/GUI/Screen.h"
#include "../../Mya/Graphics/GUI/TextView.h"
#include "../../Mya/Graphics/GUI/EditText.h"
#include "../../Mya/Graphics/GUI/Button.h"

#include "../Assets.h"
#include "GameplayScreen.h"

class ConnectScreen : public Screen {
public:
	Assets * assets;

	TextView * tv_ip, * tv_port, * tv_name;
	EditText * et_ip, * et_port, * et_name;
	Button * btn_connect;

	ConnectScreen(Mya);

	virtual void render(Mya);
	virtual void mouseKeyUp(Mya, SDL_MouseButtonEvent&);
	virtual void keyUp(Mya, Uint8);
};