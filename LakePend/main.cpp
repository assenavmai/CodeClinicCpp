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

const char * file = "/home/vanessa/Documents/LPO_weatherdata/Environmental_Data_Deep_Moor_2012.txt";

int main(int argc, char const *argv[])
{
	ifstream fp;
	stringstream ss;
	double windGust, airTemp, baroPress;
	string line, dataItem, temp;
	vector<LPOData> lpoVector;


	windGust = airTemp = baroPress = 0.0;


	try
	{
		fp.open("./test", ios::in);
		
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

	getline(fp, line);

	while(getline(fp, line))
	{
		ss.str(line);
		getline(ss, dataItem, ' ');
		Date date(dataItem, '_');

		for(int i = 0; i < 8; i++)
		{
			getline(ss, dataItem, '\t');

			if(i == 1)
			{
				airTemp = stod(dataItem);
			}
			else if(i == 2)
			{
				baroPress = stod(dataItem);
			}
			else if(i == 6)
			{
				windGust = stod(dataItem);
			}
		}

	}

	printf("%lf %lf %lf\n", airTemp, baroPress, windGust);

	return 0;
}