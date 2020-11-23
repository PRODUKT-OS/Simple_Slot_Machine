#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"
#include <deque> 
#include <cmath>

Game* Game::instance = NULL;
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

	mySlot = new Slot();

}



void Game::render(void)
{

	Image* framebuffer = new Image(1260, 800);

	srand(static_cast <unsigned> (Game::instance->time));
	float r = rand() * 0.01;
	float timeSpinning = 2 + fmod(r, 3);

	//renderizar reels
	mySlot->renderWheels(mySlot->reels, mySlot->reelsPos, framebuffer);
	//renderizar background
	framebuffer->drawImage(mySlot->bg, 0, 0);
	//renderizar boton
	mySlot->renderPlayButton(framebuffer);
	//reordenar vectores
	mySlot->checkAllSymbols();


	//en caso de girar
	if (mySlot->rolling) {
		mySlot->spin(timeSpinning);
	}
	else {
		//en caso de frenar
		mySlot->stop(timeSpinning);
	}
	//si hay ganancias
	if (mySlot->winner) {

		mySlot->printWinningRectangle(framebuffer);
	}
	//send image to screen
	showFramebuffer(framebuffer);
	framebuffer->~Image();
}

void Game::update(double seconds_elapsed)
{

	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE))
	{
		if (mySlot->standby) {
			mySlot->clicking = false;
			mySlot->rolling = true;
			mySlot->standby = false;
			mySlot->winner = false;
			mySlot->tClick = Game::instance->time;
		}
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
			mySlot->clicking = true;

}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (Input::mouse_position.x > 430 && Input::mouse_position.x < 856 && Input::mouse_position.y > 700 && Input::mouse_position.y < 788)
		if (event.button == SDL_BUTTON_LEFT && mySlot->standby) {
			mySlot->clicking = false;
			mySlot->rolling = true;
			mySlot->winner = false;
			mySlot->standby = false;
			mySlot->tClick = Game::instance->time;
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

