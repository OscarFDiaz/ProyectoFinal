#include "song.h"
using namespace std;

Song::Song(){}

Song::Song(const Song& s) : artist(s.artist), name(s.name), genre(s.genre){ }//< Constructor copia

string Song::getArtist() const{
    return artist;
}
void Song::setArtist(const string &r){
    artist = r;
}
string Song::getName() const{
    return name;
}
void Song::setName(const string &n){
    name = n;
}
string Song::getGenre() const{
    return genre;
}
void Song::setGenre(const string &g){
    genre = g;
}
string Song::toString(){
    string line = "|-----------------------------------------------------------------|";
    return "   " + name + "   |      " + artist + "      |   " + genre + "\n" + line;

}
Song& Song::operator=(const Song& s) {
    artist = s.artist;
    name = s.name;
    genre = s.genre;
    return *this;
}
ostream &operator << (ostream &o, Song &s){
    o << "\t+ Reproduciendo: " + s.getName() + " - " + s.getArtist() + '\n'
      << "\t+ Artista: " << s.getArtist() << endl
      << "\t+ Nombre: " << s.getName() << endl
      << "\t+ Genero: " << s.getGenre();
    return o;
}
istream& operator >> (istream& is, Song& s){
    getline(is, s.artist);
    getline(is, s.name);
    getline(is, s.genre);
    return is;
}
bool Song::operator==(const Song& s) {
    return s.name == name;
}
bool Song::operator!=(const Song& s) {
    return s.name != name;
}
bool Song::operator<=(const Song&s) {
    return s.name <= name; //< Modificar
}
bool Song::operator>=(const Song&s) {
    return s.name >= name; //< Modificar
}
bool Song::operator<(const Song&s) {
    return s.name < name; //< Modificar
}
bool Song::operator>(const Song&s) {
    return s.name > name; //< Modificar
}
