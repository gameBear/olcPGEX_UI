/*

olcPGEX_UI Demo - NotPong!

	+ ------------------------------------------------------------+
	|					Demo of olcPGEX_UI v 1.2				  |
	|		   "This is not pong at all" - ZleapingBear			  |
	+-------------------------------------------------------------+

What is this ?
~~~~~~~~~~~~~
Simple demo of the UI exte4nsione fore the oneLoneCoder - Pixel game engine

All code within is preovided for free, and may be used as seen fit as long as it follows the guideline laied out
in hte licence note in both olcPGEX.h and olcPixelGameEngine.h

The art is free and can be used as seen fit without limitations.

Documentation will be added over time. in the mean time you can find me here:



*/


#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "olcPGEX_UI.h"
#include <random>

#define m_PI 3.14159265358979323846

static int screenW = 900, screenH = 600;
//some field information
int lineWidth = 5, innerLines = 3, ballR = 6, playerPoints = 0, aiPoints = 0, playTimeMIN = 3, AplayTimeMIN = 3, aiPrecision = 40;
point_2d playerPos, AiPos, boarSize;
float playerSpeed, AiSpeed, playTimeSEC = 0, AplayTimeSEC = 0;


int getBetween(int min, int max) {
	static std::mt19937 generator(time(NULL));
	std::uniform_int_distribution<int> dis(min, max);
	return dis(generator);
}

// some Enums and structs we will be using
enum artStyle {
	pge_style, paint_style
};
struct score {
	score(int nP, int nAP, std::string pName) : pPoint(nP), aPoint(nAP), playerName(pName) {
		value = (float)pPoint - (float)aPoint;
	};
	score(std::string input) {
		int data = 0;
		std::string newField = "";
		for (int i = 0; i < input.size(); i++) {
			
			if (input[i] != ':') newField += input[i];
			else {
				if (data == 0) {
					pPoint = std::stoi(newField);
					newField = "";
					data = 1;
				}
				else if (data == 1) {
					aPoint = std::stoi(newField);
					newField = "";
					data = 2;
				}
				else if (data == 2) {
					value = std::stof(newField);
					newField = "";
					data = 3;
				}
				else if (data == 3) {
					playerName = newField;
					newField = "";
					data = 4;
				}
			}
		}
	};

	int pPoint, aPoint;
	float value;
	std::string playerName;

	int comapre(int pP, int aP) {
		float f_score = pP - aP;
		if (f_score >= value) return 1;
		else if (value > f_score) return -1;
		return 0;
	}

	std::string getString() {
		std::string output = "";
		output += std::to_string(pPoint) + ":" + std::to_string(aPoint) + ":" + std::to_string(value) + ":" + playerName + ":";
		return output;
	}
	std::string getScoreOut(int place) {
		std::string output = "";
		if (place == 1) output += "1st:  ";
		else if (place == 2) output += "2nd:  ";
		else if (place == 3) output += "3rd:  ";
		else if (place < 10) output += std::to_string(place) + "th:  ";
		else output += "10th: ";
		for (int i = 0; i < 12; i++) {
			if (i < playerName.size()) output += playerName[i];
			else output += "_";
		}
		output += " : " + std::to_string(pPoint) + " vs AI: " + std::to_string(aPoint);
		return output;
	}
};

