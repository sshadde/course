#pragma once // ��������� #pragma once ������������� ������������ ��������� ������������� ����� � ����� � ��� �� �������������� ������

#include <iostream> // ��������� ����������� ���������� �����-������
#include <string> // ��������� ����������� ���������� ��� ������ � ��������
#include <algorithm> // ��������� ����������� ���������� ��� ������ � �����������

// ����� ��� ������������� ����������� ������� ������
class GuessResult {
public:
    int correctDigits; // ���������� ��������� ��������� ����
    int correctPositions; // ���������� ���� �� ����� ������

    // ����������� ������ GuessResult
    GuessResult(int digits, int positions);
};

// ����������� ����� ����
class Game {
protected:
    std::string secretNumber; // ��������� �����

public:
    // ����������� ������ Game
    Game(std::string number);

    // ����������� ������� ��� ������� ������
    virtual GuessResult guessNumber(std::string number) = 0;
};

// ����� ������, ����������� �� Game
class Player : public Game {
public:
    // ����������� ������ Player
    Player(std::string number);

    // ���������������� ����� ��� ������� ������
    GuessResult guessNumber(std::string number) override;
};

// ������� ��� ��������� ������������ �����
std::string generateNumber();
