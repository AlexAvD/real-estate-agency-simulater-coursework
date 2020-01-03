#include <random>
#include <limits>
#include <stack>
#include <iomanip>
#include <algorithm>
#include <string>

#include "Random.h"
#include "Date.h"
#include "helpers.h"

#include "Person.h"

#include "Seller.h" 
#include "Buyer.h"
#include "Realtor.h"
#include "Agency.h"

using std::cout;
using std::endl;

int main() {	 
	setRus();
/* 
	cout << Person::generate() << endl;
	cout << Person::generate(); */


	/* for (int i = 0; i < 5; i++) {
		cout << Random::getInt(10, 99) << endl;
	} 
 */
 


	/* cout << Person::generate() << "\n\n";
	cout << Person::generate();  */

	// cout << '"' << trim(" a ") << '"';

	/* print<std::string>({
		trim("  a  "), 
		"lol"
	}); */

	/* Seller s = Seller::generate();
	Person *pp = &s;

	cout << *pp; */

	// std::vector<std::string> lines = readFile("./data/properties.txt");
	// cout << handleLines(, ':');

	// cout << lines;
	
	// cout << *test() << '\n';
	
	Person r = Person::generate();

	cout << r;

	return 0; 
}

  