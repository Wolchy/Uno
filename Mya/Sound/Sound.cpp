#include "Sound.h"

Sound::Sound(std::string path) {
	sound = Mix_LoadWAV(path.c_str());
	if (sound)
		std::cout << "Loaded sound: " << path.c_str() << "!" << std::endl;
	else
		std::cout << "Error Loading sound: " << path.c_str() << ", with error: " << Mix_GetError() << "!" << std::endl;
}

void Sound::destroy() {
	Mix_FreeChunk(sound);
	sound = NULL;
}

void Sound::play() {
	Mix_PlayChannel(-1, sound, 0);
}