#include "MainMenu.h"

MainMenu::MainMenu(Mya mya) : Screen::Screen("screenMainMenu")
{
	assets = new Assets(mya);

	btn_host = new Button("Host Server", *assets->font, mya.getRenderer(), 5, 5);
	btn_connect = new Button("Connect", *assets->font, mya.getRenderer(), 5, 35);

}

void MainMenu::render(Mya mya)
{
	btn_host->renderButton(mya.getRenderer());
	btn_connect->renderButton(mya.getRenderer());
}

void MainMenu::mouseKeyUp(Mya mya, SDL_MouseButtonEvent & k)
{
	if (k.button == SDL_BUTTON_LEFT) {
		if(btn_host->wasPressed(mouseX, mouseY)){
			mya.setScreen(new ServerScreen(mya));
		}
		if (btn_connect->wasPressed(mouseX, mouseY)) {
			mya.setScreen(new ConnectScreen(mya));
		}
	}
}
