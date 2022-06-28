#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip> 
#include <fstream> 
#include <regex>   
#include "windows.h"
using namespace std;


const int MAX_LEN = 100;
//������� ���������� ��������� ��� ��������� � ���� ��������� ������
const regex r_time("([0-1][0-9]|2[0-3])\\:([0-5][0-9])");
const regex b_number("\301\\-([0-9]{3,4})");
const regex time_InTheAir("-[0-9]{1,10}");
const regex r_flightNumber("(����[0-9]{1,4})");


//�������� ���������, ����������� �� �����
struct Words
{
	char* time;
	char* model;
	char* planeNumber;
	char* flight;
};

//��������� ��� ���������� ������
struct Index {
	int id;
	char* F_Number;
	char* departure;
};


//������� ������ �������
void Print_table(Index* IndexStrs, Words* ROW, const int N_struct);
//������� �������������� �������� � ���������� ������ �� �����
int FileReadWords(const char* FNAME, Words* ROW, const int N_lines, int& N_struct);
//������� ��� ������ ���������� ����� � ����� � �������� �������� ������ �����
int Out_File_Lines(const char* FNAME);

void Sort(Index* IndexStrs, const int N_struct);