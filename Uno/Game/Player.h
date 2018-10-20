#pragma once

#include <vector>
#include <iostream>

#include "Card.h"
#include "../utils/SplitString.h"

class Player {
public:
	int user = -1, points = 0, rounds = 0;
	std::vector<Card> cards;
	std::string name = "nullPlayer";

	Player();

	void takeCard(Card);
	int calcPoints();
	std::vector<Card> getUsableCards(Card);
	void useCard(Card);
};