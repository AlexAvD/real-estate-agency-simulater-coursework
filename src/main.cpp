#include <iostream>
#include <stack>
#include "Agency.h"

using std::cout;
using std::endl;

const std::string PATH_TO_REALTORS 	= "./data/realtors.txt";
const std::string PATH_TO_FLATS 		= "./data/flats.txt";
const std::string PATH_TO_HOUSES 		= "./data/houses.txt";
const std::string PATH_TO_REPORT 		= "./data/report.txt";

int main() {	 
	setConsoleUTF8();

	std::stack<Realtor> realtors;
	std::stack<Flat> flats;
	std::stack<House> houses;

	Realtor::getRealtorsFromFile(PATH_TO_REALTORS, &realtors);
	Flat::getFlatsFromFile(PATH_TO_FLATS, &flats);
	House::getHousesFromFile(PATH_TO_HOUSES, &houses);
 
	Agency agency(&realtors, &flats, &houses);

	agency.simulate();
	agency.writeReport(PATH_TO_REPORT);	

	cout << "complete";  

	return 0;        
}

