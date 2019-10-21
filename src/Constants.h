#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

const unsigned int MIN_FPS = 20;
const unsigned int MAX_FRAME_TIME = 1000 / MIN_FPS;
const float MAX_DELTA_TIME = MAX_FRAME_TIME / 1000.0f;

enum LayerType
{
    TILEMAP_LAYER = 0,
    VEGETATION_LAYER = 1,
    ENEMY_LAYER = 2,
    PLAYER_LAYER = 3,
    PROJECTILE_LAYER = 4,
    UI_LAYER = 5
};

const unsigned int NUM_LAYERS = 6;

#endif

