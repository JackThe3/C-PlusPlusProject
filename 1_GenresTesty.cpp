#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "2_Film.h"
#include "3_Collection.h"

using namespace ::testing;

TEST(GenresTest, genre) {
    Genres g("empty");  //vtvory prazdne zanre
    g.add("FANTASY");
    g.add("fantasy");
    ASSERT_TRUE(g.isGenre("FANTASY"));
    ASSERT_FALSE(g.isGenre("ACTION"));
}

TEST(GenresTest, genreinput) {
    Genres g = Genres("FAnTASY aCTION");    //vtvory zanre FANTASY a ACTION
    ASSERT_TRUE(g.isGenre("FANTASY"));
    ASSERT_TRUE(g.isGenre("ACTION"));
}

TEST(GenresTest, genreinputwrongnumber) {
    Genres g = Genres("F5AnTASY aCION");    //nepovoleny znak "5" , vytvory emprty genres
    ASSERT_FALSE(g.isGenre("F5ANTASY"));
    ASSERT_FALSE(g.isGenre("ACTION"));
    ASSERT_TRUE(g.empty());
}

TEST(GenresTest, genreinputwrongnline) {
    Genres g = Genres("F\nAnTASY aCION");   //nepovoleny znak "\n" , vytvory emprty genres
    ASSERT_FALSE(g.isGenre("F5ANTASY"));
    ASSERT_FALSE(g.isGenre("ACTION"));
    ASSERT_TRUE(g.empty());
}

TEST(GenresTest, genredefault) {
    Genres g = Genres();   //vytvory defaultne genres.
    ASSERT_FALSE(g.isGenre("F5ANTASY"));
    ASSERT_TRUE(g.isGenre("ACTION"));
    ASSERT_FALSE(g.empty());
}

TEST(GenresTest, genreToString) {
    Genres g = Genres("empty");
    g.add("FANTASY");
    g.add("fantasy");
    g.add("hORROr");
    g.add("5");
    g.add("ACTION");
    ASSERT_FALSE(g.empty());
    ASSERT_EQ("ACTION FANTASY HORROR", g.toString());
}