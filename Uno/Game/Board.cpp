#include "Board.h"

Board::Board()
{
}

void Board::useCard(Card c)
{
	if (c.type == "cardReverse") {
		reverse = !reverse;
	}
	if (c.type == "cardBlock") {
		cycleUser();
	}
}

void Board::cycleUser()
{
	if (reverse) {
		user++;
		if (user > players.size()-1)
			user = 0;
	}
	else {
		user--;
		if (user < 0 ||user > players.size()-1)
			user = players.size()-1;
	}
}

void Board::start()
{
	reverse = false;
	deck.deck.clear();
	for (int i = 0; i < players.size(); i++) {
		players[i].cards.clear();
	}
	pile.deck.clear();

	deck.gen();
	deck.shuffle();
	for (int ii = 0; ii < 7; ii++) {
		for (int i = 0; i < players.size(); i++) {
			players[i].takeCard(deck.grabCard());
		}
	}
	user = rand() % players.size();
	pile.deck.push_back(deck.grabCard());

	std::cout << "Random user is: " << std::to_string(user) << std::endl;

	for (Player p : players) {
		std::cout << "name: " << p.name << ", id: " << std::to_string(p.user) << std::endl;
	}
}

void Board::handleWin()
{
	for (int i = 0; i < players.size(); i++) {
		players[i].points = players[i].calcPoints();
	}
}
