
// Snack.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "Snake.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSnake::CSnake() {
	len = 1;
	head = Dire::Right;
	body[0].xPos = 10;
	body[0].yPos = 10;
}
	
CSnake::~CSnake() {

}

void CSnake::MoveLeft() {
	for (int i = (this->len) - 1; i > 0; i--) {
		body[i].xPos = body[i - 1].xPos;
		body[i].yPos = body[i - 1].yPos;
	}
	body[0].yPos--;
	if (body[0].yPos < 0) {
		body[0].yPos = 33;
	}
	head = Dire::Left;
}

void CSnake::MoveRight() {
	for (int i = (this->len) - 1; i > 0; i--) {
		body[i].xPos = body[i - 1].xPos;
		body[i].yPos = body[i - 1].yPos;
	}
	body[0].yPos++;
	if (body[0].yPos > 33) {
		body[0].yPos = 0;
	}
	head = Dire::Right;
}

void CSnake::MoveUp() {
	for (int i = (this->len) - 1; i > 0; i--) {
		body[i].xPos = body[i - 1].xPos;
		body[i].yPos = body[i - 1].yPos;
	}
	body[0].xPos--;
	if (body[0].xPos < 0) {
		body[0].xPos = 29;
	}
	head = Dire::Up;
}

void CSnake::MoveDown() {
	for (int i = (this->len) - 1; i > 0; i--) {
		body[i].xPos = body[i - 1].xPos;
		body[i].yPos = body[i - 1].yPos;
	}
	body[0].xPos++;
	if (body[0].xPos > 29) {
		body[0].xPos = 0;
	}
	head = Dire::Down;
}

void CSnake::Init() {
	len = 1;
	head = Dire::Right;
	body[0].xPos = 10;
	body[0].yPos = 10;
}
