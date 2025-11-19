#include <iostream>
using namespace std;
//#include <GL/glew.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

<<<<<<< HEAD
#include "Lsystem.h";
#include "TurtleGraphics.h";


/*resize the viewport to the window when the user resizes*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}

/* input control callback function*/
void processInput(GLFWwindow *window)
{
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window, true);
}

void ConvertVec3(float Geometry[], Vec3 Vector, int startPoint) {
    int vectorIndex = startPoint * 3;
    Geometry[vectorIndex+0] = Vector.x;
    Geometry[vectorIndex+1] = Vector.y;
    Geometry[vectorIndex+2] = Vector.z;
}

void PlotLsystem() {
	// Define Geometry for line drawing

    //float Geometry[] =
    //{
    //     0.0f, 0.f, 0.0f,
    //};

    vector<vector<unsigned int>> lineIndicesArray;


    //  This vector stores all the vertices generated from the L-system
    vector<Vec3> vertices;
	// This vector stores all the indices for the current line being drawn
    vector<unsigned int> currentIndices;
    


    unsigned int GeometryIndices[] =
    {
         0,
    };

	Vec4 startPoint = { 0.0f, 0.0f, 0.0f, 0.0f };
    vertices.push_back(Vec3({ 0.0f, 0.0f, 0.0f }));

    
    // Lindenmayer System

    // Step 1 Defining Axiom
    string axiom = "F";

    // Step 2 define production rules e.g. A --> AAB
    unordered_map<char, string> rules;

    /*rules['A'] = "AB";
    rules['B'] = "A";*/

    rules['F'] = "F[+F]F[-F]F";

    string currentLSystem = Lsystem(axiom, rules);

	// Get the History of All Push and Pop Operations
    stack<Vec4> VectorHistory;
    VectorHistory.push({startPoint});

    // Get the History of All Push and Pop points and where they are in the index
    stack<int> IndexHistory;
    IndexHistory.push({ 0 });



    Vec3 currentPosition = vertices[0];
    float currentOrientation = 0.0f; // in radians
	int currentIndex = 0;

    cout << currentLSystem << endl;
    for (int i = 0; i < currentLSystem.length(); ++i) {
        char command = currentLSystem[i];

        switch (command) {
        case 'F':
            // draw forward
            cout << "Draw Forward" << endl;
			// code to draw a line forward

			//VERTEX POSITION
            currentPosition.x += 0.1f*sin(currentOrientation); // move the start point up by 0.1 units
            currentPosition.y += 0.1f*cos(currentOrientation);
            vertices.push_back(currentPosition);

            // INDEX POS
            currentIndex++;
            currentIndices.push_back(currentIndex);
            break;
        case '+':
            // turn right
            cout << "Turn Right" << endl;
            currentOrientation -= 26;
            break;
        case '-':
            // turn left
            cout << "Turn Left" << endl;
            currentOrientation += 26;
            break;
        case '[':
            {
            // push position and angle to stack
            cout << "Push to Stack" << endl;
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
            cout << "Pop from Stack" << endl;

			// VERTEX POSITION
            Vec4 LastPosition = VectorHistory.top();
			// reset current position to the last pushed position
            currentPosition.x = LastPosition.x;
            currentPosition.y = LastPosition.y;
            currentPosition.z = LastPosition.z;
			currentOrientation = LastPosition.radians; // reset orientation
            VectorHistory.pop();

            // INDEX
            currentIndices.push_back(IndexHistory.top());
            IndexHistory.pop();

            lineIndicesArray.push_back(currentIndices);
            break;
        default:
            // ignore unrecognized characters
            break;
	    }

    }
    cout << lineIndicesArray.size() << endl;
    for (int i = 0; i < lineIndicesArray.size(); ++i) {
        for (int j = 0; j < lineIndicesArray[i].size(); ++j) {
            cout << lineIndicesArray[i][j] << ", ";
        }
        cout << endl;
	}
	



	return;
}

int main(void)
{
    std::cout << "Hello World" << std::endl;
    GLFWwindow* window;

    //LindenMayer System
    Lsystem();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialise GLAD before calling any OpenGL Function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    
   
    //if(glewInit() != GLEW_OK){
    //    cout << "Unable to load glew" << endl;
    //}
    //else{
    //    cout << glGetString(GL_VERSION) << endl;
    //}

   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//    // Created vertices for buffer object
//    float vertices[] = {
//        // first triangle
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f,  0.5f, 0.0f,
//        // second triangle
//        0.5f, -0.5f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f   // top left
//    };

 // SCENE

   // Created vertex for element buffer object
   float firstSquare[] = {
    0.1f,  0.1f, 0.0f,  // top right
    0.1f, -0.9f, 0.0f,  // bottom right
   -0.9f, -0.9f, 0.0f,  // bottom left
   -0.9f,  0.9f, 0.0f   // top left 
   };
   unsigned int firstSquareIndices[] = {  // note that we start from 0!
       0, 1, 3,   // first triangle
       1, 2, 3    // second triangle
   };

   float secondSquare[] = {
       0.9f,  0.9f, 0.0f,  // top right
       0.9f, -0.1f, 0.0f,  // bottom right
      -0.1f, -0.1f, 0.0f,  // bottom left
      -0.1f,  0.9f, 0.0f   // top left 
  };
   unsigned int secondSquareIndices[] = {  // note that we start from 0!
       0, 1, 3,   // first triangle
       1, 2, 3    // second triangle
   }; 

   float lines[] =
   {
        0.5f, 0.8f, 0.0f,
        0.5f, -0.8f, 0.0f
   };

   unsigned int linesIndices[] =
   {
        0, 1
   };

   // VAO, VBOs and EBOs Array for the number of objects in the scene.
   unsigned int VBOs[3], VAOs[3], EBOs[3];
   glGenVertexArrays(3, VAOs); 
   glGenBuffers(3, VBOs);
   glGenBuffers(3, EBOs);
   
// First Square

    //Bind Vertex array object
    glBindVertexArray(VAOs[0]);
    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // Linking Vertex Attributes location = 0, vec3
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(firstSquareIndices), firstSquareIndices, GL_STATIC_DRAW);

    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

// Second Square

   //Bind Vertex array object
   glBindVertexArray(VAOs[1]);
   // 0. copy our vertices array in a buffer for OpenGL to use
   glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
   // Linking Vertex Attributes location = 0, vec3
   glBufferData(GL_ARRAY_BUFFER, sizeof(secondSquare), secondSquare, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(secondSquareIndices), secondSquareIndices, GL_STATIC_DRAW);

   // 1. then set the vertex attributes pointers
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);  
   glBindVertexArray(0);

