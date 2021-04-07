#ifndef Editor_H
#define Editor_H

#include "LinkedList.h"
#include "Position.h"
#include <string>
#include <fstream>
#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

class Editor
{
public:
	Editor();//default constructor
	// takes input from the user 
	// takes the filename from the user
   //letting user to type lines and create a new file named by user
	Editor(string);
	//constructor which takes one string parameter
	~Editor(); // destructor

	void run();
	//get command from the user and processs it
// :q 
	void displaylines(); // displays the file
private:
	// to update the file and display on the console
	// x dd involved
	inline void update_display(Position);
	LinkedList <string> lines;
	string fName; // file name
};


#endif


