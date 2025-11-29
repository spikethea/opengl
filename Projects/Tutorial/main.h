#pragma once

#include "Lsystem.h";


class TurtleGraphics {

    //  This vector stores all the vertices generated from the L-system
    vector<Vec3> vertices;
    // list of list of indices for the LSystem indices
    vector<vector<unsigned int>> lineIndicesArray;
public:
    // pure float number values for OpenGL
    vector<float> lines;
    vector<int> indices;


	void PlotLsystem();
	void ConvertVec3List();
    void FlattenIndices();
};


struct LSystemData
{
	vector<vector<unsigned int>> lineIndicesArray;
	vector<Vec3> vertices;
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
