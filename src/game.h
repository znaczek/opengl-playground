#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <GL/glew.h>
#include "models/board.h"
#include "models/figure.h"
#include "models/blocks.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "gltext.hpp"

class Game {

public:
    Game(GLFWwindow* window);

public:
    void tick();

private:
    GLFWwindow* window;
    Board *board;
    Figure* figure;
    std::vector<CBlock> blocks;
    Blocks* blocksModel;
    gltext::Font font;
    int state = 0;
    int score = 0;
    int colorIndex = 0;
    double lastForcedMove = -1;

    void drawBoard();
    void keyCallback(GLFWwindow* window, int key,int scancode, int action, int mods);
    void move(glm::vec3 potentialMove);
    void handleLevel();
    void addFigure();
    bool hasCollision(std::vector<CBlock> figureBlocks, glm::vec3 potentialMove);
    void updateBlocksModel();
    void rotateCamera();
};


#endif //TETRIS_GAME_H
