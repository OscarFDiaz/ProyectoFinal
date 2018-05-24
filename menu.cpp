#include "menu.h"
#include <conio.h>
#include <iomanip>
#include <windows.h>
using namespace std;

List<Song> myLista; ///Lista ligada
List<Song> myUserLista;
Song s; ///Objeto song
string myStr; ///String para uso
Node<Song>* place; ///Nodo puntero para las busquedas
Node<Song>* place2;
bool loaded = false;
bool loadedMain = false;

void gotoxy(int x, int y){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

string radioPlayerText = R"(
              ;
              ;;
              ;';.
              ;  ;;
              ;   ;;
              ;    ;;
              ;   ;'  _____
              ;  '   (, /  |  /)
         ,;;;,;        /---| (/   _____  _   '
         ;;;;;;     ) /    |_/ )_(_)/ (_(_(_ '
         `;;;;'    (_/
                         )";

string adminText = R"(
                          _  __ _  _  _  _
                         / \(_ | \|_||_)|_)
                         \_/__)|_/| ||  |
              _______________________________________
             |              ADMIN MENU               |
             '------------------' '------------------'
        )";
string userText = R"(
                          _  __ _  _  _  _
                         / \(_ | \|_||_)|_)
                         \_/__)|_/| ||  |
              _______________________________________
             |                USUARIO                |
             '------------------' '------------------'
     )";
string byeText = R"(
                          _  __ _  _  _  _
                         / \(_ | \|_||_)|_)
                         \_/__)|_/| ||  |
              _______________________________________
             |              HASTA LUEGO              |
             '------------------' '------------------'
        )";
string wawe1 = R"(
                  ^                       ^         ^
              ^   |           ^           |         |
              |   |     ^     |         ^ |   ^     |
              |   |     |     | ^       | |   |   ^ |
              |   |   ^ |   ^ | |       | | ^ |   | |
              |   |   | |   | | | ^   ^ | | | | ^ | |
              | ^ |   | | ^ | | | | ^ | | | | | | | |
              | | | ^ | | | | | | | | | | | | | | | |
             ++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++)";
string wawe2 = R"(
                        ^         ^       ^
                        |     ^   |   ^   |
                ^       |     |   |   |   |     ^   ^
                |       | ^   |   | ^ |   | ^   |   |
              ^ |   ^   | |   |   | | |   | |   |   |
              | |   |   | |   |   | | |   | | ^ | ^ |
              | |   | ^ | |   | ^ | | | ^ | | | | | |
              | | ^ | | | | ^ | | | | | | | | | | | |
             ++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++)";
string wawe3 = R"(
                  ^   ^             ^             ^
                  |   |             |   ^   |     |
                ^ |   |     ^     ^ |   |   |     |
                | |   |     | ^   | | ^ |   | ^   |
              ^ | |   |   ^ | |   | | | |   | | ^ | ^
              | | | ^ |   | | |   | | | |   | | | | |
              | | | | |   | | |   | | | | ^ | | | | |
              | | | | | ^ | | | ^ | | | | | | | | | |
             ++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++)";

Menu::Menu(){

    while (true) {
        ///Intro del programa
        clearScreen();
        cout << R"(
        .--------.----------------------------------------.
        |  __)__________________________________________  |
        | |.-------------------------------------------.| |
        | ||              _  __ _  _  _  _             || |
        | ||             / \(_ | \|_||_)|_)            || |
        | ||             \_/__)|_/| ||  |              || |
        |,||  _______________________________________  || |
        | || |            MUSIC PLAYER APP           | || |
        |.|| '------------------' '------------------' ||,|
        |:||     _____________       _____________     || |
        |:||    |  ADMIN [1]  |     | USUARIO [2] |    ||-|
        |:||    '-------------'     '-------------'    ||:|
        |:||_________________CLOSE [0]_________________||:|
        |     ,`-------,----------.-------.---------------|
        '-'---------'-------------'-------'---------------' )"<< endl;
             char key = ' ';
             key = _getch();
             if (key == '1') {
                 adminMenu();
             }else if (key == '2') {
                 userMenu();
             }else if (key == '0') {
                 clearScreen();
                 cout << byeText << endl;
                 break;
             }
    }
}

