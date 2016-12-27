#ifndef _FILE_PROCESS_H
#define _FILE_PROCESS_H

#include <fstream>
#include <string>

#include "FileException.h"

const FileException in_file("File could not be opened for reading.");
const FileException out_file("File could not be opened for writing.");

using namespace std;

void openInFile(string filename, ifstream &infile) {

    try
    {
        infile.open(filename, ios::in);

        if(!infile.is_open())
        {
            throw in_file;
        }
    }
    catch(FileException &e)
    {
        cout << "Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void openOutFile(string filename, ofstream &outfile) {

    try
    {
        outfile.open(filename, ios::out);

        if(!outfile.is_open())
        {
            throw out_file;
        }
    }
    catch(FileException &e)
    {
        cout << "Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void processFile(ifstream &in, ofstream &out) {

	string line, dataItem;
	double airTemp, baroPress, windGust;

	//Loop through the file and parse and store the values into the class object, then into a vector
    getline(in, line); // disregard the first line of the file
    cout << line << endl;

    while(getline(in, line))
    {
        stringstream ss(line);
        getline(ss, dataItem, ' ');

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

	    out << airTemp << '\t' << baroPress << '\t' << windGust << '\n';
    }
}



#endif