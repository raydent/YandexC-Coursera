#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string& international_number) {
	stringstream ss;
	ss << international_number;
	char plus;
	if (!(ss >> plus) || plus != '+')
		throw invalid_argument("no plus");
	if (!(getline(ss, country_code_, '-')))
		throw invalid_argument("no country code");
	//if (!(ss >> plus) || plus != '-')
		//throw invalid_argument("no defis");
	if (!(getline(ss, city_code_, '-')))
		throw invalid_argument("no city code");
	//if (!(ss >> plus) || plus != '-')
		//throw invalid_argument("no second defis");
	if (!(ss >> local_number_))
		throw invalid_argument("no local number");
}
string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
	return "+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber();
}
