#include <bangtal.h>
#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

SceneID startScene, instruction, hollywood, hanamura, volskaya, victory, defeat;
ObjectID startButton, title , playButton, ok, deadeye, hand, reload, trooper[3], bas[2], ori, retry;
SoundID startBGM, hollywoodBGM, volskayaBGM, hanamuraBGM , gunshot, kill, ready;
TimerID timer1, timer2;

int trooperHP[3] = { 1, 1, 1 }, basHP[2] = { 2, 2 }, oriHP = 3, meter = 0, ammo = 6, killed = 0, i = 0, stage = 1;
bool gunVisible = false, spawn = false;

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

void highNoon() {
	BGM("Sound/highNoon.mp3", true);
	timer2 = createTimer(7.0f);
	startTimer(timer2);
}

bool stage_end() {
	if (killed == 6) {
		return true;
	}
	else return false;
}

void start_stage(SceneID stage) {
	for (int i = 0; i < 3; i++) {
		trooper[i] = createObject("Images/trooper.png", stage, rand() % 1000, rand() % 500, true);
		}	
	for (int i = 0; i < 2; i++) {
		bas[i] = createObject("Images/bas.png", stage, rand() % 1000, rand() % 500, true);
	}
	ori = createObject("Images/ori.png", stage, rand() % 1000, rand() % 500, true);
}

void set_stage(SceneID scene, SoundID bgm, const char* mp3, float time) {
	enterScene(scene);
	bgm = BGM(mp3, true);
	
	hand = createObject("Images/hand.png", scene, 800, 0, true);
	gunVisible = true;
	deadeye = createObject("Images/deadeye.png", scene, 540, 10, false);
	reload = createObject("Images/reload.png", scene, 1100, 200, true);

	setTimer(timer1, time);
	showTimer(timer1);
	startTimer(timer1);

	start_stage(scene);
}

void reset() {
	stage++;
	killed = 0;
	for (i = 0; i < 3; i++) {
		trooperHP[i] = 1;
	}
	for (i = 0; i < 2; i++) {
		basHP[i] = 2;
	}
	oriHP = 3;
}

void game(bool clear) {
	if (clear) {
		if (stage == 1) {
			reset();
			stopSound(startBGM);
			set_stage(hollywood, hollywoodBGM, "Sound/hollywoodBGM.mp3", 20.0f);
		}
		else if (stage == 2) {
			reset();
			stopSound(hollywoodBGM);
			set_stage(hanamura, hanamuraBGM, "Sound/hanamuraBGM.mp3", 16.0f);
		}
		else if (stage == 3) {
			reset();
			stopSound(hanamuraBGM);
			set_stage(volskaya, volskayaBGM, "Sound/volskayaBGM.mp3", 12.0f);
		}
		else if (stage == 4) {
			stopTimer(timer1);
			victory = createScene("승리", "victory.png");
			enterScene(victory);
			BGM("Sound/victoryBGM.mp3", true);
		}
	}
}

void hit(int HP, ObjectID enemy) {
	if (HP == 0) {
		hideObject(enemy);
		kill = createSound("Sound/kill.mp3");
		playSound(kill);
		meter++;
		killed++;
		if (meter >= 13) {
			deadeye = createObject("Images/deadeye.png", hollywood, 540, 10, true);
			deadeye = createObject("Images/deadeye.png", hanamura, 540, 10, true);
			deadeye = createObject("Images/deadeye.png", volskaya, 540, 10, true);
			ready = createSound("Sound/ready.mp3");
			playSound(ready);
		}
	}
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == playButton) {
		enterScene(instruction);
	}
	else if (object == ok) {
		game(true);
	}
	else if (object == reload) {
		ammo = 6;
	}
	else if (object == deadeye) {
		highNoon();
	}
	else if (gunVisible && ammo > 0) {
		gunshot = createSound("Sound/gunshot.mp3");
		playSound(gunshot);
		ammo--;
		if (object == trooper[0]) {
			trooperHP[0]--;
			hit(trooperHP[0], trooper[0]);
		}
		else if (object == trooper[1]) {
			trooperHP[1]--;
			hit(trooperHP[1], trooper[1]);
		}
		else if (object == trooper[2]) { 
			trooperHP[2]--; 
			hit(trooperHP[2], trooper[2]);
		}
		else if (object == bas[0]) {
			basHP[0]--;
			hit(basHP[0], bas[0]);
		}
		else if (object == bas[1]) { 
			basHP[1]--; 
			hit(basHP[1], bas[1]);
		}
		else if (object == ori) {
			oriHP--;
			hit(oriHP, ori);
		}
		game(stage_end());
	}
	else if (object == retry) {
		meter = 0;
		stage = 1;
		game(true);
		stopSound(defeat);
	}
}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		gunVisible = false;
		defeat = createScene("패배", "defeat.png");
		enterScene(defeat);
		BGM("Sound/defeatBGM.mp3", true);
		retry = createObject("Images/retry.png", defeat, 550, 200, true);
	}
	if (timer == timer2) {
		game(true);
	}
}

int main() {
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	
	startScene = createScene("시작화면", "start.jpg");
	instruction = createScene("미션설명", "instruction.png");
	hollywood = createScene("할리우드", "hollywood.jpg");
	hanamura = createScene("하나무라", "hanamura.jpg");
	volskaya = createScene("볼스카야", "volskaya.jpg");

	startBGM = BGM("Sound/startBGM.mp3", true);
	
	title = createObject("Images/title.png", startScene, 30, 550, true);
	playButton = createObject("Images/play.png", startScene, 50, 470, true);
	ok = createObject("Images/ok.png", instruction, 1100, 20, true);
	
	timer1 = createTimer(10.0f);
	
	srand(time(NULL));
	startGame(startScene);
}