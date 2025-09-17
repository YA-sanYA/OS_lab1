#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <regex>
#include "employee.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	if (argc != 4) {
		std::cerr << "\nОшибка. Неверное количество аргументов\n";
		return 1;
	}

	std::string filename = argv[1];
	std::regex patternBin(R"(^[^\\/:*?"<>|]+\.[bB][iI][nN]$)");
	if (!std::regex_match(filename, patternBin)) {
		std::cerr << "Ошибка. Имя файла " << filename << " не корректно\n";
		return 1;
	}

	std::string titlename = argv[2];
	std::regex patternTxt(R"(^[^\\/:*?"<>|]+\.[tT][xX][tT]$)");
	if (!std::regex_match(titlename, patternTxt)) {
		std::cerr << "Ошибка. Имя файла " << titlename << " не корректно\n";
		return 1;
	}

	double salary = std::atof(argv[3]);
	if (salary <= 0) {
		std::cerr << "\nОшибка. Зарплата должна быть больше 0\n";
		return 1;
	}

	std::ifstream fin(filename, std::ios::binary);
	if (!fin.is_open()) {
		std::cerr << "\nОшибка. Не удалось открыть файл " << filename << " \n";
		return 1;
	}

	std::vector<employee> data;
	employee empl;
	while (fin.read(reinterpret_cast<char*>(&empl), sizeof(empl))) {
		data.push_back(empl);
	}
	fin.close();

	std::ofstream fout(titlename);
	if (!fout.is_open()) {
		std::cerr << "\nОшибка. Файл " << titlename << " не открылся\n";
		return 1;
	}

	fout << "Отчёт по файлу " << filename << ":\n";
	fout << std::left
		<< std::setw(20) << "Номер сотрудника"
		<< std::setw(20) << "Имя сотрудника"
		<< std::setw(10) << "Часы"
		<< std::setw(15) << "Зарплата"
		<< "\n";
	for (const auto& e : data) {
		fout << std::left
			<< std::setw(20) << e.num
			<< std::setw(20) << e.name
			<< std::setw(10) << e.hours
			<< std::setw(15) << e.hours * salary
			<< "\n";
	}

	fout.close();

	std::cout << "\nФайл " << titlename << " успешно создан\n";
	return 0;
}