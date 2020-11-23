#include "slot.h"
#include "game.h"

Slot::Slot() {
	font.loadTGA("data/font.tga");
	bg.loadTGA("data/interface.tga");
	bellIMG.loadTGA("data/1.tga");
	watermelonIMG.loadTGA("data/2.tga");
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

	reels[0] = { ORANGE, BELL, WATERMELON, CHERRY, BLUEBERRY, LEMON, GRAPE, BLUEBERRY, BELL, BELL, ORANGE, GRAPE };
	reels[1] = { WATERMELON, CHERRY, BELL, BLUEBERRY, CHERRY, GRAPE, ORANGE, LEMON, LEMON, LEMON, CHERRY, LEMON, BLUEBERRY, LEMON, CHERRY };
	reels[2] = { GRAPE,WATERMELON,BLUEBERRY,GRAPE,BELL,LEMON,CHERRY,BELL,BELL,BELL,ORANGE,ORANGE,GRAPE };
	reels[3] = { LEMON, BLUEBERRY, BLUEBERRY, LEMON, GRAPE, ORANGE,WATERMELON,WATERMELON, BELL,CHERRY,CHERRY,LEMON,ORANGE,BLUEBERRY,LEMON };
	reels[4] = { GRAPE,CHERRY,BELL,WATERMELON,ORANGE,ORANGE,BLUEBERRY,BLUEBERRY,ORANGE,ORANGE,GRAPE,BELL,WATERMELON,CHERRY };

	reelsPos[0] = { Vector2(55, 15 - 212 * 5),Vector2(55, 15 - 212 * 4),Vector2(55, 15 - 212 * 3),Vector2(55, 15 - 212 * 2),Vector2(55, 15 - 212 * 1),Vector2(55, 15),Vector2(55, 15 + 212 * 1),Vector2(55, 15 + 212 * 2),Vector2(55, 15 + 212 * 3),Vector2(55, 15 + 212 * 4),Vector2(55, 15 + 212 * 5),Vector2(55, 15 + 212 * 6) };
	reelsPos[1] = { Vector2(294, 15 - 212 * 5),Vector2(294, 15 - 212 * 4),Vector2(294, 15 - 212 * 3),Vector2(294, 15 - 212 * 2),Vector2(294, 15 - 212 * 1),Vector2(294, 15),Vector2(294, 15 + 212 * 1),Vector2(294, 15 + 212 * 2),Vector2(294, 15 + 212 * 3),Vector2(294, 15 + 212 * 4),Vector2(294, 15 + 212 * 5),Vector2(294, 15 + 212 * 6),Vector2(294, 15 + 212 * 7),Vector2(294, 15 + 212 * 8),Vector2(294, 15 + 212 * 9) };
	reelsPos[2] = { Vector2(533, 15 - 212 * 5),Vector2(533, 15 - 212 * 4),Vector2(533, 15 - 212 * 3),Vector2(533, 15 - 212 * 2),Vector2(533, 15 - 212 * 1),Vector2(533, 15),Vector2(533, 15 + 212 * 1),Vector2(533, 15 + 212 * 2),Vector2(533, 15 + 212 * 3),Vector2(533, 15 + 212 * 4),Vector2(533, 15 + 212 * 5),Vector2(533, 15 + 212 * 6),Vector2(533, 15 + 212 * 7) };
	reelsPos[3] = { Vector2(772, 15 - 212 * 5),Vector2(772, 15 - 212 * 4),Vector2(772, 15 - 212 * 3),Vector2(772, 15 - 212 * 2),Vector2(772, 15 - 212 * 1),Vector2(772, 15),Vector2(772, 15 + 212 * 1),Vector2(772, 15 + 212 * 2),Vector2(772, 15 + 212 * 3),Vector2(772, 15 + 212 * 4),Vector2(772, 15 + 212 * 5),Vector2(772, 15 + 212 * 6),Vector2(772, 15 + 212 * 7),Vector2(772, 15 + 212 * 8),Vector2(772, 15 + 212 * 9) };
	reelsPos[4] = { Vector2(1011, 15 - 212 * 5),Vector2(1011, 15 - 212 * 4),Vector2(1011, 15 - 212 * 3),Vector2(1011, 15 - 212 * 2),Vector2(1011, 15 - 212 * 1),Vector2(1011, 15),Vector2(1011, 15 + 212 * 1),Vector2(1011, 15 + 212 * 2),Vector2(1011, 15 + 212 * 3),Vector2(1011, 15 + 212 * 4),Vector2(1011, 15 + 212 * 5),Vector2(1011, 15 + 212 * 6),Vector2(1011, 15 + 212 * 7),Vector2(1011, 15 + 212 * 8) };

}

int Slot::getYpos(int i) {
	if (i <= 5)
		return 15 - 212 * (5 - i);
	else
		return 15 + 212 * (i - 5);

}

