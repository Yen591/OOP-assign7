#include "gameObject.h"
#include "dino.h"
#include "environment.h"
#include "iconFactory.h"
#include "block.h"
#include <iostream>

Dino::Dino() : GameObject(IconFactory::NxMColor(Size(1, 1), RED), Position{1, 14}) {}

void Dino::startJump() { 
	if (jumpState == 0) {
		jumpState = 1;
	}
}

void Dino::update() {
	switch (jumpState) {
		case 1:
			_pos.y() -= 1;
			jumpState = 2;
			break;
		case 2:
			_pos.y() -= 1;
			jumpState = 3;
			break;
		case 3:
			_pos.y() += 1;
			jumpState = 4;
			break;
		case 4:
			_pos.y() += 1;
			jumpState = 0;
			break;
		default:
			break;
	}
}

int Dino::getJumpState() const {
	return jumpState;
}

int Dino::getScore() const {
	return score;
}

void Dino::onCollision(ICollider* other) {
    Block* block = dynamic_cast<Block*>(other);
    if (!block) return;

    if (block->getType() == COIN) {
        score++;
    } else if (block->getType() == CACTUS) {
        _alive = false;
    }
}
