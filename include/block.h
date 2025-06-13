#ifndef RPS_H
#define RPS_H

#include "collider.h"
#include "gameObject.h"
#include "unit.h"

enum Type { CACTUS, COIN };

class Block : public GameObject {

	public:
		Block(Type type, Position pos);
		void update() override;
		void onCollision(ICollider *other) override;

		Type getType();
		void setType(Type type);

	private:
		Type _type;
};
#endif
