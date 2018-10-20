#include <string>
#include <Windows.h>

#include "Mya\Mya.h"

#include "Uno/GUI/MainMenu.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));

	Mya mya;
	mya.init("Uno");
	
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	mya.setScreen(new MainMenu(mya));

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		if ((arg == "-s") || (arg == "-server")) {
			std::cout << "Setting it to server mode!" << std::endl;
			mya.isServer = true;
		}
		if ((arg == "-c") || (arg == "-console")) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
		}
	}

	while (mya.isRunning()) {
		mya.update();
		mya.render();
	}
	mya.close();

	return 1;
}