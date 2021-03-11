// Lecture7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <vector> 
#include <fstream>

using namespace std;	//function prototyping 
string nameio(int);
string popio();
string mayorio();
void cityinput(map<string, vector<string>>);
int checkformore(map<string,vector<string>>);
void cityfileinput(map<string, vector<string>>);
void cityprint();

vector<string> make_vector(string a, string b) { //custom method for vector class 
	vector<string> v;
	v.push_back(a);
	v.push_back(b);
	return v;
}

int main()
{
	map<string, vector<string>> dataMap;	//driver functions. creates map and calls the required functions to write and print 
	cityinput(dataMap);
	cityprint();
	return 0;
}

string nameio(int citycount)	//helper function that takes input for city name 
{
	string output;

	if (citycount == 0)
	{
		cout << "Please Input the City name you would like to use: ";
		cin >> output;

		return output;
	}
	else
	{
		cout << "Please input the next city name you would like to use: ";
		cin >> output;

		return output;
	}
}

string popio()	//helper function that takes input for city population 
{
	string output;

	cout << "Please Input the population for this city: ";
	cin >> output;

	return output;

}

string mayorio()	// helper function that takes input for the city mayor
{
	string output;
	cout << "Please input the major who runs this city: ";
	cin >> output;

	return output;
}

void cityinput(map<string, vector<string>> dataMap)	//driver function that takes input for city name, populations, and mayor, then checks if the user will put in additional cities
{
	
	int citycount = 0;
	int init = 0;
	while (init == 0)
	{
		string cityname;
		string citypop;
		string citymayor;
		cityname = nameio(citycount);
		citypop = popio();
		citymayor = mayorio();

		dataMap.insert(pair<string, vector<string>>(cityname, make_vector(citypop, citymayor)));

		init = checkformore(dataMap);
	}
}

int checkformore(map<string, vector<string>> dataMap) //helper function calls additional functions, including a call for the driver function to add an unlimited amount of cities, whatever the user desires. 
{
	cout << "Would you like to add another city? ";
	string answer;
	cin >> answer;
	if (answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("YES") == 0)
	{
		cityinput(dataMap);
	}
	else if (answer.compare("no") == 0 || answer.compare("No") == 0 || answer.compare("NO") == 0)
	{
		cityfileinput(dataMap);
		return 1;
	}
	else
	{
		cout << "Please use 'YES' or 'NO'" << "\n";
		checkformore(dataMap);
	}
	return 1;
}

void cityfileinput(map<string, vector<string>> dataMap) //takes the data input from the user and inputs it into file in alphabetical order
{
	ofstream output;
	output.open("cities.txt");
	for (auto it = dataMap.begin(); it != dataMap.end(); ++it)
	{
		vector<string> v = it->second;
		output << it->first << '\t' << v.front() << '\t' << v.back() << endl;
	}
	output.close();
}

void cityprint() //takes data from a file and prints it onto the screen 
{
	ifstream inFile;
	inFile.open("cities.txt");
	string s; 
	while (!inFile.eof())
	{
		getline(inFile, s);
		cout << s << "\n";
	}
}
