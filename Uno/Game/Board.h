#pragma once

#include <vector>
#include <iostream>

#include "Deck.h"
#include "Player.h"

class Board {
public:
	Deck deck, pile;
	std::vector<Player> players;
	int user = 0;

	bool reverse = false;
	bool isThisRealLife = false;

	Board();

	void useCard(Card);
	void cycleUser();
	void start();
	void handleWin();
};