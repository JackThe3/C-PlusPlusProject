#include <string>
#include "algorithm"
#include "3_Collection.h"
#include "4_User.h"

///Preferencia je zaner, herec a herci.
///Ak preferencia eete nebola pridana tak ju prida a nastavy "skore" na hodnotu rating.
///Inak "skore" ku skore pripocita rating/rate (Rate je mozne nastavit v 4_User.h)
void User::inserpreference(const string& preferencName, int rating, int rate) {
    if (preferencName.empty()){
        return;
    }
    if (preference.count(preferencName) != 1){
        preference.insert(pair<string, int>(preferencName, rating));
        return;
    }
    int score = (preference[preferencName] + rating / rate);
    if (score <= 0){
        this->preference.erase(preferencName);
        return;
    }
    preference[preferencName] = score;
}

///Ohodnoty film a spracuje preferencie pre pouzivatela.
///Ak sa meni hodnotenie uz hodnoteneho filmu tak
bool User::rateFilm(const Film& film, int rating) {
    if (!this->isUserLoggedIn() || !(rating > 0 && rating < 11)){
        return false;
    }
    if (userRating.count(film) > 0){
        int currentRating = userRating[film];
        this->inserpreference(film.getDirector(), currentRating * -1);
        this->inserpreference(film.getGenre(), currentRating * -1);
        for (const string & actor : film.getActors()) {
            this->inserpreference(actor, currentRating * -1);
        }
    }
    this->inserpreference(film.getDirector(), rating, directorRate);
    for (const string & actor : film.getActors()) {
        this->inserpreference(actor, rating, actorRate);
    }
    this->inserpreference(film.getGenre(), rating,genreRate);
    userRating[film] = rating;
    return true;
}

///Sort vector podla kluca(pair.second)
bool bysecond(const Filmpair &a,const Filmpair &b){
    return a.second>b.second;
}

///Vytvory vector podla preferencici Usra a jeho priatelov
vector<Filmpair> User::recommned(Collection c) {
    vector<Filmpair> recommended;
    map<string, int> k;

    k.insert(preference.begin(), preference.end());

    for (User *f : friendList){
        for (auto &friendPreference : f->getPreference()){
            this->inserpreference(friendPreference.first, friendPreference.second , friendRate);
        }
    }

    for (const auto& film : c.getFilms()) {
        int actorcount = 0;
        if (!this->wasRated(film)) {
            int director = preference[film.getDirector()];
            int rate = preference[film.getGenre()];
            auto a = film.getActors();
            for (auto const &j  : preference) {
                if (count(a.begin(), a.end(), j.first)) {
                    actorcount += j.second;
                }
            }
            recommended.emplace_back(film, rate + director + actorcount);
        }
    }
    sort(recommended.begin(),recommended.end(),bysecond);
    preference = move(k);
    return recommended;
}