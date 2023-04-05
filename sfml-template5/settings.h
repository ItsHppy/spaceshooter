#pragma once
#include "SFML/Graphics.hpp"

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 1000;
const std::string WINDOW_TITLE = "SFML Space Shooter P33122";
const float FPS = 60.f;

const std::string PLAYER_FILE_NAME = "images\\orangeship.png";
const std::string LASER_FILE_NAME = "images\\redlaser.png";
const float PLAYER_WIDTH = 99.f;
const float PLAYER_HEIGHT = 75.f;
const sf::Vector2f PLAYER_START_POS{ (WINDOW_WIDTH - PLAYER_WIDTH) / 2, WINDOW_HEIGHT - PLAYER_HEIGHT };
const float PLAYER_SPEED = 10.f;
const float LASER_SPEED = -15.f;

const int METEORS_QTY = 20;
const float FIRE_COOLDOWN = 200;

const std::string FONT_FILE_NAME = "DS-DIGIT.TTF";
const size_t CHAR_SIZE = 32;
const size_t CHAR1_SIZE = 64;
const std::string END_FILE_NAME = "images\\goodgame.h";