#include "myLib.h"
#include "titleScreen.h"
#include "gameover.h"
#include "youwin.h"
#include "game.h"

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	//Draw Start Screen
	drawImage3(0, 0, TITLESCREEN_WIDTH, TITLESCREEN_HEIGHT, titleScreen);

	//var to keep track of current position in game
	int inGame = 0;
	int inTitle = 1;

	while(1)
	{

		//START GAME
		if(inTitle == 1 && KEY_DOWN_NOW(BUTTON_START)) {
			inGame = 1;
			inTitle = 0;
			int bgcolor = GRAY;
			DMA[3].src = &bgcolor;
			DMA[3].dst = videoBuffer;
			DMA[3].cnt = 38400 | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;

			drawLevel1Board();
			refillLives();
			resetBoard();
		}

		//JUMP BACK TO TITLE SCREEN
		if(KEY_DOWN_NOW(BUTTON_SELECT)) {
			inGame = 0;
			inTitle = 1;
			drawImage3(0, 0, TITLESCREEN_WIDTH, TITLESCREEN_HEIGHT, titleScreen);
		}

		//GAME PLAY
		if(inGame == 1) {
			if(KEY_DOWN_NOW(BUTTON_RIGHT)) {
				moveRight();
			} else if(KEY_DOWN_NOW(BUTTON_LEFT)) {
				moveLeft();
			} else if(KEY_DOWN_NOW(BUTTON_UP)) {
				moveUp();
			} else if(KEY_DOWN_NOW(BUTTON_DOWN)) {
				moveDown();
			}

			waitForVblank();
			clearOld();
			drawCurr();

			//test if reach end of level
			if(isWin() == 1) {
				drawImage3(0, 0, YOUWIN_WIDTH, YOUWIN_HEIGHT, youwin);
				inGame = 0;
				inTitle = 0;
			}

			//test for Collisions with Enemies
			if(isCollide() > 0) {
				if(currLives() > 0) {
					resetBoard();
				} else {
					//out of lives = game over
					inGame = 0;
					inTitle = 0;
					drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
				}
			}

		}
	}
	return 0;

}