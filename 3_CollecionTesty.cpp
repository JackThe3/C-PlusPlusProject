#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "2_Film.h"
#include "3_Collection.h"

//informacie o filoch: https://www.imdb.com
TEST(CollectionTest, collection) {
    Collection c;
    Film a = Film("film", 2020, "SCIFI");
    Film o = Film("Hobbit", 2012, "FANTASY");
    Film b = Film("Hobbit", 2012, "FANTASY");
    Film d = Film("Hobbit2", 2014, "FANTASY");
    Film zly = Film("asfag", 45, "FANTASY");
    ASSERT_TRUE(zly.filmEmpty());
    ASSERT_FALSE(c.addfilm(zly));
    ASSERT_FALSE(c.addfilm(a));
    Genres g;
    g.add("SCIFI");
    a = Film("Star Wars: Episode IV - A New Hope", 1977, "SCIFI", g);
    c.addfilm(a);
    c.addfilm(o);
    c.addfilm(b);
    c.addfilm(d);
    ASSERT_EQ("Star Wars: Episode IV - A New Hope;1977;SCIFI", c[0].info());
    ASSERT_EQ("Hobbit;2012;FANTASY", c["Hobbit"].info());
}


TEST(CollectionTest, collectionfile) {
    Collection c("subor.txt");
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY;D:P.Jackson;A:Martin Freeman,Ian McKellen", c[0].info());
    ASSERT_EQ("Hobbit Drak;2014;FANTASY", c[1].shortInfo());
}

TEST(CollectionTest, collectionfileandgenres) {
    Genres g;
    g.add("SCIFI");
    Collection c("subor.txt", g);
    ASSERT_EQ("STAR WARS;2019;SCIFI", c["STAR WARS"].info());
    ASSERT_EQ("The Lion King;2019;MUSICAL", c["The Lion King;2019"].info());
    ASSERT_EQ("The Lion King;1994;MUSICAL", c["The Lion King;1994"].info());
    ASSERT_FALSE(c["The Lion King;2019"] == c["The Lion King;1994"]);
    ASSERT_TRUE(c["The Lion King;2019"] != c["STAR WARS"]);
}


TEST(CollectionTest, createfile) {
    Collection c("subor.txt");
    Film d = Film("Hobbit2", 2014, "FANTASY");
    c.addfilm(d);
    c.createFile("new.txt");
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY;D:P.Jackson;A:Martin Freeman,Ian McKellen", c[0].info());
    ASSERT_EQ("Hobbit Drak;2014;FANTASY", c[1].shortInfo());
    c["Hobbit2"].setDirector("P.Jackson");
    ASSERT_EQ("Hobbit2;2014;FANTASY;D:P.Jackson", c["Hobbit2"].info());
}