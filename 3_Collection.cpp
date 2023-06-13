#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "2_Film.h"
#include "3_Collection.h"

///Prida film do Collection a vrti true. Film sa moze nachadzat v Collection len raz.
bool Collection::addfilm(const Film& film) {
    if (film.filmEmpty()){
        return false;
    }
    for (Film & allfilm : allfilms) {
        if (allfilm.getName() == film.getName() && allfilm.getYear() == film.getYear()){
            return false;
        }
    }
    allfilms.push_back(film);
    return true;
}
///Indexje sa od 0.
Film &Collection::operator[](size_t index) {
    return allfilms[index];
}

///Povoleny format je [nazovfilmu] alebo [nazovfilmu;rok]
Film &Collection::operator[](const string& index) {
    int check = index.find(';');
    if (check == -1){
        for (Film & film : allfilms) {
            if (film.getName() == index){
                return film;
            }
        }
    }
    int year = 0;
    stringstream syear(index.substr(index.find(';') + 1));
    syear >> year;
    string name = index.substr(0,index.find(';'));
    for (Film & film : allfilms) {
        if (film.getName() == name && film.getYear() == year){
            return film;
        }
    }
    throw std::out_of_range ("Not exists");
}

///Z txt suboru v ktorom je "info" format vytvory Collection.
Collection::Collection(const string& fname, const Genres& g) {
    ifstream input(fname);

    if (!input) {
        throw std::runtime_error("Could not open file");
    }
    string line;
    while (getline(input, line)) {
        if (count(line.begin(), line.end(), ';') < 2){
            continue;
        }
        int year = 0;
        string name = line.substr(0, line.find(';'));

        line.erase(0, line.find(';') + 1);

        stringstream s(line.substr(0, line.find(';')));
        s >> year;
        line.erase(0, line.find(';') + 1);

        string genre = line.substr(0, line.find(';'));
        line.erase(0, line.find(';') + 1);

        if (name.empty() || year == 0 || genre.empty()){
            continue;
        }

        transform(genre.begin(), genre.end(), genre.begin(), ::toupper);

        Film vloz = *new Film(name, year, genre, g);

        if (!line.empty()) {
            if (line[0] == 'D' && line[1] == ':') {
                line.erase(0, 2);
                string director = line.substr(0, line.find(';'));
                line.erase(0, line.find(';') + 1);
                vloz.setDirector(director);
            }
            if (line[0] == 'A' && line[1] == ':') {
                line.erase(0, 2);
                string actorslist = line.substr(0, line.find(';'));
                line.erase(0, line.find(';') + 1);
                vloz.setActors(actorslist);
            }
        }
        this->addfilm(vloz);
    }
    input.close();
}

///Z preferencii vytvory Collection.
Collection::Collection(const vector<Filmpair>& reccomended) {
    for (const auto & i : reccomended) {
        this->addfilm(i.first);
    }
}


///Vytvory file s formatom info pre vsetky Film v Collection.
void Collection::createFile(const string& fname) {
    ofstream newfile;
    newfile.open(fname, ios::out);
    for (auto & allfilm : allfilms) {
        string vloz = allfilm.info() + '\n';
        newfile << vloz;
    }
    newfile.close();
}

