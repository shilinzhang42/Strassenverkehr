#include "AktivesVO.h"
#include <iostream>
#include <iomanip>

using namespace std;

int AktivesVO::p_iMaxID;
map<string, AktivesVO*> AktivesVO::p_pVOs;

AktivesVO::AktivesVO()
{
	vInitialisiere();
}

AktivesVO::AktivesVO(const string& sName)
{
	vInitialisiere();
	p_sName = sName;
	if (p_pVOs.find(sName) != p_pVOs.end())
		throw "Objekt '" + sName + "' ist bereits vorhanden.";
	p_pVOs[sName] = this;
}

AktivesVO::AktivesVO(const AktivesVO& other)
{
	vInitialisiere();
	p_sName = other.p_sName;
}

AktivesVO::~AktivesVO()
{
}

void AktivesVO::vInitialisiere()
{
	p_sName = "";
	p_iID = p_iMaxID++;
	p_dZeit = 0.0;
}


ostream& AktivesVO::ostreamAusgabe(ostream& os) const
{
	os << resetiosflags(ios::right) << setiosflags(ios::left | ios::fixed);
	os << setprecision(1);
	os << setw(4) << p_iID;
	os << setw(7) << p_sName << " : ";

	return os;
}

istream& AktivesVO::istreamEingabe(istream& is)
{
	if (p_sName != "")
		throw string("Name bereits gesetzt.");
	is >> p_sName;

	if (p_pVOs.find(p_sName) != p_pVOs.end())
		throw "Objekt '" + p_sName + "' ist bereits vorhanden.";
	p_pVOs[p_sName] = this;

	return is;
}

void AktivesVO::vAusgabe() const
{
	ostreamAusgabe(cout);
}


AktivesVO& AktivesVO::operator=(const AktivesVO& other)
{
	p_sName = other.p_sName;
	p_iID = other.p_iID;

	return *this;
}

const string& AktivesVO::getName() const
{
	return p_sName;
}

AktivesVO* AktivesVO::ptObjekt(string sName)
{
	map<string, AktivesVO*>::iterator it = p_pVOs.find(sName);
	if (it == p_pVOs.end())
		throw "Unbekanntes Objekt '" + sName + "'.";
	return it->second;
}

/*Durch operatoren Überladung wird für << ostreamAusgabe aufgerufen.*/
ostream& operator<<(ostream& os, const AktivesVO& vo)
{
	return vo.ostreamAusgabe(os);
}

istream& operator>>(istream& is, AktivesVO& vo)
{
	return vo.istreamEingabe(is);
}