#include "Assets.h"

Assets::Assets(Mya mya)
{
	std::string base = SDL_GetBasePath();

	font = new Font(base + "assets\\gui\\font.ttf");
}

void Assets::registerTexture(std::string p, std::string i)
{
	onu.push_back(nou(p,i));
}

Texture * Assets::getTexture(std::string s)
{
	for (Texture*t : texs) {
		if (t->id == s)
			return t;
	}
	return nullptr;
}

void Assets::init(SDL_Renderer * r)
{
	texs.clear();
	for (nou nuo : onu) {
		Texture* t = new Texture(nuo.a, r);
		t->id = nuo.b;
		texs.push_back(t);
	}
}
