#pragma once

#ifndef H_Board
#define H_Board

#include <iostream>
#include <string>
using namespace std;

class Board {
public:
	string getName() {
		return name;
	}
	int getPosition() {
		return position;
	}
	//iName is input name
	void setName(string iName) {
		name = iName;
	}
	//iPosition is input position
	void setPosition(int iPosition) {
		position = iPosition;
	}

	int getPrice() {
		return price;
	}
	int getMortgagePrice() {
		return mortgagePrice;
	}
	int getRentPrice() {
		return rentPrice;
	}
	bool getIsOwned() {
		return isOwned;
	}
	bool getIsMortgaged() {
		return isMortgaged;
	}
	bool getIsMonopolized() {
		return isMonopolized;
	}
	string getColor() {
		return color;
	}
	string getOwner() {
		return owner;
	}

	//iPrice is input Price;
	void setPrice(int iPrice) {
		price = iPrice;
	}
	//iMortgagePrice is input mortgage price
	void setMortgagePrice(int iMortgagePrice) {
		mortgagePrice = iMortgagePrice;
	}
	//iRentPrice is input rent price
	void setRentPrice(int iRentPrice) {
		rentPrice = iRentPrice;
	}
	//isOwned set to true because once owned
	//a property will always be owned by someone
	void setIsOwned() {
		isOwned = true;
	}
	//isMortgaged is flipped whenever setIsMortgage
	//is called because it doesn't need to be set
	//to specific values.
	void setIsMortgaged() {
		isMortgaged = !isMortgaged;
	}
	//isMonopolized is flipped whenever setIsMonopolized
	//is called because it doesn't need to be set
	//to specific values.
	void setIsMonopolized() {
		isMonopolized = !isMonopolized;
	}
	//iColor is input color
	void setColor(string iColor) {
		color = iColor;
	}
	//iOwner is input owner
	void setOwner(string iOwner) {
		owner = iOwner;
	}


private:
	int position = 0;
	string name = " ";
	//Possibly want isOccupied
	int price = 0, mortgagePrice = 0, rentPrice = 0;
	bool isOwned = false, isMortgaged = false, isMonopolized = false;
	string color = " ";
	string owner = " ";
	//isTwo or isThree or isFour
};

#endif