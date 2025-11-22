<<<<<<< HEAD
=======
#pragma once

>>>>>>> 5f5a8ce24e46dd3a502b78bfe3607ed33eff6118
#include <string>
#include <unordered_map>

using namespace std;

<<<<<<< HEAD
string applyRules(const string& current, const unordered_map<char, string>& rules);

void Lsystem();
=======
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, radians; };

string applyRules(const string& current, const unordered_map<char, string>& rules);

string Lsystem(string axiom, unordered_map<char, string> rules, int interactions);

>>>>>>> 5f5a8ce24e46dd3a502b78bfe3607ed33eff6118
