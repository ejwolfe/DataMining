﻿/*
Eric Wolfe
Dr. Yu
CS 490 - Data Mining
id3Weather Program
Due date: 3/20/2017

Program Description:

In this assignment, you are to write a C++ program (using Visual C++ 2015) that reads training data in WEKA arff format and generates id3Weather decision tree in a format similar to that of the tree generated by Weka id3Weather. Please note the following:
1.	Your algorithm will use the entire data set to generate the tree. You may assume that the attributes (a) are of nominal type (i.e., no numeric data), and (b) have no missing values.
2.	In general, the basic id3Weather algorithm uses entropyWeather measure to select the best attribute to divide the data set. It continues to select attribute for further branching (based on the subSetWeather of data belong to that branch) until either (a) all attributes have been used, or (b) all instances under a node belong to the same class.  This ensures a 0% error rate on the training set although it may not work the best with future data due to over-fitting.


Psuedocode from book:

(1) create a node N;
(2) if tuples in D are all of the same class, C, then
(3) return N as a leaf node labeled with the class C;
(4) if attribute list is empty then
(5) return N as a leaf node labeled with the majority class in D; // majority voting
(6) apply Attribute selection method(D, attribute list) to find the “best” splitting criterion;
(7) label node N with splitting criterion;
(8) if splitting attribute is discrete-valued and
multiway splits allowed then // not restricted to binary trees
(9) attribute list  attribute list 􀀀 splitting attribute; // remove splitting attribute
(10) for each outcome j of splitting criterion
// partition the tuples and grow subtrees for each partition
(11) let Dj be the set of data tuples in D satisfying outcome j; // a partition
(12) if Dj is empty then
(13) attach a leaf labeled with the majority class in D to node N;
(14) else attach the node returned by Generate decision tree(Dj , attribute list) to node N;
endfor
(15) return N;


Performance summary:

Unfortunately, my program will run only on the weather data. I spent 30+ hours on this program and nothing worked. Every pusedocode that I found was different from one another.
I tried the books psuedocode and it gave me an output that was not correct. I did write functions to figure out the gain and then use the gain to pick the best avaliable attribute.
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

//Parsing function for reading in the files.
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

//Values for each one of the attributes
vector<string> attributeValuesWeather(int attribute)
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
		break;
	}
	return values;
}

//Utility function for adding up the values in the list.
void summarizeExamplesWeather(vector<weather> examples, int targetAttribute, int answers[])
{
	vector<string> values = attributeValuesWeather(targetAttribute);
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

//Gets the subSetWeather of data based on the attribute and value you give it.
vector<weather> subSetWeather(vector<weather> examples, int attribute, string value)
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

//Calculates the entropyWeather
double entropyWeather(vector<weather> examples)
{
	int answers[2] = { 0, 0 };
	summarizeExamplesWeather(examples, 4, answers);
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

//Calculates the gain for the given attribute
double infoGainWeather(vector<weather> examples, int attribute)
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
	for (string value : attributeValuesWeather(attribute))
	{
		vector<weather> sub = subSetWeather(examples, attribute, value);
		gain -= (sub.size() / examples.size()) * entropyWeather(sub);
	}
	return gain;
}

//Main function for running id3Weather
node id3Weather(vector<weather> examples, vector<int> attributes, int targetAttribute)
{
	node n;
	int yes = 0, no = 0;
	int v[4] = { 0, 0, 0, 0 };
	string s0 = examples[0].outlook, s1 = examples[0].temp, s2 = examples[0].hum, s3 = examples[0].windy;
	if (examples[0].play == "yes")
	{
		yes++;
	}
	else
	{
		no++;
	}
	for (int i = 1; i < examples.size(); i++)
	{
		if (s0 == examples[i].outlook)
			v[0]++;
		else
			v[0] = 0;
		if (s1 == examples[i].temp)
			v[1]++;
		else
			v[1] = 0;
		if (s2 == examples[i].hum)
			v[2]++;
		else
			v[2] = 0;
		if (s3 == examples[i].windy)
			v[3]++;
		else
			v[3] = 0;
		if (examples[i].play == "yes")
			yes++;
		else
			no++;
	}
	if (yes == examples.size())
	{
		n.label = "yes";
		return n;
	}
	else if (no == examples.size())
	{
		n.label = "no";
		return n;
	}
	else if (attributes.empty())
	{
		int max = 0;
		for (int i = 0; i < 5; i++)
		{
			if (v[i] > max)
				max = i;
		}
		switch (max)
		{
		case(0):
			n.label = s0;
			break;
		case(1):
			n.label = s1;
			break;
		case(2):
			n.label = s2;
			break;
		case(3):
			n.label = s3;
			break;
		}
		return n;
	}
	else
	{
		double gain = 0, prevGain = 0;
		int bestA = 0;
		for (int i : attributes)
		{
			gain = infoGainWeather(examples, i);
			if (gain > prevGain)
			{
				bestA = i;
				prevGain = gain;
			}
		}
		n.decision = bestA;
		switch (bestA)
		{
		case(0):
			n.label = "outlook";
			break;
		case(1):
			n.label = "temp";
			break;
		case(2):
			n.label = "hum";
			break;
		case(3):
			n.label = "windy";
			break;
		}
		for (string value : attributeValuesWeather(bestA))
		{
			vector<weather> sub = subSetWeather(examples, bestA, value);
			if (!sub.empty())
			{
				vector<int> newAttributes;
				for (int i : attributes)
				{
					if (i != bestA)
					{
						newAttributes.push_back(i);
					}
				}
				n.addBranch.push_back(id3Weather(sub, newAttributes, targetAttribute));
			}
			else
			{
				int v[4] = { 0, 0, 0, 0 };
				string s0 = examples[0].outlook, s1 = examples[0].temp, s2 = examples[0].hum, s3 = examples[0].windy;
				for (int i = 1; i < examples.size(); i++)
				{
					if (s0 == examples[i].outlook)
						v[0]++;
					else
						v[0] = 0;
					if (s1 == examples[i].temp)
						v[1]++;
					else
						v[1] = 0;
					if (s2 == examples[i].hum)
						v[2]++;
					else
						v[2] = 0;
					if (s3 == examples[i].windy)
						v[3]++;
					else
						v[3] = 0;
				}
				int max = 0;
				for (int i = 0; i < 5; i++)
				{
					if (v[i] > max)
						max = i;
				}
				switch (max)
				{
				case(0):
					n.label = s0;
					break;
				case(1):
					n.label = s1;
					break;
				case(2):
					n.label = s2;
					break;
				case(3):
					n.label = s3;
					break;
				}
			}
		}
	}
	return n;
}

vector<string> attributeValuesRestaurant(int attribute)
{
	vector<string> values;
	switch (attribute)
	{
	case(0):
		values.push_back("Yes");
		values.push_back("No");
		break;
	case(1):
		values.push_back("Yes");
		values.push_back("No");
		break;
	case(2):
		values.push_back("Yes");
		values.push_back("No");
		break;
	case(3):
		values.push_back("Yes");
		values.push_back("No");
		break;
	case(4):
		values.push_back("Some");
		values.push_back("Full");
		values.push_back("None");
		break;
	case(5):
		values.push_back("$");
		values.push_back("$$");
		values.push_back("$$$");
		break;
	case(6):
		values.push_back("Yes");
		values.push_back("No");
		break;
	case(7):
		values.push_back("Yes");
		values.push_back("No");
		break;
	case(8):
		values.push_back("French");
		values.push_back("Thai");
		values.push_back("Burger");
		values.push_back("Italian");
		break;
	case(9):
		values.push_back("0-10");
		values.push_back("10-30");
		values.push_back("30-60");
		values.push_back(">60");
		break;
	case(10):
		values.push_back("Yes");
		values.push_back("No");
		break;
	}
	return values;
}

//Utility function for adding up the values in the list.
void summarizeExamplesRestaurant(vector<restaurant> examples, int targetAttribute, int answers[])
{
	vector<string> values = attributeValuesRestaurant(targetAttribute);
	int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
	for (restaurant res : examples)
	{
		switch (targetAttribute)
		{
		case(0):
			if (res.alt == values[0])
				v1++;
			else
				v2++;
			break;
		case(1):
			if (res.bar == values[0])
				v1++;
			else
				v2++;
			break;
		case(2):
			if (res.fri == values[0])
				v1++;
			else
				v2++;
			break;
		case(3):
			if (res.hun == values[0])
				v1++;
			else
				v2++;
			break;
		case(4):
			if (res.pat == values[0])
				v1++;
			else if (res.pat == values[1])
				v2++;
			else
				v3++;
			break;
		case(5):
			if (res.price == values[0])
				v1++;
			else if (res.price == values[1])
				v2++;
			else
				v3++;
			break;
		case(6):
			if (res.rain == values[0])
				v1++;
			else
				v2++;
			break;
		case(7):
			if (res.res == values[0])
				v1++;
			else
				v2++;
			break;
		case(8):
			if (res.type == values[0])
				v1++;
			else if (res.type == values[1])
				v2++;
			else if (res.type == values[2])
				v3++;
			else
				v4++;
			break;
		case(9):
			if (res.est == values[0])
				v1++;
			else if (res.est == values[1])
				v2++;
			else if (res.est == values[2])
				v3++;
			else
				v4++;
			break;
		case(10):
			if (res.wait == values[0])
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
	if (v4 != 0)
	{
		answers[3] = v4;
	}
}

//Gets the subSetRestaurant of data based on the attribute and value you give it.
vector<restaurant> subSetRestaurant(vector<restaurant> examples, int attribute, string value)
{
	vector<restaurant> temp;
	for (int i = 0; i < examples.size(); i++)
	{
		switch (attribute)
		{
		case(0):
			if (examples[i].alt == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(1):
			if (examples[i].bar == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(2):
			if (examples[i].fri == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(3):
			if (examples[i].hun == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(4):
			if (examples[i].pat == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(5):
			if (examples[i].price == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(6):
			if (examples[i].rain == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(7):
			if (examples[i].res == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(8):
			if (examples[i].type == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(9):
			if (examples[i].est == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		case(10):
			if (examples[i].wait == value)
			{
				temp.push_back(examples[i]);
			}
			break;
		}
	}
	return temp;
}

//Calculates the entropyWeather
double entropyRestaurant(vector<restaurant> examples)
{
	int answers[2] = { 0, 0 };
	summarizeExamplesRestaurant(examples, 10, answers);
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

//Calculates the gain for the given attribute
double infoGainRestaurant(vector<restaurant> examples, int attribute)
{
	double yes = 0, no = 0;
	for (int i = 0; i < examples.size(); i++)
	{
		if (examples[i].wait == "yes")
			yes++;
		else
			no++;
	}
	double gain = -((yes / examples.size()) * log2(yes / examples.size())) - ((no / examples.size()) * log2(no / examples.size()));
	for (string value : attributeValuesRestaurant(attribute))
	{
		vector<restaurant> sub = subSetRestaurant(examples, attribute, value);
		gain -= (sub.size() / examples.size()) * entropyRestaurant(sub);
	}
	return gain;
}

//Main function for running id3Weather
node id3Restaurant(vector<restaurant> examples, vector<int> attributes, int targetAttribute)
{
	node n;
	int yes = 0, no = 0;
	int v[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	string s0 = examples[0].alt, s1 = examples[0].bar, s2 = examples[0].fri, s3 = examples[0].hun, s4 = examples[0].pat, s5 = examples[0].price
		, s6 = examples[0].rain, s7 = examples[0].res, s8 = examples[0].type, s9 = examples[0].est;
	if (examples[0].wait == "yes")
	{
		yes++;
	}
	else
	{
		no++;
	}
	for (int i = 1; i < examples.size(); i++)
	{
		if (s0 == examples[i].alt)
			v[0]++;
		else
			v[0] = 0;
		if (s1 == examples[i].bar)
			v[1]++;
		else
			v[1] = 0;
		if (s2 == examples[i].fri)
			v[2]++;
		else
			v[2] = 0;
		if (s3 == examples[i].hun)
			v[3]++;
		else
			v[3] = 0;
		if (s4 == examples[i].pat)
			v[4]++;
		else
			v[4] = 0;
		if (s5 == examples[i].price)
			v[5]++;
		else
			v[5] = 0;
		if (s6 == examples[i].hun)
			v[6]++;
		else
			v[6] = 0;
		if (s7 == examples[i].hun)
			v[7]++;
		else
			v[7] = 0;
		if (s8 == examples[i].hun)
			v[8]++;
		else
			v[8] = 0;
		if (s9 == examples[i].hun)
			v[9]++;
		else
			v[9] = 0;
		if (examples[i].wait == "yes")
			yes++;
		else
			no++;
	}
	if (yes == examples.size())
	{
		n.label = "yes";
		return n;
	}
	else if (no == examples.size())
	{
		n.label = "no";
		return n;
	}
	else if (attributes.empty())
	{
		int max = 0;
		for (int i = 0; i < 10; i++)
		{
			if (v[i] > max)
				max = i;
		}
		switch (max)
		{
		case(0):
			n.label = s0;
			break;
		case(1):
			n.label = s1;
			break;
		case(2):
			n.label = s2;
			break;
		case(3):
			n.label = s3;
			break;
		case(4):
			n.label = s4;
			break;
		case(5):
			n.label = s5;
			break;
		case(6):
			n.label = s6;
			break;
		case(7):
			n.label = s7;
			break;
		case(9):
			n.label = s9;
			break;
		case(8):
			n.label = s8;
			break;
		}
		return n;
	}
	else
	{
		double gain = 0, prevGain = 0;
		int bestA = 0;
		for (int i : attributes)
		{
			gain = infoGainRestaurant(examples, i);
			if (gain > prevGain)
			{
				bestA = i;
				prevGain = gain;
			}
		}
		n.decision = bestA;
		switch (bestA)
		{
		case(0):
			n.label = "alt";
			break;
		case(1):
			n.label = "bar";
			break;
		case(2):
			n.label = "fri";
			break;
		case(3):
			n.label = "hun";
			break;
		case(4):
			n.label = "pat";
			break;
		case(5):
			n.label = "price";
			break;
		case(6):
			n.label = "rain";
			break;
		case(7):
			n.label = "res";
			break;
		case(9):
			n.label = "est";
			break;
		case(8):
			n.label = "type";
			break;
		}
		for (string value : attributeValuesRestaurant(bestA))
		{
			vector<restaurant> sub = subSetRestaurant(examples, bestA, value);
			if (!sub.empty())
			{
				vector<int> newAttributes;
				for (int i : attributes)
				{
					if (i != bestA)
					{
						newAttributes.push_back(i);
					}
				}
				n.addBranch.push_back(id3Restaurant(sub, newAttributes, targetAttribute));
			}
			else
			{
				int v[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
				string s0 = examples[0].alt, s1 = examples[0].bar, s2 = examples[0].fri, s3 = examples[0].hun, s4 = examples[0].pat, s5 = examples[0].price
					, s6 = examples[0].rain, s7 = examples[0].res, s8 = examples[0].type, s9 = examples[0].est;
				for (int i = 1; i < examples.size(); i++)
				{
					if (s0 == examples[i].alt)
						v[0]++;
					else
						v[0] = 0;
					if (s1 == examples[i].bar)
						v[1]++;
					else
						v[1] = 0;
					if (s2 == examples[i].fri)
						v[2]++;
					else
						v[2] = 0;
					if (s3 == examples[i].hun)
						v[3]++;
					else
						v[3] = 0;
					if (s4 == examples[i].pat)
						v[4]++;
					else
						v[4] = 0;
					if (s5 == examples[i].price)
						v[5]++;
					else
						v[5] = 0;
					if (s6 == examples[i].rain)
						v[6]++;
					else
						v[6] = 0;
					if (s7 == examples[i].res)
						v[7]++;
					else
						v[7] = 0;
					if (s8 == examples[i].type)
						v[8]++;
					else
						v[8] = 0;
					if (s9 == examples[i].est)
						v[9]++;
					else
						v[9] = 0;
				}
				int max = 0;
				for (int i = 0; i < 10; i++)
				{
					if (v[i] > max)
						max = i;
				}
				switch (max)
				{
				case(0):
					n.label = s0;
					break;
				case(1):
					n.label = s1;
					break;
				case(2):
					n.label = s2;
					break;
				case(3):
					n.label = s3;
					break;
				case(4):
					n.label = s4;
					break;
				case(5):
					n.label = s5;
					break;
				case(6):
					n.label = s6;
					break;
				case(7):
					n.label = s7;
					break;
				case(9):
					n.label = s9;
					break;
				case(8):
					n.label = s8;
					break;
				}
			}
		}
	}
	return n;
}

int main()
{
	cout << "Please enter name of the data file: \t";
	string fileName = "restaurant.arff";
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
		vector<int> attributes = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		node root = id3Restaurant(restaurants, attributes, 10);
		cout << "restaurant.arff" << endl;
		for (node n1 : root.addBranch)
		{
			cout << n1.label << endl;
			if (!n1.addBranch.empty())
			{
				for (node n2 : n1.addBranch)
				{
					cout << "|\t" << n2.label << endl;
					if (!n2.addBranch.empty())
					{
						for (node n3 : n2.addBranch)
						{
							cout << "\t|\t" << n3.label << endl;
						}
					}
				}
			}
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
		//cout << infoGainWeather(weathers, 0);
		vector<int> attributes = { 0, 1, 2, 3 };
		node root = id3Weather(weathers, attributes, 4);
		cout << "weather.nominal.arff" << endl;
		for (node n1 : root.addBranch)
		{
			cout << n1.label << endl;
			if (!n1.addBranch.empty())
			{
				for (node n2 : n1.addBranch)
				{
					cout << "|\t" << n2.label << endl;
					if (!n2.addBranch.empty())
					{
						for (node n3 : n2.addBranch)
						{
							cout << "\t|\t" << n3.label << endl;
						}
					}
				}
			}
		}
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
