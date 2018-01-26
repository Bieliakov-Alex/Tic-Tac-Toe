#include "TTTGame.h"



void TTTGame::setLength(int length)
{
	if (length > 0)
	{
		this->length = length;
	}
	else
	{
		this->length = 3;
	}
}

void TTTGame::setWidth(int width)
{
	if (width>0)
	{
		this->width = width;
	}
	else
	{
		this->width = 3;
	}
}

void TTTGame::setCross(char cross)
{
	if (cross != '_')
	{
		this->cross = cross;
	}
	else
	{
		this->cross = 'x';
	}
}

void TTTGame::setToe(char toe)
{
	if (toe != '_')
	{
		this->toe = toe;
	}
	else
	{
		this->toe = 'o';
	}
}

void TTTGame::setCountElements(int countElements)
{
	if (countElements>0&&this->getLength()>0&&this->getWidth()>0&&countElements<=this->getLength()&&countElements<=this->getWidth())
	{
		this->countElements = countElements;
	}
	else
	{
		this->countElements = 3;
	}
}

TTTGame::TTTGame(int length, int width, int countElements, char cross, char toe)
{
	this->setLength(length);
	this->setWidth(width);
	this->setCountElements(countElements);
	this->setCross(cross);
	this->setToe(toe);

	//выделяем память под поле
	this->field = new char*[this->getLength()];
	for (size_t i = 0; i < this->getLength(); i++)
	{
		this->field[i] = new char[this->getWidth()];
	}

	//заполняем поле пробелами
	for (size_t i = 0; i < this->getLength(); i++)
	{
		for (size_t j = 0; j < this->getWidth(); j++)
		{
			this->field[i][j] = '_';
		}
	}

	this->gameEnd = false;
	this->gameState = CONTINUE;
}

TTTGame::~TTTGame()
{
	for (size_t i = 0; i < this->getLength(); i++)
	{
		delete[] this->field[i];
	}
	delete this->field;
}

const char ** TTTGame::getField() const
{
	return (const char**)field;
}

int TTTGame::getLength() const
{
	return this->length;
}

int TTTGame::getWidth() const
{
	return this->width;
}

bool TTTGame::firstPlayerMove(int length, int width)
{
	if (length-1<0||width-1<0||length - 1 > this->getLength() || width - 1 > this->getWidth() || this->field[length - 1][width - 1] != '_')
	{
		return false;
	}
	else
	{
		this->field[length - 1][width - 1] = this->cross;
		return true;
	}
}

bool TTTGame::secondPlayerMove(int length, int width)
{
	if (length - 1<0 || width - 1<0 || length - 1 > this->getLength() || width - 1 > this->getWidth() || this->field[length - 1][width - 1] != '_')
	{
		return false;
	}
	else
	{
		this->field[length - 1][width - 1] = this->toe;
		return true;
	}
}

void TTTGame::calculateState()
{
	//проверка победы первого игрока
	if (this->checkHorizontal(this->cross)||this->checkVertical(this->cross)||this->checkSouthEastDiagonal(this->cross)||this->checkSouthWestDiagonal(this->cross))
	{
		this->gameEnd = true;
		this->gameState = GameState::FIRST_PLAYER_WIN;
		return;
	}
	//проверка победы второго игрока
	else if (this->checkHorizontal(this->toe) || this->checkVertical(this->toe) || this->checkSouthEastDiagonal(this->toe) || this->checkSouthWestDiagonal(this->toe))
	{
		this->gameEnd = true;
		this->gameState = GameState::SECOND_PLAYER_WIN;
		return;
	}
	//проверка ничьи
	else if(this->checkDraw())
	{
		this->gameEnd = true;
		this->gameState = GameState::DRAW;
		return;
	}
	return;
}

bool TTTGame::checkDraw()const
{
	for (size_t i = 0; i < this->getLength(); i++)
	{
		for (size_t j = 0; j < this->getWidth(); j++)
		{
			if (this->field[i][j] == '_') return false;
		}
	}

	return true;
}

bool TTTGame::checkWin(char symbol) const
{
	return false;
}

bool TTTGame::checkHorizontal(char symbol) const
{
	for (size_t i = 0; i < this->getLength(); i++)
	{
		for (size_t j = 0; j < this->getWidth()-this->countElements+1; j++)
		{
			if (this->field[i][j] == symbol)
			{
				bool symbolWin = true;
				for (size_t k = j+1; k < j+countElements; k++)
				{
					if (this->field[i][k] != symbol)
					{
						symbolWin = false;
						break;
					}
				}
				if (symbolWin)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool TTTGame::checkVertical(char symbol) const
{
	for (size_t i = 0; i < this->getLength()-this->countElements+1; i++)
	{
		for (size_t j = 0; j < this->getWidth(); j++)
		{
			if (this->field[i][j] == symbol)
			{
				bool symbolWin = true;
				for (size_t k = i+1; k < countElements+i; k++)
				{
					if (this->field[k][j] != symbol)
					{
						symbolWin = false;
						break;
					}
				}
				if (symbolWin)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool TTTGame::checkSouthEastDiagonal(char symbol) const
{
	for (size_t i = 0; i < this->getLength()-this->countElements+1; i++)
	{
		for (size_t j = 0; j < this->getWidth()-this->countElements+1; j++)
		{
			if (this->field[i][j]==symbol)
			{
				bool symbolWin = true;
				for (size_t k = i+1,l=j+1; (k < this->countElements+i)&&(l<this->countElements+j); k++,l++)
				{
					if (this->field[k][l]!=symbol)
					{
						symbolWin = false;
						break;
					}
				}
				if (symbolWin)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool TTTGame::checkSouthWestDiagonal(char symbol) const
{
	for (size_t i = this->getLength()-1;i>-2+this->countElements; i--)
	{
		for (size_t j = this->getWidth()-1; j > -2+this->countElements; j--)
		{
			if (this->field[i][j] == symbol)
			{
				bool symbolWin = true;
				for (size_t k = i-1, l = j-1;(k>i+this->countElements)&&(l>j+this->countElements) ; k--, l--)
				{
					if (this->field[k][l] != symbol)
					{
						symbolWin = false;
						break;
					}
				}
				if (symbolWin)
				{
					return true;
				}
			}
		}
	}
	return false;
}
