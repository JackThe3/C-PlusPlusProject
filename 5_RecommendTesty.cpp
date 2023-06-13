#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "2_Film.h"
#include "3_Collection.h"
#include "4_User.h"

//Komentare s vypoctom su pre:
/*
genreRate = 2;
directorRate = 3;
actorRate = 3;
friendRate = 3; //3
*/

TEST(RecommendTest, rating) {
    Genres g;
    g.add("SCIFI");
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    ASSERT_EQ("STAR WARS;2019;SCIFI", c["STAR WARS"].info());
    jano.logIn("password");
    Film film = c["Hobbit Cesta"];
    jano.rateFilm(film, 10);
    film = c[1];
    jano.rateFilm(film, 5);
    jano.rateFilm(c["Lord of War"], 4);
    ASSERT_TRUE(jano.wasRated(c["Lord of War"]));
    ASSERT_EQ(10, jano.getRating(c["Hobbit Cesta"]));
    ASSERT_EQ(-1, jano.getRating(c["Logan"]));
    jano.logOff();
    ASSERT_FALSE(jano.isUserLoggedIn());
}

TEST(RecommendTest, ratingprepisanie) {
    Genres g;
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    jano.logIn("password");
    Film film = c["Hobbit Cesta"];
    jano.rateFilm(film, 10);
    jano.rateFilm(film, 5);
    ASSERT_EQ(5, jano.getRating(c["Hobbit Cesta"]));
    ASSERT_EQ(5, jano.getPreference()["FANTASY"]);  //2x ten isty
    ASSERT_EQ(-1, jano.getRating(c["Logan"]));
    jano.logOff();
    ASSERT_FALSE(jano.isUserLoggedIn());
}

TEST(RecommendTest, ratingprepisanie2) {
    Genres g;
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    jano.logIn("password");
    Film film1 = c["Hobbit Cesta"];
    jano.rateFilm(film1, 10);
    Film film2 = c["Hobbit Drak"];
    jano.rateFilm(film2, 5);
    int rate = 10 + (5/genreRate);
    ASSERT_EQ(rate, jano.getPreference()["FANTASY"]);     //10 + (5/(genreRate))
    jano.rateFilm(film1, 5);
    ASSERT_EQ(5, jano.getRating(c["Hobbit Cesta"]));
    ASSERT_EQ(rate - 10 + (5/genreRate), jano.getPreference()["FANTASY"]);     //rate - 10 + (5/(genreRate)
    jano.logOff();
}


TEST(RecommendTest, preference) {
    Genres g;
    g.add("SCIFI");
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    ASSERT_EQ("STAR WARS;2019;SCIFI", c["STAR WARS"].info());
    jano.logIn("password");
    Film film = c["Hobbit Cesta"];
    jano.rateFilm(film, 10);
    film = c[1];    //hobbit Drak
    jano.rateFilm(film, 5);
    int rate = 10 + (5/genreRate);
    ASSERT_EQ(10, jano.getRating(c["Hobbit Cesta"]));                                                                                                      //2
    ASSERT_EQ(rate, jano.getPreference()["FANTASY"]);  //Hobbit Cesta pridal skore 10 pre FANTASY ,, Hobbit drak uz hodnotenie na fantasy mal tak prida 5/(genreRate) + predchadzajuci rating(10) 10+2
    jano.logOff();
    ASSERT_FALSE(jano.isUserLoggedIn());
}

TEST(RecommendTest, actorpreference) {
    Genres g;
    g.add("SCIFI");
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    jano.logIn("password");
    Film film = c["Total Recall"];
    jano.rateFilm(film,10);
    auto a = jano.recommned(c); //10 pre action 10 pre herca A.S.   //oba boli pridane prvy krat preto 10 + 10 = 20
    jano.logOff();
    ASSERT_FALSE(jano.isUserLoggedIn());
    Collection odporucane(a);
    ASSERT_EQ("Terminator 2: Judgment Day", odporucane[0].getName());
    ASSERT_EQ(20, a[0].second);
}

TEST(RecommendTest, genreandactorpreference) {
    Genres g;
    g.add("SCIFI");
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    ASSERT_EQ("STAR WARS;2019;SCIFI", c["STAR WARS"].info());
    jano.logIn("password");
    Film film = c[0];
    jano.rateFilm(c["Hobbit Cesta;2012"],10);
    film = c[1];
    jano.rateFilm(c["Hobbit Drak"],5);
    film = c[2];
    jano.rateFilm(film,4);
    auto a = jano.recommned(c); //F 12 a D jackson 11
    jano.logOff();
    int rate = 10 + 5/genreRate; //pre genreRate==2 -> 12
    ASSERT_FALSE(jano.isUserLoggedIn());
    ASSERT_EQ(rate, a[0].second); //12
    ASSERT_EQ("DRAMA", a[1].first.getGenre());

}


TEST(RecommendTest, genrepreferencewithfriend) {
    User jano = User("Jano", "password");
    User fero = User("fero", "password");
    jano.logIn("password");
    ASSERT_TRUE(jano.addFriend(&fero));
    Genres g;
    g.add("SCIFI");
    fero.logIn("password");
    Collection c("subor.txt", g);
    fero.rateFilm(c["The Lion King;2019"], 8); //Musical preference = 8
    fero.rateFilm(c["STAR WARS"], 8);  //Scifi preference = 8
    fero.rateFilm(c["Lord of Ring;2002"], 8);  //Fantasy preference = 8
    Film film = c[0];
    jano.rateFilm(film,10); //F 10
    film = c[1];
    jano.rateFilm(film,5);  //F 5
    film = c[2];
    jano.rateFilm(film,4);  //D 4
    auto a = jano.recommned(c);
    jano.logOff();
    int rate = 10 + 5/genreRate + 8/friendRate;
    ASSERT_FALSE(jano.isUserLoggedIn());
    ASSERT_EQ(rate, a[0].second);     //10 + (5/2) + (8/3)
}

TEST(RecommendTest, genrepreferencewithfriendanddirector) {
    User jano = User("Jano", "password");
    User *fero = new User("fero", "password");
    jano.logIn("password");
    ASSERT_TRUE(jano.addFriend(fero));
    Genres g;
    g.add("SCIFI");
    fero->logIn("password");
    Collection c("subor.txt", g);
    fero->rateFilm(c["The Lion King;2019"], 8); //M 8
    fero->rateFilm(c["STAR WARS"], 8);  //S 8
    fero->rateFilm(c["Lord of Ring;2002"], 8);  //F 8
    Film film = c[0];
    jano.rateFilm(film,10); //F 10
    film = c[1];
    jano.rateFilm(film,5);  //F 5   10 + (5/2)
    film = c[2];
    jano.rateFilm(film,4);  //D 4
    int jenoFantasySkore = (10 + 5/genreRate);
    auto a = jano.recommned(c);
    ASSERT_FALSE(fero->addFriend(fero));
    ASSERT_TRUE(fero->addFriend(&jano));
    jano.logOff();
    auto b = fero->recommned(c);
    int rate1 = 10 + 5/genreRate + 8/friendRate;
    ASSERT_EQ(rate1, a[0].second);     //10 + (5/2) + (8/3) //pre genreRate==2 friendRate==3
    int rate2 = 8 + jenoFantasySkore/friendRate + 11 + 10 + 10;
    ASSERT_EQ(rate2, b[0].second);     //fero preferenia na Fantasy = 8    janova je 10 + (5/2) cize 14/3 + 8 = 12    kede fero nema hodnotenie na P.jacksona tak dostanevalue 11 -> 12 + 11 = 23 + 10 a 10 za hercov
}
