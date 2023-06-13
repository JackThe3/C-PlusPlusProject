#include <iostream>
#include <fstream>
#include <string>
#include "algorithm"
#include "3_Collection.h"
#include "4_User.h"

using namespace std;

///Zaregistruje pouzivatela.
User::User(string username, string heslo) {
    this->name = move(username);
    this->password = move(heslo);
}

///Prihlasi pouzivatela.
bool User::logIn(const string& loginPassword) {
    if (loginPassword == this->password){
        login = true;
        return true;
    }
    return false;
}

///Skontroluje ci je User prihlaseny.
bool User::isUserLoggedIn() const {
    if (login){
        return true;
    }
    return false;
}

///User si prida priatela do friendlistu.
bool User::addFriend(User *who) {
    if (this == who){
        return false;
    }
    if (this->isUserLoggedIn()){
        this->friendList.insert(who);
        return true;
    }
    return false;
}

///Skontoluje ci su pouzivatelia priatelia.
bool User::areFriends(User *who) {
    if (friendList.count((User *const) who) == 0){
        return false;
    }
    return true;
}

///Skontroluje ci su pouzivatelia rovnaky.
bool User::operator==(User &rhs) {
    if (this->getUsername() == rhs.getUsername()){
        return true;
    }
    return false;
}

///Skontoluje ci Film bol hodnoteny.
bool User::wasRated(Film raredFilm) {
    for (auto & i : userRating) {
        if (i.first == raredFilm){
            return true;
        }
    }
    return false;
}

///Vrati rating filmu, ak este nebol hodnoteny vrati -1.
int User::getRating(Film film) {
    for (auto & i : userRating) {
        if (i.first == film){
            return i.second;
        }
    }
    return -1;
}

///Vrati string vo formate: <nazovfilmu>;<rokpremiery>;<ZANER>%<hodnotenie>, ak nebol hodnoteny vrati "Not Rated".
string User::info(const Film& ratedfilm) {
    string answer;
    int rating = this->getRating(ratedfilm);
    if (rating == -1){
        return "Not Rated";
    }
    answer = ratedfilm.shortInfo() +"%" + to_string(rating);
    return answer;
}

///Vytvory osobny subor pouzivatela v ktorom su vsetky jeho hodnotene filmi.
///Use musi byt prihlaseny. Subor bude mat meno: <Username>_User_file.
bool User::createUserFile() {
    if (!this->isUserLoggedIn()){
        return false;
    }
    string fname = this->getUsername() + "_User_file";
    ofstream newfile;
    newfile.open(fname, ios::out);
    for (const auto & i : getRated()) {
        string vloz = this->info(i.first) + '\n';
        newfile << vloz;
    }
    newfile.close();
    return true;
}
