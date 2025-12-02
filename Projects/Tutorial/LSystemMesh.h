#pragma once
#include <vector>
#include <stack>;
#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "LSystem.h"


using namespace std;



class Mesh {
public:
    // pure float number values for OpenGL
    vector<float> lines;
    vector<unsigned int> indices;

    // Constructor
    void init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        std::cout << "Mesh created: VAO=" << VAO
            << ", VBO=" << VBO
            << ", EBO=" << EBO << std::endl;
    }

    // Destructor
    void release() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);

        std::cout << "Mesh Destroyed: VAO=" << VAO
            << ", VBO=" << VBO
            << ", EBO=" << EBO << std::endl;
    }

    float DegToRad(float degrees) {
        return degrees * M_PI / 180;
    }

    void uploadMeshToGPU() {
        if (lines.empty() || indices.empty()) {
            std::cerr << "Warning: Mesh has no vertices or indices to upload!" << std::endl;
            return;
        }

        if (lines.size() % 3 != 0) {
            std::cerr << "Warning: lines vector size is not divisible by 3!" << std::endl;
        }
		
        //Bind Vertex array object
        glBindVertexArray(VAO);
        // 0. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Linking Vertex Attributes location = 0, vec3
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lines.size(), lines.data(), GL_STATIC_DRAW);

        //Bind index array object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        //then set the vertex attributes pointers/ vertex layout
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //GLint vaoID;
        //glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoID);
        //std::cout << "Currently bound VAO: " << vaoID << std::endl;
        std::cout << "Uploading Mesh to GP" << std::endl;
        glBindVertexArray(0);

    }

    void updateVertices(const std::vector<Vec3>& vertices)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0,
            vertices.size() * sizeof(Vec3),
            vertices.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
            0,
            indices.size() * sizeof(unsigned int),
            indices.data());
    }

    void DrawMesh() const {
        GLint vaoID;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoID);
        //std::cout << "Currently bound VAO: " << vaoID << std::endl;
        glBindVertexArray(VAO);
        if (!indices.empty()) {
            glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
        }
        else 
            cout << "No Indices to draw!" << endl;
        glBindVertexArray(0);

    }

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    GLsizei indexCount = 0;
};



class LSystemMesh : public Mesh {

public:
    //  This vector stores all the vertices generated from the L-system
    vector<Vec3> vertices;
    // list of list of indices for the LSystem indices
    vector<vector<unsigned int>> lineIndicesArray;

    // LSystem parameters
    LSystem lSystem;

    // Graphics Options
    float unit = 0.01f;
    float angleDeg = 20.0f;

    LSystemMesh(LSystem Lsystem, float unitLength, float angleDeg) {
		this->lSystem = Lsystem;
        this->unit = unitLength;
		this->angleDeg = angleDeg;

        PlotLsystem(Lsystem.evaluate());
        ConvertVec3List();
        FlattenIndices();
		
    }

    void updateLSystem() {
		cout << "Updating LSystem Mesh"<< endl << "Iterations: "<< lSystem.iterations << endl;
        vertices.clear();
        lines.clear();
        indices.clear();
        lineIndicesArray.clear();

        PlotLsystem(lSystem.evaluate());
        ConvertVec3List();
        FlattenIndices();
        updateVertices(vertices);
    }





    void ConvertVec3List() {

        for (int i = 0; i < vertices.size(); ++i) {
            Vec3 Vector = vertices[i];
            lines.push_back(Vector.x);
            lines.push_back(Vector.y);
            lines.push_back(Vector.z);

        }

        //cout << "vec3list" << endl;
        //cout << "[";
        //for (int i = 0; i < lines.size(); ++i) {
        //    cout << lines[i] << ", ";
        //}
        //cout << "]" << endl;

        return;
    }

    void PlotLsystem(string LSystemData) {


        // This vector stores all the indices for the current line being drawn
        vector<unsigned int> currentIndices;

        Vec4 startPoint = { 0.0f, -0.5f, 0.0f, 0.0f };
        vertices.push_back(Vec3({ 0.0f, -0.5f, 0.0f }));



        // Get the History of All Push and Pop Operations
        stack<Vec4> VectorHistory;
        VectorHistory.push({ startPoint });

        // Get the History of All Push and Pop points and where they are in the index
        stack<int> IndexHistory;
        IndexHistory.push({ 0 });



        Vec3 currentPosition = vertices[0];
        float currentOrientation = 0.0f; // in radians
        int currentIndex = 0;

        //cout << LSystemData << endl;
        for (int i = 0; i < LSystemData.length(); ++i) {
            char command = LSystemData[i];

            switch (command) {
            case 'F':
                // draw forward
                //cout << "Draw Forward" << endl;
                // code to draw a line forward

                //VERTEX POSITION
                currentPosition.x += unit * sin(currentOrientation); // move the start point up by 0.1 units
                currentPosition.y += unit * cos(currentOrientation);
                vertices.push_back(currentPosition);

                // INDEX POS
                currentIndex++;
                currentIndices.push_back(currentIndex);
                break;
            case '+':
                // turn right
                //cout << "Turn Right" << endl;
                currentOrientation -= DegToRad(angleDeg);
                break;
            case '-':
                // turn left
                //cout << "Turn Left" << endl;
                currentOrientation += DegToRad(angleDeg);
                break;
            case '[':
            {
                // push position and angle to stack
                //cout << "Push to Stack" << endl;
                // VERTEX POSITION
                Vec4 pushVector4 = {
                    currentPosition.x,
                    currentPosition.y,
                    currentPosition.z,
                    currentOrientation
                };
                VectorHistory.push({ pushVector4 });

                // INDEX
                IndexHistory.push(currentIndex);
                break;
            }
            case ']':
                // pop position and angle from stack
                //cout << "Pop from Stack" << endl;

                // VERTEX POSITION
                Vec4 LastPosition = VectorHistory.top();
                // reset current position to the last pushed position
                currentPosition.x = LastPosition.x;
                currentPosition.y = LastPosition.y;
                currentPosition.z = LastPosition.z;
                currentOrientation = LastPosition.radians; // reset orientation
                VectorHistory.pop();

                // INDEX
                if (!currentIndices.empty()) {
                    lineIndicesArray.push_back(currentIndices);
                    currentIndices.clear();
                }

                if (!IndexHistory.empty()) {
                    currentIndices.push_back(IndexHistory.top());
                    IndexHistory.pop();
                }


                break;
            default:
                // ignore unrecognized characters
                break;
            }

        }


        //convert vector to C array
        //int* verticesArray = &vertices[0];

        //for (int i = 0; i < vertices.size(); ++i) {

        //    cout << "Vertex " << i << " X:" << vertices[i].x << " Y:" << vertices[i].y << endl;

        //    cout << endl;
        //}


        //for (int i = 0; i < lineIndicesArray.size(); ++i) {
        //    for (int j = 0; j < lineIndicesArray[i].size(); ++j) {
        //        cout << lineIndicesArray[i][j] << ", ";
        //    }
        //    cout << endl;
        //}

        //LSystemData tmp = {
        //lineIndicesArray,
        //vertices
        //};

        //vertices = tmp.vertices;
        //lineIndicesArray = tmp.lineIndicesArray;


        return;
    }


    void FlattenIndices() {
        cout << "FlattenIndices" << endl;
        for (const auto& seq : lineIndicesArray) {
            if (seq.size() < 2) continue;
            for (size_t j = 1; j < seq.size(); ++j) {
                indices.push_back(seq[j - 1]);
                indices.push_back(seq[j]);
                // cout << "pushing into indices" << endl;
            }
        }
    }
};