// Line Drawing
   //Bind Vertex array object
   glBindVertexArray(VAOs[2]);
   // 0. copy our vertices array in a buffer for OpenGL to use
   glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
   // Linking Vertex Attributes location = 0, vec3
   glBufferData(GL_ARRAY_BUFFER, sizeof(lines), lines, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(linesIndices), linesIndices, GL_STATIC_DRAW);

   // 1. then set the vertex attributes pointers
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   glBindVertexArray(0);

   


       // SHADERS
       const char *vertexShaderSource = "#version 330 core\n"
           "layout (location = 0) in vec3 aPos;\n"
           "void main()\n"
           "{\n"
           "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
       "}\0";

       const char *fragmentShader1Source = "#version 330 core\n"
           "out vec4 FragColor;\n"
           "void main()\n"
           "{\n"
           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
       "}\0";

       const char *fragmentShader2Source = "#version 330 core\n"
           "out vec4 FragColor;\n"
           "void main()\n"
           "{\n"
           "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
       "}\0";
       

       // initiate vertex shader
       unsigned int vertexShader;
       vertexShader = glCreateShader(GL_VERTEX_SHADER);

       glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
       glCompileShader(vertexShader);

       // check vertex compilation was successful
       int  success;
       char infoLog[512];
       glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

       if(!success)
       {
           glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
       }

       // initiate fragment shader and equivalent shader program
       unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
       unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // the second fragment shader that outputs the color yellow
       unsigned int shaderProgramOrange = glCreateProgram();
       unsigned int shaderProgramYellow = glCreateProgram();
       
       // attach shader program to fragment shader & vertex shader
       glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
       glCompileShader(fragmentShaderOrange);
       glAttachShader(shaderProgramOrange, vertexShader);
       glAttachShader(shaderProgramOrange, fragmentShaderOrange);

       // attach shader program to fragment shader & vertex shader
       glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
       glCompileShader(fragmentShaderYellow);
       glAttachShader(shaderProgramYellow, vertexShader);
       glAttachShader(shaderProgramYellow, fragmentShaderYellow);
       
       
       glLinkProgram(shaderProgramOrange);
       glLinkProgram(shaderProgramYellow);

       // COMPILE LOG CHECKS FOR SHADER TEST WORKING
       // check vertex compilation was successful
       int  fragementSuccess;
       char fragmentInfoLog[512];
       glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);

       if(!success)
       {
           glGetShaderInfoLog(vertexShader, 512, NULL, fragmentInfoLog);
           std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentInfoLog << std::endl;
       } else {
           glGetShaderInfoLog(vertexShader, 512, NULL, fragmentInfoLog);
           std::cout << "SHADER::FRAGMENT::SUCCESS\n" << fragmentInfoLog << std::endl;
       }

       // check for shader program  errors
       glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
       if(!success) {
           glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
           std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
       } else {
           glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
           std::cout << "SHADER::PROGRAM::SUCCESS\n" << infoLog << std::endl;
       }




       // Remove from memory as we dont need the shader object(s) once weve linked in the the program
       glDeleteShader(vertexShader);
       glDeleteShader(fragmentShaderOrange);
       glDeleteShader(fragmentShaderYellow);

