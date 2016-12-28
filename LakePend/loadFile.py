""" 

	Loads the file to the database.
	Called in main.cpp
"""
import mysql.connector
from mysql.connector import errorcode

config = {
	'user' : '@@USER@@',
	'password' : '@@PASS@@',
	'host' : '127.0.0.1',
	'database' : 'lpo_data',
	'allow_local_infile' : 1,
}

print("Connecting to database...");

try:
	cnx = mysql.connector.connect(**config);
	cursor = cnx.cursor();

	cursor.execute("TRUNCATE TABLE file_data");
	cnx.commit();

	cursor.execute("LOAD DATA LOCAL INFILE './outfile' INTO TABLE file_data;");
	cnx.commit();

except mysql.connector.Error as err:
	if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
		print("Credentials are incorrect.");
	elif err.errno == errorcode.ER_BAD_DB_ERROR:
		print("The specified database does not exist.");
	else:
		print(err);
else:
	print("Closing connection...");
	cnx.close();