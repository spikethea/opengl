#pragma once

#include <vector>
#include <cmath>

#include "TurtleGraphics.h"
#include "LSystem.h";
#include <iostream>

using namespace std;

class Mesh {
    public:


    // pure float number values for OpenGL
    vector<float> lines;
	vector<int> indices;
};



class LSystemMesh: public Mesh {

    public:
        //  This vector stores all the vertices generated from the L-system
        vector<Vec3> vertices;
        // list of list of indices for the LSystem indices
        vector<vector<unsigned int>> lineIndicesArray;

    void ConvertVec3List() {

        for (int i = 0; i < vertices.size(); ++i) {
            Vec3 Vector = vertices[i];
            lines.push_back(Vector.x);
            lines.push_back(Vector.y);
            lines.push_back(Vector.z);

        }

        cout << "vec3list" << endl;
        cout << "[";
        for (int i = 0; i < lines.size(); ++i) {
            cout << lines[i] << ", ";
        }
        cout << "]" << endl;

        return;
    }
};