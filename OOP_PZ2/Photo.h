#pragma once
#include <string>
#include <chrono>
#include <vector>

class Place;
class Person;
class Album;

class Photo
{
public:
	void setDir(const std::string& dir) { Dir = dir; }
	void setDate(const std::chrono::system_clock::time_point& date) { Date = date; }
	void addCapturedPerson(Person* person) { capturedPeople.push_back(person); }
	void addCapturedPlace(Place* place) { capturedPlaces.push_back(place); }
	void setComment(const std::string& comm) { comment = comm; }
	void setParentAlbum(Album* album) { parentAlbum = album; }

	std::string getDir() const { return Dir; }
	std::chrono::system_clock::time_point getDate() const { return Date; }
	const std::vector<Person*>& getCapturedPeople() const { return capturedPeople; }
	const std::vector<Place*>& getCapturedPlaces() const { return capturedPlaces; }
	std::string getComment() const { return comment; }
	Album* getParentAlbum() const { return parentAlbum; }

private:
	std::string Dir;
	std::chrono::system_clock::time_point Date;
	std::vector<Person*> capturedPeople;
	std::vector<Place*> capturedPlaces;
	std::string comment;
	Album* parentAlbum = nullptr;
};