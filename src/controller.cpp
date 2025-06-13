#include <iostream>
#include <ctime>
#include <thread>
#include <random>
#include <unistd.h>
#include <termios.h>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"


Controller::Controller(View& view) : _view(view){

	_objs.emplace_back(GameObjectFactory::createPlayer());
}


void Controller::run() {
	// initial setup
	std::cin.tie(0);
	std::ios::sync_with_stdio(0);
	configure_terminal();

	// init state
	int input = -1;
	clock_t start, end;

	// random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 5);

	// Main loop
	while (true) {
		start = clock();
		// game loop goes here
		input = read_input();

		// ESC to exit program
		if(input==27)break;

		this->handleInput(input);

		// check collision
		for (size_t i = 0; i < _objs.size(); ++i) {
			for (size_t j = i + 1; j < _objs.size(); ++j) {
				if (_objs[i]->intersect(_objs[j])) {
					_objs[i]->onCollision(_objs[j]);
					_objs[j]->onCollision(_objs[i]);
				}
			}
		}

		// check alive 
		for (auto it = _objs.begin(); it != _objs.end(); ) {
			if (!(*it)->isAlive()) {
				delete *it;
				it = _objs.erase(it);
			} else {
				++it;
			}
		}

		_view.resetLatest();
		for(GameObject* obj : _objs) 
		{

			obj->update();

			_view.updateGameObject(obj);
		}

		// add new object
		int rd_num = dist(gen);	
		if (rd_num == 1 && space == false) {
			_objs.emplace_back(GameObjectFactory::createCactus());
			space = true;
		} else if (rd_num == 2 && space == false) {
			_objs.emplace_back(GameObjectFactory::createCoin());
			space = true;
		} else {
			space = false;
		}

		_view.render();
		end = clock();
		// frame rate normalization
		double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
		if (time_taken > SPF) continue;
		int frameDelay = int((SPF - time_taken) * 1000); // 0.1 seconds
		if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay

		// check score
		checkScore();
		if (win) {
			std::cout << "You win!!!\n";
			break;
		}

		// check player alive
		if (!(_objs[0])->isAlive()) {
			std::cout << "You lose.\n";
			break;
		}
	}
}


void Controller::handleInput(int keyInput){
	if(keyInput==-1)return;

	if(keyInput == 'w' || keyInput == 'W') {
		auto* player = dynamic_cast<Dino*>(_objs[0]);
		if (player) {
			player->startJump();
		}
	}
}

void Controller::checkScore() {
	auto* player = dynamic_cast<Dino*>(_objs[0]);
	if (player) {
		if (player->getScore() >= 10) {
			win = true;
		}
	}
}

void Controller::update(){}

void reset_terminal() {
	printf("\e[m"); // reset color changes
	printf("\e[?25h"); // show cursor
	fflush(stdout);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
	tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit

	new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
	new_termios.c_cc[VMIN] = 0;
	new_termios.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

	printf("\e[?25l"); // hide cursor
	std::atexit(reset_terminal);
}


int read_input() {
	fflush(stdout);
	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
	return n > 0 ? buf[n - 1] : -1;
}

