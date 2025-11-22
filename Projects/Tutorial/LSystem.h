#pragma once

#include <string>
#include <unordered_map>

using namespace std;

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, radians; };

string applyRules(const string& current, const unordered_map<char, string>& rules);

string Lsystem(string axiom, unordered_map<char, string> rules, int interactions);

