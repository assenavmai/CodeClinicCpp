#ifndef _LPODATA_H
#define _LPODATA_H

#include "Date.h"

class LPOData {
	double wind, air, baro;
	Date dateRecorded;
public:
	LPOData(double, double, double);
	~LPOData();
	void setAirTemp(double at);
	void setBaroPressure(double bp);
	void setWindGust(double wg);
	double getAirTemp();
	double getBaroPressure();
	double getWindGust();
};

LPOData::LPOData(double at, double bp, double wg) {

	air = at;
	baro = bp;
	wind = wg;
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

#endif