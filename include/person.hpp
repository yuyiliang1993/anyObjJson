#pragma once
#include "serialize.hpp"

using namespace json;

struct Person;
struct Singer {
	std::string type;
	int age;
};

struct Address {
	std::string country;
	std::string city;
	std::string street;
	std::vector<Person> neighbors;
};
struct Friend {
	std::string relation;
	json::ANY secret;
};

struct Person {
	std::string name;
	int age;
	Address address;
	std::vector<Friend> _friends;
	json::ANY secret;	
	
	//friend std::ostream& operator<< (std::ostream&, const Person&);

	friend bool operator==(const Person &ob1, const Person &ob2);
	bool operator==(const Person &rhs);
    
};

template<class Archive>
void serialize(Archive& ar, Singer& a)
{
	ar	& JSON_NI_SERIALIZATION_NVP(a, type)
		& JSON_NI_SERIALIZATION_NVP(a, age);
}

template<class Archive>
void serialize(Archive& ar, Address& a)
{
	ar	& JSON_NI_SERIALIZATION_NVP(a, country)
		& JSON_NI_SERIALIZATION_NVP(a, city)
		& JSON_NI_SERIALIZATION_NVP(a, street)
		& JSON_NI_SERIALIZATION_NVP(a, neighbors);
}

template<class Archive>
void serialize(Archive& ar, Friend& a)
{
	ar	& JSON_NI_SERIALIZATION_NVP(a, relation)
		& JSON_NI_SERIALIZATION_NVP(a, secret);
}

template<class Archive>
void serialize(Archive& ar, Person& a)
{
	ar	& JSON_NI_SERIALIZATION_NVP(a, name)
		& JSON_NI_SERIALIZATION_NVP(a, age)
		& JSON_NI_SERIALIZATION_NVP(a, address)
		& JSON_NI_SERIALIZATION_NVP(a, _friends)
		& JSON_NI_SERIALIZATION_NVP(a, secret);
}

bool operator==(const Person  &ob1, const Person &ob2)
{
	return (ob1.name == ob2.name && ob1.age == ob2.age);
}
 
bool Person::operator==(const Person &rhs)
{
	return (name == rhs.name && age == rhs.age);
}