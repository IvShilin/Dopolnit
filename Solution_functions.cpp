
#include "Header.h"
//Функция вывода таблицы
void Print_table(Index* IndexStrs, Words* ROW, const int N_struct) {

	const char VerticalLine = (char)186;		//"║" - ВЕРТИКАЛЬНАЯ ЛИНИЯ
	const char HorizontalLine = (char)205;		//"═" - ГОРИЗОНТАЛЬНАЯ ЛИНИЯ
	const char TopLeftCorner = (char)201;		//"╔" - ЛЕВЫЙ ВЕРХНИЙ УГОЛ
	const char TopRightCorner = (char)187;		//"╗" - ПРАВЫЙ ВЕРХНИЙ УГОЛ
	const char BottomLeftCorner = (char)200;	//"╚" - ЛЕВЫЙ НИЖНИЙ УГОЛ
	const char BottomRightCorner = (char)188;	//"╝" - ПРАВЫЙ НИЖНИЙ УГОЛ
	const char LeftJunction = (char)185;		//"╣" - ПОВОРОТ ВЛЕВО
	const char RightJunction = (char)204;		//"╠" - ПОВОРОТ ВПРАВО
	const char BottomJunction = (char)203;		//"╦" - ПОВОРОТ ВНИЗ
	const char TopJunction = (char)202;			//"╩" - ПОВОРОТ ВВЕРХ
	const char CrossJunction = (char)206;		//"╬" - ПЕРЕКРЕСТОК
	const char Space = (char)32;
	

	//Задание верхней границы таблицы
	setlocale(LC_ALL, "C");
	cout << "\t" << TopLeftCorner << setfill(HorizontalLine) << setw(20)
		 << BottomJunction << setw(20) << BottomJunction
		 << setw(20) << BottomJunction << setw(20) << TopRightCorner << endl;
	//Задание шапки таблицы
	cout << "\t" << VerticalLine << setfill(Space)
		 << setw(19) << right << "Aircraft brand" << VerticalLine
		 << setw(19) << right << "Board number" << VerticalLine
		 << setw(19) << right << "Flight number" << VerticalLine
		 << setw(19) << right << "Boarding time" << VerticalLine << endl;

	//вывод основной части таблицы
	int i = 0;
	while (i < N_struct) {
		cout << "\t" << RightJunction << setfill(HorizontalLine)
			 << setw(20) << CrossJunction << setw(20)
			 << CrossJunction << setw(20) << CrossJunction << setw(20)
			 << LeftJunction << endl;

		cout << "\t" << VerticalLine << setfill(Space) << setw(19)
			 << right;
		setlocale(LC_ALL, "ru");
		cout << ROW[IndexStrs[i].id].model;
		setlocale(LC_ALL, "C");
		cout << VerticalLine << setw(19) << right;
		setlocale(LC_ALL, "ru");
		cout << ROW[IndexStrs[i].id].planeNumber;
		setlocale(LC_ALL, "C");
		cout << VerticalLine << setw(19) << right;
		setlocale(LC_ALL, "ru");
		cout << ROW[IndexStrs[i].id].flight;
		setlocale(LC_ALL, "C");
		cout << VerticalLine << setw(19) << right;
		setlocale(LC_ALL, "ru");
		cout << ROW[IndexStrs[i].id].time;
		setlocale(LC_ALL, "C");
		cout << VerticalLine << endl;
		
		i++;
	}
	//Вывод конца таблицы
	cout << "\t" << BottomLeftCorner << setfill(HorizontalLine)
		 << setw(20) << TopJunction << setw(20) << TopJunction
		 << setw(20) << TopJunction << setw(20)
		 << BottomRightCorner << endl;

}

