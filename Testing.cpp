#include "Board.h"
#include "Players.h"
#include <fstream>
#include <iomanip>


void buildBoard(Board tile[], int num_spaces);
void checkSpace(Board tile[], Players player[], int index, int playerNum);
int declareBankruptcy(Board tile[], Players player[], int index, int playerNum);
void buy(Board tile[], Players player[], int index, int playerNum);
void addTile(Board tile[], Players player[], int index, int playerNum);
void rent(Board tile[], Players player[], int index, int playerNum);
int propertyRent(Board tile[], Players player[], int index, int playerNum);
int utilityRent(Board tile[], Players player[], int index, int playerNum);
int railroadRent(Board tile[], Players player[], int index, int playerNum);
void tax(Board tile[], Players player[], int index, int playerNum);
void checkMortgage(Board tile[], Players player[], int index, int playerNum, int owed, string toPay);
void checkMortgage(Board tile[], Players player[], int index, int playerNum);
void forceBankruptcy(Board tile[], Players player[], int index, int playerNum, int owed, string toPay);
void mortgage(Board tile[], Players player[], int index, int playerNum);
void buildMortgage(Board tile[], Players player[], int index, int playerNum);
void build(Board tile[], Players player[], int index, int playerNum);
void removeHouses(Board tile[], Players player[], int index, int playerNum);
void giveTile(Board tile[], Players player[], int index, int playerNum);
void monopolize(Board tile[], Players player[], int index, int PlayerNum);
bool checkIsMortgaged(Board tile[], Players player[], int index, int playerNum);

const int BROWN1 = 1;
const int BROWN2 = 3;
const int RAILROAD1 = 5;
const int LIGHT_BLUE1 = 6;
const int LIGHT_BLUE2 = 8;
const int LIGHT_BLUE3 = 9;
const int PINK1 = 11;
const int UTILITY1 = 12;
const int PINK2 = 13;
const int PINK3 = 14;
const int RAILROAD2 = 15;
const int ORANGE1 = 16;
const int ORANGE2 = 18;
const int ORANGE3 = 19;
const int F_PARKING = 20;
const int RED1 = 21;
const int RED2 = 23;
const int RED3 = 24;
const int RAILROAD3 = 25;
const int YELLOW1 = 26;
const int YELLOW2 = 27;
const int UTILITY2 = 28;
const int YELLOW3 = 29;
const int GT_JAIL = 30;
const int GREEN1 = 31;
const int GREEN2 = 32;
const int GREEN3 = 34;
const int RAILROAD4 = 35;
const int DARK_BLUE1 = 37;
const int DARK_BLUE2 = 39;
const int JAIL = 40;

