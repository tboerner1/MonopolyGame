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
		for (int i = 0; i < 28; i++) {
			indexOfSpacesOwned[i] = -1;
		}
	}

	int getPosition() {
		return position;
	}
	int getMoney() {
		return money;
	}
	int getPlayerNum() {
		return playerNum;
	}
	string getPiece() {
		return piece;
	}
	int getDie1() {
		return die1;
	}
	int getDie2() {
		return die2;
	}
	bool getIsBankrupt() {
		return isBankrupt;
	}
	int getSpacesOwnedIndex(int index) {
		return indexOfSpacesOwned[index];
	}
	int getNumRailroads() {
		return numRailroads;
	}

	//iPosition is input position
	void setPosition(int iPosition) {
		position = iPosition;
	}
	//iMoney is input money
	void setMoney(int iMoney) {
		money = iMoney;
	}
	void subtractMoney(int value) {
		money -= value;
	}
	void addMoney(int value) {
		money += value;
	}
	//iPlayerNum is input playerNum
	void setPlayerNum(int iPlayerNum) {
		playerNum = iPlayerNum;
	}
	//iPiece is input piece
	void setPiece(string iPiece) {
		piece = iPiece;
	}
	//Once isBankrupt is true, it cannot be false again until a new game is started.
	void setBankrupt() {
		isBankrupt = true;
	}
	//This function initializes all the positions in the array to -1
	void initializeSpacesOwned() {
		for (int i = 0; i < 28; i++) {
			indexOfSpacesOwned[i] = -1;
		}
	}
	//index is the index of the tile
	void addProperty(int index) {
		int i = 0;
		while (index > indexOfSpacesOwned[i] && indexOfSpacesOwned[i] != -1) {
			i++;
		}
		for (int j = 28 - 2; j > i; j--) {
			indexOfSpacesOwned[j + 1] = indexOfSpacesOwned[j];
		}
		indexOfSpacesOwned[i] = index;
	}
	void subtractProperty(int index) {
		int i = 0;
		while (index != indexOfSpacesOwned[i]) {
			i++;
		}
		for (int j = i; j < 28 - 1; j++) {
			indexOfSpacesOwned[j] = indexOfSpacesOwned[j + 1];
		}
	}
	void addRailroad() {
		numRailroads += 1;
	}
	void subtractRailroad() {
		numRailroads -= 1;
	}

	//this function rolls two dice for an object of type Players.
	void rollDice() {
		string choice;
		cout << "Roll Dice? (y or n)";
		cin >> choice;
		cout << endl;
		if (choice == "Y" || choice == "y") {
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
	int playerNum = 0;
	string piece = " ";
	bool isBankrupt = false;
	int die1 = 0;
	int die2 = 0;
	string die3 = " ";
	int indexOfSpacesOwned[28];

	int numRailroads = 0;


	//This function moves the player after 2 dice are rolled.
	void move(int die1, int die2) {
		for (int i = 0; i < die1 + die2; i++) {
			if (position == 40) {
				position = 1;
				cout << "You passed GO, collect $200" << endl;
				money += 200;
				cout << "You now have $" << money << endl << endl;
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