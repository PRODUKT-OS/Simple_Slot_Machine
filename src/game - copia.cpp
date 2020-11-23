#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"
#include <deque> 
#include <cmath>

#define LEMON 0
#define GRAPE 1
#define ORANGE 2
#define WATERMELON 3
#define CHERRY 4
#define BLUEBERRY 5
#define BELL 6

#define REELS 5
#define ROWS 3

Game* Game::instance = NULL;
bool rolling = false;
bool clicking = false;
bool winner = false;
int prize = 0;
float speed[REELS] = { 0,0,0,0,0 };
float tClick = 0;
int lastposreel1 = 15 + 212 * 6;
int lastposreel2 = 15 + 212 * 9;
int lastposreel3 = 15 + 212 * 7;
int lastposreel4 = 15 + 212 * 9;
int lastposreel5 = 15 + 212 * 8;
Image font;
Image minifont;
Image bg;
Image cherryIMG, bellIMG, watermelonIMG, orangeIMG, grapeIMG, lemonIMG, blueberryIMG, spinNormalIMG, spinClickIMG, spinDisableIMG;
Color bgcolor(130, 80, 100);
std::deque<int> reel1 = { ORANGE, BELL, WATERMELON, CHERRY, BLUEBERRY, LEMON, GRAPE, BLUEBERRY, BELL, BELL, ORANGE, GRAPE };
std::deque<int> reel2 = { WATERMELON, CHERRY, BELL, BLUEBERRY, CHERRY, GRAPE, ORANGE, LEMON, LEMON, LEMON, CHERRY, LEMON, BLUEBERRY, LEMON, CHERRY };
std::deque<int> reel3 = { GRAPE,WATERMELON,BLUEBERRY,GRAPE,BELL,LEMON,CHERRY,BELL,BELL,BELL,ORANGE,ORANGE,GRAPE };
std::deque<int> reel4 = { LEMON, BLUEBERRY, BLUEBERRY, LEMON, GRAPE, ORANGE,WATERMELON,WATERMELON, BELL,CHERRY,CHERRY,LEMON,ORANGE,BLUEBERRY,LEMON };
std::deque<int> reel5 = { GRAPE,CHERRY,BELL,WATERMELON,ORANGE,ORANGE,BLUEBERRY,BLUEBERRY,ORANGE,ORANGE,GRAPE,BELL,WATERMELON,CHERRY };
std::deque<Vector2> reel1pos = { Vector2(55, 15 - 212 * 5),Vector2(55, 15 - 212 * 4),Vector2(55, 15 - 212 * 3),Vector2(55, 15 - 212 * 2),Vector2(55, 15 - 212 * 1),Vector2(55, 15),Vector2(55, 15 + 212 * 1),Vector2(55, 15 + 212 * 2),Vector2(55, 15 + 212 * 3),Vector2(55, 15 + 212 * 4),Vector2(55, 15 + 212 * 5),Vector2(55, 15 + 212 * 6) };
std::deque<Vector2> reel2pos = { Vector2(294, 15 - 212 * 5),Vector2(294, 15 - 212 * 4),Vector2(294, 15 - 212 * 3),Vector2(294, 15 - 212 * 2),Vector2(294, 15 - 212 * 1),Vector2(294, 15),Vector2(294, 15 + 212 * 1),Vector2(294, 15 + 212 * 2),Vector2(294, 15 + 212 * 3),Vector2(294, 15 + 212 * 4),Vector2(294, 15 + 212 * 5),Vector2(294, 15 + 212 * 6),Vector2(294, 15 + 212 * 7),Vector2(294, 15 + 212 * 8),Vector2(294, 15 + 212 * 9) };
std::deque<Vector2> reel3pos = { Vector2(533, 15 - 212 * 5),Vector2(533, 15 - 212 * 4),Vector2(533, 15 - 212 * 3),Vector2(533, 15 - 212 * 2),Vector2(533, 15 - 212 * 1),Vector2(533, 15),Vector2(533, 15 + 212 * 1),Vector2(533, 15 + 212 * 2),Vector2(533, 15 + 212 * 3),Vector2(533, 15 + 212 * 4),Vector2(533, 15 + 212 * 5),Vector2(533, 15 + 212 * 6),Vector2(533, 15 + 212 * 7) };
std::deque<Vector2> reel4pos = { Vector2(772, 15 - 212 * 5),Vector2(772, 15 - 212 * 4),Vector2(772, 15 - 212 * 3),Vector2(772, 15 - 212 * 2),Vector2(772, 15 - 212 * 1),Vector2(772, 15),Vector2(772, 15 + 212 * 1),Vector2(772, 15 + 212 * 2),Vector2(772, 15 + 212 * 3),Vector2(772, 15 + 212 * 4),Vector2(772, 15 + 212 * 5),Vector2(772, 15 + 212 * 6),Vector2(772, 15 + 212 * 7),Vector2(772, 15 + 212 * 8),Vector2(772, 15 + 212 * 9) };
std::deque<Vector2> reel5pos = { Vector2(1011, 15 - 212 * 5),Vector2(1011, 15 - 212 * 4),Vector2(1011, 15 - 212 * 3),Vector2(1011, 15 - 212 * 2),Vector2(1011, 15 - 212 * 1),Vector2(1011, 15),Vector2(1011, 15 + 212 * 1),Vector2(1011, 15 + 212 * 2),Vector2(1011, 15 + 212 * 3),Vector2(1011, 15 + 212 * 4),Vector2(1011, 15 + 212 * 5),Vector2(1011, 15 + 212 * 6),Vector2(1011, 15 + 212 * 7),Vector2(1011, 15 + 212 * 8) };
Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;


	font.loadTGA("data/font.tga"); //load bitmap-font image
	bg.loadTGA("data/interface.tga"); //example to load an sprite
	bellIMG.loadTGA("data/1.tga");
	watermelonIMG.loadTGA("data/1.tga");
	grapeIMG.loadTGA("data/3.tga");
	blueberryIMG.loadTGA("data/4.tga");
	orangeIMG.loadTGA("data/5.tga");
	lemonIMG.loadTGA("data/6.tga");
	cherryIMG.loadTGA("data/7.tga");
	spinNormalIMG.loadTGA("data/spin_normal.tga");
	spinNormalIMG.scale(426, 88);
	spinClickIMG.loadTGA("data/spin_click.tga");
	spinClickIMG.scale(426, 88);
	spinDisableIMG.loadTGA("data/spin_disable.tga");
	spinDisableIMG.scale(426, 88);
	//enableAudio(); //enable this line if you plan to add audio to your application
	synth.playSample("data/coin.wav", 1, true);
	synth.osc1.amplitude = 0.5;
}

