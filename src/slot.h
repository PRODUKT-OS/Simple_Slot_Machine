#ifndef SLOT //macros to ensure the code is included once
#define SLOT


#include <deque> 
#include <cmath>
#include "utils.h"
#include "image.h"

#define LEMON 0
#define GRAPE 1
#define ORANGE 2
#define WATERMELON 3
#define CHERRY 4
#define BLUEBERRY 5
#define BELL 6

#define REELS 5
#define ROWS 3

#define LP1 12
#define LP2 15
#define LP3 13
#define LP4 15
#define LP5 14

struct Reward {
	int prize = 0;
	Vector2 lineCount[ROWS];
};

class Slot
{
public:
	std::deque<int> reels[REELS];
	std::deque<Vector2> reelsPos[REELS];
	float speed[REELS] = { 0,0,0,0,0 };
	bool rolling = false;
	bool standby = false;
	bool clicking = false;
	bool winner = false;
	Reward rw;
	//int prize = 0;
	float tClick = 0;
	Image font, bg, cherryIMG, bellIMG, watermelonIMG, orangeIMG, grapeIMG, lemonIMG, blueberryIMG, spinNormalIMG, spinClickIMG, spinDisableIMG;


	//Animation* anim;
	Slot();
	int Slot::getYpos(int i);
	void Slot::setDefaultPositions(std::deque<Vector2>& positions);
	void Slot::renderWheels(std::deque<int> reels[], std::deque<Vector2> reelsPos[], Image* framebuffer);
	void Slot::checkLastSymbolPos(std::deque<Vector2>& reelPos, std::deque<int>& reelSymbol, int lastpos);
	void Slot::checkAllSymbols();
	void Slot::renderPlayButton(Image* framebuffer);
	int Slot::earnings(int symbol, int count);
	void Slot::printWinningRectangle(Image* framebuffer);
	int Slot::checkResult();
	void Slot::stop(float time);
	void Slot::spin(float time);
};

#endif