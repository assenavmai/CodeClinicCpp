/** Author: Vanessa White
	Program: Statistical Analysis - Lake Pend
	Date: December 22nd, 2016
**/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "Date.h"
#include "LPOData.h"
#include "FileException.h"

using namespace std;

const FileException e_file("File could not be opened.");

const char * file = "/home/vanessa/Documents/LPO_weatherdata/Environmental_Data_Deep_Moor_2013.txt";

int main(int argc, char const *argv[])
{
	//Declaration of variables
	ifstream fp;
	stringstream ss;
	double windGust, airTemp, baroPress;
	string line, dataItem, temp;
	LPOData lpo;
	vector<LPOData> lpoVector;


	windGust = airTemp = baroPress = 0.0; //init


	//open the file
	try
	{
		fp.open(file, ios::in);
		
		if(!fp.is_open())
		{
			throw e_file;
		}
	}
	catch(FileException &e)
	{
		cout << "Error: " << e.what() << endl;
		exit(EXIT_FAILURE);
	}

	getline(fp, line); // disregard the first line of the file

	//Loop through the file and parse and store the values into the class object, then into a vector
	while(getline(fp, line))
	{
		//Date not being used right now
		ss.str(line);
		getline(ss, dataItem, ' ');
		Date date(dataItem, '_');

		for(int i = 0; i < 8; i++)
		{
			getline(ss, dataItem, '\t');

			if(i == 1)
			{
				lpo.setAirTemp(stod(dataItem));
			}
			else if(i == 2)
			{
				lpo.setBaroPressure(stod(dataItem));
			}
			else if(i == 6)
			{
				lpo.setWindGust(stod(dataItem));
			}
		}

		lpoVector.push_back(lpo);
	}

	return 0;
}