#ifndef _LPODATA_H
#define _LPODATA_H

class LPOData {
	double wind, air, baro;
public:
	LPOData();
	LPOData(double, double, double);
	~LPOData();
	void setAirTemp(double at);
	void setBaroPressure(double bp);
	void setWindGust(double wg);
	double getAirTemp();
	double getBaroPressure();
	double getWingGust();
};

LPOData::LPOData(double at, double bp, double wg) {

	air = at;
	baro = bp;
	wind = wg;
}

#endif