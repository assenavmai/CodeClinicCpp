/** \file file_process.h 
 * Processes the file used within the program.
 * Functions included to open the file, close the file and to read and write to a file.
 */
#ifndef _FILE_PROCESS_H
#define _FILE_PROCESS_H

#include <fstream>
#include <string>

#include "FileException.h"

const FileException in_file("File could not be opened for reading.");
const FileException out_file("File could not be opened for writing.");

/**\namespace std */
using namespace std;

/*! \fn void openInFile(string filename, ifstream &infile)
 * \brief Opens the specified filename for reading.
 * \param filename: a string containing the file to be opened.
 * \param infile: an ifstream.
 * \exception in_file: if the file cannot be opened.
 */
void openInFile(string filename, ifstream &infile) {

    try
    {
        infile.open(filename, ios::in);

        if(!infile.is_open())
        {
            throw in_file; //!< throwing an exception specified at the beginning of the file 
        }
    }
    catch(FileException &e)
    {
        cout << "Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}


/*! \fn void openOutFile(string filename, ofstream &outfile)
 * \brief Opens the specified filename for writing.
 * \param filename: a string containing the file to be opened.
 * \param outfile: an ofstream.
 * \exception out_file: if the file cannot be opened.
 */
void openOutFile(string filename, ofstream &outfile) {

    try
    {
        outfile.open(filename, ios::out);

        if(!outfile.is_open())
        {
            throw out_file; //!< throwing an exception specified at the beginning of the file 
        }
    }
    catch(FileException &e)
    {
        cout << "Error: " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

/*! \fn void processFile(ifstream &in, ofstream &out)
 * \brief Reads the file contents of the ifstream and writes the air temperature,
 			barometric pressure and wind gust to the ofstream file.
 * \param in: an ifstream.
 * \param out: an ofstream.
 */
void processFile(ifstream &in, ofstream &out) {

	string line, dataItem;
	double airTemp, baroPress, windGust;

    getline(in, line); //! Disregards the first line of the file since it is just headers

    while(getline(in, line))
    {
        stringstream ss(line);
        getline(ss, dataItem, ' '); /**< The beginning of the file is delimited with a space, rather than a tab */

        for(int i = 0; i < 8; i++) /**< Only 8 headings in the file */
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