#pragma once
#include <pch.h>
enum TextureId {
    EMPTY,
    MARIO_STAND,
    MARIO_RUN_1,
    MARIO_RUN_2,
    MARIO_RUN_3,
    MARIO_JUMP,
    MARIO_DRIFT,
    MARIO_DEAD,
    MARIO_GROWING,
    SUPER_MARIO_STAND,
    SUPER_MARIO_RUN_1,
    SUPER_MARIO_RUN_2,
    SUPER_MARIO_RUN_3,
    SUPER_MARIO_JUMP,
    SUPER_MARIO_DRIFT,
    SUPER_MARIO_DUCK,
    GOOMBA,
    GOOMBA_CRUSHED,
    QUESTION_BLOCK_1,
    QUESTION_BLOCK_2,
    QUESTION_BLOCK_3,
    QUESTION_BLOCK_OFF,
    MUSHROOM,
    FLOOR,
    TUBE_TOP_LEFT,
    TUBE_TOP_RIGHT,
    TUBE_RIGHT,
    TUBE_LEFT,
    CLOUD,
    BRICK,
    BLOCK,
    BUSH_RIGHT,
    BUSH_CENTER,
    BUSH_LEFT,
    BACKGROUND_CLOUD_TOP_LEFT,
    BACKGROUND_CLOUD_TOP_CENTER,
    BACKGROUND_CLOUD_TOP_RIGHT,
    BACKGROUND_CLOUD_BOTTOM_LEFT,
    BACKGROUND_CLOUD_BOTTOM_CENTER,
    BACKGROUND_CLOUD_BOTTOM_RIGHT,
    BRICK_DEBRIS_1,
    BRICK_DEBRIS_2,
    BRICK_DEBRIS_3,
    BRICK_DEBRIS_4,
    BACKGROUND_MOUNTAIN_1,
    BACKGROUND_MOUNTAIN_2,
    BACKGROUND_MOUNTAIN_3,
    BACKGROUND_MOUNTAIN_4,
    BACKGROUND_MOUNTAIN_5,
    COIN_1,
    COIN_2,
    COIN_3,
    COIN_4,
    TURTLE_1,
    TURTLE_2,
    TURTLE_SHELL_1,
    TURTLE_SHELL_2,
    FLAG_TOP,
    FLAG_RIGHT,
    FLAG_LEFT,
    FLAG_POLE,
    CASTLE_1,
    CASTLE_2,
    CASTLE_3,
    CASTLE_4,
    CASTLE_5,
    CASTLE_6,
    CASTLE_DOOR,
    CASTLE_8,
    COIN_SMALL_1,
    COIN_SMALL_2,
    COIN_SMALL_3,
    ONE_UP,
    ONE_UP_LABEL,
    ONEHUNDRED,
    TWOHUNDRED,
    THOUSAND,
    MARIO_FLAG_1,
    MARIO_FLAG_2,
};

struct TextureComponent {
    explicit TextureComponent(TextureId id) : id{id} {};

    TextureId id;

    bool flipV = false;
    bool flipH = false;

    int w = 0;
    int h = 0;
    int offSetX = 0;
    int offSetY = 0;

    ~TextureComponent() = default;
};

struct AnimationComponent {
    AnimationComponent(
        std::vector<TextureId> &&textures,
        int duration,
        bool flipH = false,
        bool flipV = false,
        bool loop = true
    ) : textures{std::move(textures)},
        duration{duration},
        flipH{flipH},
        flipV{flipV},
        loop{loop} {}
    std::vector<TextureId> textures;
    int duration = 0;
    int counter = 0;
    bool flipH = false;
    bool flipV = false;
    bool loop = true;
    size_t currentTexture = 0;
};
