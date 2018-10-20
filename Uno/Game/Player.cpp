#include "Player.h"

Player::Player()
{
}

void Player::takeCard(Card c)
{
	cards.push_back(c);
}

int Player::calcPoints()
{
	int p = 0;
	for (Card c : cards) {
		if (c.type == "cardReverse")
			p += 10;
		else if (c.type == "cardBlock")
			p += 10;
		else if (c.type == "cardPlusTwo")
			p += 10;
		else if (c.type == "cardWild")
			p += 25;
		else if (c.type == "cardWild4")
			p += 25;
		else {
			SplitString ss;
			std::vector<std::string> asda = ss.split(c.type, "d");
			int i = std::stoi(asda[1]);
			p += i;
		}
	}
	return p;
}

std::vector<Card> Player::getUsableCards(Card card)
{
	std::vector<Card> c;

	for (Card cc : cards) {
		if (cc.color == card.color)
			c.push_back(cc);
		else if (cc.type == card.type)
			c.push_back(cc);
		else if (cc.type == "cardWild" || cc.type == "cardWild4")
			c.push_back(cc);
	}

	return c;
}

void Player::useCard(Card card)
{
	std::cout << "useCard" << std::endl;
	
	std::vector<Card> ccards;
	bool lolz = false;
	
	for (Card c : cards) {
		if (!lolz) {
			if (c.type == card.type &&c.color == card.color) {
				lolz = true;
			}
			else {
				ccards.push_back(c);
			}
		}
		else {
			ccards.push_back(c);
		}
	}
	cards = ccards;

	std::cout << "endUseCard" << std::endl;
}
