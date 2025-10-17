#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Album.h"
#include "Photo.h"
#include "Person.h"
#include "Place.h"
#include <map>
#include <algorithm>

using namespace std;

void addPerson(vector<Person*>& people, const string& fullName, const string& sex)
{
	Person* person = new Person();

	person->setFullName(fullName);
	person->setSex(sex);

	people.push_back(person);
}


void addPlace(vector<Place*>& places, const string& name, const string& city, const string& country)
{
	Place* place = new Place();
	place->setName(name);
	place->setCity(city);
	place->setCountry(country);
	places.push_back(place);
}

void addAlbum(vector<Album*>& albums, const string& name)
{
	Album* album = new Album();
	album->setName(name);
	albums.push_back(album);
}

void addPhoto(vector<Photo*>& photos, const string& dir, const chrono::system_clock::time_point& date,
	const vector<Person*>& capturedPeople, const vector<Place*>& capturedPlaces,
	const string& comment, Album* parentAlbum)
{
	Photo* photo = new Photo();
	photo->setDir(dir);
	photo->setDate(date);

	for (Person* person : capturedPeople)
	{
		photo->addCapturedPerson(person);
	}

	for (Place* place : capturedPlaces)
	{
		photo->addCapturedPlace(place);
	}
	photo->setComment(comment);

	if (parentAlbum)
	{
		parentAlbum->addPhoto(photo);
	}

	photos.push_back(photo);
}

