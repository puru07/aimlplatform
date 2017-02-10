#include "aimltools.h"

AIMLMap::AIMLMap() {
	path = "..\\files\\maps\\Map_default.txt";
	name = "Map_default.txt";
	map = nullptr;
}

AIMLMap::AIMLMap(string filename) {
	//Parse the name
	if (filename.substr(0, 2) != "..") {
		name = filename;
		path = "..\\files\\maps\\";
		path.append(filename);
	}
	else {
		path = filename;
		int cutPos = filename.find_last_of("\\");
		name = filename.substr(cutPos + 1, filename.length() - cutPos - 1);
	}
	cout << "Getting map [" << name << "] at directory [" << path << "]." << endl;
	row = 0;
	column = 0;
	map = nullptr;
}

AIMLMap::~AIMLMap() {
	if (map != nullptr) {
		delete[] map;
		map = nullptr;
	}
}

string AIMLMap::getName() {
	return name;
}

char *AIMLMap::getMap() {
	return map;
}

int AIMLMap::getRow() {
	return row;
}

int AIMLMap::getColumn() {
	return column;
}

void AIMLMap::putMap(int r, int c, char m[]) {
	if (strlen(m) != r * c) {
		cout << "Input size unmatched" << endl;
	}
	else {
		row = r;
		column = c;
		int l = r * c;
		if (map != nullptr) {
			delete[] map;
		}
		map = new char[l];
		for (int i = 0; i < l; i++) {
			map[i] = m[i];
		}
	}
}

int AIMLMap::readMAP(void) {
	//Try to open a file
	ifstream fileIn(path);
	if (!fileIn) {
		cout << "Failed to open that file." << endl;
		cout << "Check if file exists at that directory." << endl;
		row = 0;
		column = 0;
		map = nullptr;
		return 0;
	}
	else {
		cout << "Open file successfully!" << endl;
		string line;
		getline(fileIn, line);
		int spacePos = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line.at(i) == ' ') {
				spacePos = i;
				break;
			}
		}
		row = stoi(line.substr(0, spacePos));
		column = stoi(line.substr(spacePos + 1, line.length() - spacePos - 1));
		cout << "The map has [" << row << "] rows and [" << column << "] columns." << endl;
		map = new char[row * column];
		for (int i = 0; i < row; i++) {
			if (getline(fileIn, line)) {
				int l = line.length();
				for (int j = 0; j < column; j++) {
					if (j < l) {
						map[i * column + j] = line.at(j);
					}
				}
			}
		}
	}
	return 1;
}

void AIMLMap::writeName(string n) {
	int l = name.length();
	path = path.substr(0, path.length() - l);
	name = n;
	path.append(name);
}

void AIMLMap::writeToFile() {
	if (map == nullptr) {
		cout << "No map found!" << endl;
	}
	else {
		ofstream fileOut(path);
		if (!fileOut) {
			cout << "Unable to write new file." << endl;
		}
		else {
			fileOut << row << " " << column << "\n";
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < column; j++) {
					fileOut << map[i * column + j];
				}
				fileOut << "\n";
			}
			fileOut << "\n";
			fileOut << flush;
			fileOut.close();
		}
	}
}

void AIMLMap::display() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << map[i * column + j];
		}
		cout << endl;
	}
}

double AIMLMap::distance(int a1, int a2, int b1, int b2) {
	int d1 = a1 - b1;
	int d2 = a2 - b2;
	double sum = (double)d1 * d1 + (double)d2 * d2;
	return sqrt(sum);
}