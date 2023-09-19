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
	int getPrice() {
		return price;
	}
	int getMortgagePrice() {
		return mortgagePrice;
	}
	int getRentPrice() {
		return rentPrice;
	}
	int getPriceOfHouse() {
		return priceOfHouse;
	}
	int getRent1() {
		return rent1;
	}
	int getRent2() {
		return rent2;
	}
	int getRent3() {
		return rent3;
	}
	int getRent4() {
		return rent4;
	}
	int getRentHotel() {
		return rentHotel;
	}
	int getNumHouses() {
		return numHouses;
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
	int getOwner() {
		return owner;
	}
	string getId() {
		return id;
	}

	//iPosition is input position
	void setPosition(int iPosition) {
		position = iPosition;
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
	//iPriceOfHouse is input priceOfHouse
	void setPriceOfHouse(int iPriceOfHouse) {
		priceOfHouse = iPriceOfHouse;
	}
	//iRent is input rent price
	void setRent1(int iRent) {
		rent1 = iRent;
	}
	//iRent is input rent price
	void setRent2(int iRent) {
		rent2 = iRent;
	}
	//iRent is input rent price
	void setRent3(int iRent) {
		rent3 = iRent;
	}
	//iRent is input rent price
	void setRent4(int iRent) {
		rent4 = iRent;
	}
	//iRent is input rent price
	void setRentHotel(int iRent) {
		rentHotel = iRent;
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
	void setOwner(int iOwner) {
		owner = iOwner;
	}
	//iId is input id
	void setId(string iId) {
		id = iId;
	}

	//adds houses up to 5
	void addHouse() {
		if (numHouses < 5) {
			numHouses += 1;
		}
	}
	//subtracts houses down to 0
	void subtractHouse() {
		if (numHouses > 0) {
			numHouses -= 1;
		}
	}



private:
	int position = 0;
	string name = " ";
	//Possibly want isOccupied
	int price = 0, mortgagePrice = 0, rentPrice = 0;
	//set initial rent prices for buildings
	int rent1 = 0, rent2 = 0, rent3 = 0, rent4 = 0, rentHotel = 0;
	int priceOfHouse = 0;
	int numHouses = 0;
	int owner = 0;
	bool isOwned = false, isMortgaged = false, isMonopolized = false;
	string color = " ";
	string id = " ";
	//isTwo or isThree or isFour
};

#endif