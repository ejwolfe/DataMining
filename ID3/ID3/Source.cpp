/*
Eric Wolfe
Dr. Yu
CS 490 - Data Mining
ID3 Program
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

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

void getRestaurant(restaurant &res, string &line)
{
	res.alt = getInput(line);
	res.bar = getInput(line);
	res.fri = getInput(line);
	res.hun = getInput(line);
	res.pat = getInput(line);
	res.price = getInput(line);
	res.rain = getInput(line);
	res.res = getInput(line);
	res.type = getInput(line);
	res.est = getInput(line);
	res.wait = getInput(line);
}

void printRestaurant(restaurant &res)
{
	cout << res.alt << endl;
	cout << res.bar << endl;
	cout << res.fri << endl;
	cout << res.hun << endl;
	cout << res.pat << endl;
	cout << res.price << endl;
	cout << res.rain << endl;
	cout << res.res << endl;
	cout << res.type << endl;
	cout << res.est << endl;
	cout << res.wait << endl;
}

void getContact(contact &con, string &line)
{
	con.age = getInput(line);
	con.spec = getInput(line);
	con.ast = getInput(line);
	con.tear = getInput(line);
	con.lense = getInput(line);
}

void printContact(contact &con)
{
	cout << con.age << endl;
	cout << con.spec << endl;
	cout << con.ast << endl;
	cout << con.tear << endl;
	cout << con.lense << endl;
}

void getWeather(weather &wea, string &line)
{
	wea.outlook = getInput(line);
	wea.temp = getInput(line);
	wea.hum = getInput(line);
	wea.windy = getInput(line);
	wea.play = getInput(line);
}

void printWeather(weather &wea)
{
	cout << wea.outlook << endl;
	cout << wea.temp << endl;
	cout << wea.hum << endl;
	cout << wea.windy << endl;
	cout << wea.play << endl;
}

struct node
{
	string label = "";
	int decision = -1;
	vector<node> addBranch;
};

vector<string> attributeValues(int attribute)
{
	vector<string> values;
	switch (attribute)
	{
	case(0):
		values.push_back("sunny");
		values.push_back("overcast");
		values.push_back("rainy");
		break;
	case(1):
		values.push_back("hot");
		values.push_back("mild");
		values.push_back("cool");
		break;
	case(2):
		values.push_back("high");
		values.push_back("normal");
		break;
	case(3):
		values.push_back("TRUE");
		values.push_back("FALSE");
		break;
	case(4):
		values.push_back("yes");
		values.push_back("no");
	}
	return values;
}

void summarizeExamples(vector<weather> examples, int targetAttribute, int answers[])
{
	vector<string> values = attributeValues(targetAttribute);
	int v1 = 0, v2 = 0, v3 = 0;
	for (weather wea : examples)
	{
		switch (targetAttribute)
		{
		case(0):
			if (wea.outlook == values[0])
				v1++;
			else if (wea.outlook == values[1])
				v2++;
			else
				v3++;
			break;
		case(1):
			if (wea.temp == values[0])
				v1++;
			else if (wea.temp == values[1])
				v2++;
			else
				v3++;
			break;
		case(2):
			if (wea.hum == values[0])
				v1++;
			else
				v2++;
			break;
		case(3):
			if (wea.windy == values[0])
				v1++;
			else
				v2++;
			break;
		case(4):
			if (wea.play == values[0])
				v1++;
			else
				v2++;
			break;

		}
	}
	if (v1 != 0)
	{
		answers[0] = v1;
	}
	if (v2 != 0)
	{
		answers[1] = v2;
	}
	if (v3 != 0)
	{
		answers[2] = v3;
	}
}

vector<weather> subSet(vector<weather> examples, int attribute, string value)
{
	vector<weather> temp;
	for (int i = 0; i < examples.size(); i++)
	{
		switch (attribute)
		{
		case(0):
			if (examples[i].outlook == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(1):
			if (examples[i].temp == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(2):
			if (examples[i].hum == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(3):
			if (examples[i].windy == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(4):
			if (examples[i].play == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		}
	}
	return temp;
}

double entropy(vector<weather> examples)
{
	int answers[2] = { 0, 0 };
	summarizeExamples(examples, 4, answers);
	double yes = answers[0], no = answers[1];
	if (yes == 0)
	{
		return -((no / examples.size()) * log2(no / examples.size()));
	}
	else if (no == 0)
	{
		return -((yes / examples.size()) * log2(yes / examples.size()));
	}
	else
	{
		return -((yes / examples.size()) * log2(yes / examples.size())) - ((no / examples.size()) * log2(no / examples.size()));
	}
}

double infoGain(vector<weather> examples, int attribute)
{
	double yes = 0, no = 0;
	for (int i = 0; i < examples.size(); i++)
	{
		if (examples[i].play == "yes")
			yes++;
		else
			no++;
	}
	double gain = -((yes / examples.size()) * log2(yes / examples.size())) - ((no / examples.size()) * log2(no / examples.size()));
	for (string value : attributeValues(attribute))
	{
		vector<weather> sub = subSet(examples, attribute, value);
		gain -= (sub.size() / examples.size()) * entropy(sub);
	}
	return gain;
}

node id3(vector<weather> examples, vector<int> attributes, int targetAttribute)
{
	node n1;
	int size = 0;
	int* answers;
	if (targetAttribute == 0 || targetAttribute == 1)
	{
		answers = new int[3];
		size = 3;
	}
	else
	{
		answers = new int[2];
		size = 2;
	}
	summarizeExamples(examples, targetAttribute, answers);
	vector<string> values = attributeValues(targetAttribute);
	for (int i = 0; i < size; i++)
	{
		if (answers[i] == examples.size())
		{
			n1.label = values[i];
		}
	}
	if (attributes.empty())
	{
		int array0[3] = { 0, 0, 0 }, array1[3] = { 0, 0, 0 }, array2[2] = { 0, 0}, array3[2] = { 0, 0 }, array4[2] = { 0, 0 };
		int a[5] = { 0, 0, 0, 0, 0 };
		for (int i = 0; i < examples.size(); i++)
		{
			if (examples[i].outlook == "sunny")
				array0[0]++;
			if (examples[i].outlook == "overcast")
				array0[1]++;
			if (examples[i].outlook == "rainy")
				array0[2]++;
			if (examples[i].temp == "hot")
				array1[0]++;
			if (examples[i].temp == "mild")
				array1[1]++;
			if (examples[i].temp == "cool")
				array1[2]++;
			if (examples[i].hum == "high")
				array2[0]++;
			if (examples[i].hum == "normal")
				array2[1]++;
			if (examples[i].windy == "TRUE")
				array3[0]++;
			if (examples[i].windy == "FALSE")
				array3[1]++;
			if (examples[i].play == "yes")
				array4[0]++;
			if (examples[i].play == "no")
				array4[1]++;
		}
		for (int i = 0; i < 3; i++)
		{
			if (array0[i] > a[0])
				a[0] = array0[i];
			if (array1[i] > a[1])
				a[1] = array1[i];
		}
		for (int i = 0; i < 2; i++)
		{
			if (array2[i] > a[2])
				a[2] = array2[i];
			if (array3[i] > a[3])
				a[3] = array3[i];
			if (array4[i] > a[4])
				a[4] = array4[i];
		}
		int max = 0;
		for (int i = 0; i < 5; i++)
		{
			if (a[i] > max)
				max = i;
		}
		switch (max)
		{
		case(0):
			n1.label = "outlook";
			break;
		case(1):
			n1.label = "temp";
			break;
		case(2):
			n1.label = "hum";
			break;
		case(3):
			n1.label = "windy";
			break;
		case(4):
			n1.label = "play";
			break;
		}
	}
	double gain = 0, prevGain = 0;
	int bestA = 0;
	for (int i : attributes)
	{
		gain = infoGain(examples, i);
		if (gain > prevGain)
		{
			bestA = i;
			prevGain = gain;
		}
	}
	n1.decision = bestA;
	vector<int> newAttributes;
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i] != bestA)
		{
			newAttributes.push_back(attributes[i]);
		}
	}
	for (string value : attributeValues(bestA))
	{
		vector<weather> sub = subSet(examples, bestA, value);
		if (!sub.empty())
		{
			if (newAttributes == attributes)
			{
				vector<int> a;
				n1.addBranch.push_back(id3(sub, a, bestA));
			}
			n1.addBranch.push_back(id3(sub, newAttributes, bestA));
		}
	}
	return n1;
}

int main()
{
	cout << "Please enter name of the data file: \t";
	string fileName = "weather.nominal.arff";
	//cin >> fileName;

	ifstream fileInput;
	fileInput.open(fileName);

	if (fileName == "restaurant.arff")
	{
		vector<restaurant> restaurants;
			string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < 11; i++)
		{
			string line;
			fileInput >> line;
			restaurant res;
			getRestaurant(res, line);
			restaurants.push_back(res);
			//printRestaurant(restaurants[i]);
		}
	}
	else if (fileName == "weather.nominal.arff")
	{
		vector<weather> weathers;
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < 14; i++)
		{
			string line;
			fileInput >> line;
			weather wea;
			getWeather(wea, line);
			weathers.push_back(wea);
			//printWeather(weathers[i]);
		}
		//cout << infoGain(weathers, 0);
		vector<int> attributes = { 0, 1, 2, 3, 4 };
		id3(weathers, attributes, 0);
	}
	else if (fileName == "contact-lenses.arff")
	{
		vector<contact> contacts;
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < 24; i++)
		{
			string line;
			fileInput >> line;
			contact con;
			getContact(con, line);
			contacts.push_back(con);
			printContact(contacts[i]);
		}
	}
	else
	{
		cout << "\nFile does not exist";
	}

	return 0;
}