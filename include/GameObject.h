#pragma once
#include "pch.h"
using json = nlohmann::json;
#include "AbstractEntity.h"
#include "Components/Position.h"
#include "Components/BoundingBox.h"
#include "Components/Texture.h"

// Derived class for a normal block
class NormalBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    NormalBlock()=default;
    NormalBlock(Texture2D texture, Vector2 position);
    ~NormalBlock()=default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a broken block
class BrokenBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    BrokenBlock()=default;
    BrokenBlock(Texture2D texture, Vector2 position);
    ~BrokenBlock()=default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a hard block
class HardBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    HardBlock()=default;
    HardBlock(Texture2D texture, Vector2 position);
    ~HardBlock()=default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a ground block
class GroundBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    GroundBlock()=default;
    GroundBlock(Texture2D texture, Vector2 position);
    ~GroundBlock()=default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a question block
class QuestionBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    QuestionBlock()=default;
    QuestionBlock(Texture2D texture, Vector2 position);
    ~QuestionBlock()=default;
    void draw() override;
    void update(float deltaTime) override;
};

class Pipe : public AbstractEntity {
private:
    bool isCollision = false;
public:
    Pipe()=default;
    Pipe(Vector2 position, Vector2 size);
    ~Pipe()=default;
    void draw() override;
    void update(float deltaTime) override;
};
class Flag: public AbstractEntity {
private:
    bool isCollision = false;
public:
    Flag()=default;
    Flag(Vector2 position);
    ~Flag()=default;
    void draw() override;
    void update(float deltaTime) override;
};
//-----------------------OLD--------
//class Block : public AbstractEntity,
//               public IDrawable,
//               public IUpdatable {
// public:
//     Block() = default;
//     Block(std::string name) : AbstractEntity(name) {}
//     Block(std::string name, Texture2D texture, Vector2 position) : AbstractEntity(name) {
//     }
//     virtual void draw() = 0;
//     virtual ~Block() = default;
// };

// // Derived class for a normal block
// class NormalBlock : public Block {
// public:
//     NormalBlock() = default;
//     NormalBlock(Texture2D texture, Vector2 position) : Block("NormalBlock", texture, position) {
//         addComponent<PositionComponent>(position);
//         addComponent<BoundingBoxComponent>(Vector2{16, 16});
//         addComponent<TextureComponent>().addTexture("Normal", texture);
//     }
//     ~NormalBlock() = default;
//     void draw() override {
//         getComponent<TextureComponent>().drawTexture("Normal");
//     }
//     void update() override {
//         // Implementation of the update function
//     }
// };

// // Derived class for a broken block
// class BrokenBlock : public Block {
// public:
//     BrokenBlock() = default;
//     BrokenBlock(Texture2D texture, Vector2 position) : Block("BrokenBlock", texture, position) {
//         addComponent<PositionComponent>(position);
//         addComponent<BoundingBoxComponent>(Vector2{16, 16});
//         addComponent<TextureComponent>().addTexture("Normal", texture);
//     }
//     ~BrokenBlock() = default;
//     void draw() override {
//         getComponent<TextureComponent>().drawTexture("Normal");
//     }
//     void update() override {
//         // Implementation of the update function
//     }
// };

// // Derived class for a hard block
// class HardBlock : public Block {
// public:
//     HardBlock() = default;
//     HardBlock(Texture2D texture, Vector2 position) : Block("HardBlock", texture, position) {
//       addComponent<PositionComponent>(position);
//         addComponent<BoundingBoxComponent>(Vector2{16, 16});
//         addComponent<TextureComponent>().addTexture("Normal", texture);
//     }
//     ~HardBlock() = default;
//     void draw() override {
//         getComponent<TextureComponent>().drawTexture("Normal");
//     }
//     void update() override {
//         // Implementation of the update function
//     }
// };

// // Derived class for a ground block
// class GroundBlock : public Block {
// public:
//     GroundBlock() = default;
//     GroundBlock(Texture2D texture, Vector2 position) : Block("GroundBlock", texture, position) {
//       addComponent<PositionComponent>(position);
//         addComponent<BoundingBoxComponent>(Vector2{16, 16});
//         addComponent<TextureComponent>().addTexture("Normal", texture);
//     }
//     ~GroundBlock() = default;
//     void draw() override {
//         getComponent<TextureComponent>().drawTexture("Normal");
//     }
//     void update() override {
//         // Implementation of the update function
//     }
// };

// // Derived class for a question block
// class QuestionBlock : public Block {
// public:
//     QuestionBlock() = default;
//     QuestionBlock(Texture2D texture, Vector2 position) : Block("QuestionBlock", texture, position) {
//       addComponent<PositionComponent>(position);
//         addComponent<BoundingBoxComponent>(Vector2{16, 16});
//         addComponent<TextureComponent>().addTexture("Normal", texture);
//     }
//     ~QuestionBlock() = default;
//     void draw() override {
//         getComponent<TextureComponent>().drawTexture("Normal");
//     }
//     void update() override {
//         // Implementation of the update function
//     }
// };