// RENDER LOOP

       /* Loop until the user closes the window */
       while (!glfwWindowShouldClose(window))
       {
           //input
           processInput(window);

           /* Render here */
           glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background color
           glClear(GL_COLOR_BUFFER_BIT);

           // This works
           // glBegin(GL_POLYGON);
           // glVertex2f(-0.5f, -0.5f);
           // glVertex2f(0.5f, -0.5f);
           // glVertex2f(0.5f, 0.5f);
           // glVertex2f(-0.5f, 0.5f);
           // glEnd();

            // Classic OpenGL Line
           //glBegin(GL_LINES);
           //glVertex3f(0.5f, 0.5f, 0.0f);
           //glVertex3f(0.5f, -0.5f, 0.0f);
           //glEnd();

           /*Code To print First Square*/
           // 2. use our shader program when we want to render an object
           glUseProgram(shaderProgramOrange);
           //// 3. now draw the object
           glBindVertexArray(VAOs[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

           glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

           /*Code To print Second Square*/
           // 2. use our shader program when we want to render an object
           glUseProgram(shaderProgramYellow);
           // 3. now draw the object
           glBindVertexArray(VAOs[1]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

           glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

           /*Code To print Lines*/
           // 2. use our shader program when we want to render an object
           glUseProgram(shaderProgramOrange);
           // 3. now draw the object
           glBindVertexArray(VAOs[2]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

           glDrawArrays(GL_LINES, 0, 2);

           /* Poll for and process events */
           glfwPollEvents();
           /* Swap front and back buffers */
           glfwSwapBuffers(window);
       }

   
   // optional: de-allocate all resources once they've outlived their purpose:
   // ------------------------------------------------------------------------
   glDeleteVertexArrays(2, VAOs);
   glDeleteBuffers(2, VBOs);
   glDeleteBuffers(2, EBOs);
   glDeleteProgram(shaderProgramOrange);
   glDeleteProgram(shaderProgramYellow);


    glfwTerminate();
    return 0;
}
