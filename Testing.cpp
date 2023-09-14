#include "Board.h"
#include "Players.h"
#include <fstream>

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

void buildBoard(Board tile[], int num_spaces) {
	ifstream iFile;
	int tempI;
	string tempS;
	iFile.open("BoardData.txt");

	for (int i = 0; i < num_spaces; i++) {
		iFile >> tempI;
		tile[i].setPosition(tempI);
		iFile >> tempS;
		tile[i].setColor(tempS);
		iFile >> tempI;
		tile[i].setPrice(tempI);
		tile[i].setMortgagePrice(tempI / 2);
		iFile >> tempI;
		tile[i].setRentPrice(tempI);
		iFile.ignore();
		getline(iFile, tempS);
		tile[i].setName(tempS);
	}
}

void checkSpace(Board tile[], int position) {
	int index = position - 1;
	cout << "You landed on: " << endl;
	cout << tile[index].getPosition() << " ";
	cout << tile[index].getColor() << " ";
	cout << tile[index].getPrice() << " ";
	cout << tile[index].getMortgagePrice() << " ";
	cout << tile[index].getRentPrice() << endl;
	cout << tile[index].getName() << endl << endl;
}

int declareBankruptcy(Players player[], int index) {
	char choice;
	cout << "Do you want to declare bankruptcy? (y or n): ";
	cin >> choice;
	cout << endl;
	if(choice == 'y'){
		player[index].setBankrupt();
		cout << "You declared bankruptcy. Goodbye!" << endl;
		return 1;
	}
	else {
		cout << "Turn Over" << endl;
		return 0;
	}
}