struct pongBall {
	pongBall() : coords(screenW*0.5, screenH*0.6), frozen(true), countDown(4), baseCountDown(4), ballSpeed(500), direction(getBetween(-31416, 31416)*0.0001) {};
	point_2d coords;
	bool frozen, stall = false;
	float countDown, xspeed, yspeed, ballSpeed, direction, baseCountDown, stallBall = 0;
	point_2d getCoords() { return coords; }
	int getCountDown() {
		if (frozen) return (int)countDown;
		else return 0;
	}
	int update(float fElapsedTime) {
		if (frozen) {
			countDown -= fElapsedTime;
			if (countDown <= 0) {
				frozen = false;
				stall = false;
			}
		}
		else {
			stallBall += fElapsedTime;
			if (stallBall > 10) {
				reset(0);
				stall = true;
			}
			coords.x += xspeed * fElapsedTime;
			coords.y += yspeed * fElapsedTime;
			if (coords.x > screenW - (ballR + lineWidth) && xspeed > 0) {
				xspeed = xspeed * -1;
				return -1;
			}
			else if (coords.x < 0 + (ballR + lineWidth) && xspeed < 0) {
				xspeed = xspeed * -1;
				return 1;
			}
			else if (xspeed > 0) {
				if (isPointInRect(point_2d(coords.x + 7, coords.y), UI_rect(AiPos, boarSize.x, boarSize.y))) {
					float dif = (coords.y - (AiPos.y + boarSize.y * 0.5)) * 0.008;
					//direction = -direction;
					direction += dif;
					xspeed = cos(direction) * ballSpeed;
					yspeed = sin(direction) * ballSpeed;
					stallBall = 0;
					while (isPointInRect(point_2d(coords.x + 7, coords.y), UI_rect(AiPos, boarSize.x, boarSize.y))) coords.x -= 0.2;
				}
			}
			else if (xspeed < 0) {
				if (isPointInRect(point_2d(coords.x - 7, coords.y), UI_rect(playerPos, boarSize.x, boarSize.y))) {
					float dif = (coords.y- (playerPos.y + boarSize.y * 0.5)) * 0.008;
					direction += dif;
					direction = -direction;
					xspeed = cos(direction) * ballSpeed * -1;
					yspeed = sin(direction) * ballSpeed;
					stallBall = 0;
					while (isPointInRect(point_2d(coords.x - 7, coords.y), UI_rect(playerPos, boarSize.x, boarSize.y))) coords.x += 0.2;
				}
			}

			if (coords.y > screenH*0.9 - (ballR + lineWidth) && yspeed > 0) yspeed = yspeed * -1;
			else if (coords.y < screenH*0.1 + (ballR + lineWidth) && yspeed < 0) yspeed = yspeed * -1;
		}
		return 0;
	}
	void reset(int dir) {
		if (dir == -1)coords.x = screenW * 0.3;
		else if (dir == 1)coords.x = screenW * 0.7;
		else coords.x = screenW * 0.5;
		coords.y = screenH * 0.5;
		stallBall = 0;
		frozen = true;
		countDown = baseCountDown;
		direction = (((getBetween(0, m_PI*2500)) * 0.0001f) + (m_PI * 0.875));
		if(dir != 0) xspeed = cos(direction) * ballSpeed * dir;
		else if(getBetween(0,1)) xspeed = cos(direction) * ballSpeed;
		else xspeed = cos(direction) * ballSpeed * -1;
		yspeed = sin(direction) * ballSpeed;
	}
};

//Some forward declarations and NON drawing functions and of all global variables
pgrSTAGE currentStage = RUN_INTRO;
olc::UI_STAGE_CONTROLL myUI;
pongBall g_ball;
pongBall mouse_ball;
std::vector<score> highScores;
std::string playerNameString;

bool gameUPDATE(float fElapsedTime, bool reset, point_2d mouseCoords);
void optionsUPDATE(float fElapsedTime, pongBall &ball);
void loadHighScore(std::vector<score> &toLoadInto, std::string &playerN);
void saveHighScore(std::vector<score> &toSave, std::string &playerN);
void reviewScore(std::vector<score> &oldScores, int pP, int aP, std::string playerN);
artStyle art = paint_style;
bool animation = true, overTime = false;

olc::Sprite PaintBTN; 
olc::Sprite PaintMAIN;
olc::Sprite PaintGAME;
olc::Sprite PaintHIGH;
olc::Sprite PaintOPT;
olc::Sprite PaintPAUSE;

// running everything.
class pongGame : public olc::PixelGameEngine
{
public:
	pongGame()
	{
		SetPixelMode(olc::Pixel::NORMAL);
		g_ball.reset(0);
		sAppName = "UI Sample";
		ShowCursor(false);
	}

private:

	// All drwaing functions should be created here.
	void drawBall(pongBall ball, float fElapsedTime) {
		if (art == pge_style) {
			DrawCircle(ball.getCoords().x, ball.getCoords().y, ballR + 1, olc::BLACK);
			FillCircle(ball.getCoords().x, ball.getCoords().y, ballR, olc::WHITE);
		}
		else if (art == paint_style) {
			SetPixelMode(olc::Pixel::ALPHA);
			if (animation) {
				static float imageFrame = 0;
				if ((ball.xspeed < 0)) {
					imageFrame += fElapsedTime * 16;
					if ((int)imageFrame >= 7) imageFrame = 0.01;
				}
				else {
					imageFrame -= fElapsedTime * 16;
					if ((int)imageFrame <= 0) imageFrame = 7.99;
				}
				DrawPartialSprite(ball.getCoords().x - 7, ball.getCoords().y - 7, &PaintBTN, 0 + (15 * (int)imageFrame), 83, 15, 15);
			}
			else DrawPartialSprite(ball.getCoords().x-7, ball.getCoords().y-7, &PaintBTN, 0, 83, 15, 15);
			SetPixelMode(olc::Pixel::NORMAL);
		}
		else {
			DrawString(ball.getCoords().x, ball.getCoords().y, "ERROR", olc::RED, 2U);
		}
		if (ball.frozen) {
			DrawString(ball.getCoords().x, ball.getCoords().y - 64, std::to_string(ball.getCountDown()), olc::RED, 2U);
			if(ball.stall) DrawString(ball.getCoords().x, ball.getCoords().y - 80, "STALL BALL", olc::RED, 2U);
		}
	}

