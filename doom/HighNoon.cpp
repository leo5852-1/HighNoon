#include <bangtal.h>

SceneID startScene, instruction;
ObjectID startButton, title , playButton, ok, deadeye;
SoundID startBGM;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}
	return object;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == playButton) {
		enterScene(instruction);
	}
	else if (object == ok) {
		stopSound(startBGM);
	
	}
}

int main() {
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	
	setMouseCallback(mouseCallback);
	
	startScene = createScene("시작화면", "start.jpg");
	instruction = createScene("미션설명", "instruction.png");

	startBGM = createSound("Sound/startBGM.mp3");
	playSound(startBGM);
	
	title = createObject("Images/title.png", startScene, 30, 550, true);
	playButton = createObject("Images/play.png", startScene, 50, 470, true);
	ok = createObject("Images/ok.png", instruction, 1100, 20, true);

	startGame(startScene);
}