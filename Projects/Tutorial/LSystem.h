
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, radians; };


class LSystem {
	public:
	string axiom = "F";
	unordered_map<char, string> rules;
	int iterations;
	string evaluate();
	string applyRules(const string& current, const unordered_map<char, string>& rules);
};

