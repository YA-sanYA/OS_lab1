#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "employee.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Ошибка. Неверное количество аргументов\n";
		return 1;
	}

	std::string filename = argv[1];
	std::string titlename = argv[2];

	double salary = std::atof(argv[3]);
	if (salary <= 0) {
		std::cout << "Ошибка. Зарплата должна быть больше 0\n";
	}

	std::ifstream fin(filename, std::ios::binary);
	if (!fin.is_open()) {
		std::cout << "Ошибка. Файл " << filename << " не открылся\n";
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
		std::cout << "Ошибка. Файл " << titlename << " не открылся\n";
		return 1;
	}

	fout << "Отчёт по файлу\n";
	fout << "Номер сотрудника\tимя сотрудника\tчасы\tзарплата.\n";
	for (const auto& e : data) {
		fout << e.num << "\t" << e.name << "\t" << e.hours << "\t" << e.hours * salary << "\n";
	}

	fout.close();
	std::cout << "Файл " << titlename << " успешно создан\n";
	return 0;
}