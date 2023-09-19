#include "Board.h"
#include "Players.h"
#include <fstream>
#include <iomanip>

void buildBoard(Board tile[], int num_spaces);
void checkSpace(Board tile[], Players player[], int position, int playerNum);
int declareBankruptcy(Board tile[], Players player[], int index, int playerNum);
void buy(Board tile[], Players player[], int index, int playerNum);
void rent(Board tile[], Players player[], int index, int playerNum);


int main() {

	const int NUM_SPACES = 41;
	const int NUM_PLAYERS = 3;
	const int MONEY = 500;
	int num_bankrupt = 0;
	Board tile[NUM_SPACES];
	buildBoard(tile, NUM_SPACES);
	Players player[NUM_PLAYERS];

	for (int j = 0; j < NUM_PLAYERS; j++) {
		player[j].setPlayerNum(j + 1);
		player[j].setMoney(MONEY);
	}
	
	int i = 0;
	do{
		if (!player[i].getIsBankrupt()) {
			cout << "Player " << i + 1 << ": " << endl;
			player[i].rollDice();
			checkSpace(tile, player, player[i].getPosition(), player[i].getPlayerNum());
			num_bankrupt += declareBankruptcy(tile, player, i, player[i].getPlayerNum());
		}
		if (i < NUM_PLAYERS - 1) {
			i++;
		}
		else {
			i = 0;
		}
	} while (num_bankrupt < NUM_PLAYERS - 1);


}


//This function creates the board by pulling data from a .txt file
void buildBoard(Board tile[], int num_spaces) {
	ifstream iFile;
	int tempI;
	string tempS;
	string id;
	iFile.open("BoardData.txt");

	for (int i = 0; i < num_spaces; i++) {
		iFile >> tempI;
		tile[i].setPosition(tempI);
		iFile >> id;
		tile[i].setId(id);
		if (id == "bProperty") {
			iFile >> tempS;
			tile[i].setColor(tempS);
		}
		if (id == "bProperty" || id == "utility" || id == "railroad") {
			iFile >> tempI;
			tile[i].setPrice(tempI);
			tile[i].setMortgagePrice(tempI / 2);
		}
		if (id == "bProperty" || id == "railroad") {
			iFile >> tempI;
			tile[i].setRentPrice(tempI);
		}
		if (id == "bProperty") {
			iFile >> tempI;
			tile[i].setRent1(tempI);
			iFile >> tempI;
			tile[i].setRent2(tempI);
			iFile >> tempI;
			tile[i].setRent3(tempI);
			iFile >> tempI;
			tile[i].setRent4(tempI);
			iFile >> tempI;
			tile[i].setRentHotel(tempI);
			iFile >> tempI;
			tile[i].setPriceOfHouse(tempI);
		}
		iFile.ignore();
		getline(iFile, tempS);
		tile[i].setName(tempS);
	}
}

//this function gives the information about the space that the current player
//lands on.
void checkSpace(Board tile[], Players player[], int position, int playerNum) {
	int index = position - 1;
	cout << "You landed on: " << endl;
	cout << tile[index].getName() << " ";
	if (tile[index].getColor() != " ") {
		cout << "(" << tile[index].getColor() << ")";
	}
	cout << endl << endl;
	if (tile[index].getId() == "bProperty" || tile[index].getId() == "utility" || tile[index].getId() == "railroad") {
		if (!tile[index].getIsOwned()) {
			buy(tile, player, index, playerNum);
			
		}
		else{
			if (tile[index].getId() == "bProperty") {
				rent(tile, player, index, playerNum);
			}
		}
	}

	//cout << left << setw(16) << "Position:" << right << setw(22) << tile[index].getPosition()<< endl;
	//cout << left << setw(16) << "Color:" << right << setw(22) << tile[index].getColor()<< endl;
	//cout << left << setw(16) << "Price:" << right << setw(22) << tile[index].getPrice() << endl;
	//cout << left << setw(16) << "Mortgage Price:" << right << setw(22) << tile[index].getMortgagePrice() << endl;
	//cout << left << setw(16) << "Rent Price:" << right << setw(22) << tile[index].getRentPrice() << endl;
	//cout << left << setw(16) << "Rent 1 House:" << right << setw(22) << tile[index].getRent1() << endl;
	//cout << left << setw(16) << "Rent 2 Houses:" << right << setw(22) << tile[index].getRent2() << endl;
	//cout << left << setw(16) << "Rent 3 Houses:" << right << setw(22) << tile[index].getRent3() << endl;
	//cout << left << setw(16) << "Rent 4 Houses:" << right << setw(22) << tile[index].getRent4() << endl;
	//cout << left << setw(16) << "Rent Hotel:" << right << setw(22) << tile[index].getRentHotel() << endl;
	//cout << left << setw(16) << "Price Of House:" << right << setw(22) << tile[index].getPriceOfHouse() << endl;
	//cout << left << setw(16) << "Name:" << right << setw(22) << tile[index].getName() << endl << endl;
}

