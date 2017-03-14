/*
Eric Wolfe
Dr. Yu
CS 490 - Data Mining
ID3 Program
 */

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const int rSIZE = 11;
const int wSIZE = 14;
const int cSIZE = 24;

struct contact
{
	string age; // age {young, pre-presbyopic, presbyopic}
	string spec; //spectacle-prescrip {myope, hypermetrope}
	string ast; //astigmatism {no, yes}
	string tear; //tear-prod-rate {reduced, normal}
	string lense;  //contact-lenses {soft, hard, none}
};

struct weather
{
	string outlook; //outlook {sunny, overcast, rainy}
	string temp; //temperature {hot, mild, cool}
	string hum; //humidity {high, normal}
	string windy; //windy {TRUE, FALSE}
	string play; //play {yes, no}
};

struct restaurant
{
	string alt; //{Yes, No}
	string bar; //{Yes, No}
	string fri; //{Yes, No}
	string hun; //{Yes, No}
	string pat; //{Some, Full, None}
	string price; //{$, $$, $$$}
	string rain; //{Yes, No}
	string res; //{Yes, No}
	string type; //{French, Thai, Burger, Italian}
	string est; //{0-10, 10-30, 30-60, >60}
	string wait; //{Yes, No}
};

string getInput(string &line)
{
	string substring = line.substr(0, line.find(","));
	line.erase(0, line.find(",") + 1);
	return substring;
}

double getEntropy(int size, int num1, num2)
{
    return 
}

int main()
{
	cout << "Please enter name of the data file: \t";
	string fileName = "";
	cin >> fileName;

	ifstream fileInput;
	fileInput.open(fileName);

	if (fileName == "restaurant.arff")
	{
		string restaurants[rSIZE][rSIZE];
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < rSIZE; i++)
		{
			string line;
			fileInput >> line;
      for (int j = 0; j < rSIZE; j++)
      {
        restaurants[i][j] = getInput(line);
      }
		}
	}
	else if (fileName == "weather.nominal.arff")
	{
		string weathers[wSIZE][wSIZE];
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < wSIZE; i++)
		{
			string line;
			fileInput >> line;
			for (int j = 0; j < wSIZE; j++)
      {
        weathers[i][j] = getInput(line);
      }
		}
	}
	else if (fileName == "contact-lenses.arff")
	{
		string contacts[cSIZE][cSIZE];
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < cSIZE; i++)
		{
			string line;
			fileInput >> line;
			for (int j = 0; j < cSIZE; j++)
      {
        contacts[i][j] = getInput(line);
      }
		}
	}
	else
	{
		cout << "\nFile does not exist";
	}

	return 0;
}
