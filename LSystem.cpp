#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#include "Lsystem.h";

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

void Lsystem() {
	// Lindenmayer System
	
	// Step 1 Defining Axiom
	string axiom = "A";

	// Step 2 define production rules e.g. A --> AAB
	unordered_map<char, string> rules;
	rules['A'] = "AB";
	rules['B'] = "A";

	// Step 3 How many iterations are we going to do?
	int interactions = 6;

	// Step 4 Apply rules in number of interations
	string current = axiom;
	for (int i = 0; i < interactions; ++i) {
		current = applyRules(current, rules);
		cout << "Interation " << i + 1 << ": " << current << "\n";
	}

	return;
}