	void drawPlayField(pongBall ball, float fElapsedTime) {
		if (art == pge_style) {
			FillRect(screenW * 0.1, screenH * 0.1, screenW*0.8, lineWidth, olc::DARK_YELLOW);
			FillRect(screenW * 0.1, screenH * 0.9 - lineWidth, screenW*0.8, lineWidth, olc::DARK_YELLOW);
			FillRect(screenW * 0.1, screenH * 0.1, lineWidth, screenH * 0.8, olc::DARK_YELLOW);
			FillRect(screenW * 0.9 - lineWidth, screenH * 0.1, lineWidth, screenH * 0.8, olc::DARK_YELLOW);

			FillRect(screenW * 0.5 - (innerLines * 0.5), screenH * 0.1, innerLines, screenH * 0.8, olc::WHITE);

			FillRect(screenW * 0.25 - innerLines, screenH * 0.25, innerLines, screenH * 0.5, olc::WHITE);
			FillRect(screenW * 0.75, screenH * 0.25, innerLines, screenH * 0.5, olc::WHITE);

			FillRect(screenW * 0.1, screenH * 0.25 - innerLines, screenW * 0.8, innerLines, olc::WHITE);
			FillRect(screenW * 0.25, screenH * 0.5 - (innerLines * 0.5), screenW * 0.5, innerLines, olc::WHITE);
			FillRect(screenW * 0.1, screenH * 0.75, screenW * 0.8, innerLines, olc::WHITE);

			FillRect(playerPos.x, playerPos.y, boarSize.x, boarSize.y, olc::BLUE);
			FillRect(AiPos.x, AiPos.y, boarSize.x, boarSize.y, olc::RED);

		}
		else if (art == paint_style) {
			SetPixelMode(olc::Pixel::ALPHA);
			DrawSprite(0, 0, &PaintGAME);
			if (myUI.hasCommand("PAUSE_PROGRAM", true)) DrawPartialSprite(0, 0, &PaintBTN, 0, 52, 900, 31);
			if (animation) {
				static float boardFrame = 0;
				boardFrame += fElapsedTime * (3 + getBetween(1, 4));
				if ((int)boardFrame >= 6) boardFrame = 0.01;
				static float AIboardFrame = 0;
				AIboardFrame += fElapsedTime * (3 + getBetween(1, 4));
				if ((int)AIboardFrame >= 6) AIboardFrame = 0.01;

				DrawPartialSprite(playerPos.x, playerPos.y, &PaintBTN, boarSize.x * (int)boardFrame, 98, boarSize.x, boarSize.y);
				DrawPartialSprite(AiPos.x, AiPos.y, &PaintBTN, boarSize.x * (int)AIboardFrame, 198, boarSize.x, boarSize.y);
			}
			else {
				DrawPartialSprite(playerPos.x, playerPos.y, &PaintBTN, 0, 98, boarSize.x, boarSize.y);
				DrawPartialSprite(AiPos.x, AiPos.y, &PaintBTN, 0, 198, boarSize.x, boarSize.y);
			}
			SetPixelMode(olc::Pixel::NORMAL);

		}
		else {
			DrawString(screenW*0.3, screenH * 0.5, "ERROR ART", olc::RED, 6U);
		}
		DrawString(screenW * 0.08, screenH * 0.925, std::to_string(playerPoints), olc::WHITE, 3U);
		DrawString(screenW * 0.9, screenH * 0.925, std::to_string(aiPoints), olc::WHITE, 3U);
		if(playTimeMIN >= 0) DrawString(screenW * 0.48, screenH * 0.925, std::to_string((int)(playTimeMIN)) + ":" + std::to_string((int)(playTimeSEC)), olc::WHITE, 2U);
		else DrawString(screenW * 0.48, screenH * 0.925, "-" + std::to_string((int)(0 - (playTimeMIN+1))) + ":" + std::to_string((int)(60 - playTimeSEC)), olc::WHITE, 2U);
	}

