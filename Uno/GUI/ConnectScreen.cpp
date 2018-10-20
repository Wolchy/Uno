#include "ConnectScreen.h"

ConnectScreen::ConnectScreen(Mya mya) : Screen::Screen("connectionScreen")
{
	assets = new Assets(mya);

	tv_ip = new TextView(*assets->font, "IP: ", 5, 5, mya.getRenderer());
	tv_port = new TextView(*assets->font, "Port: ", 5, 35, mya.getRenderer());
	et_ip = new EditText("25.61.254.188", *assets->font, mya.getRenderer(), tv_ip->tex.w + 5, 5);
	et_port = new EditText("9998", *assets->font, mya.getRenderer(), tv_port->tex.w + 5, 35);
	btn_connect = new Button("Connect", *assets->font, mya.getRenderer(), 5, 95);
	tv_name = new TextView(*assets->font, "Name: ", 5, 65, mya.getRenderer());
	et_name = new EditText("PlayerName", *assets->font, mya.getRenderer(), tv_name->tex.w + 5, 65);

}

void ConnectScreen::render(Mya mya)
{
	tv_ip->render(mya.getRenderer());
	tv_port->render(mya.getRenderer());
	et_ip->butt->renderButton(mya.getRenderer());
	et_port->butt->renderButton(mya.getRenderer());
	btn_connect->renderButton(mya.getRenderer());
	tv_name->render(mya.getRenderer());
	et_name->butt->renderButton(mya.getRenderer());
}

void ConnectScreen::mouseKeyUp(Mya mya, SDL_MouseButtonEvent & k)
{
	if (k.button == SDL_BUTTON_LEFT) {
		et_ip->wasPressed(mouseX, mouseY);
		et_port->wasPressed(mouseX, mouseY);
		et_name->wasPressed(mouseX, mouseY);
		if (btn_connect->wasPressed(mouseX, mouseY)) {
			std::string ip = et_ip->butt->tv->getText();
			int port = std::stoi(et_port->butt->tv->getText());
			std::string name = et_name->butt->tv->getText();

			mya.setScreen(new GameplayScreen(mya, name, ip, port));
		}
	}
}

void ConnectScreen::keyUp(Mya mya, Uint8 k)
{
	et_ip->handleKey(k, mya.getRenderer());
	et_port->handleKey(k, mya.getRenderer());
	et_name->handleKey(k, mya.getRenderer());
}
