#pragma once
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Game {
public:
	void Loading();
};

class GameField {
private:
	const int rows = 8;
	const int cols = 8;

public:
	int rows_new = this->rows;
	int cols_new = this->cols;
	int** mas = new int* [rows + 1];
	void FillingField();
	void DrawingField(int** mas);
	~GameField();
};

class Player {
private:
	char secondIndex = 0;
	int firstIndex = 0;
	int copyRows;
	int copyCols;
	int progress = 1;
	int firstIndexForMove = 0;
	char secondIndexForMove = 0;
	struct Point {
		int xPoint;
		char yPoint;
		Point(int x, char y);
	};
	vector<Point> pointsForWhite;
	vector<Point> pointsForBlack;
public:
	int** copyMas;
	Player(int** mas, int rows, int cols);
	void choiceOfCheckers();
	void checkersMove(int firstIndexForMoveFunc, char secondIndexForMoveFunc, int firstIndex, char secondIndex);
	void attack();
	void queenAttack();
	bool checkingOnTheQueen(int& first, char& second, int& progress);
	~Player();
};

void openRules();
void welcome();
