#include "block.h"
#include "iconFactory.h"
#include "gameObject.h"
#include "gameObjectFactory.h"

Block::Block(Type type, Position pos)
	: GameObject(IconFactory::NxMColor(Vec2(1, 1), (type==CACTUS? GREEN:YELLOW)), pos), _type(type) {
	_alive = true;
}

void Block::update() {
	// move right per frame
	_pos.x() -= 1;
	if (_pos.x() < 0) {
		_alive = false;
	}
}

Type Block::getType() {
	return _type;
}

void Block::setType(Type type) {
	_type = type;
}

void Block::onCollision(ICollider* other) {
    _alive = false;
}
