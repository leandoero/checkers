#include "checkers.h";


void Game::Loading() {
	cout << "loading";
	for (int i = 0; i < 3; ++i) {
		cout << ".";
		this_thread::sleep_for(chrono::seconds(1)); // Задержка 1 секунда
	}
}

void GameField::FillingField() {
	for (int i = 0; i < rows; i++)
	{
		mas[i] = new int[cols + 1];
	}

	for (int i = 0; i < rows; i++)
	{
		if (i >= 5) {
			for (int j = 0; j < cols; j++) {
				mas[i][j] = { 0 };
				if ((i + j) % 2 != 0) {
					mas[i][j] = { 2 };
				}
			}
		}
		else if (i <= 2) {
			for (int j = 0; j < cols; j++) {
				mas[i][j] = { 0 };
				if ((i + j) % 2 != 0) {
					mas[i][j] = { 1 };
				}
			}
		}
		else {
			for (int j = 0; j < cols; j++) {
				mas[i][j] = { 0 };
			}
		}
	}
}
void GameField::DrawingField(int** mas)
{
	cout << "Пустая клетка - 0\n" <<
		"Белые шашки - 1\n" <<
		"Чёрные шашки - 2\n\n" <<
		"Для выбора другой шашки в поле <Введите координаты хода:> вписать 100 A\n" <<
		"Для смены хода после атаки в поле <Введите координаты хода:> вписать 105 B\n" <<
		"Для выхода в меню в поле <Введите координаты хода:> или <Выберите шашку:> вписать 110 C\n" << endl;
	for (char i = 'A'; i < 'A' + cols; i++)
	{
		cout << "   " << i << " ";
	}
	for (int i = 0; i < rows; i++)
	{
		cout << endl;
		cout << i + 1;
		for (int j = 0; j < cols; j++) {
			cout << "| " << mas[i][j] << " |";
		}
		cout << endl;
	}
}
GameField::~GameField() {

	for (int i = 0; i < rows; i++)
	{
		delete[] mas[i];
	}
	delete[] mas;


}

Player::Point::Point(int x, char y) : xPoint(x), yPoint(y) {}

Player::Player(int** mas, int rows, int cols) {
	this->copyRows = rows;
	this->copyCols = cols;
	this->copyMas = new int* [copyRows + 1];
	for (int i = 0; i < copyRows; i++)
	{
		copyMas[i] = new int[copyCols + 1];
	}
	for (int i = 0; i < copyRows; i++)
	{
		for (int j = 0; j < copyCols; j++)
		{
			copyMas[i][j] = mas[i][j];
		}

	}

}
void Player::choiceOfCheckers() {
	unsigned int firstCoord = 0;
	char secondCoord;
	bool validInput = true;
	while (validInput) {
		if (progress % 2 != 0) {

			cout << "\n\n-------- Ход белых --------" << endl;
			cout << "\nВыберите шашку: ";
			cin >> firstCoord >> secondCoord;
			secondCoord = toupper(secondCoord);
			this->secondIndex = secondCoord - 65;
			this->firstIndex = firstCoord - 1;
			if (firstCoord == 110 && secondCoord == 'C') {
				validInput = false;
				system("cls");
				welcome();
			}
			else if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Ошибка: программа ожидает получить корректный ввод. " << endl;
				continue;
			}

			else if (firstCoord > 9 || secondCoord > 'H') {
				cout << "Некорректный ввод!" << endl;
				continue;
			}

			else if (copyMas[firstIndex][secondIndex] != 1 && copyMas[firstIndex][secondIndex] != 2) {
				cout << "Некорректный ввод! Введите ещё раз: ";
				continue;
			}
			else {

				validInput = false;

				checkersMove(0, 0, firstIndex, secondIndex);
				break;
			}
		}
		else {

			cout << "\n\n-------- Ход черных --------" << endl;
			cout << "\nВыберите шашку: ";
			cin >> firstCoord >> secondCoord;

			secondCoord = toupper(secondCoord);
			this->secondIndex = secondCoord - 65;
			this->firstIndex = firstCoord - 1;

			if (firstCoord == 110 && secondCoord == 'C') {
				validInput = false;
				system("cls");
				welcome();
			}
			else if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Ошибка: программа ожидает получить корректный ввод. " << endl;
				continue;
			}

			else if (firstCoord > 9 || secondCoord > 'H') {
				cout << "Некорректный ввод!" << endl;
				continue;
			}
			else if (copyMas[firstIndex][secondIndex] != 1 && copyMas[firstIndex][secondIndex] != 2) {
				cout << "Некорректный ввод! ";
				continue;
			}
			else {

				validInput = false;
				checkersMove(0, 0, firstIndex, secondIndex);
				break;
			}
		}
	}
}

