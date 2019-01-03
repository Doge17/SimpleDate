// MaDate.cpp : Defines the entry point for the console application.

#include  "pch.h"
//#include "stdafx.h"
#include "madate.h"
#include <iostream>
#include <string>
using namespace std;

//TODO: Ajouter fonction en toute lettre qui affiche la date l'expression 20/12/12 en : "Jeudi 20 Decembre 2018"  (done)
madate::madate()
{
	_jour = 01;
	_mois = 01;
	_annee = 1900;
}

int
sakamoto(int d, int m, int y)
{
	int Increment[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + Increment[m - 1] + d) % 7;
}

int
bissextile(unsigned int x)
{
	return ((x % 4 == 0) && (x % 100 != 0) || (x % 400 == 0));
}

int
madate::totalMois()
{


	int totalJourMois;
	switch (this->_mois)		//convert le mois en jour accumule
	{
	case 1:
		totalJourMois = 0;
		break;
	case 2:
		totalJourMois = 31;
		break;
	case 3:
		totalJourMois = 59;
		break;
	case 4:
		totalJourMois = 90;
		break;
	case 5:
		totalJourMois = 120;
		break;
	case 6:
		totalJourMois = 151;
		break;
	case 7:
		totalJourMois = 181;
		break;
	case 8:
		totalJourMois = 212;
		break;
	case 9:
		totalJourMois = 243;
		break;
	case 10:
		totalJourMois = 273;
		break;
	case 11:
		totalJourMois = 304;
		break;
	case 12:
		totalJourMois = 334;
		break;
	}
	if (bissextile(this->_annee) && this->_mois > 2)
	{
		totalJourMois++;
	}
	return totalJourMois;

}

int
madate::TotalAnnee(madate lhs)
{
	int totalJourAnnee;
	int cpt = 0;
	if (lhs._annee > this->_annee)
		totalJourAnnee = (lhs._annee - this->_annee) * 365;
	else
		totalJourAnnee = (this->_annee - lhs._annee) * 365;

	for (int i = this->_annee; i < lhs._annee; i++)	//Bissextilite
	{
		if (bissextile(i))
		{
			cpt++;
		}
	}
	totalJourAnnee += cpt;	//on ajoute le nbr de bissextilite
	return totalJourAnnee;
}



// TODO : Fix jourecoule(madate lhs) DONE!!!!!! 
int
madate::jourecoule(madate lhs)
{

	int fromDay, toDay;
	if (this->_jour < lhs._jour)
	{
		fromDay = this->_jour + this->totalMois();	//juste
		//int a = lhs.totalMois();//juste
		//int b = this->TotalAnnee(lhs);//faux
		toDay = lhs._jour + lhs.totalMois() + this->TotalAnnee(lhs);
	}
	else
	{
		fromDay = lhs._jour + lhs.totalMois();
		toDay = this->_jour + this->totalMois() + lhs.TotalAnnee(*this);
	}
	return toDay - fromDay;



}


int
madate::jourecoule()		// depuis 1 janvier de l'anne courante
{

	int total = 0;

	int i;

	for (i = 1; i < this->_mois; i++)
	{

		total += this->nbrjour[i];


	}

	if (this->isBesxtile() && i > 2)
	{
		total++;


	}
	total += this->_jour;
	return total;

}


bool
madate::isBesxtile()
{
	return ((this->_annee % 4 == 0) && (this->_annee % 100 != 0)
		|| (this->_annee % 400 == 0));
}


madate::madate(int ctorjour, int ctormois, long int ctorannee)	// TODO: Controle (Positive)
{
	//TODO :fix les conneries de l'user(done)

	//check annee
	int negativeCheck = (1 > ctormois) ? 1 : ctormois;

	_mois = (negativeCheck > 12) ? 12 : negativeCheck;
	//check jour
	negativeCheck = (1 > ctorjour) ? 1 : ctorjour;

	if (((ctorannee % 4 == 0) && (ctorannee % 100 != 0)) && _mois == 2 && (ctorannee % 400 == 0))	//TODO: test bisextilite (done)
		_jour = (negativeCheck > 29) ? 29 : negativeCheck;
	else
		_jour = (negativeCheck > nbrjour[_mois]) ? nbrjour[_mois] : negativeCheck;

	//      TODO :(optional) fix l'erreur de la date aleatoire sans utiliser jourmax (done)

	if (ctorannee < 100)
	{
		if (ctorannee <= 40)
		{
			_annee = 2000 + ctorannee;
		}
		else
		{
			_annee = 1900 + ctorannee;
		}
	}
	else
		_annee = (0 > ctorannee) ? (-ctorannee) : ctorannee;


}



void
madate::operator++ ()
{
	this->_jour++;

	if (this->_jour > nbrjour[this->_mois])
	{
		this->_jour = this->_jour - nbrjour[this->_mois];
		this->_mois++;
		if (this->_mois > 12)
		{
			this->_mois = this->_mois - 12;
			this->_annee++;

		}
	}

}				// TODO : a fix (done)



int const
madate::enTouteLettre()
{
	std::string strMois[] =
	{
	"", "Janvier", "Fevrier", "Mars", "Avril",
		"May", "Juin", "Julliet", "Aout", "Septembre", "Octobre",
		"Novembre", "Decembre" };
	std::string strJour[] =
	{
	"", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi",
		"Dimanche" };
	std::
		cout << "le  " << strJour[sakamoto(_jour, _mois, _annee)] << " " <<
		this->_jour << " " << strMois[this->_mois] << " " << this->_annee<<std::endl;
	return 0;
}



int const
madate::enNum()
{
	std::cout << this->_jour << '/' << this->_mois << '/' << this->
		_annee << std::endl;
	return 0;
}

long int
madate::excel()
{
	return this->_mois * 1000 + this->_jour + this->_annee * 10000;
}

bool const
madate::operator> (madate & lhs)
{
	return this->excel() > lhs.excel();
}

bool const
madate::operator< (madate & lhs)
{

	return this->excel() < lhs.excel();
}

bool const
madate::operator== (madate & lhs)
{
	return this->excel() == lhs.excel();
}

madate::~madate()
{
}
