#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#pragma once

#include "1_Genres.h"

///    Filmy ukladaju len svoj nazov, rok premiery, zaner, rezisera a hercov.
///    Ak sa pri vytvarany filmu neuvedu genres tak filmy budu pouzivat defaultne genres.
///    Nazov filmu, rok a zaner su povinne.

class Film {
    string name;
    int year = 0;
    string genre;
    string director;
    vector<string> actors;
    Genres allowed = Genres(gdefault);

public:
    Film(const string& name, int year, const string& genre, const Genres& g = Genres());
    Film()= default;

    string getName() const {return name;}
    int getYear() const {return year;}
    string getGenre() const {return genre;}
    string getDirector() const {return director;}
    vector<string> getActors() const {return actors;}

    bool setName(const string& filmname);
    bool setYear( int newyear);
    bool setGenre(const string& newgenre);
    bool setDirector(const string& dname);
    bool setActors(const string& actorslist);

    bool operator== (Film &rhs) const;
    bool operator!= (Film &rhs) const;
    bool operator< (const Film &rhs) const;

    string info() const;
    string infoActors() const;
    string shortInfo() const;

    bool filmEmpty() const;
};

