#include <bangtal.h>

SceneID startScene, instruction, hollywood, hanamura, volskaya;
ObjectID startButton, title , playButton, ok, deadeye, hand, trooper[3], bas[2], ori;
SoundID startBGM, hollywoodBGM, volskayaBGM, hanamuraBGM;
TimerID timer1;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}
	return object;
}

SoundID BGM(const char* mp3, bool play) {
	SoundID sound = createSound(mp3);
	if (play) {
		playSound(sound);
	}
	return sound;
}



void game_stage(SceneID scene, SoundID bgm, const char* mp3, float time) {
	enterScene(scene);
	bgm = BGM(mp3, true);
	
	hand = createObject("Images/hand.png", scene, 800, 0, true);
	deadeye = createObject("Images/deadeye.png", scene, 540, 10, false);

	setTimer(timer1, time);
	showTimer(timer1);
	startTimer(timer1);

	if (scene == hollywood) {

	}
	else if (scene == hanamura) {

	}
	else if (scene == volskaya) {

	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == playButton) {
		enterScene(instruction);
	}
	else if (object == ok) {
		stopSound(startBGM);
		game_stage(hollywood, hollywoodBGM, "Sound/hollywoodBGM.mp3", 20.0f);
	}
}

int main() {
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	
	setMouseCallback(mouseCallback);
	
	startScene = createScene("시작화면", "start.jpg");
	instruction = createScene("미션설명", "instruction.png");
	hollywood = createScene("할리우드", "hollywood.jpg");
	hanamura = createScene("하나무라", "hanamura.jpg");
	volskaya = createScene("볼스카야", "volskkaya.jpg");

	startBGM = BGM("Sound/startBGM.mp3", true);
	
	title = createObject("Images/title.png", startScene, 30, 550, true);
	playButton = createObject("Images/play.png", startScene, 50, 470, true);
	ok = createObject("Images/ok.png", instruction, 1100, 20, true);
	
	timer1 = createTimer(55.0f);

	startGame(startScene);
}