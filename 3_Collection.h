#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#pragma once

#include "2_Film.h"
typedef pair<Film,int> Filmpair;

///   Filmy sa vkladaju do "Collecion", budu as neskor pouzivat na rating filmov.
///   Collecion mozeme nacitat z txt file a Collecion mozeme zapisat do txt file.
///   Collecion sa da indoxovat podla cila, string nazovfilmu alebo string nazovfilmu;rokpremiery
///   Filmy v Collecion mozu mat rovnaky nazov a zaner ale nesmu mat rovnaky rok premiery
///   Collection sa indexuje od 0.
class Collection {

    vector<Film> allfilms;

public:
    Collection() = default;
    Collection(const string& fname, const Genres& g = Genres());
    Collection(const vector<Filmpair>& reccomended);
    Film &operator[](size_t index);
    Film &operator[](const string& index);
    bool addfilm(const Film& film);
    void createFile(const string& fname);
    const vector<Film> &getFilms(){return allfilms;}
};

