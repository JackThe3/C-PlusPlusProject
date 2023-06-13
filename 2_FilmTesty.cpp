#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "2_Film.h"

using namespace ::testing;


TEST(FilmTest, emptyfilm) {
    Film a = Film();
    ASSERT_TRUE(a.filmEmpty());
}

TEST(FilmTest, tentorok) {
    time_t t = std::time(nullptr);
    tm* now = std::localtime(&t);
    const int year = now->tm_year + 1900;
    Film a = Film("film", year, "ACTION");
    ASSERT_FALSE(a.filmEmpty());
}

TEST(FilmTest, zanerzly) {
    Film a = Film("film", 2020, "SCIFI");  //zaner SCIFI nie je v gdefault
    ASSERT_EQ("", a.getName());
    ASSERT_EQ(0, a.getYear());
    ASSERT_EQ("", a.getGenre());
    ASSERT_TRUE(a.filmEmpty());
}

TEST(FilmTest, filmzly) {
    Film a = Film("fi\nlm", 2020, "ACTION"); //znak \n nieje povoleny
    ASSERT_EQ("", a.getName());
    ASSERT_EQ(0, a.getYear());
    ASSERT_EQ("", a.getGenre());
    ASSERT_TRUE(a.filmEmpty());
}

TEST(FilmTest, rokzly) {
    Film a = Film("film", 1800, "SCIFI");   // rok moze byt od roku 1900 do sucestneho roku "2021",,, premenna yearnow v subore 1_Film.cpp
    ASSERT_EQ("", a.getName());
    ASSERT_EQ(0, a.getYear());
    ASSERT_EQ("", a.getGenre());
    ASSERT_TRUE(a.filmEmpty());
}

TEST(FilmTest, rokzlyodva) {        //sucastny rok + 2
    time_t t = std::time(nullptr);
    tm* now = std::localtime(&t);
    const int year = now->tm_year + 1900 + 2;
    Film a = Film("film", year, "SCIFI");
    ASSERT_EQ("", a.getName());
    ASSERT_EQ(0, a.getYear());
    ASSERT_EQ("", a.getGenre());
    ASSERT_TRUE(a.filmEmpty());
}


TEST(FilmTest, film) {
    Film a = Film("Star Wars Episode IV - A New Hope", 1977, "SCIFI");
    ASSERT_TRUE(a.filmEmpty());
    Genres g;
    g.add("sCiFi");
    a = Film("Star Wars: Episode IV - A New Hope", 1977, "SCIFI", g);
    ASSERT_EQ("Star Wars: Episode IV - A New Hope", a.getName());
    ASSERT_EQ(1977, a.getYear());
    ASSERT_EQ("SCIFI", a.getGenre());
    ASSERT_FALSE(a.filmEmpty());
}

TEST(FilmTest, filminfozly) {
    Film a = Film("film", 1800, "SCIFI");
    ASSERT_EQ("Empty_Film", a.info());
    ASSERT_TRUE(a.filmEmpty());
}


TEST(FilmTest, filminfo) { // info format je: "<meno>;<rok>;<zaner>D:<reziser;A:<herec>,<herec>,..." reziser a hereci nemusia byt uvedeny.
    Film a = Film("film", 2020, "SCIFI");
    Genres g;
    g.add("sCiFi");
    a = Film("Star Wars: Episode IV - A New Hope", 1977, "SCIFI", g);
    ASSERT_EQ("Star Wars: Episode IV - A New Hope;1977;SCIFI", a.info());
}

TEST(FilmTest, porovannie) { //musia mat rovnaky nazov a rok
    Film a = Film("The Lion King", 2019, "MUSICAL");
    Film b = Film("The Lion King", 1994, "MUSICAL");
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(FilmTest, setfilm) {
    Film a = Film();
    ASSERT_EQ("", a.getName());
    a.setName("Hobbit Cesta");
    a.setName("");
    ASSERT_EQ("Hobbit Cesta", a.getName());
    a.setYear(2012);
    a.setGenre("SCIFI");
    ASSERT_EQ("Empty_Film", a.info());
    a.setGenre("FANTASY");
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY", a.info());
    ASSERT_FALSE(a.filmEmpty());
}

TEST(FilmTest, emptyfilmdirector) {
    Film a = Film();
    a.setDirector("P.Jackson");
    ASSERT_EQ("", a.getDirector());
}

TEST(FilmTest, setfilmdirector) {
    Film a = Film();
    ASSERT_EQ("", a.getName());
    a.setName("Hobbit Cesta");
    ASSERT_EQ("Hobbit Cesta", a.getName());
    a.setYear(2012);
    a.setGenre("SCIFI");
    ASSERT_EQ("Empty_Film", a.info());
    a.setGenre("FANTASY");
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY", a.info());
    ASSERT_FALSE(a.filmEmpty());
    a.setDirector("P.Jackson");
    ASSERT_EQ("P.Jackson", a.getDirector());
}

TEST(FilmTest, setfilmactors) { //herci sa uvadzaju vo formate <herec>,<herec>...
    Film a = Film();
    a.setName("Hobbit Cesta");
    a.setYear(2012);
    a.setGenre("FANTASY");
    a.setDirector("P.Jackson");
    string actors = "Martin Freeman,Ian McKellen,Richard Armitage,Ken Stott,Graham McTavish,William Kircher,James Nesbitt,Stephen Hunter,Dean O'Gorman,Aidan Turner,John Callen";
    a.setActors(actors);
    ASSERT_EQ(11, a.getActors().size());
    a.setActors("");
    ASSERT_EQ(0, a.getActors().size());
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY;D:P.Jackson", a.info());
    a.setActors("Martin Freeman, Ian McKellen,");
    ASSERT_EQ(2, a.getActors().size());
    ASSERT_EQ("Hobbit Cesta;2012;FANTASY;D:P.Jackson;A:Martin Freeman,Ian McKellen", a.info());

}