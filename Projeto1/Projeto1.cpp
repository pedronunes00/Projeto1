// Include standard headers
#include <stdio.h>
#include <stdlib.h>

//Shapes
#include <C:\Users\pedro\source\repos\Projeto1\Projeto1\Shapes.h>

//Board
#include<C:\Users\pedro\source\repos\Projeto1\Projeto1\Board.h>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// GLM header file
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

// shaders header file
#include "shader.cpp"

#include <windows.h>

// Vertex array object (VAO)
GLuint VertexArrayID;

// Vertex buffer object (VBO)
GLuint vertexbuffer;


// color buffer object (CBO)
GLuint colorbuffer;

// GLSL program from the shader
GLuint programID;


GLint WindowWidth = 500;
GLint WindowHeight = 750;
bool isPastInterval(double interval);

Board *board = new Board();
//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    // VAO
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("C:/Users/pedro/source/repos/Projeto1/Projeto1/SimpleVertexShader.vertexshader", "C:/Users/pedro/source/repos/Projeto1/Projeto1/SimpleFragmentShader.fragmentshader");

    GLfloat g_vertex_buffer_data[] = {
       0.0f, 0.0f, 0.0f,
       0.0f, 5.0f, 0.0f,
       5.0f, 0.0f, 0.0f,
       5.0f, 0.0f, 0.0f,
       0.0f, 5.0f, 0.0f,
       5.0f, 5.0f, 0.0f,
    };
    

    // One color for each vertex. They were generated randomly.
    int auxc = 0;
    GLfloat g_color_buffer_data[] = {
       1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
    };


    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

}
//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

//--------------------------------------------------------------------------------
void drawBody(GLfloat x, GLfloat y)
{
    // Clear the screen
    //glClear(GL_COLOR_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-25.0f, 25.0f, -50.0f, 50.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around

    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);


    glm::mat4 trans1;
    trans1 = glm::translate(glm::mat4(1.0), glm::vec3(x, y, 0.0f));
    unsigned int m = glGetUniformLocation(programID, "trans1");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans1[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );


    //glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(20);
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    //glDrawArrays(GL_POINTS, 0, 9); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//--------------------------------------------------------------------------------

int main(void)
{
    // Initialise GLFW
    glfwInit();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window
    window = glfwCreateWindow(WindowWidth, WindowHeight, "Moving House in 2D ", NULL, NULL);

    // Create window context
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);

    // White background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // transfer my data (vertices, colors, and shaders) to GPU side
    transferDataToGPUMemory();

    //Initialization of variables
    Shapes shape;
    shape.type = 0;
    shape.rotation = 0;
    Position auxpos;
    int piece[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            auxpos.row = i;
            auxpos.col = j;
            piece[i][j] = shape.getValue(auxpos);
        }
    }
    int row = 0;
    int col = 0;
    int score = 0;
    Position pos;
    Shapes currentTetromino;
    currentTetromino.type = 3;
    currentTetromino.rotation = rand() % 4;
    pos.row = 0;
    pos.col = 5;
    Board * auxBoard = new Board();
    // render scene for each frame
    do {
        board->deleteFullLines();
        // drawing callback
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                Position aux;
                aux.row = x;
                aux.col = y;
                if (currentTetromino.getValue(aux) != 0)
                    drawBody(-25.0f + 5.0f * (pos.col + aux.col), 50.0f - 5.0f * (pos.row + aux.row));
            }
        }
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                if (board->board[i][j]) {
                    drawBody(-25.0f + 5.0f * j, 50.0f - 5.0f * i);
                }
            }
        }
       if (isPastInterval(1)) {
            pos.row++;
        }
         // check left, right and rotate
        if (glfwGetKey(window , GLFW_KEY_A) == GLFW_PRESS) {
            pos.col--;
            if (board->isCollision(currentTetromino, pos)) 
                pos.col++;
            Sleep(50);
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            pos.col++;
            if (board->isCollision(currentTetromino, pos)) 
                pos.col--;
            Sleep(50);
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            pos.row++;
            Sleep(50);
        }
        else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            currentTetromino.rotation = (currentTetromino.rotation + 1) % 4;
            if (board->isCollision(currentTetromino, pos)) {
                currentTetromino.rotation--;
                if (currentTetromino.rotation < 0) currentTetromino.rotation = 3;
            }
            Sleep(50);
        }
        else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
            while (!board->isCollision(currentTetromino, pos)) {
                pos.row++;
            }
            Sleep(50);
        }
        /*while (board->isCollision(currentTetromino, pos)) {
                if (pos.col > COLUMNS / 2) pos.col--;
                else if (pos.col <= COLUMNS / 2) pos.col++;
            }*/

        //drawBody(-25.0f + 5.0f * pos.col, 50.0f - 5.0f * pos.row);
        //check if collision, if so, store piece at pos->row-1;
        if (board->isCollision(currentTetromino, pos)) {
            pos.row--;
            board->storeTetromino(currentTetromino, pos);
            currentTetromino.type = rand() % 7;
            currentTetromino.rotation = rand() % 4;
            pos.row = 0;
            pos.col = 5;
        }

        if (board->isGameOver()) {
            board->clearBoard();
            score = 0;
            break;
        }
        
        // Swap buffers
        glfwSwapBuffers(window);

        // looking for events
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);



    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);


    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


bool isPastInterval(double interval) {
    static double previousTime = glfwGetTime();
    double currentTime = glfwGetTime();
    if ((currentTime - previousTime) >= interval) {
        previousTime = currentTime;
        return true;
    }
    return false;
}
