#include "Deck.h"

Deck::Deck()
{
}

void Deck::gen()
{
	deck.clear();
	for (int i = 0; i < 4; i++) {
		std::string color = "null";
		if (i == 1)
			color = "blue";
		if (i == 2)
			color = "red";
		if (i == 3)
			color = "green";
		if (i == 0)
			color = "yellow";
		Card c_0;
		c_0.color = color;
		c_0.type = "card0";
		deck.push_back(c_0);

		for (int a = 0; a < 2; a++) {
			for (int ii = 1; ii < 10; ii++) {
				Card c;
				c.color = color;
				c.type = "card"+std::to_string(ii);
				deck.push_back(c);
			}
			Card c_block;
			c_block.color = color;
			c_block.type = "cardBlock";
			deck.push_back(c_block);
			Card c_reverse;
			c_reverse.color = color;
			c_reverse.type = "cardReverse";
			deck.push_back(c_reverse);
			Card c_plus_two;
			c_plus_two.color = color;
			c_plus_two.type = "cardPlusTwo";
			deck.push_back(c_plus_two);
		}

		Card c;
		c.type = "cardWild";
		deck.push_back(c);
		Card cc;
		cc.type = "cardWild4";
		deck.push_back(cc);
	}
}

void Deck::shuffle()
{
	std::random_shuffle(deck.begin(), deck.end());
}

Card Deck::grabCard()
{
	Card card = deck[deck.size()-1];
	deck.pop_back();
	return card;
}
