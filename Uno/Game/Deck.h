#pragma once

#include <vector>
#include <algorithm>
#include <random>

#include "Card.h"

class Deck {
public:
	std::vector<Card> deck;

	Deck();

	void gen();
	void shuffle();
	Card grabCard();
};