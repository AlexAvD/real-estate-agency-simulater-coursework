#include <iostream>
#include <stack>

#include "Agency.h"

using std::cout;
using std::endl;

const std::string pathToRealtors 	= "./data/realtors.txt";
const std::string pathToFlats 		= "./data/flats.txt";
const std::string pathToHouses 		= "./data/houses.txt";
const std::string pathToReport 		= "./data/report.txt";

int main() {	 
	setConsoleUTF8();

	/* std::stack<Realtor> realtors;
	std::stack<Flat> flats;
	std::stack<House> houses;

	Realtor::getRealtorsFromFile(pathToRealtors, &realtors);
	Flat::getFlatsFromFile(pathToFlats, &flats);
	House::getHousesFromFile(pathToHouses, &houses);
 
	Agency agency(&realtors, &flats, &houses);

	agency.simulate();
 
	cout << agency.getBuyers().size() << "\n";
	cout << agency.getSellers().size() << "\n"; */

	for (int i = 0; i < 20; i++) {
		cout << asymp(i, 5, 7, 2) << '\t' << asymp(i, 7, 10, 2) << '\n';
	}

	/* auto as = agency.getAvailableSellers();

	while (as.size()) {
		cout << *as.top() << '\n';
		as.pop();
	} */

	// agency.generateAndAddSeller();

	// cout << *agency.getSeller();

	// agency.addSeller(agency.getRealEstates().top()->getOwner());

	// RealEstate *rs = agency.getRealEstate();
	/* cout << *agency.getRealEstate() << '\n';
	cout << *agency.getRealEstate() << '\n';
	cout << *agency.getRealEstate() << '\n'; */

	/*
 */


  /*
	agency.simulate();
	agency.writeReport(pathToReport);

	cout << "COMPLETE"; 
	

	cout << agency.getFlatsForSale()->size() << '\n';
	cout << agency.getHousesForSale()->size() << '\n';
	cout << agency.getSoldRealEstates()->size() << '\n';
	cout << agency.getRevenue() << '\n';  */

	// cout << Random::getDouble();
	// cout << *agency.getHouses(); 


	return 0;  
}

