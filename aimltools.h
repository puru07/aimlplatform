#ifndef AIMLTOOLS_H_INCLUDED
#define AIMLTOOLS_H_INCLUDED

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <math.h>

using namespace std;

class AIMLMap {
protected:
	string name;
	string path;
	int row;
	int column;
	char *map;
public:
	AIMLMap();
	AIMLMap(string filename);
	~AIMLMap();

	string getName();
	char *getMap();
	int getRow();
	int getColumn();

	void putMap(int r, int c, char m[]);

	int readMAP(void);
	void writeName(string n);
	void writeToFile();

	void display();

	double distance(int a1, int a2, int b1, int b2);
};

#endif