void Slot::setDefaultPositions(std::deque<Vector2>& positions) {
	for (int i = 0; i < positions.size(); i++) {
		if (i <= 5)
			positions[i].y = 15 - 212 * (5 - i);
		else
			positions[i].y = 15 + 212 * (i - 5);
	}
}
//para cada reel renderizo cada simbolo
void Slot::renderWheels(std::deque<int> reels[], std::deque<Vector2> reelsPos[], Image* framebuffer) {

	for (int i = 0; i < REELS; i++) {
		for (int j = 0; j < reelsPos[i].size(); j++) {
			if (reels[i][j] == LEMON) {
				framebuffer->drawImage(lemonIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
			if (reels[i][j] == GRAPE) {
				framebuffer->drawImage(grapeIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
			if (reels[i][j] == ORANGE) {
				framebuffer->drawImage(orangeIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
			if (reels[i][j] == WATERMELON) {
				framebuffer->drawImage(watermelonIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
			if (reels[i][j] == CHERRY) {
				framebuffer->drawImage(cherryIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
			if (reels[i][j] == BLUEBERRY) {
				framebuffer->drawImage(blueberryIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
			if (reels[i][j] == BELL) {
				framebuffer->drawImage(bellIMG, reelsPos[i][j].x, reelsPos[i][j].y);
			}
		}
	}

}
//reordenar simbolos cuando pasan cierto limite
void Slot::checkLastSymbolPos(std::deque<Vector2>& reelPos, std::deque<int>& reelSymbol, int lastpos) {

	if (reelPos[reelPos.size() - 1].y >= getYpos(lastpos)) {
		reelSymbol.push_front(reelSymbol.back());
		reelSymbol.pop_back();
		reelPos.push_front(reelPos.back());
		reelPos[0].y = reelPos[1].y - 212;
		reelPos.pop_back();

	}
}

void Slot::checkAllSymbols() {
	checkLastSymbolPos(reelsPos[0], reels[0], LP1);
	checkLastSymbolPos(reelsPos[1], reels[1], LP2);
	checkLastSymbolPos(reelsPos[2], reels[2], LP3);
	checkLastSymbolPos(reelsPos[3], reels[3], LP4);
	checkLastSymbolPos(reelsPos[4], reels[4], LP5);
}
//renderizar boton
void Slot::renderPlayButton(Image* framebuffer) {
	if (!clicking && standby)
		framebuffer->drawImage(spinNormalIMG, 430, 700);
	else if (clicking && standby)
		framebuffer->drawImage(spinClickIMG, 430, 700);
	else if (!standby)
		framebuffer->drawImage(spinDisableIMG, 430, 700);
}
//calcular ganancias
int Slot::earnings(int symbol, int count) {
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
//cuando paran todas las reels miro los resultados
int Slot::checkResult() {
	int resultMatrix[3][5];
	int win = 0;
	memset(rw.lineCount, 0, sizeof(rw.lineCount));

	for (int i = 0; i < REELS; i++)
		for (int j = 0; j < ROWS; j++)
			resultMatrix[j][i] = reels[i][j + 5];


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
			rw.lineCount[i].y = earnings(firstValue, count);
			rw.lineCount[i].x = count;
			win += rw.lineCount[i].y;
			winner = true;
		}
	}

	return win;
}
//renderizar rectangulo cuando hay premio
void Slot::printWinningRectangle(Image* framebuffer) {
	for (int i = 0; i < ROWS; i++) {
		if (rw.lineCount[i].x != 0) {
			framebuffer->drawLine(55, getYpos(i + 5), 224 * rw.lineCount[i].x + 80, getYpos(i + 5), Color::WHITE);
			framebuffer->drawLine(55, getYpos(i + 6), 224 * rw.lineCount[i].x + 80, getYpos(i + 6), Color::WHITE);
			framebuffer->drawLine(55, getYpos(i + 5), 55, getYpos(i + 6), Color::WHITE);
			framebuffer->drawLine(224 * rw.lineCount[i].x + 80, getYpos(i + 5), 224 * rw.lineCount[i].x + 80, getYpos(i + 6), Color::WHITE);
			framebuffer->drawText(std::to_string((int)rw.lineCount[i].y), 224 * rw.lineCount[i].x + 90, getYpos(i + 5) + 50, font, 7 * 5, 9 * 5);
			framebuffer->drawText(std::to_string(rw.prize), (framebuffer->width) - 200, (framebuffer->height) - 70, font, 7 * 5, 9 * 5);
		}
	}
}
//funcion para detener las reels
void Slot::stop(float time) {

	float deltaTime = Game::instance->time - tClick;
	if (speed[0] == 0 && speed[1] == 0 && speed[2] == 0 && speed[3] == 0 && speed[4] == 0) {
		if (!standby) {
			standby = true;
			rolling = false;
			int r = checkResult();
			if (r > 0) {
				rw.prize = r;
			}
		}
		return;
	}

	if (time - deltaTime > 0) {
		speed[0] -= (speed[0] - 1 / 30 * deltaTime) * 0.01;
		speed[1] -= (speed[1] - 1 / 30 * deltaTime) * 0.007;
		speed[2] -= (speed[2] - 1 / 30 * deltaTime) * 0.005;
		speed[3] -= (speed[3] - 1 / 30 * deltaTime) * 0.004;
		speed[4] -= (speed[4] - 1 / 30 * deltaTime) * 0.003;

		for (int i = 0; i < REELS; i++) {
			if (speed[i] < 3)
				speed[i] = 3;
		}
	}
	else {

		for (int i = 0; i < REELS; i++) {
			if (abs(reelsPos[i][7].y - getYpos(7)) < 20 && (i == 0 || speed[i - 1] == 0)) {
				speed[i] = 0;
				setDefaultPositions(reelsPos[i]);
			}
		}
	}
	for (int i = 0; i < REELS; i++) {
		if (speed[i] != 0) {
			for (int j = 0; j < reelsPos[i].size(); j++) {
				reelsPos[i][j].y += speed[i];
			}
		}
	}
}
//funcion para girar las reels
void Slot::spin(float time) {
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

	for (int i = 0; i < REELS; i++) {
		for (int j = 0; j < reels[i].size(); j++) {
			reelsPos[i][j].y += speed[i];
		}
	}

	for (int i = 0; i < REELS; i++) {
		if (speed[i] >= 40)
			speed[i] = 40;
	}

}