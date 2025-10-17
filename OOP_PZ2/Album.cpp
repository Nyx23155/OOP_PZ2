#include "Album.h"
#include "Photo.h"
#include <iostream>
using namespace std;

void Album::setName(const string& name)
{
	Name = name;
}

string Album::getName() const
{
	return Name;
}

vector<Photo*> Album::getPhotos() const {
	return photos;
}

void Album::addPhoto(Photo* photo) {

	if(!photo)
	{
		cout << "Cannot add a null photo to the album." << endl;
		return;
	}

	if (photo->getParentAlbum() == nullptr)
	{
		photos.push_back(photo);
		photo->setParentAlbum(this);
	}
	else
	{
		cout << "Error: Photo '"<< photo->getDir() <<"' already belongs to an album: "<< photo->getParentAlbum()->getName() << endl;
	}

}

