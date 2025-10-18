#pragma once
#include <string>
#include <vector>

class Photo;

class Album
{
public:

	~Album()
	{
		photos.clear();
	}

    void setName(const std::string& name);
    std::string getName() const;
    std::vector<Photo*> getPhotos() const;
    void addPhoto(Photo* photo);

private:
    std::string Name;
    std::vector<Photo*> photos;
};