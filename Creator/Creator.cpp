#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <regex>
#include "employee.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc != 3) {
        std::cerr << "\nОшибка. Неверное количество аргументов\n";
        std::cerr << "Использование: Creator <имя_файла> <количество_записей>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::regex pattern(R"(^[^\\/:*?"<>|]+\.[bB][iI][nN]$)");
    if (!std::regex_match(filename, pattern)) {
        std::cerr << "Ошибка. Имя файла " << filename << " не корректно\n";
        return 1;
    }

    int recordCount = atoi(argv[2]);
    if (recordCount <= 0) {
        std::cerr << "\nОшибка. Количество записей должно быть числом больше 0\n";
        return 1;
    }

    std::ofstream fout(filename, std::ios::binary);
    if (!fout.is_open()) {
        std::cerr << "\nОшибка. Не удалось открыть файл " << filename << "\n";
        return 1;
    }

    for (int i = 0; i < recordCount; i++) {
        employee empl;

        std::cout << "\nСотрудник #" << (i + 1) << "\n";

        std::cout << "Введите идентификационный номер сотрудника: ";
        while (!(std::cin >> empl.num) || empl.num < 0) {
            std::cerr << "Ошибка. Номер сотрудника должен быть неотрицательным числом\n";
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cerr << "Попробуйте ещё раз: ";
        }

        std::cout << "Введите имя сотрудника (не более 9 символов): ";
        std::cin >> empl.name;
        while (strlen(empl.name) == 0 || strlen(empl.name) >= 10) {
            std::cerr << "Ошибка. Имя сотрудника должно содержать от 1 до 9 символов\n";
            std::cerr << "Попробуйте ещё раз: ";
            std::cin >> empl.name;
        }

        std::cout << "Введите количество отработанных часов сотрудника: ";
        while (!(std::cin >> empl.hours) || empl.hours < 0) {
            std::cerr << "Ошибка. Количество часов должно быть неотрицательным числом\n";
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cerr << "Попробуйте ещё раз: ";
        }

        fout.write(reinterpret_cast<char*>(&empl), sizeof(employee));
    }

    fout.close();

    std::cout << "\nФайл " << filename << " успешно создан.\n";
    return 0;
}
