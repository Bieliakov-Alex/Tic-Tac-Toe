#pragma once

//перечисление состояния игры
//CONTINE - игра продолжается
//FIRST_PLAYER_WIN - победил первый игрок
//SECOND_PLAYER_WIN - победил второй игрок
//DRAW - ничья
enum GameState {CONTINUE, FIRST_PLAYER_WIN, SECOND_PLAYER_WIN, DRAW};

class TTTGame
{
private:
	//размер поля по вертикали
	int length{ 0 };
	//размер поля по горизонтали
	int width{ 0 };
	//поле
	char** field;
	//символ крестика
	char cross;
	//символ нолика
	char toe;
	//признак конца игры
	bool gameEnd;
	//количество элементов в ряд для победы
	int countElements{ 0 };
	//состояние игры - продолжается, победа первого\второго игрока, ничья
	GameState gameState;

	void setLength(int length);
	void setWidth(int width);
	void setCross(char cross);
	void setToe(char toe);
	void setCountElements(int countElements);

public:
	TTTGame(int length=3, int width=3, int countElements=3, char cross='x', char toe='o');
	virtual ~TTTGame();
	const char** getField()const;
	int getLength()const;
	int getWidth()const;
	bool firstPlayerMove(int length, int width);
	bool secondPlayerMove(int length, int width);
	void calculateState();

	bool checkDraw()const;
	bool checkWin(char symbol)const;
	bool checkHorizontal(char symbol)const;
	bool checkVertical(char symbol)const;
	//TODO: Реализовать проверку диагоналей
};

