#include "game.h" // Подключение заголовочного файла с определениями классов и функций
#include <ctime> // Подключение библиотеки для работы с временем

// Определение конструктора класса GuessResult
GuessResult::GuessResult(int digits, int positions) : correctDigits(digits), correctPositions(positions) {}

// Определение конструктора класса Game, инициализирующего секретное число
Game::Game(std::string number) : secretNumber(number) {}

// Определение конструктора класса Player, наследующегося от Game
Player::Player(std::string number) : Game(number) {}

// Определение метода guessNumber класса Player для догадок игрока
GuessResult Player::guessNumber(std::string number) {
    int correctDigits = 0; // Переменная для количества правильно угаданных цифр
    int correctPositions = 0; // Переменная для количества цифр на своих местах

    std::string tempSecret = secretNumber; // Создание временной копии секретного числа
    std::string tempGuess = number; // Создание временной копии догадки игрока

    // Проверка угаданных цифр и позиций
    for (int i = 0; i < secretNumber.length(); ++i) {
        if (tempGuess[i] == tempSecret[i]) { // Если цифра угадана и находится на своем месте
            correctPositions++; // Увеличение счетчика цифр на своих местах
            tempSecret[i] = 'x'; // Помечаем цифру в секретном числе, чтобы исключить ее повторное угадывание
            tempGuess[i] = 'y'; // Помечаем цифру в догадке игрока, чтобы исключить ее повторное угадывание
        }
    }

    // Проверка правильных цифр без учета позиции
    for (int i = 0; i < secretNumber.length(); ++i) {
        if (tempGuess[i] != 'y') { // Если цифра в догадке игрока не была помечена
            auto it = tempSecret.find(tempGuess[i]); // Поиск цифры в секретном числе
            if (it != std::string::npos) { // Если цифра найдена
                correctDigits++; // Увеличение счетчика правильно угаданных цифр
                tempSecret[it] = 'x'; // Помечаем цифру в секретном числе, чтобы исключить ее повторное угадывание
            }
        }
    }

    // Возвращение результата угаданных цифр и позиций
    return GuessResult(correctDigits, correctPositions);
}

// Функция для генерации трехзначного числа
std::string generateNumber() {
    return std::to_string(100 + (rand() % 900)); // Генерация числа от 100 до 999
}

int main() {
    setlocale(LC_ALL, "Rus"); // Установка русской локали для корректного вывода на кириллице

    srand(time(0)); // Инициализация генератора случайных чисел на основе текущего времени

    // Вывод приветствия и правил игры
    std::cout << "Вас приветствует игра 'Угадай число!'.\nСуть игры такова: программа задумывает трехзначное число\n"
        << "Вы вводите свое предположение\nПрограмма выводит два параметра:\n"
        << "Количество верно угаданных цифр и позиций, на которых эти числа расположены\n\n";
    std::cout << "Для выхода из игры введите 0.\n\n";

    std::string secretNumber = generateNumber(); // Генерация секретного числа

    Player player(secretNumber); // Создание объекта игрока

    bool guessed = false; // Флаг, определяющий, угадано ли число

    while (!guessed) { // Основной цикл игры
        std::string guess; // Переменная для хранения догадки игрока
        std::cout << "Введите ваше предположение: ";

        std::cin >> guess; // Ввод догадки игрока

        if (guess == "0") { // Проверка на выход из игры
            std::cout << "\nИгра завершена!" << std::endl;
            return 0;
        }
        if (guess == "ans") { // Вывод секретного числа для проверки
            std::cout << secretNumber << std::endl;
            continue;
        }

        if (guess.length() != secretNumber.length()) { // Проверка длины догадки игрока
            std::cout << "Длина числа должна быть равна " << secretNumber.length() << ". Попробуйте еще раз." << std::endl;
            continue;
        }

        GuessResult result = player.guessNumber(guess); // Проверка догадки игрока
        // Вывод результатов догадки
        std::cout << "Угадано цифр: " << result.correctDigits + result.correctPositions << ", правильных позиций: " << result.correctPositions << "\n\n";

        if (result.correctPositions == secretNumber.length()) { // Проверка на угадывание числа
            std::cout << "Поздравляем, число угадано!" << std::endl;
            guessed = true; // Установка флага угадывания числа
        }
    }

    return 0; // Возврат из функции main
}