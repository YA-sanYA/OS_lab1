#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "employee.h"

bool runProcess(LPWSTR cmdLine, DWORD& exitCode) {
    STARTUPINFO si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    if (!CreateProcess(
        NULL,
        cmdLine,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        std::cerr << "Ошибка запуска процесса: " << GetLastError() << "\n";
        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cerr << "Ошибка. Не удалось получить код возврата процесса\n";
        exitCode = -1;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

void printBinaryFile(std::wstring filename) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin.is_open()) {
        std::cerr << "Ошибка. Не удалось открыть бинарный файл.\n";
        return;
    }

    std::cout << "\nСодержимое бинарного файла:\n";
    employee empl;
    while (fin.read(reinterpret_cast<char*>(&empl), sizeof(empl))) {
        std::cout << "ID: " << empl.num;
        std::cout << ", Имя: " << empl.name;
        std::cout << ", Отработанные часы: " << empl.hours << "\n";
    }
    std::cout << "\n";

    fin.close();
}

void printTextFile(std::wstring filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Ошибка. Не удалось открыть текстовый файл.\n";
        return;
    }

    std::cout << "\nСодержимое текстового файла:\n";
    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << "\n";
    }
    std::cout << "\n";

    fin.close();
}

int main() {
    setlocale(LC_ALL, "Russian");

    DWORD code;
    std::wstring binaryFile;
    int count;

    std::cout << "Введите имя бинарного файла: ";
    std::wcin >> binaryFile;

    std::cout << "Введите количество записей: ";
    std::cin >> count;

    std::wstring creatorCommand = L"Creator.exe " + binaryFile + L" " + std::to_wstring(count);
    if (!runProcess(&creatorCommand[0], code)) {
        return 1;
    }
    if (code) {
        std::cerr << "\nCreator завершился с ошибкой! Код: " << code << "\n";
        return 1;
    }

    printBinaryFile(binaryFile);

    std::wstring reportFile;
    double salary;

    std::cout << "Введите имя файла отчёта: ";
    std::wcin >> reportFile;

    std::cout << "Введите оплату за час: ";
    std::cin >> salary;

    std::wstring reporterCommand = L"Reporter.exe " + binaryFile + L" " + reportFile + L" " + std::to_wstring(salary);
    if (!runProcess(&reporterCommand[0], code)) {
        return 1;
    }
    if (code) {
        std::cerr << "\nReporter завершился с ошибкой! Код: " << code << "\n";
        return 1;
    }

    printTextFile(reportFile);

    std::cout << "Работа завершена";
}
