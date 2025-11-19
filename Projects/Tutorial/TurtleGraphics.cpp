// turtle_opengl.cpp
// Minimal Turtle Graphics system using OpenGL 3.3, GLFW and GLAD
// Single-file example: maintains a list of line segments and renders them
// Build dependencies: GLFW, GLAD (or your preferred loader), OpenGL 3.3
// Build example (Linux):
// - Install libs: sudo apt install libglfw3-dev libglew-dev libglm-dev
// - You need a GL loader (the example uses glad). If you have glad sources, compile with them.
// - Example compile (assuming glad.c is in the same folder):
// g++ -std=c++17 turtle_opengl.cpp glad.c -lglfw -ldl -lGL -o turtle
// Controls at runtime:
// W / Up : move forward
// S / Down : move backward
// A / Left : rotate left
// D / Right : rotate right
// Space : toggle pen up/down
// C : clear drawing
// R : reset turtle to origin
// 1-3 : change pen color (1=red,2=green,3=blue)


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>


// --- Simple math ---
struct Vec2 { float x, y; };
static inline Vec2 makev(float x, float y) { return { x,y }; }


// --- Turtle state ---
struct TurtleState {
	Vec2 pos{ 0.0f, 0.0f };
	float angle = 0.0f; // radians, 0 pointing to +X
	bool penDown = true;
	float cr = 1.0f, cg = 1.0f, cb = 1.0f;
};


// Store segments as endpoints + color
struct Segment { Vec2 a, b; float r, g, b; };


static std::vector<Segment> segments;
static TurtleState turtle;


// OpenGL objects
static GLuint shaderProgram = 0;
static GLuint vbo = 0, vao = 0;


// Projection (world bounds)
float worldLeft = -400.0f, worldRight = 400.0f, worldBottom = -300.0f, worldTop = 300.0f;


// Window size
int winW = 800, winH = 600;


// --- Shaders ---
const char* vertexShaderSrc = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aCol;
uniform mat4 uProj;
out vec3 vColor;
void main(){
vec4 p = uProj * vec4(aPos, 0.0, 1.0);
gl_Position = p;
vColor = aCol;
}
)glsl";


const char* fragmentShaderSrc = R"glsl(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main(){ FragColor = vec4(vColor, 1.0); }
)glsl";


GLuint compileShader(GLenum type, const char* src) {
	GLuint s = glCreateShader(type);
	glShaderSource(s, 1, &src, nullptr);
	glCompileShader(s);
	GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		char log[1024]; glGetShaderInfoLog(s, 1024, nullptr, log);
		std::cerr << "Shader compile error: " << log << std::endl;
		std::exit(1);
	}
	return s;
}


void setupGL() {