	void drawINTRO(float fElapsedTime) {
		static float position = screenH;
		position -= fElapsedTime * screenH * 0.1;
		DrawString(screenW * 0.05, position, "Hello out there\nThis is defenetly NOT pong\nBut it is a demonstration of \nboth the olcPGE and the PGEX_UI\n\n\nReally? Why are you reading this?\n\n\n\n\n\n\n\n\n\n\n\nOh... yea...\n\n\n\nPress Space to skip!", olc::WHITE, 3U);
	}
	void drawMAIN() {
		if (art == pge_style) {
			
		}
		else if (art == paint_style) {
			DrawSprite(0, 0, &PaintMAIN);
			SetPixelMode(olc::Pixel::ALPHA);
			
			if (myUI.hasCommand("RUN_PROGRAM", true)) DrawPartialSprite(0, 240, &PaintBTN, 0, 323, 900, 81);
			if (myUI.hasCommand("HIGHSCORE", true)) DrawPartialSprite(112, 360, &PaintBTN, 224, 243, 676, 40);
			if (myUI.hasCommand("PGR_OPTIONS", true)) DrawPartialSprite(112, 420, &PaintBTN, 224, 203, 676, 40);
			if (myUI.hasCommand("CREDITS", true)) DrawPartialSprite(112, 480, &PaintBTN, 224, 283, 676, 40);
			SetPixelMode(olc::Pixel::NORMAL);
		}
		else {
		}
		if(playerNameString != "XXXXXX") DrawString(250, screenH * 0.150, "Welcome " + playerNameString, olc::BLACK, 3U);
		else DrawString(250, screenH * 0.150, "Welcome, to NotPong!", olc::BLACK, 3U);
	}

	void drawOPTIONS(pongBall ball, float fElapsedTime) {


		if (art == pge_style) {
			drawPlayField(ball, fElapsedTime);
			drawBall(g_ball, fElapsedTime);
			SetPixelMode(olc::Pixel::ALPHA);
			FillRect(0, 0, screenW, screenH, olc::Pixel(80, 80, 80, 200));
			SetPixelMode(olc::Pixel::NORMAL);
		}
		else if (art == paint_style) {
			DrawSprite(0, 0, &PaintOPT);
			SetPixelMode(olc::Pixel::ALPHA);
			if (myUI.hasCommand("MAIN_MENU", true)) DrawPartialSprite(0, 0, &PaintBTN, 0, 0, 900, 52);
			DrawPartialSprite(myUI.getX(10), myUI.getY(10), &PaintBTN, 144, 83, 34, 21);
			DrawPartialSprite(myUI.getX(11), myUI.getY(11), &PaintBTN, 144, 104, 21, 34);
			DrawPartialSprite(myUI.getX(12), myUI.getY(12), &PaintBTN, 144, 104, 21, 34);
			DrawPartialSprite(myUI.getX(13), myUI.getY(13), &PaintBTN, 144, 104, 21, 34);
			DrawPartialSprite(myUI.getX(14), myUI.getY(14), &PaintBTN, 144, 104, 21, 34);
			DrawPartialSprite(myUI.getX(15), myUI.getY(15), &PaintBTN, 144, 104, 21, 34);
			SetPixelMode(olc::Pixel::NORMAL);
		}
		else {

		}


		DrawString(25, screenH * 0.92, "BALL SPEED: \n" + std::to_string((int)(ball.ballSpeed * 0.1)) + "%", olc::BLACK, 2U);
		DrawString(125, screenH * 0.125, "COUNT DOWN TIME: \n" + std::to_string((int)(ball.baseCountDown - 1)) + " SEC", olc::BLACK, 2U);
		if (art == pge_style) DrawString(125, screenH * 0.225, "ART STYLE: \nolcPGE", olc::BLACK, 2U);
		else if (art == paint_style) DrawString(125, screenH * 0.225, "ART STYLE: \nPaint", olc::BLACK, 2U);
		else DrawString(125, screenH * 0.225, "ART STYLE: \n ERROR!", olc::BLACK, 2U);
		if (animation)	DrawString(125, screenH * 0.325, "ANIMATION: ON", olc::BLACK, 2U);
		else DrawString(125, screenH * 0.325, "ANIMATION: OFF", olc::BLACK, 2U);
		DrawString(125, screenH * 0.425, "PLAYTIME: \n" + std::to_string((int)(AplayTimeMIN)) + ":" + std::to_string((int)(AplayTimeSEC)), olc::BLACK, 2U);
		DrawString(125, screenH * 0.525, "OPPONENT PRECISION: \n" + std::to_string((int)(aiPrecision)) + "%", olc::BLACK, 2U);
		DrawString(125, screenH * 0.625, "PLAYER NAME:", olc::BLACK, 2U);
		DrawString(324, screenH * 0.625, playerNameString, olc::WHITE, 2U);

	}


