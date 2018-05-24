#ifndef SONG_H
#define SONG_H
#include <string>
#include <iostream>
#include <cstdio>

class Song{
    public:
        Song();
        Song(const Song&);

        std::string getArtist() const;
        void setArtist(const std::string &);

        std::string getName() const;
        void setName(const std::string &);

        std::string getGenre() const;
        void setGenre(const std::string &);

        std::string toString();

        void addSong(Song s);

        Song& operator = (const Song&);

        friend std::ostream& operator << (std::ostream&, Song&);
        friend std::istream& operator >> (std::istream&, Song&);

        bool operator == (const Song&);
        bool operator != (const Song&);
        bool operator <= (const Song&);
        bool operator >= (const Song&);
        bool operator < (const Song&);
        bool operator > (const Song&);

    private:
        std::string artist;
        std::string name;
        std::string genre;
};

#endif
