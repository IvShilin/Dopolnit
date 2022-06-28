#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip> 
#include <fstream> 
#include <regex>   
#include "windows.h"
using namespace std;


const int MAX_LEN = 100;
//Перечен регулярных выражений для сравнения с ними считанных данных
const regex r_time("([0-1][0-9]|2[0-3])\\:([0-5][0-9])");
const regex b_number("\301\\-([0-9]{3,4})");
const regex time_InTheAir("-[0-9]{1,10}");
const regex r_flightNumber("(РЕЙС[0-9]{1,4})");


//Основные структуры, считываемые из файла
struct Words
{
	char* time;
	char* model;
	char* planeNumber;
	char* flight;
};

//Структуры для сортировки данных
struct Index {
	int id;
	char* F_Number;
	char* departure;
};


//Функция печати таблицы
void Print_table(Index* IndexStrs, Words* ROW, const int N_struct);
//Функция дополнительной проверки и считывание данных из файла
int FileReadWords(const char* FNAME, Words* ROW, const int N_lines, int& N_struct);
//Функция для вывода количества строк в файле и основных проверок самого файла
int Out_File_Lines(const char* FNAME);

void Sort(Index* IndexStrs, const int N_struct);