	void drawPAUSE() {
		if (art == pge_style) {
		
		}
		else if (art == paint_style) {
			DrawSprite(0, 0, &PaintPAUSE);
			DrawString(324, screenH * 150, playerNameString, olc::BLACK, 2U);
			SetPixelMode(olc::Pixel::ALPHA);
			if (myUI.hasCommand("RUN_PROGRAM", true)) DrawPartialSprite(113, 301, &PaintBTN, 224, 83, 676, 40);
			if (myUI.hasCommand("MAIN_MENU", true)) DrawPartialSprite(113, 361, &PaintBTN, 224, 123, 676, 40);
			if (myUI.hasCommand("CREDITS", true)) DrawPartialSprite(113, 421, &PaintBTN, 224, 163, 676, 40);
			SetPixelMode(olc::Pixel::NORMAL);
		}
		else {

		}
	}

	void drawHIGH() {
		if (art == pge_style) {
			
		}
		else if (art == paint_style) {
			DrawSprite(0, 0, &PaintHIGH);
			if (myUI.hasCommand("MAIN_MENU", true)) DrawPartialSprite(0, 0, &PaintBTN, 0, 0, 900, 52);
		}
		else {

		}
		if (playerPoints > aiPoints) DrawString(125, screenH * 0.125, "CONGRATULATIONS " + playerNameString + "\nYOU WON!\n" + std::to_string((int)(playerPoints)) + " vs " + std::to_string((int)(aiPoints)), olc::WHITE, 2U);
		else if (playerPoints < aiPoints) DrawString(125, screenH * 0.125, "WHAT THAT!\nTHE PC WON!\n" + std::to_string((int)(playerPoints)) + " vs " + std::to_string((int)(aiPoints)), olc::WHITE, 2U);
		for (int i = 0; i < 10; i++)  DrawString(125, screenH * 0.25 + (screenH * 0.05 * i), highScores[i].getScoreOut(i+1), olc::BLACK, 2U);

	}

