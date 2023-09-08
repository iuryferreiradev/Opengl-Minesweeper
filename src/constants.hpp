#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/glm.hpp>
#include <map>

constexpr int SCREEN_WIDTH = 384;
constexpr int SCREEN_HEIGHT = 456;
constexpr float TILE_SIZE = 24.0f;
constexpr float OFFSET_Y = 72.0f;
constexpr int COLS = 16;
constexpr int ROWS = 16;
constexpr int BOMB_AMOUNT = 40;
constexpr glm::vec4 BACKGROUND = glm::vec4(75.0 / 255.0, 148.0 /255.0, 110.0 /255.0, 1.0);
constexpr glm::vec4 GREEN_ONE = glm::vec4(192.0 / 255.0, 224.0 /255.0, 132.0 /255.0, 1.0);
constexpr glm::vec4 GREEN_TWO = glm::vec4(186.0 / 255.0, 220.0 /255.0, 127.0 /255.0, 1.0);
constexpr glm::vec4 DARKGREEN = glm::vec4(75.0 / 255.0, 116.0 /255.0, 50.0 /255.0, 1.0);
constexpr glm::vec4 BROWN_ONE = glm::vec4(229.0 / 255.0, 193.0 /255.0, 161.0 /255.0, 1.0);
constexpr glm::vec4 BROWN_TWO = glm::vec4(215.0 / 255.0, 183.0 /255.0, 155.0 /255.0, 1.0);
constexpr glm::vec4 HIGHLIGHT = glm::vec4(1.0, 1.0, 1.0, 0.4);

constexpr glm::vec4 NUMBER_COLORS[] = {
  //             RED            GREEN          BLE            OP
  glm::vec4(0.0   / 255.0, 0.0   / 255.0, 255.0 / 255.0, 1.0), // rgb(0, 0, 255)
  glm::vec4(0.0   / 255.0, 128.0 / 255.0, 0.0   / 255.0, 1.0), // rgb(0, 128, 0)
  glm::vec4(255.0 / 255.0, 0.0   / 255.0, 0.0   / 255.0, 1.0), // rgb(255, 0, 0)
  glm::vec4(0.0   / 255.0, 0.0   / 255.0, 128.0 / 255.0, 1.0), // rgb(0, 0, 128)
  glm::vec4(128.0 / 255.0, 0.0   / 255.0, 0.0   / 255.0, 1.0), // rgb(128, 0, 0)
  glm::vec4(0.0   / 255.0, 128.0 / 255.0, 128.0 / 255.0, 1.0), // rgb(0, 128, 128)
  glm::vec4(0.0   / 255.0, 0.0   / 255.0, 0.0   / 255.0, 1.0), // rgb(0, 0, 0)
  glm::vec4(128.0 / 255.0, 128.0 / 255.0, 128.0 / 255.0, 1.0), // rgb(128, 128, 128)
};

#endif