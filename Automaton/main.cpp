//Questions : Keeping a file open for continued reading in a function//
// removing quotes from a string(when quotes automatically are placed)
// output to open window, such as notepad
// infinite loops, always bad?
// if so, how to continue checking for bottom line -- pause until inputFile.get() == 40(again)?

#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<ctime>
#include<time.h>
#include <sstream>
#include"SendKeys.h"
using namespace std;

//Global Variables
ifstream inputFile;			//File to recieve input from
string fileLoc;				//Holds the location of the input file
string myself;
int linesRead=0;			//Holds # of lines already read
HWND hwnd;

void skipString(int,string&);
void getCommand(string, string, string);
void checkForEnd(string&);

int main()
{
	string name;				//Name recieved from input file
	string windowName = "Shadowbane";
	string command;				//Command recieved from input file
	string stringHolder;			//Holds each string read for sizing purposes
	bool foundSelf = false;



	do{
	cout << "Please drag and drop the log file" << endl;
	cin.ignore();
	getline(cin,fileLoc);
	fileLoc.pop_back();
	inputFile.open(fileLoc.c_str());
	if(inputFile.fail())
		cout << "\nERROR LOADING FILE.\n" << endl;
	}while(!inputFile);

	cout << "Enter name of window to capture.  Leave blank for default\n(Default is \"Shadowbane\")" << endl;
	getline(cin, windowName);
	if(windowName == "")
	{
	windowName = "Shadowbane";
	}

	hwnd = FindWindow(NULL, windowName.c_str());
	while(!hwnd)
	{
		cout << "FAIL! Enter a different window name";
	getline(cin, windowName);
	hwnd = FindWindow(NULL, windowName.c_str());
	}


	cout << "Window capture success!" << endl;
	cout << "Rename Window for security (and multiboxing) purposes" << endl;
	getline(cin,windowName);
	if(windowName == "")
	{
	windowName = "Shadowbane";
	}
	SendMessage(hwnd,WM_SETTEXT,0, (LPARAM)windowName.c_str());

	hwnd = FindWindow(NULL, windowName.c_str());

	do
	{		
	checkForEnd(stringHolder);	//Tests to see if end of file is reached

	skipString(1,stringHolder);

	inputFile >> name;

	

	skipString(1,stringHolder);
	if(!foundSelf)
	{
	inputFile >> myself;
	myself.pop_back();
	foundSelf = true;
	}
	else
	{
	skipString(1,stringHolder);
	}
	

	inputFile >> command;
	getline(inputFile, stringHolder);

		if(name != "[Tell]" && name != myself)
	{
		time_t rawtime;
		time (&rawtime);

		cout << ctime (&rawtime)  << "Command received from " << name << endl;	
		getCommand(command, name, stringHolder);
	}
		  // Checks for valid command entry	
	linesRead++;

	checkForEnd(stringHolder);	//Tests to see if end of file is reached
	
	}while(inputFile.peek() == 40);
	
	cout << "Crash error: " << inputFile.get() << endl;
	
	inputFile.close();
		return 0;
}


void checkForEnd(string &stringHolder)
{
	while(inputFile.peek() == -1)
	{
		inputFile.close();
		inputFile.open(fileLoc.c_str());
	
		for(int i=0;i<linesRead;i++)
		{
			getline(inputFile, stringHolder);
		}
	}
}



void skipString(int skipNum, string &holder)
{
		for(int count = 0; count < skipNum; count++)
	{
	inputFile >> holder;
	}
}

void getCommand(string command, string name, string stringHolder)
{
	HWND AGC;
	HWND TPanel;
	HWND TPageControl;
	HWND TTabSheet;
	HWND TListView;
	HWND POPUP;
	CSendKeys sk;

	AGC = FindWindow(NULL, "AGC 5.0 beta 2.4");
	TPanel = FindWindowEx(AGC, NULL, "TPanel", NULL);
	TPageControl = FindWindowEx(TPanel, NULL, "TPageControl", NULL);
	TTabSheet = FindWindowEx(TPageControl, NULL, "TTabSheet", "Processes");
	TListView = FindWindowEx(TTabSheet, NULL, "TListView", NULL);

	if(command == "summon") //Command for summoning
{
	static clock_t cast;
	static bool isCasted=false;
		
	if(AGC)
	{
		ShowWindow(AGC,SW_MINIMIZE);
		ShowWindow(AGC,SW_MAXIMIZE);
		//Sleep(500);
		PostMessage(TListView,WM_RBUTTONDOWN,MK_RBUTTON,MAKELPARAM(50,50));
        PostMessage(TListView,WM_RBUTTONUP,MK_RBUTTON,MAKELPARAM(50,50));
		//Sleep(500);
		sk.SendKeys("P");
		ShowWindow(AGC,SW_MINIMIZE);
		Sleep(5000);
	}

	if((double(clock() - cast) / CLOCKS_PER_SEC) < 305 && isCasted == true)
	{
		int timerLeft = 305-(double(clock() - cast) / CLOCKS_PER_SEC);
		string cool = static_cast<ostringstream*>( &(ostringstream() << timerLeft) )->str();

		string cooldown = "/tell " + name + " " + cool + " seconds";
	
		SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);
		for(int i=0;i<cooldown.length();i++)
	{
		SendMessage(hwnd, WM_CHAR, cooldown[i],0);
	}
	SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);
	}
	else
	{
	string inc = "/tell " + name + " INC";
		SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);
		for(int i=0;i<inc.length();i++)
	{
		SendMessage(hwnd, WM_CHAR, inc[i],0);
	}
		SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);
	}


	SendMessage(hwnd, WM_KEYDOWN, VK_F9,1);
	for(int i=0;i<name.length();i++)
	{
		SendMessage(hwnd, WM_CHAR, name[i],0);
	}
	SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);

	if(AGC)
	{
		Sleep(7000);

		ShowWindow(AGC,SW_MAXIMIZE);
		//sk.AppActivate(AGC);	
		//Sleep(500);
		PostMessage(TListView,WM_RBUTTONDOWN,MK_RBUTTON,MAKELPARAM(50,50));
        PostMessage(TListView,WM_RBUTTONUP,MK_RBUTTON,MAKELPARAM(50,50));
		//Sleep(500);
		sk.SendKeys("T");
		ShowWindow(AGC,SW_MINIMIZE);
		Sleep(500);
	}

	cout << "Summoning " << name << endl << endl;
	if(!isCasted || double(clock() - cast) / CLOCKS_PER_SEC >= 305)
	{
	cast = clock();
	}
	isCasted = true;
}
	else if(command == "invite") //Command for inviting to group
{
	SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);
	string invite = "/invite ";

		for(int i=0;i<invite.length();i++)
	{
		SendMessage(hwnd, WM_CHAR, invite[i],0);
	}

	for(int i=0;i<name.length();i++)
	{
		SendMessage(hwnd, WM_CHAR, name[i],0);
	}
	SendMessage(hwnd, WM_KEYDOWN, VK_RETURN,0);

	cout << "Inviting " << name << " to group" << endl << endl;
}
else
	cout << "Unknown command " << command << stringHolder << endl << endl;
}