/** \file main.cpp
 * Contains the main contents of the program.
 * Has the connection to the database, extracting data from the database, calculating the median, mean and 
 * creating the JSON file.
 */

//<! Standard C++ includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "json/json.h"

#include "file_process.h"
#include "FileException.h"

/**\namespace std */
using namespace std;

/*! \fn bool sortFunc(double i, double j)
 * \brief Helper function to sort a vector of doubles.
 * \param i: a double.
 * param j: a double
 * \return true if i is less than j, otherwise false.
 */
bool sortFunc(double i, double j) {
	return i < j;
}

/*! \fn double calculateMedian(vector<double> v)
 * \brief Calculates the median of the values stored in a vector of doubles.
 * \param v: a vector of type double.
 * \return a double which represents the median.
 */
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

/*! \fn Json::Value createJsonStructure(double mean, double median, Json::Value arr)
 * \brief Uses JSONCPP to create a JSON structure using the median and mean values.
 * \param mean: a double.
 * \param median: a double.
 * \param arr: a Json::Value from the JSONCPP package
 * \return a Json::Value
 */
Json::Value createJsonStructure(double mean, double median, Json::Value arr) {

	Json::Value set;

	set["arr"]["mean"] = mean;
	set["arr"]["median"] = median;

	arr.append(set["arr"]);

	return arr;
}

int main(void)
{

    ifstream fp;
    ofstream out, jsonData;
    stringstream query;
    double meanAir, meanBaro, meanGust, medAir, medBaro, medGust;
    vector<double> vctAir, vctBaro, vctGust;
    string line, dataItem, date, time;
	Json::Value buildJson, temp;
	Json::Value arrWind, arrAir, arrBaro;
	Json::StyledWriter styledWriter;

	string pythonFile = "@@PYTHON@@"; //!< Location of the script where the file is loaded into the MySQL database
	string command = "python ";

    openInFile(file, fp);
    openOutFile("outfile", out);
    processFile(fp, out);
    out.close();
    fp.close();

    command += pythonFile; //!< Concatenate the command

    system(command.c_str()); //!< Runs the python script 

    try 
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        driver = get_driver_instance(); //!< Creates a connection

        con = driver->connect("tcp://127.0.0.1:3306", "@@USER@@", "@@PASS@@");
        con->setSchema("@@DB@@"); //!< Connects to the MySQL lpo_data database
        

       	stmt = con->createStatement();
       	query << "SELECT AVG(air_temp) AS _mean_air, AVG(baro_pressure) as _mean_baro, \
        	AVG(wind_gust) AS _mean_gust FROM file_data";
        res = stmt->executeQuery(query.str());

		cout << "\t... Calculating mean..." << endl;;

        while (res->next()) 
        {

		    meanAir = res->getDouble("_mean_air"); //!< Access column data by alias
		    meanBaro = res->getDouble("_mean_baro"); //!< Access column data by alias
		    meanGust = res->getDouble("_mean_gust"); //!< Access column data by alias
  		}
  		
  		delete res;
		delete stmt;

		stmt = con-> createStatement();
		res = stmt->executeQuery("SELECT * FROM file_data");

		cout << "\t... Getting values from table..." << endl;

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


    cout << "\t... Calculating median..." << endl;
    medAir = calculateMedian(vctAir);
    medBaro = calculateMedian(vctBaro);
    medGust = calculateMedian(vctGust);

    arrWind = createJsonStructure(meanGust, medGust, arrWind);
    arrAir = createJsonStructure(meanAir, medAir, arrAir);
    arrBaro = createJsonStructure(meanBaro, medBaro, arrBaro);

	buildJson["barometricPressure"] = arrBaro;
	buildJson["airTemperature"] = arrAir;
	buildJson["windSpeed"] = arrWind;

	openOutFile("returnData.json", jsonData);

	jsonData << "var jsonReturnData = ";
	jsonData << styledWriter.write(buildJson);

	jsonData.close();

	cout << "Program completed. JSON file created." << endl;

    return EXIT_SUCCESS;
}

