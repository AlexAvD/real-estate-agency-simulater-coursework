#include "coursework.h"
#include <random>
#include "random.h"
#include <limits>
#include "helpers.h"
#include "Person.h"
#include "Date.h"
#include <stack>


using std::cout;
using std::endl;

int main() {	 
	// Realtor r = Realtor("lol", "lal", 19);
	/* Random r;

	for (int i = 0; i < 5; i++) {
		std::cout << "r1: " << r.getDouble(0, 10000) << "\tr2: " << r.getDouble(0, 1) << std::endl;
	} 
  */
 	setRus();

	 
/* 	for (auto & item : result) {
		for (auto const & [key, val] : item) {
			cout << key << " - " << val << endl;
		} 

		cout << '\n';
	}  */
	cout << readFile("./data/properties.txt"); 
 
	// cout << result.size(); 
	   
	return 0; 
}