	bool drawCREDIDT(float fElapsedTime) {
		static float position = screenH;
		position -= fElapsedTime * screenH * 0.1;
		DrawString(screenW * 0.05, position, "Thanks for playing\nSpecial thanks to OneLoneCode\nDavid Barr Aka Javidx9 for all his awesome videos\nand encurregment\n\nAnt to all of OneLoneCoder comunity\nOn Discord, Youtube, Github and Twitter\n\n\nThanks for playing\n\nBest Regards from Michlas Aka: ZleapingBear\n\n\n\n\n\n\n\nOh... And space to exit.. \nagain!", olc::WHITE, 2U);
		if (position < -screenH) return false;
		return true;
	}

public:
	bool OnUserCreate() override
	{
		playerNameString = "";
		loadHighScore(highScores, playerNameString);

		mouse_ball.frozen = false;
		
		PaintBTN.LoadFromFile("Art/BottonsPAINT.png"); 
		PaintMAIN.LoadFromFile("Art/mainPAINT.png"); 
		PaintGAME.LoadFromFile("Art/gamePAINT.png");
		PaintHIGH.LoadFromFile("Art/highscorePAINT.png");
		PaintOPT.LoadFromFile("Art/OptionsPAINT.png");
		PaintPAUSE.LoadFromFile("Art/pausePAINT.png");


		std::vector<pgrSTAGE> allStages;
		allStages.push_back(RUN_INTRO);
		allStages.push_back(MAIN_MENU);
		allStages.push_back(RUN_PROGRAM);
		allStages.push_back(PAUSE_PROGRAM);
		allStages.push_back(PGR_OPTIONS);
		allStages.push_back(HIGHSCORE);
		allStages.push_back(CREDITS);

		myUI.setUp(screenW, screenH, allStages);
		if (myUI.addToStage(RUN_INTRO)) {
			myUI.addNewBotton(UI_GREY, olc::Key::SPACE, true, "MAIN_MENU", 0, screenH*0.9, screenW, screenH*0.1, "PRESS SPACE TO SKIP");
		}

		if (myUI.addToStage(MAIN_MENU)) {
			myUI.addNewBotton(UI_RED, olc::Key::SPACE, true, "RUN_PROGRAM", 0, screenH*0.4, screenW, 80, "PRESS \"SPACE\" TO PLAY");
			myUI.addNewBotton(UI_BLUE, olc::Key::F, false, "HIGHSCORE", screenW*0.125, screenH*0.6, screenW*0.75, 40, "HIGHSCORE");
			myUI.addNewBotton(UI_BLUE, olc::Key::F, false, "PGR_OPTIONS", screenW*0.125, screenH*0.7, screenW*0.75, 40, "SETTINGS");
			myUI.addNewBotton(UI_BLUE, olc::Key::F, false, "CREDITS", screenW*0.125, screenH*0.8, screenW*0.75, 40, "EXIT GAME");
		}


		if (myUI.addToStage(RUN_PROGRAM)) {
			myUI.addNewBotton(UI_RED, olc::Key::P, true, "PAUSE_PROGRAM", 0, 0, screenW, screenH*0.05, "PRESS \"P\" TO PAUSE");
		}
		if (myUI.addToStage(PAUSE_PROGRAM)) {
			myUI.addNewBotton(UI_RED, olc::Key::SPACE, true, "RUN_PROGRAM", screenW*0.125, screenH*0.5, screenW*0.75, 40, "PRESS \"SPACE\" TO RESUME PLAY");
			myUI.addNewBotton("MAIN_MENU", screenW*0.125, screenH*0.6, screenW*0.75, 40, "MAIN MENU");
			myUI.addNewBotton("CREDITS", screenW*0.125, screenH*0.7, screenW*0.75, 40, "EXIT GAME");
		}

		if (myUI.addToStage(PGR_OPTIONS)) {
			myUI.addNewBotton("MAIN_MENU", 0, 0, screenW, 50, "MAIN MENU");
			myUI.addSlider(50, screenH * 0.1, screenH * 0.8, BottomTop);
			myUI.addSlider(250, screenH * 0.18, screenW * 0.15, LeftRight, SteppingSlider, std::vector<int> {1, 2, 3, 4, 5});
			myUI.addSlider(250, screenH * 0.28, screenW * 0.15, LeftRight, SteppingSlider, std::vector<int> {0, 1});
			myUI.addSlider(250, screenH * 0.38, screenW * 0.15, LeftRight, SteppingSlider, std::vector<int> {0, 1});
			myUI.addSlider(250, screenH * 0.48, screenW * 0.15, LeftRight, SteppingSlider, std::vector<int> {30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360, 390, 420, 450, 480});
			myUI.addSlider(250, screenH * 0.58, screenW * 0.15, LeftRight, SteppingSlider, std::vector<int> {40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100});
			myUI.addTextField(312, screenH * 0.61, 16);
			myUI.setValue(10, 50);
			myUI.setValue(11, 2);
			myUI.setValue(12, 1);
			myUI.setValue(13, 1);
			myUI.setValue(14, 5);
			myUI.setValue(15, 4);
			myUI.setH(16, 32);
			myUI.setW(16, 300);

			//myUI.ToggleDEBUGMODE();
		}

		if (myUI.addToStage(HIGHSCORE)) {
			myUI.addNewBotton("MAIN_MENU", 0, 0, screenW, 50, "MAIN MENU");

		}
		if (myUI.addToStage(CREDITS)) {

			myUI.addNewBotton(UI_RED, olc::Key::SPACE, true, "EXIT", screenW*0.125, screenH*5, screenW*0.75, 40, "PRESS \"SPACE\" TO EXIT");
		}
		playerPos.x = 60;
		AiPos.x = 816;
		playerPos.y = screenH * 0.5 - 50;
		AiPos.y = screenH * 0.5 - 50;
		boarSize.x = 24;
		boarSize.y = 100;
		playerSpeed = 0;
		AiSpeed = 0;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		bool stageChange = false;
		// this handles the uopdate of all items, it needs our current stage so it cvan update it.
		static pgrSTAGE lastStage = currentStage;
		myUI.Update(fElapsedTime, currentStage);
		point_2d mouse((int)GetMouseX(), (int)GetMouseY());
		mouse_ball.coords.x = mouse.x;
		mouse_ball.coords.y = mouse.y;
		//say you want to use teh stage to do stuff like letting a ball pass the screen in some odd way.
		// Short program irellevant for the setup, but demonstration of the UI_STAGE_CONTROLL handeling all things
		// we will just let a ball bounce on the screen without a care in the world.

		switch (currentStage)
		{
		case RUN_INTRO:
			// CLEAR THE SCREEN
			Clear(olc::DARK_GREY);
			drawINTRO(fElapsedTime);
			drawBall(mouse_ball, fElapsedTime);
			break;

		case MAIN_MENU:
			// CLEAR THE SCREEN
			if (lastStage != MAIN_MENU) {
				if(getBetween(0,1) == 0) g_ball.reset(-1);
				else g_ball.reset(1);
				playerPos.y = screenH * 0.5 - 50;
				AiPos.y = screenH * 0.5 - 50;
				playerSpeed = 0;
				AiSpeed = 0;
				playerPoints = 0;
				aiPoints = 0;
			}
			g_ball.update(fElapsedTime),
			Clear(olc::DARK_GREY);
			drawMAIN();
			drawBall(mouse_ball, fElapsedTime);
			break;

		case RUN_PROGRAM:
			
			if(lastStage == MAIN_MENU) gameUPDATE(fElapsedTime, true, mouse);

			if(gameUPDATE(fElapsedTime, false, mouse));
			else {
				currentStage = HIGHSCORE;
				stageChange = true;
			}

			// CLEAR THE SCREEN
			Clear(olc::VERY_DARK_YELLOW);
			drawPlayField(g_ball, fElapsedTime);
			drawBall(g_ball, fElapsedTime);
			break;

		case PAUSE_PROGRAM:
			// CLEAR THE SCREEN
			Clear(olc::DARK_GREY);
			drawPlayField(g_ball, 0);
			drawPAUSE();

			break;

		case PGR_OPTIONS:
			optionsUPDATE(fElapsedTime, g_ball);
			
			// CLEAR THE SCREEN
			Clear(olc::DARK_GREY);
			
			drawOPTIONS(g_ball, fElapsedTime);

			break;

		case HIGHSCORE:
			// CLEAR THE SCREEN
			if (lastStage == RUN_PROGRAM) reviewScore(highScores, playerPoints, aiPoints, playerNameString);
			Clear(olc::DARK_GREY);
			drawHIGH();
			break;

		case CREDITS:
			// CLEAR THE SCREEN
			
			if (lastStage != CREDITS) saveHighScore(highScores, playerNameString);
			Clear(olc::DARK_GREY);
			if(!drawCREDIDT(fElapsedTime)) return 0;
			if(myUI.hasCommand("EXIT", true)) return 0;
			break;

		default:
			DrawString(50, screenH * 0.5, "ERROR: STAGE NOT FOUND, \nDEFAULT STAGE ACTIVATED", olc::RED, 2U);
			break;
		}


		if(!stageChange) lastStage = currentStage;
		else stageChange = false;


		// This draws all items in the UI

		if (art == paint_style) {
			myUI.SetHideAll(true);
		}
		else {
			myUI.SetHideAll(false);
			if (GetKey(olc::Key::D).bReleased) myUI.ToggleDEBUGMODE();
		}

		myUI.drawUIObjects();
		if(currentStage != RUN_PROGRAM) drawBall(mouse_ball, fElapsedTime);
		
		//// lets print a string to the screen telling if the mouse is in any UI.
		//if (myUI.isMouseInUI()) DrawString(50, screenH* 0.9, ":THE MOUSE IS IN THE UI", olc::RED);
		//else DrawString(50, screenH* 0.9, ":THE MOUSE NOT IN THE UI", olc::RED);


		//// lets also draw all current commands to the screen
		//std::string myOut = myUI.getAllCmds();
		//DrawString(50, screenH* 0.95, myOut);

		
		return true;
	}
};