void buy(Board tile[], Players player[], int index, int playerNum) {
	string choice = "y";
	while (player[playerNum - 1].getMoney() < tile[index].getPrice() && choice == "y") {
		cout << "You don't have enough money to purchase this property\n"
			<< "Would you like to build/mortgage your properties? (y or n)";
		cin >> choice;
		if (choice == "Y") {
			choice = "y";
		}
	}
	if (player[playerNum - 1].getMoney() >= tile[index].getPrice()) {
		cout << "Player " << playerNum << ": Would you like to buy " << tile[index].getName()
			<< " for $" << tile[index].getPrice() << "? (y or n)";
		cin >> choice;
		if (choice == "Y" or choice == "y") {
			tile[index].setIsOwned();
			tile[index].setOwner(playerNum);
			player[playerNum - 1].subtractMoney(tile[index].getPrice());
			cout << "Player " << playerNum << " bought " << tile[index].getName() << endl;
			cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
		}
	}
	else {
		cout << "You don't have enough money to purchase this property." << endl << endl;
	}
}

void rent(Board tile[], Players player[], int index, int playerNum) {
	int tempRent = 0;
	string choice = "y";
	if (tile[index].getOwner() != playerNum) {
		cout << "This property is owned by Player " << tile[index].getOwner() << endl;
		if (tile[index].getNumHouses() == 0 && !tile[index].getIsMonopolized()) {
			tempRent = tile[index].getRentPrice();
		}
		else if (tile[index].getNumHouses() == 1) {
			tempRent = tile[index].getRent1();
		}
		else if (tile[index].getNumHouses() == 2) {
			tempRent = tile[index].getRent2();
		}
		else if (tile[index].getNumHouses() == 3) {
			tempRent = tile[index].getRent3();
		}
		else if (tile[index].getNumHouses() == 4) {
			tempRent = tile[index].getRent4();
		}
		else {
			tempRent = tile[index].getRentHotel();
		}
		cout << "You owe $" << tempRent << endl;
		if (tempRent > player[playerNum - 1].getMoney()) {
			while (player[playerNum - 1].getMoney() < tempRent && choice == "y") {
				cout << "You don't have enough money to pay rent\n"
					<< "Would you like to build/mortgage your properties? (y or n)";
				cin >> choice;
				if (choice == "Y") {
					choice = "y";
				}
			}
			if (tempRent > player[playerNum - 1].getMoney()) {
				cout << "You don't have enough money to pay rent\n"
					<< "You must declare bankruptcy\n";
				player[playerNum - 1].setMoney(-1);
			}
			else {
				player[playerNum - 1].subtractMoney(tempRent);
				cout << "Player " << playerNum << " paid Player " << tile[index].getOwner()
					<< " $" << tempRent << endl;
			}
		}
		else {
			player[playerNum - 1].subtractMoney(tempRent);
			cout << "Player " << playerNum << " paid Player " << tile[index].getOwner()
				<< " $" << tempRent << endl;
		}
	}
	else {
		cout << "This property is owned by YOU" << endl;
	}
	if (player[playerNum - 1].getMoney() != -1) {
		cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
	}
}



//This function allows the current player to declare bankruptcy
//at the end of their turn
int declareBankruptcy(Board tile[], Players player[], int index, int playerNum) {
	if (player[playerNum].getMoney() == -1) {
		player[playerNum - 1].setBankrupt();
		cout << "You declared bankruptcy. Goodbye!" << endl << endl;
		return 1;
	}
	else {
		string choice;
		cout << "Do you want to declare bankruptcy? (y or n): ";
		cin >> choice;
		if (choice == "y" || choice == "Y") {
			player[playerNum - 1].setBankrupt();
			cout << "You declared bankruptcy. Goodbye!" << endl << endl;
			return 1;
		}
		else {
			cout << "Turn Over" << endl << endl;
			return 0;
		}
	}

}