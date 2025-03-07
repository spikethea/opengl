 #include <iostream>
 using namespace std;
 #include <GL/glew.h>
 #include <GLFW/glfw3.h>

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

 int main(void)
 {
     GLFWwindow* window;

     /* Initialize the library */
     if (!glfwInit())    
         return -1;

     /* Create a windowed mode window and its OpenGL context */
     window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
     if (!window)
     {
         glfwTerminate();
         return -1;
     }

     /* Make the window's context current */
     glfwMakeContextCurrent(window);
     glViewport(0, 0, 800, 600);
     
     if(glewInit() != GLEW_OK){
         cout << "Unable to load glew" << endl;
     }
     else{
         cout << glGetString(GL_VERSION) << endl;
     }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Created vertices for buffer object
    // float vertices[] = {
    //     // first triangle
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f,  0.5f, 0.0f,
    //     // second triangle
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left
    // };

    // Created vertex for element buffer object
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO); 
    //Bind Vertex array object
    glBindVertexArray(VAO); 
    // 0. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Linking Vertex Attributes location = 0, vec3
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

     


        // SHADERS
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

        // initiate fragment shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // check vertex compilation was successful
        int  fragementSuccess;
        char fragmentInfoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, fragmentInfoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentInfoLog << std::endl;
        }

        // Create shader program
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // check for shader program  errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Remove from memory as we dont need the shader object once weve linked in the the program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);

// RENDER LOOP

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //input
            processInput(window);

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background color
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);

            /*Code To print a Triangle*/
            // 2. use our shader program when we want to render an object
            glUseProgram(shaderProgram);
            // 3. now draw the object
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // glBegin(GL_POLYGON);
            // glVertex2f(-0.5f, -0.5f);
            // glVertex2f(0.5f, -0.5f);
            // glVertex2f(0.5f, 0.5f);
            // glVertex2f(-0.5f, 0.5f);
            // glEnd();

            /* Poll for and process events */
            glfwPollEvents();
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }

    
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);


     glfwTerminate();
     return 0;
 }
