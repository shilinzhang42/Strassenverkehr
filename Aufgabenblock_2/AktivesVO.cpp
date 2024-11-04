#include "AktivesVO.h"
#include <iostream>
#include <iomanip>

using namespace std;

int AktivesVO::p_iMaxID;

AktivesVO::AktivesVO()
{
	vInitialisiere();
}

AktivesVO::AktivesVO(const string& sName)
{
	vInitialisiere();
	p_sName = sName;
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

/*Durch operatoren Überladung wird für << ostreamAusgabe aufgerufen.*/
ostream& operator<<(ostream& os, const AktivesVO& vo)
{
	return vo.ostreamAusgabe(os);
}