void Menu::userMenu()
{

    clearScreen();
    string user; //< Variable para el login del usuario
    string password; //< Variable para el password del usuario
    char ch; //< char para lo ingresado antes del pass

    cout << userText << endl;

    cout << "\t>Ingresa tu usuario: ";
    getline(cin, user);
    cout << "\t>Ingresa tu contrase~a: ";
    ch = _getch();
    while(ch != 13){//< El 13 es un enter;
       password.push_back(ch);
       cout << '*';
       ch = _getch();
    }
    if(user != "Oscar" or password != "pancho"){
        clearScreen();
        cout << userText << endl;
        cout << setw(55) << "-=ERROR:  USUARIO O CONTRASE~A INCORRECTA=-" << endl;
        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
        return;
    }


    if (loaded == false) {
        loadBuyedSongs();
    }

    while (true) {
        clearScreen();
        cout << userText << endl;
        cout << setw(60) << "User: " + user << '\n';
        cout << "\t1) Canciones." << endl;          //Ready
        cout << "\t2) Radio." << endl;              //Ready
        cout << "\t3) Tienda de canciones." << endl; //Ready
        cout << "\t4) Inventario." << endl;         //Ready
        cout << "\t0) Cerrar Sesion." << endl;      //Ready
        cout << "\tOpcion: ";
        getline(cin, myStr);

        if (myStr == "1") {// Canciones - Ready
            if (myLista.isEmpty()) {
                clearScreen();
                cout << userText << '\n';
                cout << "   -=ERROR: POR EL MOMENTO NO HAY CANCIONES EN LA BASE DE DATOS=-"<< '\n';
                cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
            }else{
                clearScreen();
                cout << userText << '\n';
                cout << setw(45) << "-=LISTA DE CANCIONES=-" << '\n';
                cout << setw(60) << ">Total: " << myLista.listSize() + 1 << '\n';
                cout << ".-----------------------------------------------------------------." << '\n';
                cout << "|      NOMBRE      |           AUTOR           |      GENERO      |" << '\n';
                cout << " ----------------------------------------------------------------- " << '\n';
                cout << myLista.toString() << '\n';
                cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
            }

        }else if(myStr == "2"){ // Radio - To-Animación

            if (myLista.isEmpty() or myLista.listSize() <= 0) {
                clearScreen();
                cout << userText << '\n';
                cout <<  "\t  -=ERROR: POR EL MOMENTO LA RADIO ESTA OFFLINE=-"<< '\n';
                cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                continue;
            }

            int n;
            int s = myLista.listSize();
            srand(time(NULL));
            n = rand()%s;
            clearScreen();
            cout << userText << '\n';
            cout << radioPlayerText << '\n';
            Song retrieve = myLista[n];
            cout << retrieve << '\n' << '\n';

            int i = 0;
            while (i < 7) { // 10... segundos
                gotoxy(1,26); cout << wawe1 << '\r' << flush;
                Sleep(500);
                gotoxy(1,26); cout << wawe2 << '\r' << flush;
                Sleep(500);
                gotoxy(1,26); cout << wawe3 << '\r' << flush;
                Sleep(500);
                i++;
            }
            cout << '\n' << setw(50) << "Pulsa una tecla para continuar...";_getch();

        }else if(myStr == "3"){ // Tienda de canciones - 2 To-Do
            while (true) {
                clearScreen();
                cout << userText << '\n';
                cout << setw(60) << "User: " + user << '\n';
                cout << "\t1)Ver todas las caciones." << '\n';         // Ready
                cout << "\t2)Comprar cancion." << '\n';                // Ready
                cout << "\t3)Ver letra de alguna cancion." << '\n';    // To-Do
                cout << "\t4)Reproducir demo de una cancion." << '\n'; // Rea-Do
                cout << "\t5)Guardar cambios." << '\n';                // Ready
                cout << "\t0)Salir." << '\n';
                cout << "\tOpcion: ";
                getline(cin, myStr);
                if (myStr=="1") { //Ver todas las canciones
                    clearScreen();
                    cout << userText << '\n';
                    cout << setw(45) << "-=LISTA DE CANCIONES=-" << '\n';
                    cout << setw(60) << ">Total: " << myLista.listSize() + 1 << '\n';
                    cout << ".-----------------------------------------------------------------." << '\n';
                    cout << "|      NOMBRE      |           AUTOR           |      GENERO      |" << '\n';
                    cout << " ----------------------------------------------------------------- " << '\n';
                    cout << myLista.toString() << '\n';
                    cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                    continue;

                }else if (myStr=="2") {// Comprar cancion - READY
                    clearScreen();
                    cout << userText << '\n';
                    cout << "\t>Ingresa el nombre de la cancion a comprar: ";
                    getline(cin, myStr);
                    s.setName(myStr);

                    place = myLista.findData(s);

                    if(myLista.isValidPos(place)){// Sí la busqueda no dío nulo se pide confirmación y se añade la canción
                        place2 = myUserLista.findData(s);
                        if (myUserLista.isValidPos(place2)) {
                            clearScreen();
                            cout << userText << '\t';
                            cout << endl << setw(45) << "-=CANCION EN PROPIEDAD=-" << endl;
                            cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                            continue;
                        } else {
                            cout << "\t>Estas seguro de comprar la cancion '" << myStr << "'? S/N: ";
                            getline(cin, myStr);
                            if(myStr == "S" or myStr == "s"){
                                clearScreen();

                                Song buyed = myLista.retrieveData(place);
                                myUserLista.insertData(myUserLista.getLastPos(), buyed);

                                cout << userText << '\n';
                                cout << endl << setw(43) << "-=COMPROBANDO DATOS=-" << endl;
                                barProgress();
                                cout << endl << setw(48) << "-=CANCION COMPRADA CON EXITO=-" << endl;
                                cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                            }else{
                                continue;
                            }
                        }
                    }else{
                        clearScreen();
                        cout << userText << '\n';
                        cout << endl << setw(48) << "-=ERROR: LA CANCION NO EXISTE=-" << endl;
                        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                        continue;
                    }

                }else if (myStr=="3") {// Ver letra de la canción - TO-DO
                    clearScreen();
                    cout << userText << '\n';
                    cout << "\t>Ingresa el nombre de la cancion para la letra: ";
                    getline(cin, myStr);
                    s.setName(myStr);

                    place = myLista.findData(s);

                    if(myLista.isValidPos(place)){
                        clearScreen();
                        cout << userText << '\n';
                        Song lyric = myLista.retrieveData(place);
                        cout << "\t>Letra cancion: \n";
                        cout << "\t " + lyric.getName() + " - " + lyric.getArtist() << '\n' << '\n';
                        loadLyrics(myStr);
                        cout << '\n' << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                    }else{
                        clearScreen();
                        cout << userText << '\n';
                        cout << endl << setw(48) << "-=ERROR: LA CANCION NO EXISTE=-" << endl;
                        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                        continue;
                    }

                }else if (myStr=="4") {// Reproducir demo - REA-DO
                    clearScreen();
                    cout << userText << '\n';
                    cout << "\t>Ingresa el nombre de la cancion a buscar: ";
                    getline(cin, myStr);
                    s.setName(myStr);

                    place = myLista.findData(s);

                    if(myLista.isValidPos(place)){
                        clearScreen();
                        Song ret = myLista.retrieveData(place);

                        cout << userText << '\n';
                        cout << radioPlayerText ;
                        cout << '\n' << setw(45) << "-=DISFRUTA DE 5 SEGUNDOS=-" << '\n' << '\n';
                        cout << ret << '\n';

                        int i = 0;
                        while (i < 4) { // 5 segundos
                            gotoxy(1,27); cout << wawe1 << '\r' << flush;
                            Sleep(500);
                            gotoxy(1,27);cout << wawe2 << '\r' << flush;
                            Sleep(500);
                            gotoxy(1,27);cout << wawe3 << '\r' << flush;
                            Sleep(500);
                            i++;
                        }
                        cout << '\n' << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                    } else {
                        clearScreen();
                        cout << userText << '\n';
                        cout << endl << setw(48) << "-=ERROR: LA CANCION NO EXISTE=-" << endl;
                        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                        continue;
                    }

                }else if (myStr== "5") {//Guardar cambios - READY
                    clearScreen();
                    saveBuyedSongs();
                    cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                }else if (myStr=="0") {
                    break;
                }
        }

        }else if(myStr == "4"){ // Inventario - READY
            while (true) {
                clearScreen();
                cout << userText << '\n';
                cout << setw(60) << "User: " + user << '\n';
                cout << "\t1)Ver mis canciones compradas." << '\n';   // Ready
                cout << "\t2)Reproducir cancion." << '\n';            // Ready
                cout << "\t3)Descargar cancion comprada." << '\n';    // Ready
                cout << "\t0)Salir." << '\n';
                cout << "\tOpcion: ";
                getline(cin, myStr);

                if (myStr == "1") { //Ver canciones compradas
                    clearScreen();
                    cout << userText << '\n';
                    cout << setw(47) << "-=CANCIONES EN PROPIEDAD=-" << '\n';
                    cout << setw(60) << ">Total: " << myUserLista.listSize() + 1 << '\n';
                    cout << ".-----------------------------------------------------------------." << '\n';
                    cout << "|      NOMBRE      |           AUTOR           |      GENERO      |" << '\n';
                    cout << " ----------------------------------------------------------------- " << '\n';
                    cout << myUserLista.toString() << '\n';
                    cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                }else if (myStr == "2") { //Reproducir cancion comprada
                    clearScreen();
                    cout << userText << '\n';
                    cout << "\t>Ingresa el nombre de la cancion a reproducir: ";
                    getline(cin, myStr);
                    s.setName(myStr);

                    place = myUserLista.findData(s);

                    if(myUserLista.isValidPos(place)){
                        clearScreen();
                        Song ret = myUserLista.retrieveData(place);

                        cout << userText << '\n';
                        cout << radioPlayerText << '\n';
                        cout << ret << '\n';

                        int i = 0;
                        while (i < 5) { // 7.5 segundos
                            gotoxy(1,27); cout << wawe1 << '\r' << flush;
                            Sleep(500);
                            gotoxy(1,27);cout << wawe2 << '\r' << flush;
                            Sleep(500);
                            gotoxy(1,27);cout << wawe3 << '\r' << flush;
                            Sleep(500);
                            i++;
                        }
                        cout << '\n' << setw(50) << "Pulsa una tecla para regresar...";_getch();clearScreen();

                    } else {
                        clearScreen();
                        cout << userText << '\n';
                        cout << endl << setw(48) << "-=ERROR: NO TIENES LA CANCION=-" << endl;
                        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                        continue;
                    }
                }else if (myStr == "3") { //Descargar canción
                    clearScreen();
                    cout << userText << '\n';
                    cout << "\t>Ingresa el nombre de la cancion a descargar: ";
                    getline(cin, myStr);
                    s.setName(myStr);

                    place = myUserLista.findData(s);

                    if (myUserLista.isValidPos(place)) {
                        clearScreen();
                        cout << userText << '\n';
                        cout << "\t>Estas seguro de descargar la cancion '" << myStr << "'? S/N: ";
                        getline(cin, myStr);
                        if(myStr == "S" or myStr == "s"){
                            clearScreen();

                            cout << userText << '\n';
                            cout << endl << setw(43) << "-=DESCARGANDO DATOS=-" << endl;
                            barProgress();
                            cout << endl << setw(48) << "-=CANCION DESCARGADA CON EXITO=-" << endl;
                            cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                        }else{
                            continue;
                        }
                    } else {
                        clearScreen();
                        cout << userText << '\n';
                        cout << endl << setw(48) << "-=ERROR: NO TIENES LA CANCION=-" << endl;
                        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
                        continue;
                    }

                }else if (myStr == "0") {
                    break;
                }
            }

        }else if(myStr == "0"){ // Cerrar sesión
            clearScreen();
            loaded = true;
            cout << byeText << '\n';
            cout << setw(50) << "Pulsa una tecla para continuar...";_getch();
            break;
        }
    }
}

