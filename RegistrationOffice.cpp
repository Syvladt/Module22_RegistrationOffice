// Не стал я разбивать на функции, т.к. разбивать особо нечего.

#include "RegistrationOffice.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

int main()
{	// Ключ - фамилия, а второй элемент - количество пациентов с такой же фамилией
	std::map<std::string, int> regOffice;
	std::map<std::string, int>::iterator pointer;
	std::string inStr = "";
	bool fail;
	// Начинаем с цикла, пока не будет введена команда bye или BYE или Bye или byE ...
	while(inStr != "BYE")
	{
		std::cout << "Enter LAST NAME or\nNEXT for erase first people or\nHELP or ? for help or\nBYE for exit from program: ";
		std::cin >> inStr;
		// Преобразуем введённую строку в строку строчных букв
		std::transform(inStr.begin(), inStr.end(), inStr.begin(), ::toupper);
		// Если введена команда bye - выход из программы
		if (inStr != "BYE")
		{	
			if (inStr == "HELP" or inStr == "?")
			{
				std::cout << "\x1B[2J\x1B[H";
				std::cout << "Your advertisement could be here.\nNext - erase fisrt people\n" << \
					"Help or ? - display help page\nBye - exit from program\n\n";
			}
			else
			{
				// Если введена команда next, то убираем первый элемент map.
				//  Но если второй элемент больше 1, то надо умен
				if (inStr == "NEXT")
				{
					// Проверка наличия элеменов в map
					if (regOffice.size() > 0)
					{	// Если людей с фамилией в начале списка больше одного, то вычитаем единицу
						if (regOffice.begin()->second > 1)
						{
							regOffice.begin()->second--;
							std::cout << "-> " << regOffice.begin()->first << '\n';
						}
						// Иначе удаляем человека из очереди
						else
						{
							std::cout << "-> " << regOffice.begin()->first << '\n';
							pointer = regOffice.begin();
							regOffice.erase(pointer);
						}
					}
					// Усли людей в очереди нет - выводит соответствующее сообщение
					else
						std::cout << "\nThe queue is empty!\n";
				}
				// Если введённый набор символов не является командой - значит это фамилия
				else
					// Если такая фамилия есть в map, то увеличиваем второй элемент на 1
					if (regOffice.count(inStr) > 0)
						regOffice[inStr]++;
					// Если в map данная фамилия не найдена, то проверяем на корректность ввода
					// В фамилии допускаются только буквы и тире, иначе выводится соответствующее сообщение
					else
					{
						do
						{
							fail = false;
							for (int i = 0; !fail && i < inStr.length(); ++i)
								if (!isalpha(inStr[i]) && inStr[i] != '-')
									fail = true;
							if (fail)
							{
								std::cout << "An incorrect LAST NAME was entered. Repeat, please.\n";
								std::cin >> inStr;
								std::transform(inStr.begin(), inStr.end(), inStr.begin(), ::toupper);
							}
						} while (fail);
						// После проверки фамилии записываем данные в map
						regOffice.insert({ inStr, 1 });
					}
				// Вывод текущего положения очереди
				for (pointer = regOffice.begin(); pointer != regOffice.end(); ++pointer)
				{
					if (pointer->second == 1)
						std::cout << "<- " << pointer->first << '\n';
					else
						for (int i = 0; i < pointer->second; ++i)
							std::cout << "<- " << pointer->first << '\n';
				}
			}
		}
	}
	std::cout << "\nThank you for use my program. Bye bye.\n";
	return 0;
}
