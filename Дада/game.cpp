#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "game.h"
using namespace::std;

void Game::replayOrNot() {
	system("Chcp 1251");
	char ans;
	cout << "������� �� ������ ������?\nY - ��\nN - ���\n";
	while (true) {
		cin >> ans;
		if (ans == 'Y' || ans == 'y' || ans == 'N' || ans == 'n') {
			break;
		}
	}//���� ����� �� ��� ������� �� ������ ������� ����� ���������� ����������� ������ ��� �����
	if (ans == 'Y' || ans == 'y')
	{
		system("cls");//������� �������
		Game::play();
	}//���� �� - ������������
	else
	{
		exit;
	}//����� �������
}

Game::Game(){}
string p1 = "\x1b[34m()\x1b[0m", p2 = "\x1b[31m[]\x1b[0m"; //����� �������


void Game::getPlayerChoice(int&i, int&j){
	string playerChoice;
	while (true) {
		cin >> playerChoice;//���� ������ ������ - ����� �� 11 �� 67
		if (playerChoice.length() == 2 && ((int)playerChoice[0] > 48 && (int)playerChoice[0] < 55) && ((int)playerChoice[1] > 48 && (int)playerChoice[1] < 56)){//���� ����� ��� ����� � �������� �������� ����
			i = playerChoice[0] - '0' - 1; j = playerChoice[1] - '0' - 1;//������� �������� ������ ������ �� ������
			if (!alreadyFilled(i, j)) {//���������, �������� �� ������
				break;//���� �������� - ������� �� �����
			}//���� �� ������ ������
			else {
				system("cls");//������� �������
				printGameDesk();//������� ���� ������
				cout << "\n������ ������ ������!\n";//��������� ������ � ��������� ������
			}//���� ������
		}
		else {
			system("cls");//������� �������
			printGameDesk();//������� ����
			cout << "\n������� ����� ������!\n";//��������� ������ � �������� �����
		}
	}


}

bool Game::alreadyFilled(int i, int j){
	return (gameDesk[i][j] == p1 || gameDesk[i][j] == p2);//���� ������ ������ ����� �� ������� - ������
}

void Game::doChoice(int i, int j, int k) {
	for (; gameDesk[i + 1][j] != p1 && gameDesk[i + 1][j] != p2 && i != 5;) {
		i++;
	}//�������� ����� ������ ���� �� ��� ���, ���� �� �������� ������� ������ ��� ������� ����, "������ ����"
	if (k % 2 == 0) {//���� ��� ������
		gameDesk[i][j] = p1;//��������� ������
	}//�����
	else {//���� ��� ��������
		gameDesk[i][j] = p2;//��������� ������
	}//�������
	system("cls");//������� �������
	printGameDesk();//� ������� ���� � ������ �������� ��������
}

void Game::clearGameDesk() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			gameDesk[i][j] = RESERVEgameDesk[i][j];//��������� ������ ���� �������� ��� ������
		}
	}
}

void Game::play() {
	clearGameDesk();//������� �����
	printGameDesk();//�������� �����
	int i; int j;//����� ���������� ��� ����������� ����
	for (int k = 0; k < 42; k++) {//�������� ������� ���, ������� ����� � ����
		if (k % 2 == 0)//���� ��� �����
			cout << "\n��� �����\n";//��� �����
		else//���� ��� �������
			cout << "\n��� �������\n";//��� �������, ��������������
		getPlayerChoice(i, j);//����� ��������� ������ ������
		doChoice(i, j, k);//����� ���������� ���� ������
		if (victoryStradegy()) {//���� ���� ���������� ��������� (���-�� ������ 4 � ��� (�����������, ��������� ��� ���������)
			if (k % 2 == 0) {//���� ��� ��� �����
				system("cls");
				printGameDesk();
				cout << "�������� �����\n";//�������� �����
			}
			else {//���� ��� ��� �������
				system("cls");
				printGameDesk();
				cout << "�������� �������\n";//�������� �������
			}
			break;//��������� ����
		}
		else if(k == 41 && !victoryStradegy())//���� ����� ��������� �� �������, � ������ ��� ������ - �����
			cout << "�����\n";//��
	}
	replayOrNot();//����� ��� ��������
}

bool Game::victoryStradegy()
{
	bool result = false;//���������� ���������� �� ������� ���������� ���������
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			int count = 0;//������� �������
			for (int k = 0; k < 4 && k < 7-j; k++) {//���� ��������� 4 ������ �� ����������� ����������
				if (gameDesk[i][j] == gameDesk[i][j+k])//��������� �� ��������
					count++;//���� ���������� - ������� ��
				if (count == 4)//���� ���������� �� ����������� 4
					result = true;//���������� ��������� ����������
			}//��������
			count = 0;
			for (int k = 0; k < 4 && k < 6 - i; k++) {//���� ��������� 4 �� ��������� ����������
				if (gameDesk[i][j] == gameDesk[i+k][j])
					count++;
				if (count == 4)
					result = true;
			}//���������
			count = 0;
			for (int k = 0; k < 4 && k < 6 - i && k < 7-j; k++) {//���� ��������� 4 �� ����������� ������ ���� ����������
				if (gameDesk[i][j] == gameDesk[i + k][j+k])
					count++;
				if (count == 4)
					result = true;
			}//��������� �
			count = 0;
			for (int k = 0; k < 4 && k < 6 - i && k < 7 - j && j - k >= 0; k++) {//���� ��������� 4 �� ����������� ����� ���� ����������
				if (gameDesk[i][j] == gameDesk[i + k][j - k])
					count++;
				if (count == 4)
					result = true;
			}//��������� �
		}
	}
	return result;//���������� ���������
}

void Game::printGameDesk() {
	cout << "____________________________________";//������� �������� ����
	for (int i = 0; i < 6; i++) {
		cout << "\n| ";//����� ������
		for (int j = 0; j < 7; j++) {
			if ((i + j) % 2 == 0) {
				cout << gameDesk[i][j] << " | ";//��������� ������ � ������ �������
			}
			else
				cout << gameDesk[i][j] << " | ";//������ ����� ����� � ������ ��������

		}
		cout << "\n------------------------------------";//������ ������
	}
	cout << "\n";
}
Game::~Game() {
	// cout << "\n\n ������� �������";
}