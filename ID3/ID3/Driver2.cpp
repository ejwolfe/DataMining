///*
//Eric Wolfe
//Dr. Yu
//CS 490 - Data Mining
//ID3 Program
// */
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <math.h>
//
//using namespace std;
//
//const int rSIZE = 11;
//const int wSIZE = 14;
//const int cSIZE = 24;
//
//struct node
//{
//	string label;
//	string decision;
//	node* addBranch;
//};
//
//struct sub
//{
//	int count = 0;
//	int yes = 0;
//	int no = 0;
//};
//
//struct examples
//{
//	int SIZE = 0;
//	string *list;
//};
//
//string outlook[3] = { "sunny", "overcast", "rainy" };
//string temperature[3] = { "hot", "mild", "cool" };
//string humidity[2] = { "high", "normal" };
//string windy[2] = { "TRUE", "FALSE" };
//string play[2] = { "yes", "no" };
//
//string getInput(string &line)
//{
//	string substring = line.substr(0, line.find(","));
//	line.erase(0, line.find(",") + 1);
//	return substring;
//}
//
//double getEntropyOfSet(int size, int num1, int num2)
//{
//	return - ((num1 / size) * log2(num1 / size)) - ((num2 / size) * log2(num2 / size));
//}
//
//double getEntropy(sub sub1)
//{
//	return - ((sub1.yes / sub1.count) * log2(sub1.yes / sub1.count)) - ((sub1.no / sub1.count) * log2(sub1.no / sub1.count));
//}
//
//sub getSubset(string weathers[][wSIZE], int attribute, string value)
//{
//	sub sub1;
//	for (int j = 0; j < wSIZE; j++)
//	{
//		if (weathers[attribute][j] == value)
//		{
//			sub1.count++;
//			if (weathers[wSIZE-1][j] == "yes")
//			{
//				sub1.yes++;
//			}
//			else
//			{
//				sub1.no++;
//			}
//		}
//	}
//}
//
//double infoGain(string weathers[][wSIZE], int attribute)
//{
//	int yes = 0, no = 0;
//	for (int j = 0; j < wSIZE; j++)
//	{
//		if (weathers[wSIZE-1][j] == "yes")
//		{
//			yes++;
//		}
//		else
//		{
//			no++;
//		}
//	}
//	double gain = getEntropyOfSet(wSIZE, yes, no);
//	switch (attribute)
//	{
//	case (0): 
//		for (string value : outlook)
//		{
//			sub sub1 = getSubset(weathers, attribute, value);
//			gain -= (sub1.count) / (wSIZE)* getEntropy(sub1);
//		}
//		break;
//	case (1):
//		for (string value : temperature)
//		{
//			sub sub1 = getSubset(weathers, attribute, value);
//			gain -= (sub1.count) / (wSIZE)* getEntropy(sub1);
//		}
//		break;
//	case (2):
//		for (string value : humidity)
//		{
//			sub sub1 = getSubset(weathers, attribute, value);
//			gain -= (sub1.count) / (wSIZE)* getEntropy(sub1);
//		}
//		break;
//	case (3):
//		for (string value : windy)
//		{
//			sub sub1 = getSubset(weathers, attribute, value);
//			gain -= (sub1.count) / (wSIZE)* getEntropy(sub1);
//		}
//		break;
//	default:
//		cout << endl << "You messed up";
//	}
//
//	return gain;
//}
//
//void id3 (string weathers[][wSIZE])
//{
//	sub sub1;
//	sub1.count = wSIZE - 1;
//}
//
//int main()
//{
//	cout << "Please enter name of the data file: \t";
//	string fileName = "";
//	cin >> fileName;
//
//	ifstream fileInput;
//	fileInput.open(fileName);
//
//	if (fileName == "restaurant.arff")
//	{
//		string restaurants[rSIZE][rSIZE];
//		string temp = "";
//		while (temp != "@data")
//		{
//			fileInput >> temp;
//		}
//		for (int i = 0; i < rSIZE; i++)
//		{
//			string line;
//			fileInput >> line;
//			for (int j = 0; j < rSIZE; j++)
//			{
//				restaurants[i][j] = getInput(line);
//			}
//		}
//	}
//	else if (fileName == "weather.nominal.arff")
//	{
//		string weathers[wSIZE][wSIZE];
//		string temp = "";
//		while (temp != "@data")
//		{
//			fileInput >> temp;
//		}
//		for (int i = 0; i < wSIZE; i++)
//		{
//			string line;
//			fileInput >> line;
//			for (int j = 0; j < wSIZE; j++)
//			{
//				weathers[i][j] = getInput(line);
//			}
//		}
//	}
//	else if (fileName == "contact-lenses.arff")
//	{
//		string contacts[cSIZE][cSIZE];
//		string temp = "";
//		while (temp != "@data")
//		{
//			fileInput >> temp;
//		}
//		for (int i = 0; i < cSIZE; i++)
//		{
//			string line;
//			fileInput >> line;
//			for (int j = 0; j < cSIZE; j++)
//			{
//				contacts[i][j] = getInput(line);
//			}
//		}
//	}
//	else
//	{
//		cout << "\nFile does not exist";
//	}
//
//	return 0;
//}
