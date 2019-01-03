#pragma once
#include <string>

class madate
{
	int _jour;
	int _mois;
	long int _annee;
	 int nbrjour[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };// si le mois est trente ou non
public:
	madate();
	madate(int ctorjour, int ctormois,long int ctorannee);
	~madate();
	int jourecoule();
	int totalMois();
	int TotalAnnee(madate lhs);
	int jourecoule(madate lhs);
	bool isBesxtile();
	const int enNum() ;
	const int enTouteLettre() ;
	void setMois(int newMois);
	void setAnnee(int newAnnee);
	void setDay(int newDay);
	bool const operator>(madate &lhs);
	void operator++();
	long int excel();
	bool const operator<(madate& lhs);
	bool const operator==(madate& lhs);
	
};

