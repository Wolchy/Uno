#pragma once

#include <vector>

#include "../Mya/Graphics/Texture.h"
#include "../Mya/Graphics/Font.h"
#include "../Mya/Mya.h"

class nou {
public:
	std::string a = "", b = "";
	nou(std::string _a, std::string _b) { a = _a; b = _b; }
};

class Assets {
public:
	Font * font;

	std::vector<Texture*> texs;
	std::vector<nou> onu;

	Assets(Mya);

	void registerTexture(std::string, std::string);
	Texture* getTexture(std::string);
	void init(SDL_Renderer*);
};