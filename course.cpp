﻿#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

// Класс для представления результатов догадок игрока (родительский класс)
class GuessResult {
public:
    int correctDigits; // количество правильно угаданных цифр
    int correctPositions; // количество цифр на своих местах

    GuessResult(int digits, int positions) : correctDigits(digits), correctPositions(positions) {} // конструктор класса-родителя с инициализацией переменных
};

// Класс игры
class Game {
protected:
    std::string secretNumber; // секретное число

public:
    Game(std::string number) : secretNumber(number) {} // конструктор класса с инициализацией secretNumber

    virtual GuessResult guessNumber(std::string number) = 0; // виртуальный метод для догадок игрока
};

// Класс игрока, наследуется от Game
class Player : public Game {
public:
    Player(std::string number) : Game(number) {} // конструктор игрока

    GuessResult guessNumber(std::string number) override { // override - функция для переопределения метода guessNumber
        int correctDigits = 0; // количество правильно угаданных цифр
        int correctPositions = 0; // количество цифр на своих местах

        std::string tempSecret = secretNumber; // временные переменные для работы цикла с проверкой
        std::string tempGuess = number;

        // Проверка угаданных цифр и позиций
        for (int i = 0; i < secretNumber.length(); ++i) {
            if (tempGuess[i] == tempSecret[i]) {
                correctPositions++;
                tempSecret[i] = 'x';
                tempGuess[i] = 'y';
            }
        }

        // Проверка правильных цифр без учета позиции
        for (int i = 0; i < secretNumber.length(); ++i) {
            if (tempGuess[i] != 'y') {
                auto it = tempSecret.find(tempGuess[i]);
                if (it != std::string::npos) {
                    correctDigits++;
                    tempSecret[it] = 'x';
                }
            }
        }

        return GuessResult(correctDigits, correctPositions); // возвращает результат угаданных цифр и позиций
    }
};

// Генерация трехзначного числа
std::string generateNumber() {
    return std::to_string(100 + (rand() % 900)); // генерация числа от 100 до 999
}

// Основная функция программы
int main() {
    setlocale(LC_ALL, "Rus"); // установка русской локали

    srand(time(0)); // инициализация генератора случайных чисел

    // вступительный текст
    std::cout << "Вас приветствует игра 'Угадай число!'.\nСуть игры такова: программа задумывает трехзначное число\n" \
        "Вы вводите свое предположение\nПрограмма выводит два параметра:\nКоличество верно угаданных цифр и позиций, на которых эти числа расположены\n\n";
    std::cout << "Для выхода из игры введите 0.\n\n";

    std::string secretNumber = generateNumber(); // генерация секретного числа

    Player player(secretNumber); // создание игрока

    bool guessed = false; // флаг, который позволяет циклу while проводить итерации, до момента разгадки числа

    while (!guessed) {
        std::string guess;
        std::cout << "Введите ваше предположение: ";

        std::cin >> guess;

        if (guess == "0") { // завершение программы при вводе "0"
            std::cout << "\nИгра завершена!" << std::endl;
            return 0;
        }
        if (guess == "ans") {
            std::cout << secretNumber << std::endl; // вывод секретного числа для разгадывания
            continue; // переход к следующей итерации цикла
        }

        if (guess.length() != secretNumber.length()) {
            std::cout << "Длина числа должна быть равна " << secretNumber.length() << ". Попробуйте еще раз." << std::endl;
            continue; // переход к следующей итерации цикла

        }

        GuessResult result = player.guessNumber(guess); // выполнение догадки игрока
        std::cout << "Угадано цифр: " << result.correctDigits + result.correctPositions << ", правильных позиций: " << result.correctPositions << "\n\n";

        if (result.correctPositions == secretNumber.length()) { // проверка условия победы
            std::cout << "Поздравляем, число угадано!" << std::endl;
            guessed = true; // установка флага победы
        }
    }

    return 0; // завершение программы
}