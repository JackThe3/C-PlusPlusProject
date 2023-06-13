#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

#pragma once

#include "2_Film.h"


///default genres rate (pouzite v 5_Recommend)
const int genreRate = 2; //2

///default director rate (pouzite v 5_Recommend)
const int directorRate = 3; //3

///default actor rate (pouzite v 5_Recommend)
const int actorRate = 3;  //3

///default friend rate (pouzite v 5_Recommend)
const int friendRate = 3; //3


/// User sa musi prihlasit aby si mohol pridat priatela alebo aby hodnotil film
/// hodnotenia je mozne ulozit do suboru s nazvom: "menouzivatelaUser_file"
/// hodnotenie je mozne od 1 do 10
/// pri hodnoteny vznika preferencia (zatial ina podla zanru)

/// ak preferenia neexistuje tak sa vytvory a ma "skore" rovne ratingu
/// ak existuje tak sa vezme stavajuci rating a pripocita sa ku nemu rating/rate.

/// ak ma uzivatel priatela tak sa vezmu priatelove preferencie a ak neexistuje tak sa vytvory a ma "skore" rovne ratingu priatela
/// ak existuje tak sa vezme stavajuci rating a pripocita sa ku nemu rating/rate. Rate sa da pravit vtomto subore.
//  Priklad:
/*
 Budem hodnotit dva filmy ktore maju rovnaky zaner = x.
 Film1 hodnotim = 10 bodov
 Film2 hodnotim = 6 bodov
 preferencia pre zaner x = Film1.hodnotenie + Film2.hodnotenie/genreRate
                                10          +   6/2

 Ak tuto preferenciu ma aj moj priatel:

 preferencia pre zaner x = Film1.hodnotenie + Film2.hodnotenie/genreRate + prietelova.prfeferencia/friendRate.
                                10          +   6/2                         + 12/3

 */
class User {
    string name;
    string password;
    bool login = false;
    set<User*> friendList;

    map<Film,int> userRating;
    map<string, int> preference;

public:
    User(string username, string heslo);
    bool logIn(const string& loginPassword);
    void logOff(){login = false;}
    bool isUserLoggedIn() const;

    string getUsername(){return name;}
    bool operator== (User &rhs);
    bool createUserFile();

    bool addFriend(User *who);
    bool areFriends(User *who);
    const set<User*> &getfriendlist(){return friendList;}

    string info(const Film& ratedfilm);

    bool wasRated(Film raredFilm);
    map<string, int> getPreference() {return preference;}
    int getRating(Film film);
    const map<Film, int> &getRated(){return userRating;}

    //5_Recommend.cpp
    bool rateFilm(const Film& film, int rating);
    void inserpreference(const string& preferencName, int rating, int rate  = 1);
    vector<Filmpair> recommned(Collection c);


};

