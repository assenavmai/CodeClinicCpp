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

double calculateMean(double total, int numElements);

int main(int argc, char const *argv[])
{
	//Declaration of variables
	ifstream fp;
	string line, dataItem, temp;
	LPOData lpo;
	vector<LPOData> lpoVector;
	double meanAir, meanBaro, meanWind;

	meanAir = meanBaro = meanWind = 0.0;


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
		//cout << "get line" << line << endl;
		//Date not being used right now
		stringstream ss(line);
		getline(ss, dataItem, '\t');
		Date date(dataItem, '_');

		for(int i = 0; i < 8; i++)
		{
			getline(ss, dataItem, '\t');
			//cout << "ok " <<  i << dataItem << endl; 

			if(i == 1)
			{
				lpo.setAirTemp(stod(dataItem));
				//cout << "air " << dataItem << endl;
			}
			else if(i == 2)
			{
				lpo.setBaroPressure(stod(dataItem));
				//cout << "baro " << dataItem << endl;
			}
			else if(i == 5)
			{
				lpo.setWindGust(stod(dataItem));
				//cout << "wind " << i << dataItem << endl;
			}
		}

		lpoVector.push_back(lpo);
	}

	//cout << (int)lpoVector.size() << endl;
	for(int i = 0; i < (int)lpoVector.size(); ++i)
	{
		meanAir += lpoVector.at(i).getAirTemp();
		meanBaro += lpoVector.at(i).getBaroPressure();
		meanWind += lpoVector.at(i).getWindGust();
	}

	meanWind = calculateMean(meanWind, (int)lpoVector.size());
	meanBaro = calculateMean(meanBaro, (int)lpoVector.size());
	meanAir = calculateMean(meanAir, (int)lpoVector.size());

	printf("%lf %lf %lf\n", meanAir, meanBaro, meanWind);


	return 0;
}

double calculateMean(double total, int numElements) {

	return (total / numElements);
}