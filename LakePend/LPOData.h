#ifndef _LPODATA_H
#define _LPODATA_H

#include "Date.h"

class LPOData {
	double wind, air, baro;
	Date dateRecorded;
public:
	LPOData();
	LPOData(double, double, double);
	LPOData(double, double, double, Date);
	~LPOData();

	void setAirTemp(double at);
	void setBaroPressure(double bp);
	void setWindGust(double wg);

	double getAirTemp();
	double getBaroPressure();
	double getWindGust();

	/*bool sortByAirTemp(LPOData &lhs, LPOData &rhs);
	bool sortByBaroPressure(LPOData &lhs, LPOData &rhs);
	bool sortByWindGust(LPOData &lhs, LPOData &rhs);*/

};

LPOData::LPOData() {
	air = 0.0;
	baro = 0.0;
	wind = 0.0;
}

LPOData::LPOData(double at, double bp, double wg) {

	air = at;
	baro = bp;
	wind = wg;
}

LPOData::LPOData(double at, double bp, double wg, Date date) {

	air = at;
	baro = bp;
	wind = wg;
	dateRecorded = date;
}

LPOData::~LPOData() {}

void LPOData::setAirTemp(double at) {
	air = at;
}

void LPOData::setBaroPressure(double bp) {
	baro = bp;
}

void LPOData::setWindGust(double wg) {
	wind = wg;
}

double LPOData::getAirTemp() {
	return air;
}

double LPOData::getBaroPressure() {
	return baro;
}

double LPOData::getWindGust() {
	return wind;
}

/*bool LPOData::sortByAirTemp(LPOData &lhs, LPOData &rhs) {
	return lhs.getAirTemp() < rhs.getAirTemp();
}

bool LPOData::sortByBaroPressure(LPOData &lhs, LPOData &rhs) {
	return lhs.getBaroPressure() < rhs.getBaroPressure();
}
bool LPOData::sortByWindGust(LPOData &lhs, LPOData &rhs) {
	return lhs.getWindGust() < rhs.getWindGust();
}*/
#endif