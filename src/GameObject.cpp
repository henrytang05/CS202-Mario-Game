#include "Entity/EntityFactory.h"


Unique <IFactory> _entityFactory;
 
  
NormalBlock::NormalBlock(Vector2 position): AbstractEntity("NormalBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("NormalBlock"));
}

void NormalBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void NormalBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

BrokenBlock::BrokenBlock(Vector2 position): AbstractEntity("BrokenBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("BrokenBlock"));
    addComponent<BlockTriggerComponent>();
}

void BrokenBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void BrokenBlock::update(float deltaTime) {
    if(this->isCollision)
    {
        this->name = "HardBlock";
        Vector2 position_fixed = this->getComponent<PositionComponent>().getPosition();
        this->removeComponent<BlockTriggerComponent>();
        this->modifyComponent<PositionComponent>(position_fixed);
        this->modifyComponent<TextureComponent>();
        this->getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("HardBlock"));
    }
    for(auto &comp : components){
        if(comp==nullptr) continue;
        comp->update(deltaTime);
    }
        
}

HardBlock::HardBlock(Vector2 position): AbstractEntity("HardBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("HardBlock"));
}

void HardBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void HardBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

GroundBlock::GroundBlock(Vector2 position): AbstractEntity("GroundBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("GroundBlock"));
}

void GroundBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void GroundBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

QuestionBlock::QuestionBlock(Vector2 position): AbstractEntity("QuestionBlock") {
    Vector2 size({16, 16});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<BlockTriggerComponent>();
    addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("QuestionBlock"));
    
    //items.push_back(_entityFactory->createCoin({position.x, position.y - 16.0f}));
    
}

void QuestionBlock::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
    // for(auto &entity : items)
    //     entity->draw();
}

void QuestionBlock::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

Pipe::Pipe(Vector2 position, Vector2 size): AbstractEntity("Pipe") {
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Pipe"));
    std::cerr<<"create pipe"<<std::endl;
}

void Pipe::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void Pipe::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

//
Flag::Flag(Vector2 position): AbstractEntity("Flag") {
    Vector2 size = {16, 16};
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Flag") );

    std::cerr<<"create flag"<<std::endl;
}

void Flag::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void Flag::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

FlagPole::FlagPole(Vector2 position): AbstractEntity("FlagPole") {
    Vector2 size = {16, 16};
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TextureComponent>();
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("FlagPole") );

    std::cerr<<"create flagpole"<<std::endl;
}

void FlagPole::draw() {
    ASSERT(hasComponent<TextureComponent>());
    getComponent<TextureComponent>().drawTexture("Normal");
}

void FlagPole::update(float deltaTime) {
    for(auto &comp : components)
        comp->update(deltaTime);
}

Piranha::Piranha(Vector2 position) : AbstractEntity("Piranha") {
Vector2 size = {16, 32};
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  vector<Texture2D> textures;
  textures.push_back(TextureManager::getInstance().getTexture("Piranha1"));
  textures.push_back(TextureManager::getInstance().getTexture("Piranha2"));
  getComponent<TextureComponent>().addTexture("Normal", textures, 0.1f, true);
  getComponent<TextureComponent>().changeState("Normal");
  addComponent<EnemyTag>();
  position_fixed = position;
}

void Piranha::update(float deltaTime) {
elapsedTime += deltaTime;
float amplitude = 30.0f; // Distance to move up and down
float frequency = 1.0f; // Speed of oscillation

auto position_change = getComponent<PositionComponent>().getPosition();
position_change.y = position_fixed.y - amplitude * (1.0f + sin(frequency * elapsedTime)) / 2.0f;

// Ensure it doesn't go below the fixed position
if (position_change.y > position_fixed.y) {
  position_change.y = position_fixed.y;
}
  getComponent<PositionComponent>().setPosition(position_change);
}

void Piranha::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

Mushroom::Mushroom(Vector2 position) {
    Vector2 size = {0,0};
    addComponent<CollisionComponent>();
    addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
    addComponent<BoundingBoxComponent>(size);
    addComponent<PositionComponent>(position);   
    position_fixed = getComponent<PositionComponent>().getPosition(); 
    addComponent<TextureComponent>();
    // vector<Texture2D> textures;
    // textures.push_back(TextureManager::getInstance().getTexture("Coin1"));
    // textures.push_back(TextureManager::getInstance().getTexture("Coin2"));
    // textures.push_back(TextureManager::getInstance().getTexture("Coin3"));
    // getComponent<TextureComponent>().addTexture("Normal", textures, 0.1f, true);
    // getComponent<TextureComponent>().changeState("Normal");
    getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Mushroom") );
}


