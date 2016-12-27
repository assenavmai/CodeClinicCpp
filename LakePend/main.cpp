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

#include "file_process.h"
#include "FileException.h"

using namespace std;

const char * file = "~/Documents/LPO_weatherdata/Environmental_Data_Deep_Moor_2013.txt";

bool sortFunc(double i, double j) {
	return i < j;
}

double calculateMedian(vector<double> v) {

    sort(v.begin(), v.end(), sortFunc);

	if(v.size() % 2 == 0)
	{
		return (v[(v.size() / 2) - 1] + v[v.size() / 2]) / 2;
	}
	else
	{
		return v[v.size() / 2];
	}
}

int main(void)
{

    ifstream fp;
    ofstream out;
    stringstream query;
    double meanAir, meanBaro, meanGust, medAir, medBaro, medGust;
    vector<double> vctAir, vctBaro, vctGust;
    string line, dataItem, date, time;
    string pythonFile = "~/Documents/CodeClinicCpp/LakePend/loadFile.py";
	string command = "python ";


    openInFile("test", fp);
    openOutFile("outfile", out);
    processFile(fp, out);
    out.close();
    fp.close();

    command += pythonFile;

    //system(command.c_str());


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
  		}
  		
  		delete res;
		delete stmt;

		stmt = con-> createStatement();
		res = stmt->executeQuery("SELECT * FROM file_data");

		while(res->next())
		{
			vctAir.push_back(res->getDouble("air_temp"));
			vctBaro.push_back(res->getDouble("baro_pressure"));
			vctGust.push_back(res->getDouble("wind_gust"));
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

    medAir = calculateMedian(vctAir);
    medBaro = calculateMedian(vctBaro);
    medGust = calculateMedian(vctGust);
    cout << medAir << " " << medBaro << " " << medGust << endl;



    return EXIT_SUCCESS;
}