void Player::checkersMove(int firstIndexForMoveFunc, char secondIndexForMoveFunc, int firstIndex, char secondIndex) {

	while (progress) {
		if (progress % 2 != 0 && copyMas[firstIndex][secondIndex] == 1) {

			bool validInput = true;

			while (validInput) {
				cout << "Введите координаты хода: ";
				cin >> firstIndexForMoveFunc >> secondIndexForMoveFunc;
				secondIndexForMoveFunc = toupper(secondIndexForMoveFunc);

				this->firstIndexForMove = firstIndexForMoveFunc - 1;
				this->secondIndexForMove = secondIndexForMoveFunc - 65;

				if (firstIndexForMoveFunc == 100 && secondIndexForMoveFunc == 'A') {
					choiceOfCheckers();
				}
				else if (firstIndexForMoveFunc == 105 && secondIndexForMoveFunc == 'B') {
					this->progress++;
					choiceOfCheckers();
				}
				else if (firstIndexForMoveFunc == 110 && secondIndexForMoveFunc == 'C') {
					validInput = false;
					system("cls");
					welcome();
				}
				else if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Ошибка: программа ожидает получить корректный ввод." << endl;
					continue;
				}
				else if (firstIndexForMoveFunc >= 9 || secondIndexForMoveFunc > 'H') {
					cout << "Ход невозможен!" << endl;
					continue;
				}
				else if (copyMas[firstIndexForMove][secondIndexForMove] == 0 && ((firstIndexForMove) != firstIndex) && ((secondIndexForMove) != secondIndex)) {

					if (firstIndex == 9) {
						copyMas[9][secondIndex] = { 0 };
						queenAttack();
					}
					else if (checkingOnTheQueen(firstIndex, secondIndex, progress)) {
						queenAttack();
					}
					else if ((abs(firstIndexForMove - firstIndex) <= 1) && (abs(secondIndexForMove - secondIndex) <= 1) && (firstIndexForMove > firstIndex)) {
						copyMas[firstIndex][secondIndex] = { 0 };
						validInput = false;

						copyMas[firstIndexForMove][secondIndexForMove] = 1;
						GameField gamefield;
						system("cls");
						gamefield.DrawingField(copyMas);
						++progress;

						choiceOfCheckers();

					}
					else if ((abs(firstIndexForMove - firstIndex) <= 2) && (abs(secondIndexForMove - secondIndex) <= 2)) {
						copyMas[firstIndex][secondIndex] = { 0 };
						attack();
					}
					else {
						cout << "Ход невозможен!" << endl;
					}

				}
				else {
					cout << "Ход невозможен! " << endl;
				}
			}
		}
		else if (progress % 2 == 0 && copyMas[firstIndex][secondIndex] == 2) {

			bool validInput = true;

			while (validInput) {

				cout << "Введите координаты хода: ";
				cin >> firstIndexForMoveFunc >> secondIndexForMoveFunc;
				secondIndexForMoveFunc = toupper(secondIndexForMoveFunc);

				this->firstIndexForMove = firstIndexForMoveFunc - 1;
				this->secondIndexForMove = secondIndexForMoveFunc - 65;

				if (firstIndexForMoveFunc == 100 && secondIndexForMoveFunc == 'A') {
					choiceOfCheckers();
				}
				else if (firstIndexForMoveFunc == 105 && secondIndexForMoveFunc == 'B') {
					this->progress++;
					choiceOfCheckers();
				}
				else if (firstIndexForMoveFunc == 110 && secondIndexForMoveFunc == 'C') {
					validInput = false;
					system("cls");
					welcome();
				}
				else if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Ошибка: программа ожидает получить корректный ввод. " << endl;
					continue;
				}
				else if (firstIndexForMoveFunc >= 9 || secondIndexForMoveFunc > 'H') {
					cout << "Ход невозможен!" << endl;
					continue;
				}
				else if (copyMas[firstIndexForMove][secondIndexForMove] == 0 && ((firstIndexForMove) != firstIndex) && ((secondIndexForMove) != secondIndex)) {
					if (firstIndex == 0) {
						copyMas[firstIndex][secondIndex] = { 0 };
						queenAttack();
					}
					else if (checkingOnTheQueen(firstIndex, secondIndex, progress)) {
						queenAttack();
					}

					else if (((abs(secondIndexForMove - secondIndex) <= 1) && (abs(firstIndexForMove - firstIndex) <= 1) && (firstIndexForMove < firstIndex))) {
						copyMas[firstIndex][secondIndex] = { 0 };
						validInput = false;

						copyMas[firstIndexForMove][secondIndexForMove] = 2;
						GameField gamefield;
						system("cls");
						gamefield.DrawingField(copyMas);
						++progress;

						choiceOfCheckers();

					}
					else if ((abs(firstIndexForMove - firstIndex) <= 2) && (abs(secondIndexForMove - secondIndex) <= 2)) {
						copyMas[firstIndex][secondIndex] = { 0 };
						attack();
					}
					else {
						cout << "Ход невозможен!" << endl;
					}

				}
				else {
					cout << "Ход невозможен!" << endl;
				}
			}
		}
		else {
			cout << "Проверьте корректность ввода.";
			choiceOfCheckers();
		}
	}
}
void Player::attack() {
	if ((progress % 2 != 0) && copyMas[firstIndexForMove][secondIndexForMove] == 0) {				//ход белых
		int firstIndexForAttack = ((firstIndex + firstIndexForMove) / 2);
		char secondIndexForAttack = ((secondIndex + secondIndexForMove) / 2);

		if (copyMas[firstIndexForAttack][secondIndexForAttack] == 2) {
			copyMas[firstIndexForMove][secondIndexForMove] = 1;
			copyMas[firstIndexForAttack][secondIndexForAttack] = { 0 };
			GameField gamefield;
			system("cls");
			this->firstIndex = firstIndexForMove;
			this->secondIndex = secondIndexForMove;
			gamefield.DrawingField(copyMas);
			checkersMove(firstIndexForMove, secondIndexForMove, firstIndex, secondIndex);

		}
	}
	else if ((progress % 2 == 0) && copyMas[firstIndexForMove][secondIndexForMove] == 0) {			//ход черных
		int firstIndexForAttack = ((firstIndex + firstIndexForMove) / 2);
		char secondIndexForAttack = ((secondIndex + secondIndexForMove) / 2);

		if (copyMas[firstIndexForAttack][secondIndexForAttack] == 1) {
			copyMas[firstIndexForMove][secondIndexForMove] = 2;
			copyMas[firstIndexForAttack][secondIndexForAttack] = { 0 };

			GameField gamefield;
			system("cls");
			this->firstIndex = firstIndexForMove;
			this->secondIndex = secondIndexForMove;
			gamefield.DrawingField(copyMas);
			checkersMove(firstIndexForMove, secondIndexForMove, firstIndex, secondIndex);

		}
	}
}
void Player::queenAttack() {
	int counter = 0;

	if (progress % 2 == 0 && copyMas[firstIndexForMove][secondIndexForMove] == 0) {	//ход черных
		for (int i = firstIndex + 1; i < firstIndexForMove; i++)
		{
			int count = 1;
			for (int j = secondIndex; j < secondIndexForMove; j++) {


				if (copyMas[firstIndex + count][secondIndex + count] == 1) {
					++counter;
				}
				else if (copyMas[firstIndex][secondIndex] == 2) {
					cout << "Ход невозможен!" << endl;
					break;
				}
				++count;
			}
		}
		if (counter > 2) {
			cout << "Ход невозможен!" << endl;
		}
		else {
			for (int i = firstIndex + 1; i < firstIndexForMove; i++)
			{
				int count = 1;

				for (int j = secondIndex; j < secondIndexForMove; j++) {
					copyMas[firstIndex + count][secondIndex + count] = 0;
					count++;
				}
			}
			copyMas[firstIndexForMove][secondIndexForMove] = 2;
		}
		GameField gamefield;
		system("cls");
		this->firstIndex = firstIndexForMove;
		this->secondIndex = secondIndexForMove;

		pointsForBlack.emplace_back(firstIndexForMove, secondIndexForMove);
		gamefield.DrawingField(copyMas);
		checkersMove(firstIndexForMove, secondIndexForMove, firstIndex, secondIndex);
	}

	//else if (progress % 2 != 0 && copyMas[firstIndexForMove][secondIndexForMove] == 0)		//ход белых
}
bool Player::checkingOnTheQueen(int& first, char& second, int& progress) {
	if (progress % 2 != 0 && copyMas[first][second] == 1) {
		for (int i = 0; i < pointsForWhite.size(); i++)
		{
			if (pointsForWhite[i].xPoint == first && pointsForWhite[i].yPoint == second) {
				return true;
				break;
			}
		}
		return false;
	}
	else if (progress % 2 == 0 && copyMas[first][second] == 2) {
		for (int i = 0; i < pointsForBlack.size(); i++)
		{
			if (pointsForBlack[i].xPoint == first && pointsForBlack[i].yPoint == second) {
				return true;
				break;
			}
		}
		return false;
	}
}
Player::~Player()
{
	for (int i = 0; i < copyRows; i++)
	{
		delete[] copyMas[i];
	}
	delete[] copyMas;
}


