#include "gameObject.h"
#include "dino.h"
#include "block.h"

class GameObjectFactory {

	public:
		static Dino* createPlayer();
		static Block* createCactus();
		static Block* createCoin();

};