bool gameUPDATE(float fElapsedTime, bool reset, point_2d mouseCoords) {
	if (!g_ball.frozen) {
		playTimeSEC -= fElapsedTime;
		if (playTimeSEC < 0) {
			if (playTimeMIN <= 0 && playerPoints != aiPoints) return false;
			else {
				playTimeMIN -= 1;
				playTimeSEC += 60;
			}
		}
		else if (playTimeMIN < 0 && playerPoints != aiPoints) return false;
	}
	int points = g_ball.update(fElapsedTime);
	if (points != 0) {
		if (points == -1) playerPoints++;
		else aiPoints++;
		g_ball.reset(points);
	}
	if (reset) {
		if (getBetween(1, 2) == 1) g_ball.reset(-1);
		else g_ball.reset(1);
		playerPoints = 0;
		aiPoints = 0;
		playTimeMIN = AplayTimeMIN;
		playTimeSEC = AplayTimeSEC;
	}

	playerPos.y += playerSpeed * fElapsedTime;
	if (playerPos.y < screenH * 0.1) playerPos.y = screenH * 0.1;
	else if (playerPos.y + boarSize.y > screenH * 0.9) playerPos.y = screenH * 0.9 - boarSize.y;
	if (mouseCoords.y < playerPos.y + (boarSize.y *0.45)) { if (playerSpeed > -1000) playerSpeed -= 15000 * fElapsedTime; }
	else if (mouseCoords.y > playerPos.y + (boarSize.y *0.55)) { if (playerSpeed < 1000) playerSpeed += 15000 * fElapsedTime; }
	else playerSpeed = playerSpeed * 0.2;

	AiPos.y += AiSpeed * fElapsedTime;
	if (AiPos.y < screenH * 0.1) AiPos.y = screenH * 0.1;
	else if (AiPos.y + boarSize.y > screenH * 0.9) AiPos.y = screenH * 0.9 - boarSize.y;
	if (g_ball.coords.y < AiPos.y + (boarSize.y *(0.1+  (3.5f / (float)aiPrecision)))) { if (AiSpeed > -(300 + aiPrecision*2)) AiSpeed -= (800 + aiPrecision * 35) * fElapsedTime; }
	else if (g_ball.coords.y > AiPos.y + (boarSize.y *(0.1- (3.5f / (float)aiPrecision)))) { if (AiSpeed < (300 + aiPrecision*2)) AiSpeed += (800 + aiPrecision * 35)  * fElapsedTime; }
	else AiSpeed = AiSpeed * 0.9975;
	return true;
}

