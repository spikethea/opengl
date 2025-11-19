#include <iostream>
#include <string>
#include <unordered_map>

#include "Lsystem.h"
using namespace std;



string applyRules(const string& current, const unordered_map<char, string>& rules) {
	string next;
	// for C in Current list
	for (char c : current) {
		auto it = rules.find(c);
		if (it != rules.end())
			// a->b means access the b member in the object a points to
			// in this case the second character of the unordered_map 
			next += it->second; // apply rule
		else
			next += c; // keep same if no rule
	}
	return next;
}

string Lsystem(string axiom, unordered_map<char, string> rules) {

	// Step 3 How many iterations are we going to do?
	int interactions = 1;
	// Step 4 Apply rules in number of interations
	string current = axiom;
	for (int i = 0; i < interactions; ++i) {
		current = applyRules(current, rules);
<<<<<<< HEAD
		cout << "Iteration " << i + 1 << ": " << current << "\n";
=======
		//cout << "Iteration " << i + 1 << ": " << current << "\n";
>>>>>>> 5f5a8ce24e46dd3a502b78bfe3607ed33eff6118
	}

	return current;
}

