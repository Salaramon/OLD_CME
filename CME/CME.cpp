// Console Map Engine v.0.1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <sstream>
#include <cmath>


int main()
{
	using namespace std;
	//Declearing & Inizialising Variables
	int nCount[12] = { 0 };
	int nWindowsizex = 48;
	int nWindowsizey = 24;
	int nWorldcoordx = 0;
	int nWorldcoordy = 0;
	char cMove = '@';
	int nPlayercoordx = nWindowsizex / 2;
	int nPlayercoordy = nWindowsizey / 2;
	string strMaplines[255];
	int nObjectx = 0;
	int nObjecty = 0;
	int nRoomx[10000] = { 0 };
	int nRoomy[10000] = { 0 };
	int nRAM = 100;								//Random Area Max
	int nRAN = -100;								//Random Area Min
	int nRanam = 5000;
	string saveLoc = "c:/CMA/saves/";
	string saveNam = "test";

	ofstream osCoordsx("testcoordsx");
	srand(5655);
	for (int nCount = 0; nCount != nRanam; nCount++) {
		osCoordsx << (rand() % (nRAM - nRAN + 1)) + nRAN << "\n";
	}
	osCoordsx.close();

	ofstream osCoordsy("testcoordsy");
	srand(5755);
	for (int nCount = 0; nCount != nRanam; nCount++) {
		osCoordsy << (rand() % (nRAM - nRAN + 1)) + nRAN << "\n";
	}
	osCoordsy.close();

	for (int nCount = 0; nCount != 10000; nCount++) {
		nRoomx[nCount] = (rand() % (nRAM - nRAN + 1)) + nRAN;
		nRoomy[nCount] = (rand() % (nRAM - nRAN + 1)) + nRAN;
	}
	//Declaring & Initializing Variables

start:
	//Creating Points
	cMove = _getch();
	if (cMove == 'w')
		--nPlayercoordy;
	if (cMove == 's')
		++nPlayercoordy;
	if (cMove == 'd')
		++nPlayercoordx;
	if (cMove == 'a')
		--nPlayercoordx;
	if (cMove == 'e') {
		string strbuff;
		string strtmp;
		int e;
		{
			ifstream ifMarkx("testcoordsx");
			ofstream ofMarkxt("testcoordsxt");
			while (!ifMarkx.eof()) {
				getline(ifMarkx, strtmp);
				strbuff += strtmp;
				strbuff += "\n";
			}
			stringstream tmp;
			tmp << nPlayercoordx + nWorldcoordx;
			tmp >> strtmp;
			strbuff += strtmp;
			strbuff += "\n";
			ofMarkxt << strbuff;
			ifMarkx.close();
			ofMarkxt.close();
			remove("testcoordsx");
			rename("testcoordsxt", "testcoordsx");
		}
		strbuff = "";
		strtmp = "";
		{
			ifstream ifMarky("testcoordsy");
			ofstream ofMarkyt("testcoordsyt");
			while (!ifMarky.eof()) {
				getline(ifMarky, strtmp);
				strbuff += strtmp;
				strbuff += "\n";
			}
			stringstream tmp;
			tmp << nPlayercoordy + nWorldcoordy;
			tmp >> strtmp;
			strbuff += strtmp;
			strbuff += "\n";
			ofMarkyt << strbuff;
			ifMarky.close();
			ofMarkyt.close();
			remove("testcoordsy");
			rename("testcoordsyt", "testcoordsy");
		}
	}

	if (nPlayercoordy >= nWindowsizey - (nWindowsizey / 5)) {
		--nPlayercoordy;
		++nWorldcoordy;
	}
	if (nPlayercoordy <= nWindowsizey / 5) {
		++nPlayercoordy;
		--nWorldcoordy;
	}
	if (nPlayercoordx >= nWindowsizex - (nWindowsizex / 5)) {
		--nPlayercoordx;
		++nWorldcoordx;
	}
	if (nPlayercoordx <= nWindowsizex / 5) {
		++nPlayercoordx;
		--nWorldcoordx;
	}

	system("CLS");
	//Creating Points

	//Create and Print
	do {
		do {
			strMaplines[nCount[1]] += " ";
			++nCount[2];
		} while (nCount[2] != nWindowsizex);
		++nCount[1];
		nCount[2] = 0;
	} while (nCount[1] != nWindowsizey);

	string line;
	ifstream isCoordsx("testcoordsx");
	ifstream isCoordsy("testcoordsy");
	if (isCoordsx.is_open() && isCoordsy.is_open()) {
		while (!isCoordsx.eof() && !isCoordsy.eof()) {
			getline(isCoordsx, line);
			nObjectx = atoi(line.c_str());
			getline(isCoordsy, line);
			nObjecty = atoi(line.c_str());
			for (int y = 0; y != nWindowsizey; y++) {
				for (int x = 0; x != nWindowsizex; x++) {
					if (y + nWorldcoordy == nObjecty && x + nWorldcoordx == nObjectx) {
						strMaplines[y].replace(x, 1, "T");
					}
				}
			}
		}
	}

	strMaplines[nPlayercoordy].replace(nPlayercoordx, 1, "+");

	for (int nCount = 0; nCount != nWindowsizey; nCount++)
		cout << strMaplines[nCount] << endl;
	//Create and Print

	//Reset Variables
	for (int nCount = 0; nCount != 255; nCount++)
		strMaplines[nCount] = "";
	nCount[1] = 0;
	nCount[2] = 0;
	nCount[3] = 0;
	nCount[4] = 0;
	nCount[5] = 0;
	nCount[6] = 0;

	cout << nPlayercoordx + nWorldcoordx << "-" << nPlayercoordy + nWorldcoordy << endl;
	cout << nWorldcoordx << "-" << nWorldcoordy << endl;
	//Reset Variables
	goto start;
	system("PAUSE");

	return 0;
}

