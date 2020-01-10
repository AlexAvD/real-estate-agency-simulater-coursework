#include <iostream>
#include <stack>

#include "Agency.h"
#include "House.h"
#include "Flat.h"

using std::cout;
using std::endl;

const std::string pathToRealtors 	= "./data/realtors.txt";
const std::string pathToFlats 		= "./data/flats.txt";
const std::string pathToHouses 		= "./data/houses.txt";
const std::string pathToReport 		= "./data/report.txt";

int main() {	 
	setConsoleUTF8();

	std::stack<Realtor> realtors;
	std::stack<Flat> flats;
	std::stack<House> houses;

	Realtor::getRealtorsFromFile(pathToRealtors, &realtors);
	Flat::getFlatsFromFile(pathToFlats, &flats);
	House::getHousesFromFile(pathToHouses, &houses);
 
	Agency agency;

	agency.setRealtors(&realtors);
	agency.setFlats(&flats);
	agency.setHouses(&houses);
  
	agency.simulate();
	agency.writeReport(pathToReport);
/* 
	cout << agency.getFlatsForSale()->size() << '\n';
	cout << agency.getHousesForSale()->size() << '\n';
	cout << agency.getSoldRealEstates()->size() << '\n';
	cout << agency.getRevenue() << '\n';  */

	
	
	// cout << *agency.getHouses(); 
 
 	


	return 0;  
}

