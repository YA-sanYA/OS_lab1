#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Ошибка. Неверное количество аргументов\n";
        std::cout << "Использование: Creator <имя_файла> <количество_записей>\n";
        return 1;
    }

    std::string filename = argv[1];

    int recordCount = atoi(argv[2]);
    if (recordCount <= 0) {
        std::cout << "Ошибка. Количество записей должно быть больше 0\n";
        return 1;
    }

    std::ofstream fout(filename, std::ios::binary);
    if (!fout.is_open()) {
        std::cout << "Ошибка. Файл не открылся\n";
        return 1;
    }

    for (int i = 0; i < recordCount; i++) {
        employee empl;

        std::cout << "\nСотрудник #" << (i + 1) << std::endl;

        std::cout << "Введите идентификационный номер сотрудника: ";
        while (!(std::cin >> empl.num) || empl.num < 0) {
            std::cout << "Ошибка. Номер сотрудника должен быть неотрицательным числом\n";
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cout << "Попробуйте ещё раз: ";
        }

        std::cout << "Введите имя сотрудника (не более 9 символов): ";
        std::cin >> empl.name;
        while (strlen(empl.name) == 0 || strlen(empl.name) >= 10) {
            std::cout << "Ошибка. Имя сотрудника должно содержать от 1 до 9 символов\n";
            std::cout << "Попробуйте ещё раз: ";
            std::cin >> empl.name;
        }

        std::cout << "Введите количество отработанных часов сотрудника: ";
        while (!(std::cin >> empl.hours) || empl.hours < 0) {
            std::cout << "Ошибка. Количество часов должно быть неотрицательным числом\n";
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cout << "Попробуйте ещё раз: ";
        }

        fout.write(reinterpret_cast<char*>(&empl), sizeof(employee));
    }

    fout.close();
    std::cout << "\nФайл '" << filename << "' успешно создан.\n";

    return 0;
}
