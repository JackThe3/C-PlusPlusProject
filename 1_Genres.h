#include <iostream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

#pragma once

///default genres
const string gdefault = "ACTION ADVENTURE COMEDY DRAMA FANTASY HISTORICAL HORROR MYSTERY MUSICAL";

///Zanre sa pouzivaju pri vytvarani Film class. Ak sa pri vytvarany neuvedie zoznam tak sa pouziju zanre:
///"ACTION ADVENTURE COMEDY DRAMA FANTASY HISTORICAL HORROR MYSTERY MUSICAL";
class Genres{
    set<string> genres;

public:
    Genres();
    Genres(const string& input);

    bool add(string genre);
    bool isGenre(string genre);
    void remove(const string& input){genres.erase(input);}
    bool empty();

    string toString();
};