void setDefaultPositions(std::deque<Vector2>& positions) {
	for (int i = 0; i < positions.size(); i++) {
		if (i <= 5)
			positions[i].y = 15 - 212 * (5 - i);
		else
			positions[i].y = 15 + 212 * (i - 5);
	}
}
void renderWheel(std::deque<int> reel, std::deque<Vector2> reelPos, Image* framebuffer) {
	for (int i = 0; i < reel.size(); i++) {
		if (reel[i] == LEMON) {
			framebuffer->drawImage(lemonIMG, reelPos[i].x, reelPos[i].y);
		}
		if (reel[i] == GRAPE) {
			framebuffer->drawImage(grapeIMG, reelPos[i].x, reelPos[i].y);
		}
		if (reel[i] == ORANGE) {
			framebuffer->drawImage(orangeIMG, reelPos[i].x, reelPos[i].y);
		}
		if (reel[i] == WATERMELON) {
			framebuffer->drawImage(watermelonIMG, reelPos[i].x, reelPos[i].y);
		}
		if (reel[i] == CHERRY) {
			framebuffer->drawImage(cherryIMG, reelPos[i].x, reelPos[i].y);
		}
		if (reel[i] == BLUEBERRY) {
			framebuffer->drawImage(blueberryIMG, reelPos[i].x, reelPos[i].y);
		}
		if (reel[i] == BELL) {
			framebuffer->drawImage(bellIMG, reelPos[i].x, reelPos[i].y);
		}
	}
}

void checkLastSymbolPos(std::deque<Vector2>& reelPos, std::deque<int>& reelSymbol, int lastpos) {
	if (reelPos[reelPos.size() - 1].y >= lastpos + 212) {
		reelSymbol.push_front(reelSymbol.back());
		reelSymbol.pop_back();
		reelPos.push_front(reelPos.back());
		reelPos[0].y = reelPos[1].y - 212;
		reelPos.pop_back();

	}
}

