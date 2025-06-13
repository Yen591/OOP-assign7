#ifndef DINO_H
#define DINO_H

#include "gameObject.h"

class Dino : public GameObject {
	private:
		int jumpState = 0; // 0: idle, 1: up1, 2: up2, 3: down1, 4: down2
		int score = 0;

	public:
		Dino();
		void startJump();
		void update() override;
		int getJumpState() const;
		int getScore() const;
		void onCollision(ICollider* other) override;
};

#endif // DINO_H