void optionsUPDATE(float fElapsedTime, pongBall &ball) {

	//if (art == paint_style) {
	//	if (myUI.isAllHidden()) {}
	//	else myUI.ToggleHideAll(false);
	//}
	//else if (myUI.isAllHidden()) myUI.ToggleHideAll(false);

	ball.ballSpeed = 200 + (8 * myUI.getSliderInt(10));
	ball.baseCountDown = myUI.getSliderInt(11) + 1;
	art = artStyle(myUI.getSliderInt(12));
	animation = myUI.getSliderInt(13);
	AplayTimeMIN = (int)(myUI.getSliderInt(14) / 60);
	AplayTimeSEC = (float)((int)(myUI.getSliderInt(14) - (AplayTimeMIN * 60)))+ 0.5;
	aiPrecision = myUI.getSliderInt(15);
	int points = g_ball.update(fElapsedTime);
	if (points != 0) {
		g_ball.reset(points);
	}
	if (myUI.getTxtFieldStr(16) != "") playerNameString = myUI.getTxtFieldStr(16);
}

void loadHighScore(std::vector<score> &toLoadInto, std::string &playerN) {
	playerN = "XXXXXX";
	std::string line;
	std::ifstream myfile("stats.sav");
	if (myfile.is_open())
	{
		int data = 0;
		while (std::getline(myfile, line))
		{
			if (data == 0) {
				if (line != "XXXXXX") playerN = line;
			}
			else toLoadInto.push_back(score(line));
			data++;
		}
		myfile.close();
	}

	while(toLoadInto.size() < 10) toLoadInto.push_back(score(0,99,"NO NAME!"));

}
void saveHighScore(std::vector<score> &toSave, std::string &playerN) {
	std::ofstream myfile("stats.sav");
	if (myfile.is_open())
	{
		
		myfile << playerN << std::endl;
		for (int i = 0; i < 10; i++) {
			myfile << toSave[i].getString() << std::endl;
		}
		myfile.close();
	}

}

void reviewScore(std::vector<score> &oldScores, int pP, int aP, std::string playerN) {
	int i = 0;
	bool saveIt = false;
	std::cout << "testing \n";
	while(i < oldScores.size()) {
		if (oldScores[i].comapre(pP, aP) == 1) {
			oldScores.insert(oldScores.begin()+i, score(pP, aP, playerN));
			saveIt = true;
			std::cout << "gotIt\n";
			i = 500;
		}
		i++;
	}
	if (saveIt) {
		saveHighScore(oldScores, playerN);
		std::cout << "Saved\n";
	}
}


int main()
{
	pongGame myGame;
	if (myGame.Construct(screenW, screenH, 1, 1))
		myGame.Start();

	return 0;
}