int main() {
	const int NUM_SPACES = 41;
	const int NUM_PLAYERS = 3;
	const int MONEY = 2000;
	int num_bankrupt = 0;
	Board tile[NUM_SPACES];
	Players player[NUM_PLAYERS];


	buildBoard(tile, NUM_SPACES);


	for (int j = 0; j < NUM_PLAYERS; j++) {
		player[j].setPlayerNum(j + 1);
		player[j].setMoney(MONEY);
		player[j].initializeSpacesOwned();
	}
	giveTile(tile, player, DARK_BLUE2, 1);
	giveTile(tile, player, DARK_BLUE1, 1);
	giveTile(tile, player, ORANGE1, 2);
	giveTile(tile, player, ORANGE2, 2);
	giveTile(tile, player, ORANGE3, 2);

	
	int i = 0;
	do{
		if (!player[i].getIsBankrupt()) {
			cout << "Player " << i + 1 << ": " << endl;
			cout << "You have $" << player[i].getMoney() << endl;
			player[i].rollDice();
			checkSpace(tile, player, player[i].getPosition() - 1, player[i].getPlayerNum());
			//TESTING PURPOSES
			checkMortgage(tile, player, player[i].getPosition() - 1, player[i].getPlayerNum());
			//FINISH TESTING
			num_bankrupt += declareBankruptcy(tile, player, player[i].getPosition()-1, player[i].getPlayerNum());
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
		if (id == "go") {
			iFile >> tempI;
			tile[i].setPrice(tempI);
		}
		if (id == "bProperty" || id == "railroad" || id == "tax") {
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
void checkSpace(Board tile[], Players player[], int index, int playerNum) {
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
		else {
			rent(tile, player, index, playerNum);
		}
	}
	if (tile[index].getId() == "tax") {
		tax(tile, player, index, playerNum);
	}
	if (tile[index].getId() == "gtJail") {
		player[playerNum - 1].setPosition(41);
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
	checkMortgage(tile, player, index, playerNum, tile[index].getPrice(), "to purchase this property");
	string choice = "y";
	if (player[playerNum - 1].getMoney() >= tile[index].getPrice()) {
		cout << "Player " << playerNum << ": Would you like to buy " << tile[index].getName()
			<< " for $" << tile[index].getPrice() << "? (y or n)";
		cin >> choice;
		if (choice == "Y" or choice == "y") {
			giveTile(tile, player, index, playerNum);
			player[playerNum - 1].subtractMoney(tile[index].getPrice());
			cout << "Player " << playerNum << " bought " << tile[index].getName() << endl;
			cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
		}
	}
	else {
		cout << "You don't have enough money to purchase this property." << endl << endl;
	}
}

//Allows giving a tile to a player without making them have to purchase it
void giveTile(Board tile[], Players player[], int index, int playerNum) {
	tile[index].setIsOwned();
	tile[index].setOwner(playerNum);
	player[playerNum - 1].addProperty(index);
	addTile(tile, player, index, playerNum);
}

//this function adds the tile in one of the player's numColor variables, it also
//monopolizes a tile if need be.
void addTile(Board tile[], Players player[], int index, int playerNum) {
	if (tile[index].getId() == "utility") {
		player[playerNum - 1].addUtility();
	}
	else if (tile[index].getId() == "railroad") {
		player[playerNum - 1].addRailroad();
	}
	else {
		if (tile[index].getColor() == "Brown") {
			player[playerNum - 1].addBrown();
		}
		else if (tile[index].getColor() == "Light_Blue") {
			player[playerNum - 1].addLightBlue();
		}
		else if (tile[index].getColor() == "Pink") {
			player[playerNum - 1].addPink();
		}
		else if (tile[index].getColor() == "Orange") {
			player[playerNum - 1].addOrange();
		}
		else if (tile[index].getColor() == "Red") {
			player[playerNum - 1].addRed();
		}
		else if (tile[index].getColor() == "Yellow") {
			player[playerNum - 1].addYellow();
		}
		else if (tile[index].getColor() == "Green") {
			player[playerNum - 1].addGreen();
		}
		else if (tile[index].getColor() == "Dark_Blue") {
			player[playerNum - 1].addDarkBlue();
		}
	}
	monopolize(tile, player, index, playerNum);
}

//This function sets any property to a monopoly if the player has the correct amount of that property
void monopolize(Board tile[], Players player[], int index, int PlayerNum) {
	if (tile[index].getId() == "utility" && player[PlayerNum-1].getNumUtilities()== 2) {
		tile[UTILITY1].setIsMonopolized();
		tile[UTILITY2].setIsMonopolized();
	}
	else if (tile[index].getId() == "railroad" && player[PlayerNum - 1].getNumUtilities() == 4) {
		tile[RAILROAD1].setIsMonopolized();
		tile[RAILROAD2].setIsMonopolized();
		tile[RAILROAD3].setIsMonopolized();
		tile[RAILROAD4].setIsMonopolized();
	}
	else if (tile[index].getId() == "bProperty") {
		if (tile[index].getColor() == "Brown" && player[PlayerNum - 1].getNumBrown() == 2) {
			tile[BROWN1].setIsMonopolized();
			tile[BROWN2].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Light_Blue" && player[PlayerNum - 1].getNumLightBlue() == 3) {
			tile[LIGHT_BLUE1].setIsMonopolized();
			tile[LIGHT_BLUE2].setIsMonopolized();
			tile[LIGHT_BLUE3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Pink" && player[PlayerNum - 1].getNumPink() == 3) {
			tile[PINK1].setIsMonopolized();
			tile[PINK2].setIsMonopolized();
			tile[PINK3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Orange" && player[PlayerNum - 1].getNumOrange() == 3) {
			tile[ORANGE1].setIsMonopolized();
			tile[ORANGE2].setIsMonopolized();
			tile[ORANGE3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Red" && player[PlayerNum - 1].getNumRed() == 3) {
			tile[RED1].setIsMonopolized();
			tile[RED2].setIsMonopolized();
			tile[RED3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Yellow" && player[PlayerNum - 1].getNumYellow() == 3) {
			tile[YELLOW1].setIsMonopolized();
			tile[YELLOW2].setIsMonopolized();
			tile[YELLOW3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Green" && player[PlayerNum - 1].getNumGreen() == 3) {
			tile[GREEN1].setIsMonopolized();
			tile[GREEN2].setIsMonopolized();
			tile[GREEN3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Dark_Blue" && player[PlayerNum - 1].getNumDarkBlue() == 2) {
			tile[DARK_BLUE1].setIsMonopolized();
			tile[DARK_BLUE2].setIsMonopolized();
		}
	}

}

//Forces the player to pay rent to another play, then the player either
//mortgages properties or declares bankruptcy
void rent(Board tile[], Players player[], int index, int playerNum) {
	int tempRent = 0;
	//checks if the property is not owned by the current player and that it
	//is not mortgaged.
	if (tile[index].getOwner() != playerNum && !tile[index].getIsMortgaged()) {
		cout << "This property is owned by Player " << tile[index].getOwner() << endl;
		//Sets the rent of buildableProperties
		if (tile[index].getId() == "bProperty") {
			tempRent = propertyRent(tile, player, index, playerNum);
		}
		//Sets the rent of utilities
		else if (tile[index].getId() == "utility") {
			tempRent = utilityRent(tile, player, index, playerNum);
		}
		//sets the rent of railroads
		else if (tile[index].getId() == "railroad") {
			tempRent = railroadRent(tile, player, index, playerNum);
		}
		cout << "You owe $" << tempRent << endl;
		checkMortgage(tile, player, index, playerNum, tempRent, "to pay for rent");
		if (tempRent > player[playerNum - 1].getMoney()) {	
			forceBankruptcy(tile, player, index, playerNum, tempRent, "to pay for rent");
		}
		if (tempRent <= player[playerNum - 1].getMoney()) {
			player[playerNum - 1].subtractMoney(tempRent);
			cout << "Player " << playerNum << " paid Player " << tile[index].getOwner()
				<< " $" << tempRent << endl;
			player[tile[index].getOwner() - 1].addMoney(tempRent);
		}
	}
	else if (tile[index].getOwner() == playerNum) {
		cout << "This property is owned by YOU" << endl;
	}
	else if (tile[index].getIsMortgaged()) {
		cout << "This property is MORTGAGED" << endl;
	}
	if (player[playerNum - 1].getMoney() != -1) {
		cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
	}
}

//This calculates the property rent and returns it to rent.
int propertyRent(Board tile[], Players player[], int index, int playerNum) {
	if (tile[index].getNumHouses() == 0 && !tile[index].getIsMonopolized()) {
		return tile[index].getRentPrice();
	}
	else if (tile[index].getNumHouses() == 0 && tile[index].getIsMonopolized()) {
		return (tile[index].getRentPrice() * 2);
	}
	else if (tile[index].getNumHouses() == 1) {
		return tile[index].getRent1();
	}
	else if (tile[index].getNumHouses() == 2) {
		return tile[index].getRent2();
	}
	else if (tile[index].getNumHouses() == 3) {
		return tile[index].getRent3();
	}
	else if (tile[index].getNumHouses() == 4) {
		return tile[index].getRent4();
	}
	else {
		return tile[index].getRentHotel();
	}
}

//This calculates the rent based on utility rent rules, then the player either
//pays the rent, mortgages properties, or declares bankruptcy
int utilityRent(Board tile[], Players player[], int index, int playerNum){
	if (!tile[index].getIsMonopolized()) {
		return (4 * (player[playerNum - 1].getDie1() + player[playerNum - 1].getDie2()));
	}
	else {
		return (10 * (player[playerNum - 1].getDie1() + player[playerNum - 1].getDie2()));
	}
}

//This calculates the rent based on railroad rent rules, then the player either
//pays the rent, mortgages properties, or declares bankruptcy
int railroadRent(Board tile[], Players player[], int index, int playerNum) {
	if (player[tile[index].getOwner() - 1].getNumRailroads() == 2) {
		return 50;
	}
	else if (player[tile[index].getOwner() - 1].getNumRailroads() == 3) {
		return 100;
	}
	else if (player[tile[index].getOwner() - 1].getNumRailroads() == 4) {
		return 200;
	}
	else {
		return 25;
	}
}

//This forces the player to pay their taxes, mortgage properties, or declare bankruptcy
void tax(Board tile[], Players player[], int index, int playerNum) {
	int tempTax = tile[index].getRentPrice();
	cout << "You owe $" << tempTax << " for taxes" << endl;
	checkMortgage(tile, player, index, playerNum, tempTax, "to pay your taxes");
	if (tempTax > player[playerNum - 1].getMoney()) {
		forceBankruptcy(tile, player, index, playerNum, tempTax, "to pay your taxes");
	}
	if (player[playerNum -1].getMoney() != -1) {
		player[playerNum - 1].subtractMoney(tempTax);
		//this adds to the price of free parking which is at index 20
		tile[F_PARKING].addPrice(tempTax);
		cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
	}
}

//This functions checks if the player wants to mortgage their properties because
//they don't have enough money to pay for something.
void checkMortgage(Board tile[], Players player[], int index, int playerNum, int owed, string toPay) {
	string choice = "n";
	while (player[playerNum - 1].getMoney() < owed) {
		cout << "You don't have enough money " << toPay << endl
			<< "Would you like to build/mortgage your properties? (y or n): ";
		cin >> choice;
		if (choice == "Y" || choice == "y") {
			cout << "You owe $" << owed << endl <<endl;
			buildMortgage(tile, player, index, playerNum);
		}
		else {
			break;
		}
	}
}

//Overloaded function based on the number of parameters. This checkMortgage
//allows players to build and mortgage their properties without forcing them to
void checkMortgage(Board tile[], Players player[], int index, int playerNum) {
	string choice = "n";
	while (player[playerNum - 1].getMoney() >= 0) {
		cout << "Would you like to build/mortgage your properties? (y or n): ";
		cin >> choice;
		cout << endl;
		if (choice == "Y" || choice == "y") {
			buildMortgage(tile, player, index, playerNum);
		}
		else {
			break;
		}
	}
}

//This prints off the list of properties for the current player
//Then it lets the player choose if they want to build or mortgage
void buildMortgage(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	//represents property choice
	int choice = -1;
	//represents build or mortgage choice
	string choice2 = " ";
	int counter = 1;
	cout << "You have $" << player[playerNum - 1].getMoney() << endl << endl;
	cout << "Here is your list of properties:" << endl;
	//i is the position in the array that stores the indexes of the properties owned
	while (player[playerNum - 1].getSpacesOwnedIndex(i) != -1 && i != 28 && choice != 0) {
		//tileIndex is the index of the tiles that the player owns
		int tileIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		cout << counter << "." << endl << tile[tileIndex].getName();
		//checks to see if the tile has a color and prints it if it does
		if (tile[tileIndex].getColor() != " ") {
			cout << "(" << tile[tileIndex].getColor() << ")" << endl;
		}
		else {
			cout << endl;
		}
		if (tile[tileIndex].getIsMonopolized() && tile[tileIndex].getId()=="bProperty") {
			cout << "House Price: $" << tile[tileIndex].getPriceOfHouse() << endl;
			if (tile[tileIndex].getNumHouses() != 5) {
				cout << "Number of Houses: " << tile[tileIndex].getNumHouses() << endl;
			}
			else {
				cout << "Hotel" << endl;
			}
		}
		cout << "Mortgage Value: $" << tile[tileIndex].getMortgagePrice() << endl;
		if (tile[tileIndex].getIsMortgaged()) {
			cout << "MORTGAGED" << endl << endl;
		}
		else {
			cout << "UNMORTGAGED" << endl << endl;
		}
		i++;
		counter++;
		if ((i == 28 && choice > 0) || player[playerNum - 1].getSpacesOwnedIndex(i) == -1) {
			cout << "Please enter the number of the property you would like to build/mortgage/unmortgage\n"
				<< "Only enter 1 number at a time. Please enter an integer value (0 to end): ";
			cin >> choice;
			cout << endl;
			if (choice > 0 && choice <= i) {
				int tileIndex = player[playerNum - 1].getSpacesOwnedIndex(choice - 1);
				//if property is a buildable property, monopolized, and not mortgaged, and doesn't 
				//have mortgaged properties in its set.
				if (tile[tileIndex].getId() == "bProperty" && tile[tileIndex].getIsMonopolized() && !tile[tileIndex].getIsMortgaged() 
					&& !checkIsMortgaged(tile, player, tileIndex, playerNum)) {
					cout << "Would you like to build or mortgage property? (Enter 'B' for build, 'M' for mortgage): ";
					cin >> choice2;
				}
				cout << endl;
				if (choice2 == "B" || choice2 == "b") {
						build(tile, player, tileIndex, playerNum);
					
				}
				else {
					mortgage(tile, player, tileIndex, playerNum);
				}
			}
			choice2 = "m";
			i = 0;
			counter = 1;
		}
	}
}

//This function allows players to add or remove houses 1 at a time
void build(Board tile[], Players player[], int index, int playerNum) {
	int choice = -1;
	int tempMoney =0;
	int tempIndex = -1;
	int i = 0;
	int j = 0;
	int tempNumHouses = 0;
	int tempNumHouses2 = 0;
	int tempNumHouses3 = 0;
	int otherPropertiesIndex[] = { -1, -1 };
	string tempColor = " ";

	cout << "NOTE: The number of houses for a property can only exceed the minimum number of \n"
		<< "houses, in that color set, by 1\n"
		<< "(The number of houses for the other properties in the set\n"
		<< "will be automatically adjusted to ensure this stays true)" << endl;
	cout << "Adding a 5th house is the same as adding a hotel" << endl << endl;
	cout << "How many houses would you like to add? (0 to end): " ;
	cin >> choice;
	if (choice > 0 && choice <= 5 - tile[index].getNumHouses()) {
		tempMoney = choice * tile[index].getPriceOfHouse();
		tempColor = tile[index].getColor();
		tempNumHouses = choice;
		//If color is not Brown or Dark_Blue, find two other properties
		if (tempColor != "Brown" && tempColor != "Dark_Blue") {
			while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1 && j < 2) {
				tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
				if (tile[tempIndex].getColor() == tempColor && tempIndex != index) {
					otherPropertiesIndex[j] = tempIndex;
					j++;
				}
				i++;
			}
		}
		//if color is Brown or Dark_Blue, find one other property.
		else {
			while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1 && j < 1) {
				tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
				if (tile[tempIndex].getColor() == tempColor && tempIndex != index) {
					otherPropertiesIndex[j] = tempIndex;
					j++;
				}
				i++;
			}
		}
		//While the first other property's number of houses is more than 1 less 
		//than the property we are building on, add up the money it would take to
		//get the first other property to have the number of houses to be 1 less
		//than the property we are building on
		for (int k = tile[otherPropertiesIndex[0]].getNumHouses(); k < tile[index].getNumHouses() + choice - 1; k++) {
			tempMoney += tile[index].getPriceOfHouse();
			tempNumHouses2 += 1;
		}
		//If there is a second other property
		if (j == 2) {
			//While the second other property's number of houses is more than 1 less 
			//than the property we are building on, add up the money it would take to
			//get the second other property to have the number of houses to be 1 less
			//than the property we are building on
			for (int k = tile[otherPropertiesIndex[1]].getNumHouses(); k < tile[index].getNumHouses() + choice - 1; k++) {
				tempMoney += tile[index].getPriceOfHouse();
				tempNumHouses3 += 1;
			}
		}
		//If the player has enough money for all the houses
		if (player[playerNum - 1].getMoney() >= tempMoney) {
			//sets the number of houses for the property we are currently building
			//on and subtracts money from the player
			for (int k = 0; k < choice; k++) {
				tile[index].addHouse();
				player[playerNum - 1].subtractMoney(tile[index].getPriceOfHouse());
			}
			cout << "Player " << playerNum << " added " << tempNumHouses << " houses to "
				<< tile[index].getName() << " (" << tile[index].getColor() << ")" << endl;
			//While the first other property's number of houses is more than 1 less 
			//than the property we are building on, add the number of houses it would take to
			//get the first other property to have the number of houses to be 1 less
			//than the property we are building on
			//Then subtract the house price from the player
			for (int k = tile[otherPropertiesIndex[0]].getNumHouses(); k < tile[index].getNumHouses() - 1; k++) {
				tile[otherPropertiesIndex[0]].addHouse();
				player[playerNum - 1].subtractMoney(tile[index].getPriceOfHouse());
			}
			cout << "Player " << playerNum << " added " << tempNumHouses2 << " houses to "
				<< tile[otherPropertiesIndex[0]].getName() << " (" << tile[otherPropertiesIndex[0]].getColor()
				<< ")" << endl;
			//If there is a second other property
			if (j == 2) {
				//While the second other property's number of houses is more than 1 less 
				//than the property we are building on, add the number of houses it would take to
				//get the second other property to have the number of houses to be 1 less
				//than the property we are building on
				//Then subtract the house price from the player
				for (int k = tile[otherPropertiesIndex[1]].getNumHouses(); k < tile[index].getNumHouses() - 1; k++) {
					tile[otherPropertiesIndex[1]].addHouse();
					player[playerNum - 1].subtractMoney(tile[index].getPriceOfHouse());
				}
				cout << "Player " << playerNum << " added " << tempNumHouses3 << " houses to "
					<< tile[otherPropertiesIndex[1]].getName() << " (" << tile[otherPropertiesIndex[1]].getColor()
					<< ")" << endl;
			}
		}
		//If the player doesn't have enough money
		else {
			cout << "Player " << playerNum << ", you don't have enough money to build "
				<< tempNumHouses + tempNumHouses2 + tempNumHouses3 << " houses" << endl;
		}
	}
	//If the player entered a number outside of how many houses the person can build
	else if(choice != 0) {
		cout << "You can't build " << choice << " houses on " << tile[index].getName()
			<< " (" << tile[index].getColor() << ")" << endl;
	}
	cout << "You now have $" << player[playerNum - 1].getMoney();
	cout << endl;
}

//This function removes the houses from every property in that color if
//one has been mortgaged, and it adds the cost of those houses to the 
//player's money
void removeHouses(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	int tempIndex = -1;
	int tempMoney = 0;
	string tempColor = tile[index].getColor();
	while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1) {
		tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		//if a tile is the same color as the tile being mortgaged, remove all the houses
		//from it and pay the user for all those houses. Then setNumHouses = 0;
		if (tile[tempIndex].getColor() == tempColor) {
			tempMoney = tile[tempIndex].getNumHouses() * tile[tempIndex].getPriceOfHouse();
			player[playerNum - 1].addMoney(tempMoney);
			tile[tempIndex].setHouseZero();
		}
		i++;
	}
	//adds mortgage price on at the end since the property will still be mortgaged.
	player[playerNum - 1].addMoney(tile[index].getMortgagePrice());
}


//Checks if there is a mortgaged property in a set
bool checkIsMortgaged(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	int tempIndex = -1;
	string tempColor = tile[index].getColor();
	while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1) {
		tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		//if a tile is the same color as the tile being mortgaged, remove all the houses
		//from it and pay the user for all those houses. Then setNumHouses = 0;
		if (tile[tempIndex].getColor() == tempColor && tile[tempIndex].getIsMortgaged()) {
			return true;
		}
		i++;
	}
	return false;
}

//This mortgages or unmortgages a property depending on what state it is in, then
//it adds or subtracts from the players money.
void mortgage(Board tile[], Players player[], int index, int playerNum) {
	//If the tile is unmortgaged and the number of houses is 0
	if (!tile[index].getIsMortgaged() && tile[index].getNumHouses() == 0) {
		player[playerNum - 1].addMoney(tile[index].getMortgagePrice());
		cout << "Player " << playerNum << " mortgaged " << tile[index].getName();
		if (tile[index].getColor() != " ") {
			cout << "(" << tile[index].getColor() << ")" << endl;
		}
		else {
			cout << endl;
		}
	}
	//if the tile is not mortgaged and the number of houses is not 0
	else if (!tile[index].getIsMortgaged() && tile[index].getIsMonopolized()) {
		removeHouses(tile, player, index, playerNum);
	}
	//if the tile is mortgaged 
	else if(tile[index].getIsMortgaged()){
		//If player has enough money
		if (player[playerNum - 1].getMoney() >= tile[index].getMortgagePrice()) {
			player[playerNum - 1].subtractMoney(tile[index].getMortgagePrice());
			cout << "Player " << playerNum << " unmortgaged " << tile[index].getName();
			if (tile[index].getColor() != " ") {
				cout << "(" << tile[index].getColor() << ")" << endl;
			}
			else {
				cout << endl;
			}
		}
		//If player doesn't have enough money
		else {
			//reverses the mortgage status because it will be reversed again at
			//the end of this function.
			tile[index].setIsMortgaged();
			cout << "You don't have enough to unmortgage that property" << endl;
		}
	}
	cout << "You now have $" << player[playerNum - 1].getMoney() << endl;
	tile[index].setIsMortgaged();
}



//Forces a player into a bankrupt state if they don't have enough money to pay for something
//that they have to pay for, such as rent or taxes.
void forceBankruptcy(Board tile[], Players player[], int index, int playerNum, int owed, string toPay) {
	if (owed > player[playerNum - 1].getMoney()) {
		cout << "You don't have enough money to pay rent\n"
			<< "You must declare bankruptcy\n";
		player[playerNum - 1].setMoney(-1);
	}
}
//This function allows the current player to declare bankruptcy
//at the end of their turn
int declareBankruptcy(Board tile[], Players player[], int index, int playerNum) {
	if (player[playerNum-1].getMoney() == -1) {
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