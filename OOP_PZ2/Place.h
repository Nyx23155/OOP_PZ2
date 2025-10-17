#pragma once
#include <string>

class Place
{
public:
	void setName(const std::string& name) { Name = name; }
	void setCity(const std::string& city) { City = city; }
	void setCountry(const std::string& country) { Country = country; }

	std::string getName() const { return Name; }
	std::string getCity() const { return City; }
	std::string getCountry() const { return Country; }

private:
	std::string Name;
	std::string City;
	std::string Country;
};