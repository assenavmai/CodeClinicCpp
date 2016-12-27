/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "Date.h"
#include "LPOData.h"
#include "FileException.h"

using namespace std;

void openOutFile(string filename, ofstream &outfile);
void openInFile(string filename, ifstream &infile);
void processFile(ifstream &in, ofstream &out);

const FileException in_file("File could not be opened for reading.");
const FileException out_file("File could not be opened for writing.");

const char * file = "~/Documents/LPO_weatherdata/Environmental_Data_Deep_Moor_2013.txt";



int main(void)
{

    ifstream fp;
    ofstream out;
    stringstream query;
    double meanAir, meanBaro, meanGust;
    string line, dataItem, date, time;
    string pythonFile = "~/Documents/CodeClinicCpp/LakePend/loadFile.py";
	string command = "python ";

    openInFile("test", fp);
    openOutFile("outfile", out);
    processFile(fp, out);
    out.close();
    fp.close();

    command += pythonFile;

    system(command.c_str());


    try 
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();

        con = driver->connect("tcp://127.0.0.1:3306", "", "");
        /* Connect to the MySQL lpo_data database */
        con->setSchema("");

       	stmt = con->createStatement();
       	query << "SELECT AVG(air_temp) AS _mean_air, AVG(baro_pressure) as _mean_baro, \
        	AVG(wind_gust) AS _mean_gust FROM file_data";
        res = stmt->executeQuery(query.str());

        while (res->next()) 
        {
		    cout << "\t... MySQL replies: ";
		    /* Access column data by alias or column name */
		    meanAir = res->getDouble("_mean_air");
		    meanBaro = res->getDouble("_mean_baro");
		    meanGust = res->getDouble("_mean_gust");
		    //cout << "\t... MySQL says it again: ";
		    /* Access column data by numeric offset, 1 is the first column */
		    //cout << res->getString(1) << endl;
  		}
  		
  		delete res;
		delete stmt;
        delete con;

    } 
    catch (sql::SQLException &e) 
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line  » "\
        << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << fixed;
    cout << setprecision(3);
    cout << meanAir << " " << meanBaro << " " << meanGust << endl;
    return EXIT_SUCCESS;
}

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