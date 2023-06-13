#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "1_Genres.h"

///Skontroluje nepovolene znaky.
bool notAllowedG(char character){
    char notallowed[] = {'\0','\n','\t','\r','\"','\'','\\',
                         '0','1','2','3','4','5','6','7','8','9','0'};
    for (int i = 0; i < sizeof(notallowed); ++i) {
        if (character == notallowed[i]){
            return true;
        }
    }
    return false;
}

///Skontroluje format zanru.
bool genresCheck(const string& genrename){
    string name = genrename;
    for (int i = 0; i < name.size(); ++i) {
        if (notAllowedG(name[i])){
            return false;
        }
    }
    return true;

}

///Prida zaner do "genres" , a vraty true. Inak vrati false.
bool Genres::add(string genre) {
    if (genresCheck(genre)){
        transform(genre.begin(), genre.end(),genre.begin(), ::toupper);
        genres.insert(genre);
        return true;
    }
    return false;
}

///Skontroluje ci sa zaner nachadza v "genres".
bool Genres::isGenre(string genre) {
    transform(genre.begin(), genre.end(),genre.begin(), ::toupper);
    if (genres.count(genre) == 1){
        return true;
    }
    return false;
}

/// Ak je input == "empty" tak vytvory prazdnu triedu Genres.
/// Inak vklada zanre zo vstutu vo formate: "<zaner> <zaner> ... .
Genres::Genres(const string& input) {
    if (!genresCheck(input) || input == "empty"){
        return;
    }
    stringstream in(input);
    string genre;
    while (in >> genre){
        this->add(genre);
    }
}

Genres::Genres() : Genres(gdefault) {
}

///Skontoluje ci je trieda Genres prazdna.
bool Genres::empty() {
    if (genres.empty()){
        return true;
    }
    return false;
}

///Vrati zanre ako string vo formate: "<zaner> <zaner> ... "
string Genres::toString() {
    string answer;
    for (const string &genre : genres){
        answer += genre + ' ';
    }
    if (answer.empty()){
        return "empty";
    }
    answer.pop_back();
    return answer;
}
