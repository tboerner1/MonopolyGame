#include "Board.h"
#include "Players.h"
#include <fstream>
#include <iomanip>

void buildBoard(Board tile[], int num_spaces);
void checkSpace(Board tile[], int position);
int declareBankruptcy(Players player[], int index);

int main() {

	const int NUM_SPACES = 41;
	const int NUM_PLAYERS = 2;
	int num_bankrupt = 0;
	Board tile[NUM_SPACES];
	buildBoard(tile, NUM_SPACES);
	Players player[NUM_PLAYERS];
	
	int i = 0;
	do{
		cout << "Player " << i + 1 << ": " << endl;
			player[i].rollDice();
			checkSpace(tile, player[i].getPosition());
			num_bankrupt += declareBankruptcy(player, i);
			if (i < NUM_PLAYERS-1) {
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
		/*if (id == "bProperty") {
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
		}*/
		iFile.ignore();
		getline(iFile, tempS);
		tile[i].setName(tempS);
	}
}

//this function gives the information about the space that the current player
//lands on.
void checkSpace(Board tile[], int position) {
	int index = position - 1;
	cout << "You landed on: " << endl;
	cout << left << setw(16) << "Position:" << right << setw(22) << tile[index].getPosition()<< endl;
	cout << left << setw(16) << "Color:" << right << setw(22) << tile[index].getColor()<< endl;
	cout << left << setw(16) << "Price:" << right << setw(22) << tile[index].getPrice() << endl;
	cout << left << setw(16) << "Mortgage Price:" << right << setw(22) << tile[index].getMortgagePrice() << endl;
	cout << left << setw(16) << "Rent Price:" << right << setw(22) << tile[index].getRentPrice() << endl;
	cout << left << setw(16) << "Rent 1 House:" << right << setw(22) << tile[index].getRent1() << endl;
	cout << left << setw(16) << "Rent 2 Houses:" << right << setw(22) << tile[index].getRent2() << endl;
	cout << left << setw(16) << "Rent 3 Houses:" << right << setw(22) << tile[index].getRent3() << endl;
	cout << left << setw(16) << "Rent 4 Houses:" << right << setw(22) << tile[index].getRent4() << endl;
	cout << left << setw(16) << "Rent Hotel:" << right << setw(22) << tile[index].getRentHotel() << endl;
	cout << left << setw(16) << "Name:" << right << setw(22) << tile[index].getName() << endl << endl;
}

//This function allows the current player to declare bankruptcy
//at the end of their turn
int declareBankruptcy(Players player[], int index) {
	string choice;
	cout << "Do you want to declare bankruptcy? (y or n): ";
	cin >> choice;
	cout << endl;
	if(choice == "y" || choice == "Y") {
		player[index].setBankrupt();
		cout << "You declared bankruptcy. Goodbye!" << endl;
		return 1;
	}
	else {
		cout << "Turn Over" << endl;
		return 0;
	}
}