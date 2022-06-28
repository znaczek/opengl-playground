#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cstdlib>
#include <cstdio>

#include "src/game.h"
#include <thread>
#include "common.h"
#include "src/constants.h"

using namespace std;
using namespace glm;


float PI = 3.1415926535897932384;
double WINDOW_WIDTH = 500;
double WINDOW_HEIGHT = 500;

GLFWwindow* window = nullptr;
Game* game;

const int FPS = 60;
const int MS_TO_NEXT_FRAME = 1000 / FPS;

typedef chrono::time_point<std::chrono::system_clock, chrono::nanoseconds> moment;

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void initOpenGLProgram() {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void init() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "GLFW initialisation error\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        fprintf(stderr, "Error in window creation\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW initialisation error\n");
    }

    game = new Game(window);

}

void loop() {
    int sleep_time = 0;
    double next_game_tick = getMills();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game->tick();
        glfwSwapBuffers(window);
        next_game_tick += MS_TO_NEXT_FRAME;
        sleep_time = next_game_tick - getMills();
        if( sleep_time >= 0 ) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        }
        else {
            // Shit, we are running behind!
        }

        glfwPollEvents();
    }
}

int main() {
    init();
	initOpenGLProgram();
    loop();
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
