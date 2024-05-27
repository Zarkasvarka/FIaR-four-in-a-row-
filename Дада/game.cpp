#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "game.h"
using namespace::std;

void Game::replayOrNot() {
	system("Chcp 1251");
	char ans;
	cout << "Желаете ли начать заного?\nY - да\nN - нет\n";
	while (true) {
		cin >> ans;
		if (ans == 'Y' || ans == 'y' || ans == 'N' || ans == 'n') {
			break;
		}
	}//пока игрок не ввёл символы из набора система будет продолжать запрашивать символ для ввода
	if (ans == 'Y' || ans == 'y')
	{
		system("cls");//очищаем консоль
		Game::play();
	}//если ДА - переигрываем
	else
	{
		exit;
	}//иначе выходим
}

Game::Game(){}
string p1 = "\x1b[34m()\x1b[0m", p2 = "\x1b[31m[]\x1b[0m"; //синий красный


void Game::getPlayerChoice(int&i, int&j){
	string playerChoice;
	while (true) {
		cin >> playerChoice;//ввод выбора игрока - число от 11 до 67
		if (playerChoice.length() == 2 && ((int)playerChoice[0] > 48 && (int)playerChoice[0] < 55) && ((int)playerChoice[1] > 48 && (int)playerChoice[1] < 56)){//если игрок ввёл число в пределах игрового поля
			i = playerChoice[0] - '0' - 1; j = playerChoice[1] - '0' - 1;//передаём значения выбора игрока по ссылке
			if (!alreadyFilled(i, j)) {//проверяем, свободна ли ячейка
				break;//если свободна - выходим из цикла
			}//если не занята ячейка
			else {
				system("cls");//очищаем консоль
				printGameDesk();//выводим поле заного
				cout << "\nДанная ячейка занята!\n";//оповещаем игрока о занятости ячейки
			}//если занята
		}
		else {
			system("cls");//очищаем консоль
			printGameDesk();//выводим поле
			cout << "\nВведите адрес ячейки!\n";//оповещаем игрока о неверном вводе
		}
	}


}

bool Game::alreadyFilled(int i, int j){
	return (gameDesk[i][j] == p1 || gameDesk[i][j] == p2);//если ячейка занята одним из игроков - ИСТИНА
}

void Game::doChoice(int i, int j, int k) {
	for (; gameDesk[i + 1][j] != p1 && gameDesk[i + 1][j] != p2 && i != 5;) {
		i++;
	}//сдвигаем выбор игрока вниз до тех пор, пока не встретим занятую ячейку или границу поля, "Кидаем вниз"
	if (k % 2 == 0) {//если ход синего
		gameDesk[i][j] = p1;//заполняем ячейку
	}//синий
	else {//если ход красного
		gameDesk[i][j] = p2;//заполняем ячейку
	}//красный
	system("cls");//очищаем консоль
	printGameDesk();//и выводим поле с новыми занятыми ячейками
}

void Game::clearGameDesk() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			gameDesk[i][j] = RESERVEgameDesk[i][j];//заполняем ячейки поля номерами для выбора
		}
	}
}

void Game::play() {
	clearGameDesk();//очищаем доску
	printGameDesk();//печатаем доску
	int i; int j;//задаём переменные для дальнейшего хода
	for (int k = 0; k < 42; k++) {//проходим столько раз, сколько ячеек в поле
		if (k % 2 == 0)//если ход синих
			cout << "\nХод синих\n";//Ход синих
		else//если ход красных
			cout << "\nХод красных\n";//Ход красных, соответственно
		getPlayerChoice(i, j);//метод получения выбора игрока
		doChoice(i, j, k);//метод выполнения хода игрока
		if (victoryStradegy()) {//если есть выйгрышная стратегия (кто-то собрал 4 в ряд (горизонталь, вертикаль или диагональ)
			if (k % 2 == 0) {//Если ход был синих
				system("cls");
				printGameDesk();
				cout << "Победили синие\n";//победили синие
			}
			else {//если ход был красных
				system("cls");
				printGameDesk();
				cout << "Победили красные\n";//победили красные
			}
			break;//завершаем игру
		}
		else if(k == 41 && !victoryStradegy())//если такой стратегии не нашлось, а ячейки все заняты - ничья
			cout << "Ничья\n";//да
	}
	replayOrNot();//метод для рестарта
}

bool Game::victoryStradegy()
{
	bool result = false;//переменная отвечающая за наличие выйгрышной стратегии
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			int count = 0;//счётчик сходств
			for (int k = 0; k < 4 && k < 7-j; k++) {//пока следующие 4 ячейки по горизонтали существуют
				if (gameDesk[i][j] == gameDesk[i][j+k])//проверяем на сходство
					count++;//если одинаковые - считаем их
				if (count == 4)//если одинаковых по горизонтали 4
					result = true;//выйгрышная стратегия существует
			}//горизонт
			count = 0;
			for (int k = 0; k < 4 && k < 6 - i; k++) {//пока следующие 4 по вертикали существуют
				if (gameDesk[i][j] == gameDesk[i+k][j])
					count++;
				if (count == 4)
					result = true;
			}//вертикаль
			count = 0;
			for (int k = 0; k < 4 && k < 6 - i && k < 7-j; k++) {//пока следующие 4 по горизонтали вправо вниз существуют
				if (gameDesk[i][j] == gameDesk[i + k][j+k])
					count++;
				if (count == 4)
					result = true;
			}//диагональ п
			count = 0;
			for (int k = 0; k < 4 && k < 6 - i && k < 7 - j && j - k >= 0; k++) {//пока следующие 4 по горизонтали влево вниз существуют
				if (gameDesk[i][j] == gameDesk[i + k][j - k])
					count++;
				if (count == 4)
					result = true;
			}//диагональ л
		}
	}
	return result;//возвращаем результат
}

void Game::printGameDesk() {
	cout << "____________________________________";//потолок игрового поля
	for (int i = 0; i < 6; i++) {
		cout << "\n| ";//левая стенка
		for (int j = 0; j < 7; j++) {
			if ((i + j) % 2 == 0) {
				cout << gameDesk[i][j] << " | ";//последняя ячейка с правой стенкой
			}
			else
				cout << gameDesk[i][j] << " | ";//ячейка между левой и правой стенками

		}
		cout << "\n------------------------------------";//нижняя стенка
	}
	cout << "\n";
}
Game::~Game() {
	// cout << "\n\n удалено успешно";
}