#pragma once // Директива #pragma once предотвращает многократное включение заголовочного файла в одном и том же трансляционном модуле

#include <iostream> // Включение стандартной библиотеки ввода-вывода
#include <string> // Включение стандартной библиотеки для работы с строками
#include <algorithm> // Включение стандартной библиотеки для работы с алгоритмами

// Класс для представления результатов догадок игрока
class GuessResult {
public:
    int correctDigits; // Количество правильно угаданных цифр
    int correctPositions; // Количество цифр на своих местах

    // Конструктор класса GuessResult
    GuessResult(int digits, int positions);
};

// Абстрактный класс игры
class Game {
protected:
    std::string secretNumber; // Секретное число

public:
    // Конструктор класса Game
    Game(std::string number);

    // Виртуальная функция для догадок игрока
    virtual GuessResult guessNumber(std::string number) = 0;
};

// Класс игрока, наследуется от Game
class Player : public Game {
public:
    // Конструктор класса Player
    Player(std::string number);

    // Переопределенный метод для догадок игрока
    GuessResult guessNumber(std::string number) override;
};

// Функция для генерации трехзначного числа
std::string generateNumber();
