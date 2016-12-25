/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

const FileException e_file("File could not be opened.");
const char * file = "/home/vanessa/Documents/LPO_weatherdata/Environmental_Data_Deep_Moor_2013.txt";


int main(void)
{

    ifstream fp;
    string line, dataItem, date, time;
    double airTemp, baroPress, /*dew, relHumid, windDir,*/ windGust/*, windSpeed*/;

    /*cout << endl;
    cout << "Running 'SELECT 'Hello World!' » \
    AS _message'..." << endl;*/


   //open the file
    try
    {
        fp.open("test", ios::in);

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

    try 
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();

        con = driver->connect("tcp://127.0.0.1:3306", "root", password);
        /* Connect to the MySQL lpo_data database */
        con->setSchema(table);

        //Loop through the file and parse and store the values into the class object, then into a vector
        getline(fp, line); // disregard the first line of the file
        cout << line << endl;

        while(getline(fp, line))
        {
            stringstream ss(line);
            stringstream querySS;
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

            cout << "INSERT INTO file_data (air_temp, baro_pressure, wind_gust) VALUES(" << airTemp << "," << baroPress \
                << "," << windGust << ")";

            querySS << "INSERT INTO file_data (air_temp, baro_pressure, wind_gust) VALUES(" << airTemp << "," << baroPress \
                << "," << windGust << ")";

            stmt = con->createStatement();
            stmt->execute(querySS.str());

            delete stmt;
        }

        fp.close();
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

    cout << endl;

    return EXIT_SUCCESS;
}
