#include "gameObjectFactory.h"
#include "environment.h"
#include "iconFactory.h"
#include <chrono>
#include <random>
#include <set>
std::random_device rd;
std::mt19937 engine(rd());
std::uniform_int_distribution<int> distX(0, GAME_WINDOW_WIDTH - 1);
std::uniform_int_distribution<int> distY(0, GAME_WINDOW_HEIGHT - 1);

Dino* GameObjectFactory::createPlayer() {
	return new Dino();
}

Block* GameObjectFactory::createCactus() {
	return new Block(CACTUS, Vec2(39, 14));
}

Block* GameObjectFactory::createCoin() {
	return new Block(COIN, Vec2(39, 14));
}

/*
   GameObject* GameObjectFactory::randomGameObject() {
   int x = distX(engine);
   int y = distY(engine);
   return new GameObject(IconFactory::NxMColor(Size(2, 2), BLUE),
   Position{x, y});
   }
 */