void openRules() {
	ifstream inputFile("rules.txt");
	if (!inputFile) {
		cout << "Не удалось открыть файл!" << endl;
	}

	std::string line;

	while (getline(inputFile, line)) {
		std::cout << line << std::endl;
	}

	inputFile.close();
}

void welcome() {

	cout << "Добро пожаловать в мир шашек! \n\n" <<
		"Выберите одно из представленного меню:\n" <<
		"1. Игра 1v1\n" <<
		"2. Мой рейтинг\n" <<
		"3. Правила\n" <<
		"4. Выход\n" << endl;

	int userInput = 0;
	bool validInput = true;

	while (validInput)
	{
		cout << "Ввод пользователя: ";
		cin >> userInput;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ошибка: программа ожидает получить корректный ввод. " << endl;
			continue;
		}

		switch (userInput)
		{
		case 1:
		{
			Game game;
			game.Loading();
			validInput = false;
			system("cls");


			GameField gamefield;
			gamefield.FillingField();
			gamefield.DrawingField(gamefield.mas);
			Player player(gamefield.mas, gamefield.rows_new, gamefield.cols_new);
			player.choiceOfCheckers();
			break;
		}
		case 2:
		{
			Game game;
			game.Loading();
			validInput = false;
			break;
		}

		case 3:
		{
			Game game;
			game.Loading();
			validInput = false;
			system("cls");
			locale::global(std::locale("ru_RU.UTF-8"));
			openRules();
		}

		case 4:
		{
			validInput = false;
			cout << "До скорых встреч! *_^" << endl;
			break;
		}

		default:
		{
			cout << "Неверный ввод! Попробуйте ещё раз!" << endl;
		}
		}
	}
}