void renderPlayButton(Image* framebuffer) {
	if (!rolling && !clicking)
		framebuffer->drawImage(spinNormalIMG, 430, 700);
	else if (clicking && !rolling)
		framebuffer->drawImage(spinClickIMG, 430, 700);
	else if (rolling)
		framebuffer->drawImage(spinDisableIMG, 430, 700);
}
int earnings(int symbol, int count) {
	if (symbol == LEMON) {
		if (count == 2)
			return 5;
		if (count == 3)
			return 10;
		if (count == 4)
			return 20;
	}
	if (symbol == GRAPE) {
		if (count == 2)
			return 10;
		if (count == 3)
			return 20;
		if (count == 4)
			return 50;
	}
	if (symbol == ORANGE) {
		if (count == 2)
			return 10;
		if (count == 3)
			return 15;
		if (count == 4)
			return 30;
	}
	if (symbol == WATERMELON) {
		if (count == 2)
			return 20;
		if (count == 3)
			return 30;
		if (count == 4)
			return 60;
	}
	if (symbol == CHERRY) {
		if (count == 2)
			return 2;
		if (count == 3)
			return 5;
		if (count == 4)
			return 10;
	}
	if (symbol == BLUEBERRY) {
		if (count == 2)
			return 10;
		if (count == 3)
			return 20;
		if (count == 4)
			return 40;
	}
	if (symbol == BELL) {
		if (count == 2)
			return 50;
		if (count == 3)
			return 75;
		if (count == 4)
			return 100;
	}
}
int checkResult() {
	int resultMatrix[3][5];
	int win = 0;
	for (int i = 0; i < REELS; i++)
		for (int j = 0; j < ROWS; j++) {
			if (i == 0)
				resultMatrix[j][i] = reel1[j + 5];
			if (i == 1)
				resultMatrix[j][i] = reel2[j + 5];
			if (i == 2)
				resultMatrix[j][i] = reel3[j + 5];
			if (i == 3)
				resultMatrix[j][i] = reel4[j + 5];
			if (i == 4)
				resultMatrix[j][i] = reel5[j + 5];
		}

	for (int i = 0; i < ROWS; i++) {
		int firstValue = resultMatrix[i][0];
		int count = 1;
		for (int j = 1; j < REELS; j++) {
			if (resultMatrix[i][j] == firstValue)
				count++;
			else
				break;
		}
		if (count > 1) {
			win += earnings(firstValue, count);
			winner = true;
		}
	}

	return win;
}
void stop(float time) {

	float deltaTime = Game::instance->time - tClick;

	if (speed[0] == 0 && speed[1] == 0 && speed[2] == 0 && speed[3] == 0 && speed[4] == 0) {

		int r = checkResult();
		if (r > 0) {

			prize = r;
			winner = true;
		}
		rolling = false;


		return;
	}
	if (time - deltaTime > 0) {
		speed[0] -= (speed[0] - 1 / 30 * deltaTime) * 0.1;
		speed[1] -= (speed[1] - 1 / 30 * deltaTime) * 0.015;
		speed[2] -= (speed[2] - 1 / 30 * deltaTime) * 0.025;
		speed[3] -= (speed[3] - 1 / 30 * deltaTime) * 0.01;
		speed[4] -= (speed[4] - 1 / 30 * deltaTime) * 0.008;

		for (int i = 0; i < REELS; i++) {
			if (speed[i] < 3)
				speed[i] = 3;
		}
	}
	else {
		if (abs(reel1pos[7].y - (15 + 212 * 2)) < 30) {
			speed[0] = 0;
			setDefaultPositions(reel1pos);
		}
		if (abs(reel2pos[7].y - (15 + 212 * 2)) < 30 && speed[0] == 0) {
			speed[1] = 0;
			setDefaultPositions(reel2pos);
		}
		if (abs(reel3pos[7].y - (15 + 212 * 2)) < 30 && speed[1] == 0) {
			speed[2] = 0;
			setDefaultPositions(reel3pos);
		}
		if (abs(reel4pos[7].y - (15 + 212 * 2)) < 30 && speed[2] == 0) {
			speed[3] = 0;
			setDefaultPositions(reel4pos);
		}
		if (abs(reel5pos[7].y - (15 + 212 * 2)) < 30 && speed[3] == 0) {
			speed[4] = 0;
			setDefaultPositions(reel5pos);
		}
	}

	if (speed[0] != 0)
		for (int i = 0; i < reel1.size(); i++) {
			reel1pos[i].y += speed[0];
		}
	if (speed[1] != 0)
		for (int i = 0; i < reel2.size(); i++) {
			reel2pos[i].y += speed[1];
		}
	if (speed[2] != 0)
		for (int i = 0; i < reel3.size(); i++) {
			reel3pos[i].y += speed[2];
		}
	if (speed[3] != 0)
		for (int i = 0; i < reel4.size(); i++) {
			reel4pos[i].y += speed[3];
		}
	if (speed[4] != 0)
		for (int i = 0; i < reel5.size(); i++) {
			reel5pos[i].y += speed[4];
		}

}

void spin(float time) {
	float elapsed_time = Game::instance->elapsed_time;
	float deltaTime = Game::instance->time - tClick;

	if (time - deltaTime > 0) {
		speed[0] += (30 * deltaTime - speed[0]) * 0.1;
		speed[1] += (30 * deltaTime - speed[1]) * 0.05;
		speed[2] += (30 * deltaTime - speed[2]) * 0.025;
		speed[3] += (30 * deltaTime - speed[3]) * 0.01;
		speed[4] += (30 * deltaTime - speed[4]) * 0.008;
	}
	else {
		tClick = Game::instance->time;
		rolling = false;
		return;
	}


	for (int i = 0; i < reel1.size(); i++) {
		reel1pos[i].y += speed[0];
	}
	for (int i = 0; i < reel2.size(); i++) {
		reel2pos[i].y += speed[1];
	}
	for (int i = 0; i < reel3.size(); i++) {
		reel3pos[i].y += speed[2];
	}
	for (int i = 0; i < reel4.size(); i++) {
		reel4pos[i].y += speed[3];
	}
	for (int i = 0; i < reel5.size(); i++) {
		reel5pos[i].y += speed[4];
	}

	for (int i = 0; i < REELS; i++) {
		if (speed[i] >= 40)
			speed[i] = 40;
	}



}


