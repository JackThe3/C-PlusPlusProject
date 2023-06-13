#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "2_Film.h"
#include "3_Collection.h"
#include "4_User.h"


TEST(UserTest, logintest) {
    User jano = User("Jano", "password");
    ASSERT_FALSE(jano.logIn("zleheslo"));
    ASSERT_FALSE(jano.isUserLoggedIn());
    ASSERT_TRUE(jano.logIn("password"));
    ASSERT_TRUE(jano.isUserLoggedIn());
}

TEST(UserTest, friendList) {
    User jano = User("Jano", "password");
    User fero = User("fero", "password");
    User karol = User("karol", "password");
    ASSERT_FALSE(jano.addFriend(&fero));
    jano.logIn("password");
    ASSERT_TRUE(jano.addFriend(&fero));
    jano.addFriend(&fero);
    ASSERT_TRUE(jano.areFriends(&fero));
    ASSERT_FALSE(jano.areFriends(&karol));
}


TEST(UserTest, userfile) {
    Genres g;
    g.add("SCIFI");
    Collection c("subor.txt", g);
    User jano = User("Jano", "password");
    ASSERT_EQ("STAR WARS;2019;SCIFI", c["STAR WARS"].info());
    jano.logIn("password");
    Film film = c["Hobbit Cesta"];
    jano.rateFilm(film, 10);
    film = c["Hobbit Drak"];    //Hobbit Drak
    jano.rateFilm(film, 5);
    jano.rateFilm(c["Lord of War"], 4);
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY%10", jano.info(c["Hobbit Cesta"]));
    ASSERT_EQ("Not Rated", jano.info(c["Logan"]));
    jano.logOff();
    ASSERT_FALSE(jano.createUserFile());
    jano.logIn("password");
    ASSERT_TRUE(jano.createUserFile());
    jano.logOff();
}
