#pragma once

#ifndef H_Players
#define H_Players

#include <iostream>
#include <string>
#include <cstdlib>
#include "Board.h"

using namespace std;

class Players {
public:
	Players() {
		srand(time(0));
	}

	int getPosition() {
		return position;
	}
	int getMoney() {
		return money;
	}
	string getPiece() {
		return piece;
	}
	bool getIsBankrupt() {
		return isBankrupt;
	}

	//iPosition is input position
	void setPosition(int iPosition) {
		position = iPosition;
	}
	//iMoney is input money
	void setMoney(int iMoney) {
		money = iMoney;
	}
	//iPiece is input piece
	void setPiece(string iPiece) {

	}
	//Once isBankrupt is true, it cannot be false again until a new game is started.
	void setBankrupt() {
		isBankrupt = true;
	}

	void rollDice() {
		char choice;
		cout << "Roll Dice? (y or n)";
		cin >> choice;
		cout << endl;
		if (choice == 'y') {
			die1 = (rand() % 6) + 1;
			die2 = (rand() % 6) + 1;
			cout << "You Rolled a " << die1 << " and a " << die2 << endl;
			move(die1, die2);
		}
		else {
			move(0, 0);
		}
	}

	
private:
	int position = 1;
	int money = 0;
	string piece = " ";
	bool isBankrupt = false;
	int die1 = 0;
	int die2 = 0;
	string die3 = " ";

	void move(int die1, int die2) {
		for (int i = 0; i < die1 + die2; i++) {
			if (position == 40) {
				position = 0;
			}
			else if (position == 41) {
				position = 41;
			}
			else {
				position += 1;
			}
		}
	}
};

#endif