//Функция дополнительной проверки и считывание данных из файла
int FileReadWords(const char* FNAME, Words* ROW, const int N_lines, int& N_struct) {

	int i = 0;   						// Кол-во прочитанных строк
	char* buff = new char[MAX_LEN];		// Буферная строка
	char* temp1 = new char[10];   		// Первый столбец
	char* temp2 = new char[10];   		// Второй столбец
	char* temp3 = new char[10];   		// Третий столбец
	char* temp4 = new char[10];   		// Четвертый столбец
	char* temp5 = new char[10];			// Столбец ошибочных данных
	int column = 0;   					// Кол-во считанных столбцов
	int* Error_Lines = new int[N_lines];// Вектор ошибок, для учёта ошибок на каждой из строк

	ifstream fin(FNAME);	//Подключение файла с неотсортированными данными
	while (!fin.eof() && i < N_lines) {
		Error_Lines[i] = 0;
		fin.getline(buff, MAX_LEN);	//Считываем строку из файла
		cout << "\nСтрока " << i + 1 << ":\t" << buff;
		//Если длина строки меньше 2 (2 так как в любой строке содержатся уравляющие символы)
		if (strlen(buff) < 2) {
			Error_Lines[i] = 1;
			i++;
			continue;
		}
		//Проверка на количество стоблцов, а дальше проверка на остальные причины
		column = sscanf(buff, "%s %s %s %s %s", temp1, temp2, temp3, temp4, temp5);
		if (column < 4) {
			Error_Lines[i] = 2;
			i++;
			continue;
		}




		//Сравние данных в переменной temp4 с регулярным выражением для времени
		if (!regex_match(temp4, r_time)) {
			if (regex_match(temp4, time_InTheAir)) {
				cout << "\033[36m\tСамолёт в воздухе!\033[0m";
			}
			else
				//Сравние данных в переменной temp2 с регулярным выражением для бортового номера
				if (!regex_match(temp2, b_number)) {
					if (!regex_match(temp3, r_flightNumber)) {
						Error_Lines[i] = 7;
						i++;
						continue;
					}
					else {
						Error_Lines[i] = 10;
						i++;
						continue;
					}
				}
				else //* Проверка на номер рейса
					if (!regex_match(temp3, r_flightNumber)) {
						if (!regex_match(temp2, b_number)) {
							Error_Lines[i] = 7;
							i++;
							continue;
						}
						else {
							Error_Lines[i] = 9;
							i++;
							continue;
						}
					}
				
				else {
					Error_Lines[i] = 3;
					i++;
					continue;
				}
				
		}

		//Сравние данных в переменной temp2 с регулярным выражением для бортового номера
		if (!regex_match(temp2, b_number)) {
			if (!regex_match(temp3, r_flightNumber)) {
				Error_Lines[i] = 8;
				i++;
				continue;
			}
				Error_Lines[i] = 4;
				i++;
				continue;

		}


		// Проверка на номер рейса
		if (!regex_match(temp3, r_flightNumber)) {
			if (!regex_match(temp2, b_number)) {
				Error_Lines[i] = 8;
				i++;
				continue;
			}
			else {
				Error_Lines[i] = 6;
				i++;
				continue;
			}
		}

		

		if (column > 4) {
			cout << "\n\033[31m" << __func__ << "():\033[0m" << " В строке " << i + 1 << " содержатся лишние данные.";
		}
		//Выделение памяти под структуры и занесение в них информации
		if (Error_Lines[i] == 0) {
			ROW -> model = new char[strlen(temp1)];
			ROW -> planeNumber = new char[strlen(temp2)];
			ROW -> flight = new char[strlen(temp3)];
			ROW -> time = new char[strlen(temp4) + 1];

			strcpy(ROW->model, temp1);
			strcpy(ROW->planeNumber, temp2);
			strcpy(ROW->flight, temp3);
			strcpy(ROW->time, temp4);

			ROW++;
			N_struct++;
		}
		i++;
	}
	cout << endl;
	if (N_struct < N_lines) {
		if (N_struct == 0) {
			cout << "\n\033[31mФатальная ошибка! не было найдено ни одной структуры!\033[0m";
			return 1;
		}
		else {
			cout << "\n\033[31m" << __func__ << "():\033[0m" << " Файл прочитан с ошибками.\nОшибки:";
			for (int i = 0; i < N_lines; i++)
				if (Error_Lines[i] != 0) {
					int error_type = Error_Lines[i];
					switch (error_type) {
					case 1:
						cout << "\nСтрока " << i + 1 << ": Данные в строке введены некорректно! (длина строки меньше двух символов)";
						break;
					case 2:
						cout << "\nСтрока " << i + 1 << ": Неверное количество введёных столбцов!";
						break;
					case 3:
						cout << "\nСтрока " << i + 1 << ": Неверный формат времени!";
						break;
					case 4:
						cout << "\nСтрока " << i + 1 << ": Неверно введён бортовой номер!";
						break;
					case 5:
						cout << "\nСтрока " << i + 1 << ": Неверно введён бортовой номер и время!";
						break;
					case 6:
						cout << "\nСтрока " << i + 1 << ": Нверно введён номер рейса!";
						break;
					case 7:
						cout << "\nСтрока " << i + 1 << ": Нверно введён номер рейса, бортовой номер и время!";
						break;
					case 8:
						cout << "\nСтрока " << i + 1 << ": Нверно введён номер рейса и боротовой номер!";
						break;
					case 9:
						cout << "\nСтрока " << i + 1 << ": Нверно введён номер рейса и время!";
						break;
					case 10:
						cout << "\nСтрока " << i + 1 << ": Нверно введён бортовой номер и время!";
					default:
						break;
					}
				}
		}

		cout << "\n\n\n";
	}
	else
		cout << "\n\033[32m\tФайл прочитан без ошибок.\033[0m\n";

	fin.close();
	delete[] temp1;
	delete[] temp2;
	delete[] temp3;
	delete[] temp4;
	delete[] buff;
	delete[] Error_Lines;
	return 0;
}

