#include "Editor.h"

void placeCursorAt(Position coordinate) {
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Default constructor.
//Let user to create a new text file and named by user
Editor::Editor() {
	string line = "";	//line is using to restore all the key for one line that user enter
	int counter = 1;	//count current line
	char word;
	for (;;) {
		for (;;) {
			// get the key from the user
			word = _getch();
			switch (word) {
				// if the key user enter is EXC which is to exit insert mode
			case 27: {
				lines.insert(counter, line);
				counter++;
				run();
				break;
			}
				   // if the key user enter is Enter which means the line end
			case '\r': {
				cout << endl;
				lines.insert(counter, line);
				counter++;
				line = "";
				break;
			}
					 //if the key user enter is backspace
			case 8: {
				if (line.length() > 0) {
					string temp = "";
					for (int i = 0; i < line.length() - 1; i++) {
						temp += line[i];
					}
					line = temp;
					system("CLS");
					displaylines();
					cout << line;
					break;
				}
				//for anyotherkey we just display it and append it to line.
			default: {
				cout << word;
				line += word;
			}
			}
			}
		}
	}
}

Editor::Editor(string fileName) {
	// open the file that the user specifies
	ifstream inFile(fileName);
	string line;
	fName = fileName;
	int counter = 1;
	//check if the file open
	if (inFile.is_open()) {
		//file open
		//get all the lines in the file and store it to the linklist class
		while (!inFile.eof()) {
			getline(inFile, line);
			lines.insert(counter, line);
			counter++;
		}
		inFile.close();
	}
	else {
		//file cannot open
		cout << "Error,the file doesn't exist\n";
		exit(0);
	}
}

Editor::~Editor() {
}

void Editor::run() {
	char directive;
	Position Cursor(0, 0);
	placeCursorAt(Cursor);
	//get input from the user but doesn't show
	//no need to press enter for the user
	for (;;) {
		directive = _getch();
		switch (directive) {
		case ':': {
			//let the cursor at the bottom
			Cursor.setY(30);
			placeCursorAt(Cursor);
			cout << directive;
			//get input from the user and shows it to the console 
			// no need to press enter for the user
			directive = _getche();
			switch (directive) {
			case 'q':
				exit(0);
			case 'w': {
				cout << "\t";
				ofstream outFile;
				string fileName;
				getline(cin, fileName);
				fName = fileName;
				outFile.open(fileName);
				for (int i = 1; i <= lines.getLength(); i++) {
					if (i == lines.getLength())
						outFile << lines.getEntry(i);
					else
						outFile << lines.getEntry(i) << endl;
				}
				outFile.close();
				exit(1);
			}
			}
		case 'd': {
			directive = _getch();
			if (directive == 'd') {
				lines.remove(Cursor.getY() + 1);
				update_display(Cursor);
				break;
			}
		}
		case 'x': {
			string newLine = "";
			string oldLine = lines.getEntry(Cursor.getY()+1);
			for (int i = 1; i < oldLine.length(); i++) {
				newLine += lines.getEntry(Cursor.getY()+1)[i];
			}
			lines.replace(Cursor.getY()+1, newLine);
			update_display(Cursor);
			break;
		}
		}
		}
	}
}

void Editor::displaylines() {
	for (int i = 1; i <= lines.getLength(); i++) {
		cout << lines.getEntry(i) << endl;
	}
}

inline void Editor::update_display(Position Cursor){
	ofstream outFile(fName);
	//empty the file
	outFile.trunc;
	for (int i = 1; i <= lines.getLength(); i++) {
		if (i == lines.getLength())
			outFile << lines.getEntry(i);
		else
			outFile << lines.getEntry(i) << endl;
	}
	system("CLS");
	displaylines();
	placeCursorAt(Cursor);
	outFile.close();
}
