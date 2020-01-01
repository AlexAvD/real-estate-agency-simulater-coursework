#include <random>
#include <limits>
#include <stack>
#include <iomanip>
#include <algorithm>

#include "helpers.h"
#include "Random.h"
#include "Person.h"
#include "Client.h"
#include "Buyer.h"
#include "Agency.h"
#include "Realtor.h"
#include "Date.h"


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



	cout << Person::generate() << "\n\n";
	cout << Person::generate(); 
 

	return 0; 
}

 