void Menu::adminMenu(){
    clearScreen(); //< Limpia la pantalla al entrar a este menu
    string user; //< Variable para el login del usuario
    string password; //< Variable para el password del usuario
    char ch; //< char para lo ingresado antes del pass

    cout << adminText << endl;

    cout << "\t>Ingresa tu usuario: ";
    getline(cin, user);
    cout << "\t>Ingresa tu contrase~a: ";
    ch = _getch();
    while(ch != 13){//< El 13 es un enter;
       password.push_back(ch);
       cout << '*';
       ch = _getch();
    }
    if(user != "ADMIN" or password != "password"){
        clearScreen();
        cout << adminText << endl;
        cout << setw(55) << "-=ERROR:  USUARIO O CONTRASE~A INCORRECTA=-" << endl;
        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
        return;
    }

    while (true) {
    clearScreen();

    cout << adminText << endl; //< OSDAP ADMIN MENU
    /// Menu estatico
    cout << setw(43) << "-=LISTA DE CANCIONES=-" << '\n' << '\n';
    cout << setw(60) << ">Total: " << myLista.listSize() + 1 << '\n';
    cout << ".-----------------------------------------------------------------." << '\n';
    cout << "|      NOMBRE      |           AUTOR           |      GENERO      |" << '\n';
    cout << " ----------------------------------------------------------------- " << '\n';
    cout << myLista.toString() << endl << endl;
    cout << "\t1) Ingresar nueva cancion." << endl;
    cout << "\t2) Eliminar cancion." << endl;
    cout << "\t3) Eliminar todo." << endl;
    cout << "\t4) Cargar lista de canciones." << endl;
    cout << "\t5) Guardar lista de canciones." << endl;
    cout << "\t0) Cerrar Sesion." << endl;
    cout << "\tOpcion: ";
    getline(cin, myStr);
    clearScreen();

    if (myStr == "1") { ///Ingresar nueva canción al objeto
        cout << adminText << endl;

        cout << "\t+> Ingresa el Artista: ";
        getline(cin, myStr);
        s.setArtist(myStr);

        cout << "\t+> Ingresa el Nombre: ";
        getline(cin, myStr);
        s.setName(myStr);

        cout << "\t+> Ingresa el Genero: ";
        getline(cin, myStr);
        s.setGenre(myStr);

        try {///Por si la memoria fisica se termina
            myLista.insertData(myLista.getLastPos(), s);
        } catch(ListException ex) {
            cout << ex.what() << endl;
        }

    }else if (myStr == "2"){///Eliminar canción
        ///Pide nombre, lo guarda, lo setea y manda a buscarlo, el nodo puntero recibe la dirección
        cout << adminText << endl;
        cout << "\t+> Ingresa el nombre de la cancion a buscar: ";
        getline(cin, myStr);
        s.setName(myStr);

        place = myLista.findData(s);

        if(myLista.isValidPos(place)){///Sí la busqueda no dío nulo se pide confirmación y se borra la canción
            cout << "\t+> Estas seguro de elimnar la cancion '" << myStr << "'? S/N: ";
            getline(cin, myStr);
            if(myStr == "S" or myStr == "s"){
                myLista.deleteData(place);
                cout << endl << setw(45) << "-=CANCION ELIMINADA=-" << endl;
                cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
            }else{
                continue;
            }
        }else{///La posicion dio nulo
            cout << endl << setw(48) << "-=ERROR: LA CANCION NO EXISTE=-" << endl;
            cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
        }

    }else if (myStr == "3"){//Eliminar todo
        ///Pedir confirmación-> proceder a borrar todo
        cout << adminText << endl;
        cout << "\t+> Estas seguro de elimnar todo? S/N: ";
        getline(cin, myStr);
        if(myStr == "S" or myStr == "s"){
            myLista.deleteAll();
            loadedMain = false;
            cout << endl << setw(45) << "-=TODO SE HA BORRADO=-" << endl;
            cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
        }else{
            continue;
        }
    }else if (myStr == "4") {//Cargar canciones
        if (loadedMain == false) {
            loadedMain = true;
            loadSongs();
        }else{
            cout << adminText << endl;
            cout << endl << setw(50) <<"-=LAS CANCIONES SE HAN CARGADO=-\n";
        }
        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
    }else if (myStr == "5") {//Guardar canciones
        saveSongs();
        cout << setw(50) << "Pulsa una tecla para continuar...";_getch();clearScreen();
    }else if (myStr == "0") { // Si elige 0 se cierra el programa
        break;
    }
    }
}

