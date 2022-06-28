#include <iostream>
#include <vector>
#include "game.h"
#include "camera.h"
#include "models/figure.h"
#include "models/blocks.h"
#include <algorithm>
#include "common.h"
#include <random>
#include <GLFW/glfw3.h>

glm::vec3 colors[] = {
        {1,   0,   0},
        {0,   1,   0},
        {0,   0,   1},
        {1,   1,   0},
        {1,   0,   1},
        {0,   1,   1},
        {0.5, 0.5, 0.5}
};

bool mouse_down = false;
double lastX = -1;
double lastY = -1;

void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (GLFW_PRESS == action) {
            mouse_down = true;

        } else if (GLFW_RELEASE == action) {
            mouse_down = false;
            lastX = -1;
            lastY = -1;
        }
    }
}

Figure *generateFigure(glm::vec3 color, float y) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> random_gen(1, 5);
    unsigned long figureIndex = random_gen(rng);

      switch (figureIndex) {
        case 1:
            return new Figure(color, {0, 9, 0}, 25,
                              glm::vec3(-4, y, -4), glm::vec3(-3, y, -4), glm::vec3(-2, y, -4), glm::vec3(-1, y, -4), glm::vec3(0, y, -4),
                              glm::vec3(-4, y, -3), glm::vec3(-3, y, -3), glm::vec3(-2, y, -3), glm::vec3(-1, y, -3), glm::vec3(0, y, -3),
                              glm::vec3(-4, y, -2), glm::vec3(-3, y, -2), glm::vec3(-2, y, -2), glm::vec3(-1, y, -2), glm::vec3(0, y, -2),
                              glm::vec3(-4, y, -1), glm::vec3(-3, y, -1), glm::vec3(-2, y, -1), glm::vec3(-1, y, -1), glm::vec3(0, y, -1),
                              glm::vec3(-4, y, -0), glm::vec3(-3, y, -0), glm::vec3(-2, y, -0), glm::vec3(-1, y, -0), glm::vec3(0, y, -0)
            );
        case 2:
            return new Figure(color, {0, 9, 0},8,
                              glm::vec3(-4, y, -4),
                              glm::vec3(-3, y, -4), glm::vec3(-2, y, -4), glm::vec3(-1, y, -4),
                              glm::vec3(-4, y, -3), glm::vec3(-4, y, -2), glm::vec3(-4, y, -1),
                              glm::vec3(-4, y -1, -4)
            );
      case 3:
          return new Figure(color, {0, 9, 0},5,
                            glm::vec3(-4, y, -4), glm::vec3(-3, y, -4), glm::vec3(-2, y, -4), glm::vec3(-1, y, -4), glm::vec3(0, y, -4)
              );
      case 4:
          return new Figure(color, {0, 9, 0}, 5,
                            glm::vec3(-4, y, -0), glm::vec3(-3, y, -0), glm::vec3(-2, y, -0), glm::vec3(-1, y, -0), glm::vec3(0, y, -0)
          );
      case 5:
          return new Figure(color, {0, 9, 0}, 1,
                            glm::vec3(-4, y, -4)
          );
    }

}

Game::Game(GLFWwindow* window) {
    this->window = window;
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mode) {
        Game *self = (Game *) glfwGetWindowUserPointer(window);
        self->keyCallback(window, key, scancode, action, mode);
    });

    glfwSetMouseButtonCallback(window, mouse_callback);
    this->board = new Board();
    this->addFigure();
    this->blocksModel = new Blocks(this->blocks);
    this->blocks = std::vector<CBlock>();

    font = gltext::Font("/home/znaczek/Desktop/OpenSans-Regular.ttf", 16, 512, 512);
    font.setDisplaySize(300, 300);
    font.cacheCharacters(
            "1234567890!@#$%^&*()abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,./;'[]\\<>?:\"{}|-=_+");
}

void Game::addFigure() {
    auto color = colors[colorIndex % (sizeof colors / 3 / 4)];
    colorIndex += 1;
    float y = 0;
    this->figure = generateFigure(color, y);
}

