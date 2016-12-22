/** Author: Vanessa White
	Program: Statistical Analysis - Lake Pend
	Date: December 22nd, 2016
**/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "LPOData.h"
#include "FileException.h"

using namespace std;

const FileException e_file("File could not be opened.");

const char * file = "/home/vanessa/Documents/LPO_weatherdata/Environmental_Data_Deep_Moor_2012.txt";

int main(int argc, char const *argv[])
{
	ifstream fp;
	double windGust, airTemp, baroPress;
	string line;

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
		cout << line << endl;

	}

	printf("%lf %lf %lf\n", airTemp, baroPress, windGust);

	return 0;
}