void Menu::saveSongs()
{
    cout << adminText << '\n';
    if (myLista.isEmpty()) {
        cout << endl << setw(55) << "-=ERROR: NO EXISTEN DATOS PARA GUARDAR=-\n";
        return;
    }
    int j = 0;
    ofstream songsList("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Songs\\ListSongs.txt", ios::out);
    while (j <= myLista.listSize()) {
        if (songsList.is_open()) {
            songsList << myLista[j].getName() << '\n';
        }
        j++;
    }
    songsList.close();

    int i = 0;
    while (i <= myLista.listSize()) {
        ofstream songsData("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Songs\\" + myLista[i].getName() + ".txt", ios::out);
        if (songsData.is_open()) {
                songsData << myLista[i].getArtist() << '\n'
                          << myLista[i].getName() << '\n'
                          << myLista[i].getGenre();
        }
        songsData.close();
        i++;
    }
    cout << endl << setw(50) << "-=LAS CANCIONES SE HAN GUARDADO=-\n";
}

void Menu::loadSongs()
{
    cout << adminText << endl;
    ifstream songsList("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Songs\\ListSongs.txt", ios::in);
    if(!songsList.is_open()){//< Si no se ha leido nada el archivo no existe, mensaje y se regresa
        cout << endl << setw(55) << "-=ERROR: NO EXISTEN DATOS PARA CARGAR=-" << '\n';
        return;
    }
    string stringToLoad;
    string stringSongToLoad;

    if (songsList.is_open()) {

        while(!songsList.eof()){
            getline(songsList, stringToLoad);

            if (songsList.eof())
                break;

            ifstream songsData("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Songs\\" + stringToLoad + ".txt", ios::in);
             if(songsData.is_open()){
                 while (!songsData.eof()) {

                     Song songLoad;

                     getline(songsData, stringSongToLoad);
                     if (songsData.eof())
                         break;
                     songLoad.setArtist(stringSongToLoad);

                     getline(songsData, stringSongToLoad);
                     songLoad.setName(stringSongToLoad);

                     getline(songsData, stringSongToLoad);
                     songLoad.setGenre(stringSongToLoad);

                     myLista.insertData(myLista.getLastPos(), songLoad);

                 }
             }
             songsData.close();
        }

    }
    songsList.close();

    cout << endl << setw(50) <<"-=LAS CANCIONES SE HAN CARGADO=-\n";

}