//what to do when the image has to be draw
void Game::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image* framebuffer = new Image(1260, 800);  //do not change framebuffer size

	//add your code here to fill the framebuffer
	//...

	srand(static_cast <unsigned> (Game::instance->time));
	float r = rand() * 0.01;
	float timeSpinning = 2 + fmod(r, 3);
	//some new useful functions
	//framebuffer.fill(bgcolor);								//fills the image with one color
	//framebuffer.drawLine( 0, 0, 100,100, Color::RED );		//draws a line
	renderWheel(reel1, reel1pos, framebuffer);					//draws full image
	renderWheel(reel2, reel2pos, framebuffer);					//draws full image
	renderWheel(reel3, reel3pos, framebuffer);					//draws full image
	renderWheel(reel4, reel4pos, framebuffer);					//draws full image
	renderWheel(reel5, reel5pos, framebuffer);					//draws full image
	framebuffer->drawImage(bg, 0, 0);					//draws full image
	checkLastSymbolPos(reel1pos, reel1, lastposreel1);
	checkLastSymbolPos(reel2pos, reel2, lastposreel2);
	checkLastSymbolPos(reel3pos, reel3, lastposreel3);
	checkLastSymbolPos(reel4pos, reel4, lastposreel4);
	checkLastSymbolPos(reel5pos, reel5, lastposreel5);
	renderPlayButton(framebuffer);


	if (rolling) {
		spin(timeSpinning);
	}
	else {
		stop(timeSpinning);
	}

	if (winner) {
		framebuffer->drawText(std::to_string(prize), (framebuffer->width) - 200, (framebuffer->height) - 70, font, 7 * 5, 9 * 5);
		std::cout << "a\n";
	}
	//send image to screen
	showFramebuffer(framebuffer);
	framebuffer->~Image();
}

void Game::update(double seconds_elapsed)
{
	//Add here your update method
	//...

	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode

	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
	}

	//example of 'was pressed'
	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) //if key A was pressed
	{
		if (!rolling) {
			clicking = false;
			rolling = true;
			winner = false;
			tClick = Game::instance->time;
		}
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
	}

	//to read the gamepad state
	if (Input::gamepads[0].isButtonPressed(A_BUTTON)) //if the A button is pressed
	{
	}

	if (Input::gamepads[0].direction & PAD_UP) //left stick pointing up
	{
		bgcolor.set(0, 255, 0);
	}
}

//Keyboard event handler (sync input)
void Game::onKeyDown(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (Input::mouse_position.x > 430 && Input::mouse_position.x < 856 && Input::mouse_position.y > 700 && Input::mouse_position.y < 788)
		if (event.button == SDL_BUTTON_LEFT)
			clicking = true;

}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (Input::mouse_position.x > 430 && Input::mouse_position.x < 856 && Input::mouse_position.y > 700 && Input::mouse_position.y < 788)
		if (event.button == SDL_BUTTON_LEFT && !rolling) {
			clicking = false;
			rolling = true;
			winner = false;
			tClick = Game::instance->time;
		}
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
	std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static GLuint texture_id = -1;
	static GLuint shader_id = -1;
	if (!texture_id)
		glGenTextures(1, &texture_id);

	//upload as texture
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glDisable(GL_CULL_FACE); glDisable(GL_DEPTH_TEST); glEnable(GL_TEXTURE_2D);
	float startx = -1.0; float starty = -1.0;
	float width = 2.0; float height = 2.0;

	//center in window
	float real_aspect = window_width / (float)window_height;
	float desired_aspect = img->width / (float)img->height;
	float diff = desired_aspect / real_aspect;
	width *= diff;
	startx = -diff;

	//compute area in pixels
	framebuffer_rect.set(floor((startx * 0.5 + 0.5) * window_width), floor((starty * 0.5 + 0.5) * window_height), floor(width * 0.5 * window_width), floor(height * 0.5 * window_height));

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(startx, starty + height);
	glTexCoord2f(1.0, 0.0); glVertex2f(startx + width, starty + height);
	glTexCoord2f(1.0, 1.0); glVertex2f(startx + width, starty);
	glTexCoord2f(0.0, 1.0); glVertex2f(startx, starty);
	glEnd();

}

