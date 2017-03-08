/*
Eric Wolfe
Dr. Yu
CS 490 - Data Mining
ID3 Program
 */

#include <string>
#include <iostream>
#include <fstream>

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

int main()
{
	cout << "Please enter name of the data file: \t";
	string fileName = "";
	cin >> fileName;

	ifstream fileInput;
	fileInput.open(fileName);

	if (fileName == "restaurant.arff")
	{
		restaurant* restaurants = new restaurant[11];
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < 11; i++)
		{
			string line;
			fileInput >> line;
			getRestaurant(restaurants[i], line);
			//printRestaurant(restaurants[i]);
		}
	}
	else if (fileName == "weather.nominal.arff")
	{
		weather* weathers = new weather[14];
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < 14; i++)
		{
			string line;
			fileInput >> line;
			getWeather(weathers[i], line);
			printWeather(weathers[i]);
		}
	}
	else if (fileName == "contact-lenses.arff")
	{
		contact* contacts = new contact[24];
		string temp = "";
		while (temp != "@data")
		{
			fileInput >> temp;
		}
		for (int i = 0; i < 24; i++)
		{
			string line;
			fileInput >> line;
			getContact(contacts[i], line);
			//printContact(contacts[i]);
		}
	}
	else
	{
		cout << "\nFile does not exist";
	}

	return 0;
}