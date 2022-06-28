/**********************************************************************************************
*                                       Курс ИНФОРМАТИКА                                      *
***********************************************************************************************
*Project type :Win64 Console Application                                                      *
*Project name :Dop                                                                            *
*File name    :Dop.exe                                                                        *
*Language     :CPP, CLION                                                                     *
*Programmers  :Папуашвили Георгий Давидович Шилини Иван Алексеевич, М3О-110Б-21               *
*Modified By  :                                                                               *
*Created      :9.05.2022                                                                      *
*Last revision:26.05.2022                                                                     *
*Comment      :Дополнительное задание                                                         *
**********************************************************************************************/

#include "Header.h"

// char* FNAME = "test1.txt";
//const char* FNAME = "test2.txt";
//const char* FNAME = "test3.txt";
//const char* FNAME = "test4.txt";
//const char* FNAME = "test5.txt";
//const char* FNAME = "test6.txt";
//const char* FNAME = "test7.txt";
//const char* FNAME = "test8.txt";
//const char* FNAME = "test9.txt";
const char* FNAME = "test.txt";

int main() {

	Words* Vec = new Words[12];				//Вектор основых структур
	int N_struct = 0;						//Кол-во считанных строк
	setlocale(LC_ALL, "ru");
	//Проверка файла на весомые ошибки и считывание количества строк
	int N_lines = Out_File_Lines(FNAME);

	if (N_lines > 0) {
		cout << "Результат чтения файла:\n";
		//Проверка файла на доп. ошибки и считывание данных
		int fatal_file_error = FileReadWords(FNAME, Vec, N_lines, N_struct);
		if (fatal_file_error == 0) {
			//Выделение памяти под массив
			Index* IndexStrs = new Index[N_struct];
			for (int i = 0; i < N_struct; i++)
			{
				IndexStrs[i].id = i;
				IndexStrs[i].departure = Vec[i].time;
				IndexStrs[i].F_Number = Vec[i].flight;
			}

			Sort(IndexStrs, N_struct);

			//печать данных в виде таблицы
			Print_table(IndexStrs, Vec, N_struct);

			
		}
	}
}