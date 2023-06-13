#include <string>
#include <algorithm>
#include "2_Film.h"
#include <ctime>

///nastavy sucastny rok
time_t t = std::time(nullptr);
tm* now = std::localtime(&t);
const int yearnow = now->tm_year + 1900;

///Skontroluje nepovolene znaky.
bool notAllowed(char character){
    char notallowed[] = {'\0','\n','\t','\r','\"','\'','\\',};
    for (int i = 0; i < sizeof(notallowed); ++i) {
        if (character == notallowed[i]){
            return true;
        }
    }
    return false;
}

///Skontroluje format zanru.
bool nameCheck(const string& filmname){
    if (filmname.empty()){
        return false;
    }
    string name = filmname;
    for (int i = 0; i < name.size(); ++i) {
        if (notAllowed(name[i])){
            return false;
        }
    }
    return true;

}

///Skontroluje vstupne hodnoty a vytvory Film. Ak sa neuvedu zanre tak sa pouziju defaultne.
Film::Film(const string& name, int year, const string &genre, const Genres& g) {
    this->allowed = g;
    if (nameCheck(name) && yearnow >= year && year >= 1900 && allowed.isGenre(genre)){
        this->name = name;
        this->year = year;
        this->genre = genre;
    }
    else{
        return;
    }
}

///// info format je: "<meno>;<rok>;<zaner>D:<reziser;A:<herec>,<herec>,..." reziser a hereci nemusia byt uvedeny.
string Film::info() const {
    string answer;
    answer += shortInfo();
    if (!director.empty()){
        answer += ";";
        answer += "D:" + this->getDirector();
    }
    if (!actors.empty()){
        answer += ";";
        answer += "A:";
        answer += this->infoActors();
    }
    return answer;
}

///shortInfo format je: "<meno>;<rok>;<zaner>".
string Film::shortInfo() const { //povodne info bez director a actors pouziva sa pri user::info
    if (this->filmEmpty()){
        return "Empty_Film";
    }
    string answer;
    answer = this->getName() + ";" + to_string(this->getYear()) + ";" + this->getGenre();
    return answer;
}

///Skontroluje ci je film prazdny.
bool Film::filmEmpty() const {
    if (this->getName().empty() || this->getYear() == 0 || this->getGenre().empty()){
        return true;
    }
    return false;
}

///Nastavy meno a vrati true. Inak vrati false.
bool Film::setName(const string& filmname) {
    if (nameCheck(filmname)){
        this->name = filmname;
        return true;
    }
    return false;
}

///Nastavy rok a vrati true. Inak vrati false.
bool Film::setYear(int newyear) {
    if (yearnow >= newyear && newyear >= 1900){
        this->year = newyear;
        return true;
    }
    return false;
}

///Nastavy zaner a vrati true. Inak vrati false.
bool Film::setGenre(const string &newgenre) {
    if (allowed.isGenre(newgenre)){
        this->genre = newgenre;
        return true;
    }
    return false;
}

///Filmy sa rovnaju vtedy, ked maju rovnaky nazov a rok. Napr. The Lion King;1994;MUSICAL != The Lion King;2019;MUSICAL
bool Film::operator==(Film &rhs) const {
    if (this->getName() == rhs.getName() && this->getYear() == rhs.getYear()){
        return true;
    }
    return false;
}

bool Film::operator!=(Film &rhs) const {
    return !this->operator==(rhs);
}

///Porovna filmy podla roku alebo podla mena.
bool Film::operator<(const Film &rhs) const {
    if (this->getYear() < rhs.getYear() || this->getName() < rhs.getName()){
        return true;
    }
    return false;
}


///Nastavy rezisera a vrati true. Inak vrati false. k je dname == "" tak vymaze rezisera.
///Film nesmie byt prazdny.
bool Film::setDirector(const string& dname) {
    if (dname.empty()){
        director = "";
        return true;
    }
    if (nameCheck(dname) && !this->filmEmpty()){
        director = dname;
        return true;
    }
    return false;
}

///Nastavy hercov a vrati true. Inak vrati false. Ak je actorslist == "" tak vymaze hercov.
///Film nesmie byt prazdny. Vsstup musi mat format: "<herec>,<herec>, ...
bool Film::setActors(const string &actorslist) {    // "" zresetuje actors
    if (actorslist.empty()){
        actors.clear();
        return true;
    }
    string copy = actorslist;
    replace( copy.begin(), copy.end(), ' ', '_');
    replace( copy.begin(), copy.end(), ',', ' ');
    if (copy.empty() || this->filmEmpty()){
        return false;
    }
    stringstream in(copy);
    string actor;
    while (in >> actor){
        replace( actor.begin(), actor.end(), '_', ' ');
        if (actor[0]== ' '){
            actor.erase(0,1);
        }
        actors.push_back(actor);
    }
    return true;
}

///Vrati hercov ako string vo formate: "<herec>,<herec>, ... "
string Film::infoActors() const {
    string answer;
    for (const string &actor : actors){
        answer += actor + ",";
    }
    if (answer.empty()){
        return "";
    }
    answer.pop_back();
    return answer;
}