void Menu::saveBuyedSongs()
{
    cout << userText << '\n';
    if (myUserLista.isEmpty()) {
        cout << endl << setw(55) << "-=ERROR: NO EXISTEN CANCIONES PARA GUARDAR=-\n";
        return;
    }
    int j = 0;
    ofstream songsList("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Buyed\\ListBuyedSongs.txt", ios::out);
    while (j <= myUserLista.listSize()) {
        if (songsList.is_open()) {
            songsList << myUserLista[j].getName() << '\n';
        }
        j++;
    }
    songsList.close();

    int i = 0;
    while (i <= myUserLista.listSize()) {
        ofstream songsData("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Buyed\\" + myUserLista[i].getName() + ".txt", ios::out);
        if (songsData.is_open()) {
                songsData << myUserLista[i].getArtist() << '\n'
                          << myUserLista[i].getName() << '\n'
                          << myUserLista[i].getGenre();
        }
        songsData.close();
        i++;
    }
    cout << endl << setw(50) << "-=LAS CANCIONES SE HAN GUARDADO=-\n";
}

void Menu::loadBuyedSongs()
{
    cout << userText << endl;
    ifstream songsList("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Buyed\\ListBuyedSongs.txt", ios::in);
    if(!songsList.is_open()){//< Si no se ha leido nada el archivo no existe, mensaje y se regresa
        cout << endl << setw(55) << "-=ERROR: NO EXISTEN CANCIONES COMPRADAS=-" << '\n';
        return;
    }
    string stringToLoad;
    string stringSongToLoad;

    if (songsList.is_open()) {

        while(!songsList.eof()){
            getline(songsList, stringToLoad);

            if (songsList.eof())
                break;

            ifstream songsData("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Buyed\\" + stringToLoad + ".txt", ios::in);
             if(songsData.is_open()){
                 while (!songsData.eof()) {

                     Song songLoad;

                     getline(songsData, stringSongToLoad);
                     if (songsData.eof())
                         break;
                     songLoad.setArtist(stringSongToLoad);

                     getline(songsData, stringSongToLoad);
                     songLoad.setName(stringSongToLoad);

                     getline(songsData, stringSongToLoad);
                     songLoad.setGenre(stringSongToLoad);

                     myUserLista.insertData(myUserLista.getLastPos(), songLoad);

                 }
             }
             songsData.close();
        }

    }
    songsList.close();

    cout << endl << setw(50) <<"-=LAS CANCIONES SE HAN CARGADO=-\n";
}

void Menu::loadLyrics(string songName)
{
    ifstream songsList("C:\\Users\\Oscar Diaz\\Documents\\QtProyectos\\Proyecto_ID\\Data\\Lyrics\\" + songName + " LY.txt", ios::in);
    if(!songsList.is_open()){//< Si no se ha leido nada el archivo no existe, mensaje y se regresa
        clearScreen();
        cout << userText << '\n';
        cout << endl << setw(53) << "-=ERROR: NO EXISTE LETRA DE LA CANCION=-" << '\n';
        return;
    }
    string stringToLoad;

    if (songsList.is_open()) {

        while(!songsList.eof()){
            getline(songsList, stringToLoad);

            if (songsList.eof())
                break;

            cout << '\t' << '\t' << stringToLoad << '\n';
        }

    }
    songsList.close();
}

void Menu::clearScreen() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

void Menu::barProgress()
{
    float progress = 0.0;
    while (progress < 1.0) {
        int barWidth = 30;

        std::cout << "\t\t[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();

        progress += 0.001;
    }
    std::cout << std::endl;
}