//Функция сортировки данных
void Sort(Index* IndexStrs, const int N_struct){
	int counter = 0; //Число самолётов в воздухе
	if (N_struct > 1) // Сортируем только если в массиве есть хотя бы 2 элемента
	{
		//Перемещаем все рейсы с отрицательным временем ближе к 0 индексу
		for (int i = 0; i < N_struct - 1; i++)
			for (int j = i + 1; j < N_struct; j++)
				//Сравнение элементов и подсчёт числа рейсов с отрицательным временем
				if (regex_match(IndexStrs[j].departure, time_InTheAir)) {
					swap(IndexStrs[j], IndexStrs[i]);
					counter++;
					break;
				}
		//Сортировка рейсов с отрицательным временем (Сортировка по номеру рейса - по убыванию)
		for (int i = 0; i < counter - 1; i++) {
			for (int j = i + 1; j < counter; j++) {
				if (strcmp(IndexStrs[i].F_Number, IndexStrs[j].F_Number) < 0) {
					swap(IndexStrs[j], IndexStrs[i]);
				}
			}

		}
		//Сортировка остальных рейсов по времени (по возрастанию)
		for (int i = counter; i < N_struct - 1; i++) {
			for (int j = i + 1; j < N_struct; j++) {
				if (strcmp(IndexStrs[i].departure, IndexStrs[j].departure) > 0)
					swap(IndexStrs[j], IndexStrs[i]);
			}
		}

	}
}

//Функция для вывода количества строк в файле и основных проверок самого файла
int Out_File_Lines(const char* FNAME)
{
	char c[MAX_LEN]; //Массив временного хранения данных
	int count = 0;	 //Счётчик строк
	ifstream file(FNAME);
	if (!file.is_open()) // Проверка удалось ли открыть файл
	{
		cout << "\033[31m" << __func__ << "():\033[0m" << " Не удалось открыть файл \"" << FNAME << "\"" << endl;
		return -1;
	}
	else {
		if (file.peek() == EOF) // Проверка на пустой файл
		{
			cout << "Файл \"" << FNAME << "\" пуст." << endl;
			file.close();
			return 0;
		}
		else {
			//Пока не конец файла, стичываем сроки и подсчитываем их количество
			while (file.peek() != EOF) {
				file.getline(c, MAX_LEN);
				++count;
			}
			file.close();
			return count;
		}
	}
}