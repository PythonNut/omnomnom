#include "engine.hpp"
#include "menu.hpp"
#include "game.hpp"


int main() {
	Engine engine;

	engine.pushState(new Menu);
	engine.pushState(new Game);
	engine.pushState(new Menu);
	engine.loop();
	return 0;
}

// TODO: Features to add by precedence:
// Eating dots
// Score + victory
// AI
// Wrap around