int main() {
    // --- ШАГ 1: Создание всех исходных данных ---

    vector<Person*> allPeople;
    addPerson(allPeople, "Ivan Petrenko", "M");     // Index 0
    addPerson(allPeople, "Maria Koval", "W");       // Index 1
    addPerson(allPeople, "Oleksiy Sydorenko", "M"); // Index 2
    addPerson(allPeople, "Olena Bondarenko", "W");  // Index 3
    addPerson(allPeople, "Sergiy Melnyk", "M");     // Index 4
    addPerson(allPeople, "Natalia Shevchenko", "W");// Index 5

    vector<Place*> allPlaces;
    addPlace(allPlaces, "Home", "Kyiv", "Ukraine");           // Index 0
    addPlace(allPlaces, "Arcadia Beach", "Odessa", "Ukraine");  // Index 1
    addPlace(allPlaces, "Carpathians", "Lviv", "Ukraine");      // Index 2
    addPlace(allPlaces, "Shevchenko Park", "Dnipro", "Ukraine"); // Index 3
    addPlace(allPlaces, "Freedom Square", "Kharkiv", "Ukraine");// Index 4
    addPlace(allPlaces, "Gorky Park", "Kharkiv", "Ukraine");   // Index 5
    addPlace(allPlaces, "Eiffel Tower", "Paris", "France");     // Index 6

    vector<Album*> allAlbums;
    addAlbum(allAlbums, "Vacation");    // Index 0
    addAlbum(allAlbums, "Family");      // Index 1
    addAlbum(allAlbums, "Landscapes");  // Index 2

    vector<Photo*> allPhotos;
    auto now = chrono::system_clock::now();

    // --- Добавляем много фотографий для наглядных результатов ---

    // Фото для статистики по ЗИМЕ
    addPhoto(allPhotos, "/photos/winter_lviv.jpg", now - chrono::hours(24 * 300),
        { allPeople[0], allPeople[1] }, { allPlaces[2] }, "Lviv in winter", allAlbums[0]);

    // Фото для статистики по ВЕСНЕ
    addPhoto(allPhotos, "/photos/spring_kyiv.jpg", now - chrono::hours(24 * 200),
        { allPeople[1], allPeople[3] }, { allPlaces[0] }, "Kyiv blooming", allAlbums[1]);

    // Фото для статистики по ЛЕТУ
    addPhoto(allPhotos, "/photos/summer_odessa.jpg", now - chrono::hours(24 * 120),
        { allPeople[0], allPeople[1], allPeople[4] }, { allPlaces[1] }, "Odessa beach party", allAlbums[0]);

    // Еще одно летнее фото, чтобы сделать Ивана и Марию "друзьями"
    addPhoto(allPhotos, "/photos/summer_hike.jpg", now - chrono::hours(24 * 110),
        { allPeople[0], allPeople[1] }, { allPlaces[2] }, "Summer mountain hike", allAlbums[0]);

    // Фото для статистики по ОСЕНИ
    addPhoto(allPhotos, "/photos/autumn_park.jpg", now - chrono::hours(24 * 20),
        { allPeople[1], allPeople[2], allPeople[3] }, { allPlaces[3] }, "Autumn walk in Dnipro", allAlbums[1]);

    // Еще одно фото, чтобы сделать Ивана и Марию "друзьями"
    addPhoto(allPhotos, "/photos/paris_trip.jpg", now - chrono::hours(24 * 150),
        { allPeople[0], allPeople[1] }, { allPlaces[6] }, "Romantic Paris", allAlbums[0]);

    // Фото годичной давности для проверки фильтра по дате
    addPhoto(allPhotos, "/photos/old_lviv.jpg", now - chrono::hours(24 * 400),
        { allPeople[0], allPeople[1] }, { allPlaces[2] }, "Throwback trip to Lviv", allAlbums[0]);

    // Групповое фото, чтобы поднять популярность Марии и города Харьков
    addPhoto(allPhotos, "/photos/group_kharkiv.jpg", now - chrono::hours(24 * 40),
        { allPeople[1], allPeople[4], allPeople[5] }, { allPlaces[4] }, "Friends in Kharkiv", allAlbums[1]);

    // Пейзажные фото для альбома "Landscapes" (без людей)
    addPhoto(allPhotos, "/photos/landscape_lviv.jpg", now - chrono::hours(24 * 180),
        {}, { allPlaces[2] }, "Lviv mountains, no people", allAlbums[2]);
    addPhoto(allPhotos, "/photos/landscape_odessa.jpg", now - chrono::hours(24 * 100),
        {}, { allPlaces[1] }, "Empty beach in Odessa", allAlbums[2]);

    // Проверка логики добавления фото, которое уже есть в другом альбоме
    cout << "\n--- Testing album logic ---" << endl;
    allAlbums[1]->addPhoto(allPhotos[0]); // Пытаемся добавить "winter_lviv.jpg" (уже в "Vacation") в "Family"
    cout << "-------------------------\n" << endl;


    // --- ШАГ 2: Выполнение задач из задания ---

    // ЗАДАЧА: Роздрукувати список фотографій за останній рік
    cout << "--- Photos from the last year ---" << endl;

    auto one_year_ago = chrono::system_clock::now() - chrono::hours(24 * 365);
    for (Photo* photo : allPhotos) {
        if (photo->getDate() > one_year_ago) {
            time_t photo_time = chrono::system_clock::to_time_t(photo->getDate());
            char time_str[26];
            ctime_s(time_str, sizeof(time_str), &photo_time);
            cout << "Path: " << photo->getDir() << ", Date: " << time_str;
        }
    }
    cout << "---------------------------------" << endl;


    // ЗАДАЧА: Роздрукувати список 5 найчастіше запечатлених міст
    cout << "\n--- Top 5 most frequent cities ---" << endl;

    map<string, int> cityCount;
    for (Photo* photo : allPhotos) {
        for (Place* place : photo->getCapturedPlaces()) {
            cityCount[place->getCity()]++;
        }
    }

    vector<pair<string, int>> sortedCities(cityCount.begin(), cityCount.end());
    sort(sortedCities.begin(), sortedCities.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
        });

    int citiesToPrint = min(5, (int)sortedCities.size());
    for (int i = 0; i < citiesToPrint; i++) {
        cout << i + 1 << ". " << sortedCities[i].first
            << " - seen: " << sortedCities[i].second << " times" << endl;
    }
    cout << "----------------------------------" << endl;

    //ЗАДАЧА: Роздрукувати список 5 найчастіше запечатлених людей за спаданням
	cout << "\n--- Top 5 most frequently captured people ---" << endl;

	map<string, int> personCount;
	for (Photo* photo : allPhotos) {
		for (Person* person : photo->getCapturedPeople()) {
			personCount[person->getFullName()]++;
		}
	}

	vector<pair<string, int>> sortedPeople(personCount.begin(), personCount.end());
	sort(sortedPeople.begin(), sortedPeople.end(),
		[](const pair<string, int>& a, const pair<string, int>& b) {
			return a.second > b.second;
		});

	int peopleToPrint = min(5, (int)sortedPeople.size());
	for (int i = 0; i < peopleToPrint; i++) {
		cout << i + 1 << ". " << sortedPeople[i].first
			<< " - captured: " << sortedPeople[i].second << " times" << endl;
	}
	cout << "----------------------------------" << endl;

    // ЗАДАЧА: Роздрукувати список альбомів, де не запечатлено жодної людини (тільки місця)
	cout << "\n--- Albums with no people ---" << endl;
	for (Album* album : allAlbums) {
		bool hasPeople = false;
		for (Photo* photo : album->getPhotos()) {
			if (!photo->getCapturedPeople().empty()) {
				hasPeople = true;
				break;
			}
		}
		if (!hasPeople) {
			cout << "Album: " << album->getName() << endl;
		}
	}
	cout << "-----------------------------" << endl;

    // ЗАДАЧА: Роздрукувати загальну кількість фотографій за сезонами кожного року зима, весна, літо, осінь
	cout << "\n--- Photo counts by season ---" << endl;

    map<string, int> totalSeasonCounts;

    for (Photo* photo : allPhotos) {
        time_t photo_time = chrono::system_clock::to_time_t(photo->getDate());
        tm local_tm;
        localtime_s(&local_tm, &photo_time);
        int month = local_tm.tm_mon + 1;

        string season;
        if (month == 12 || month <= 2) season = "Winter";
        else if (month >= 3 && month <= 5) season = "Spring";
        else if (month >= 6 && month <= 8) season = "Summer";
        else season = "Autumn";

        totalSeasonCounts[season]++;
    }

    for (const auto& entry : totalSeasonCounts) {
        cout << entry.first << ": " << entry.second << " photos" << endl;
    }
	cout << "-----------------------------" << endl;

    //ЗАДАЧА: Виявити та роздрукувати пари друзів за фотографіями: якщо пара людей спільно запечатлена на фотографіях більше 3 разів, будемо вважати таких людей друзями
	cout << "\n--- Friend pairs (more than 3 shared photos) ---" << endl;

	map<pair<string, string>, int> friendPairs;

	for (Photo* photo : allPhotos) {
		const vector<Person*>& capturedPeople = photo->getCapturedPeople();
		for (size_t i = 0; i < capturedPeople.size(); i++) {
			for (size_t j = i + 1; j < capturedPeople.size(); j++) {
				string name1 = capturedPeople[i]->getFullName();
				string name2 = capturedPeople[j]->getFullName();
				if (name1 > name2) swap(name1, name2);
				friendPairs[make_pair(name1, name2)]++;
			}
		}
	}
	for (const auto& entry : friendPairs) {
		if (entry.second > 3) {
			cout << entry.first.first << " and " << entry.first.second
				<< " - shared photos: " << entry.second << endl;
		}
	}
	cout << "----------------------------------" << endl;	

    // --- ШАГ 3: Очистка памяти ---
    cout << "\nCleaning up memory..." << endl;
    for (Person* p : allPeople) delete p;
    for (Place* p : allPlaces) delete p;
    for (Album* a : allAlbums) delete a;
    for (Photo* p : allPhotos) delete p;
    cout << "Cleanup complete." << endl;

	return 0;
}
