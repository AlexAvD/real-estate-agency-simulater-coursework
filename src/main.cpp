#include <iostream>
#include <stack>

#include "Agency.h"
#include "House.h"
#include "Flat.h"

using std::cout;
using std::endl;


int main() {	 
	setConsoleUTF8();

	std::stack<Realtor> realtors;
	std::stack<RealEstate> realEstates;

	// Realtor::getRealtorsFromFile("./data/realtors.txt", &realtors);
	// RealEstate::getRealEstatesFromFile("./data/realEstates.ext", &realEstates);

	
	// cout << realtors;

	for (int i = 0; i < 5; i++) {
		if (Random::getInt(0, 100) < 70) {
			cout << Flat::generate();
		} else {
			cout << House::generate();
		}

		cout << "\n\n";
	}

	return 0;  
}