void Game::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (state == 0) {
        if (action == GLFW_RELEASE) {
            state = 1;
        }
    } else if (state == 1) {
        if (action == GLFW_RELEASE) {
            glm::vec3 potentialMove;
            if (key == GLFW_KEY_DOWN) {
                potentialMove = glm::vec3(0, 0, -1);
            } else if (key == GLFW_KEY_UP) {
                potentialMove = glm::vec3(0, 0, 1);
            } else if (key == GLFW_KEY_LEFT) {
                potentialMove = glm::vec3(1, 0, 0);
            } else if (key == GLFW_KEY_RIGHT) {
                potentialMove = glm::vec3(-1, 0, 0);
            } else if (key == GLFW_KEY_SPACE) {
                if (mods == GLFW_MOD_SHIFT) {
                    potentialMove = glm::vec3(0, 1, 0);
                } else {
                    potentialMove = glm::vec3(0, -1, 0);
                }
            }
            this->move(potentialMove);
        }
    } else if (this->state == 2) {
        if (action == GLFW_RELEASE) {
            this->blocks = std::vector<CBlock>();
            this->updateBlocksModel();
            this->score = 0;
            this->state = 1;
            colorIndex = 0;
            delete this->figure;
            this->addFigure();
        }
    }

}

void Game::move(glm::vec3 potentialMove) {
    bool isMoveDown = potentialMove == glm::vec3(0, -1, 0);
    auto figureBlocks = this->figure->getBlocks();
    if (this->hasCollision(figureBlocks, potentialMove)) {
        if (isMoveDown) {
            if (this->figure->getPosition().y == 10) {
                this->state = 2;
            } else {
                for (auto block: figureBlocks) {
                    this->blocks.push_back(block);
                }
                this->updateBlocksModel();
                this->handleLevel();
                delete this->figure;
                this->addFigure();
            }
        }
    } else {
        this->figure->move(potentialMove);
    }
}

void Game::updateBlocksModel() {
    delete this->blocksModel;
    this->blocksModel = new Blocks(this->blocks);
}

bool Game::hasCollision(std::vector<CBlock> figureBlocks, glm::vec3 potentialMove) {
    for (auto figureBlock: figureBlocks) {
        auto potentialBlock = figureBlock.block + potentialMove;
        if (potentialBlock.x > 5 || potentialBlock.x < -5) {
            return true;
        }
        if (potentialBlock.y > 10 || potentialBlock.y < 1) {
            return true;
        }
        if (potentialBlock.z > 5 || potentialBlock.z < -5) {
            return true;
        }
        for (auto cblock: blocks) {
            if (potentialBlock == cblock.block) {
                return true;
            }
        }
    }
    return false;
}

void par(int *a) {
    for (int i = 0; i < 10; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void Game::handleLevel() {
    int levels[10] = {0};
    int levelsLowering[10] = {0};
    int currentLevelLowering = 0;

    for (auto cblock: this->blocks) {
        levels[(int) cblock.block.y - 1] += 1;
    }

    for (int i = 0; i < 10; i++) {
        levelsLowering[i] = currentLevelLowering;
        if (levels[i] == 100) {
            std::vector<CBlock> tmp = this->blocks;
            this->blocks = std::vector<CBlock>();
            for (auto cblock: tmp) {
                if (cblock.block.y - 1 != i) {
                    this->blocks.push_back(cblock);
                }
            }
            currentLevelLowering += 1;
            this->score = this->score + 1;
        }
    }

    for (auto &cblock: this->blocks) {
        cblock.block.y = cblock.block.y - levelsLowering[(int) cblock.block.y - 1];
    }
    this->updateBlocksModel();
}

void Game::drawBoard() {
    this->board->draw();
}

void Game::tick() {
    if (state == 0) {
        font.setPenPosition(60, 200);
        font.setPenColor(1.0, 0.0, 0.0);
        font.setPointSize(20);
        font.draw("Press button to start");
    } else {
        auto currentMills = getMills();
        if (currentMills - lastForcedMove > 700) {
            if (lastForcedMove > 0) {
                this->move(glm::vec3(0, -1, 0));
            }
            lastForcedMove = currentMills;
        }
        this->rotateCamera();
        this->drawBoard();
        this->figure->draw();
        this->blocksModel->draw();
        if (state == 1) {
            font.setPenPosition(250, 250);
            font.setPenColor(1.0, 0.0, 0.0);
            font.setPointSize(10);
            font.draw("Score: " + std::to_string(score));
        } else {
            font.setPenColor(1.0, 0.0, 0.0);
            font.setPointSize(20);
            font.setPenPosition(90, 190);
            font.draw("Game over");
            font.setPenPosition(100, 170);
            font.draw("Score: " + std::to_string(score));
            font.setPenPosition(60, 150);
            font.draw("Press button to restart");
        }
    }
}

void Game::rotateCamera() {
    if (mouse_down) {
        double x, y;
        glfwGetCursorPos(this->window, &x, &y);
        x = glm::clamp(x, (double) 0, (double) 500);
        y = glm::clamp(y, (double) 0, (double) 500);
        double dx = x - lastX;
        double dy = y - lastY;
        if (lastX != -1) {
            Camera::instance().rotate(dx, dy);
        }
        lastX = x;
        lastY = y;
    }
}