void Mushroom::handleCollision()
{
    CollisionComponent &collision = getComponent<CollisionComponent>();
    auto above = collision.getAbove();
    auto below = collision.getBelow();
    auto left = collision.getLeft();
    auto right = collision.getRight();

    auto &trans = getComponent<TransformComponent>();
    
    Vector2 v = trans.getVelocity();
    if (left.lock() && !left.lock()->hasComponent<EnemyTag>())
        v.x = -ENEMY_SPEED;
    if (right.lock() && !right.lock()->hasComponent<EnemyTag>())
        v.x = ENEMY_SPEED;
    if(below.lock() == nullptr)
        v.y = 100.0f;
    trans.setVelocity(v);

    getComponent<CollisionComponent>().reset();
}

void Mushroom::update(float deltaTime) {
    if(isTriggered)
    {   
        elapsedTime += deltaTime;

        auto position_change = getComponent<PositionComponent>().getPosition();
        position_change.y = position_change.y - 16.0f * deltaTime;

        // Ensure it doesn't go below the fixed position
        if (position_change.y < position_fixed.y - 16.0f) {
            position_change.y = position_fixed.y - 17.0f;
            isTriggered = false;
            getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 16.0f});
            getComponent<TransformComponent>().setVelocity((Vector2){50.0f, 10.0f});
        }
        getComponent<PositionComponent>().setPosition(position_change);
    }
    //     elapsedTime += deltaTime;
    //     Vector2 velocity = this->getComponent<TransformComponent>().getVelocity();
    //     if(elapsedTime < 0.2f) {
    //         velocity = velocity + (Vector2){0.0f, -600.0f * deltaTime};
    //     }
    //     velocity = velocity + (Vector2){0.0f, 120.0f * deltaTime};
    //     if(velocity.y >= 1200.0f) velocity.y = 1200.0f;
    //     if(velocity.y <= -1200.0f) velocity.y = -1200.0f;
    //     if(elapsedTime >= 1) {
    //         this->getComponent<PositionComponent>().setPosition(Vector2{-16,-16});
    //         velocity.y = 0.0f;
    //         isTriggered = false;
    //     }
    //     this->getComponent<TransformComponent>().setVelocity(velocity);
    // }
    if(this->getComponent<BoundingBoxComponent>().getSize().y == 16.0f)
        handleCollision();
    for(auto &comp : components)
        comp->update(deltaTime);
}

void Mushroom:: onNotify()
{
    isTriggered = true;
    getComponent<BoundingBoxComponent>().setSize({16.0f, 16.0f});  

}


Coin::Coin(Vector2 position): AbstractEntity("Coin") {
    Vector2 size({1, 1});
    addComponent<PositionComponent>(position);    
    addComponent<BoundingBoxComponent>(size);
    addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
    addComponent<BoundingBoxComponent>(size);
    addComponent<PositionComponent>(position);
    addComponent<TextureComponent>();
    addComponent<CoinSoundComponent>();
    vector<Texture2D> textures;
    textures.push_back(TextureManager::getInstance().getTexture("Coin1"));
    textures.push_back(TextureManager::getInstance().getTexture("Coin2"));
    textures.push_back(TextureManager::getInstance().getTexture("Coin3"));
    getComponent<TextureComponent>().addTexture("Normal", textures, 0.1f, true);
    getComponent<TextureComponent>().changeState("Normal");
}


void Coin::update(float deltaTime) {
    if(isTriggered){
        elapsedTime += deltaTime;
        Vector2 velocity = this->getComponent<TransformComponent>().getVelocity();
        if(elapsedTime < 0.2f) {
            velocity = velocity + (Vector2){0.0f, -600.0f * deltaTime};
        }
        velocity = velocity + (Vector2){0.0f, 120.0f * deltaTime};
        if(velocity.y >= 1200.0f) velocity.y = 1200.0f;
        if(velocity.y <= -1200.0f) velocity.y = -1200.0f;
        if(elapsedTime >= 1) {
            this->getComponent<PositionComponent>().setPosition(Vector2{-16,-16});
            velocity.y = 0.0f;
            isTriggered = false;
        }
        this->getComponent<TransformComponent>().setVelocity(velocity);
    }
    for(auto &comp : components)
        comp->update(deltaTime);
}

void Coin::onNotify()
{
    isTriggered = true;
    getComponent<BoundingBoxComponent>().setSize({16.0f, 16.0f});
    getComponent<CoinSoundComponent>().PlayCoinEffect();
}
