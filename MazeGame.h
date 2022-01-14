#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : 4996) //per utilizzare _sleep() (deprecata).

#include "ANSI-color-codes.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <limits>
#include <locale>
#include<ios>
#include <conio.h>

#ifndef MazeGame_h //HMETADATA, per evitare che il compilatore definisca più volte la stessa libreria,anche se per errore è stata inclusa più volte nel file cpp.
	#define MazeGame_h

	enum keypress {
        UP_ARROW = 72,
   	    DOWN_ARROW = 80,
   		LEFT_ARROW = 75,
   		RIGHT_ARROW = 77
	};

        using namespace std;

        class MazeGame {

        public:
            int x = 0;
            int y = -1; //altrimenti la prima riga del mio file avrebbe index 1.

        private:
            FILE* myFile = NULL;

            string bufferstring;
            char bufferline[1024] = { '\0' };
            char buffer;

            void getFirstPosition() { //il gioco si svilupperà dal basso verso l'alto.

                while (fgets(bufferline,1024,myFile) != NULL) {
                    y++; //posizione Y ultima riga.
                }

                bufferstring=bufferline;

                if ((x = (int)bufferstring.find(' ')) > bufferstring.length()) { //posizione X primo carattere ' ' in cui posizionare il giocatore.
                    cout << "\n\nL'ultima riga del file indicato non contiene whitespace (via d'uscita)...";
                    exit(EXIT_FAILURE); // L'ULTIMA RIGA DEL MIO FILE NON CONTIENE WHITESPACE...
                }

                x++; //Perchè nel loop currentchar parte da 1.

                rewind(myFile);
            }

            void printWin() {
                system("cls||clear"); //PORTABLE
                fclose(myFile);

                if (fopen_s(&myFile, "winText.txt", "r") == 0) {
                    //se può aprire il file di congratulazioni..
                    while (fgets(bufferline, 1024, myFile) != NULL) {
                        if (strcmp(bufferline, "\n") == 0) {
                            _sleep(500); //ANIMAZIONE TESTO.
                            system("cls||clear"); //PORTABLE
                        }
                        else {
                            cout << bufferline;
                        }
                    }
                }
                else {
                    system("cls||clear"); //PORTABLE
                    cout << " HAI VINTO!\nUscita...(Premi un tasto per continuare)";
                    getchar();

                    //altrimenti stampa un semplice testo a schermo...
                }
            }
            
            void printLogo() {
                if (fopen_s(&myFile, "logo.txt", "r") == 0) {
                    //se può aprire il file LOGO..
                    while (fgets(bufferline, 1024, myFile) != NULL) {
                        cout << bufferline;
                    }

                    fclose(myFile);
                }
                else {
                    cout << setw(80) << "<IL LABBIRINTO>";
                }

                cout << "\n\n1) -> E' POSSIBILE UTILIZZARE COME \"CAMPO DI GIOCO\",\nUN QUALSIASI FILE DI TESTO IL CUI CONTENUTO SI SVILUPPI VERTICALMENTE\n(Rispettivamente le due entrata ed uscita dal campo,sono situate quindi sulla prima e sull'ultima riga del file)\n\n2) -> Muoviti all'interno del \"campo\" scelto,utilizzando i comandi direzionali sulla tastiera (" << KYEL<<"ARROW_UP,"<<KRED<< "ARROW_DOWN," << KGRN <<"ARROW_LEFT," << KMAG "ARROW_RIGHT"<<RST<<")";
            }

        public:

            MazeGame() { //COSTRUTTORE CLASSE
                int check=0;
                
                setlocale(LC_ALL, "it_IT.utf8");
                printLogo();
                
                do {
                    
                   cout<<"\n\nInserire nome del file da aprire (percorso labirinto, file con estensione"<<KYEL<<".txt"<<RST<<")\n(SPECIFICARNE IL PERCORSO ASSOLUTO SE IL FILE NON SI TROVA NELLA STESSA DIRECTORY DEL SOURCE CODE.) : ";
                    getline(cin, bufferstring);

                    if ((check = fopen_s(&myFile, bufferstring.c_str(), "r")) != 0) {
                        cout << "Errore durante l'apertura del file... (Premere un tasto per continuare)";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls||clear");
                    }

                } while (check != 0);

                getFirstPosition();

            }

            ~MazeGame() { //Distruttore classe,viene chiamato quando il programma viene chiuso.
                fclose(myFile); //chiude file.
            }

            int DrawMaze (int offsetx=0, int offsety=0) { //dove disegnare il carattere corrispondente al "personaggio"

                rewind(myFile);
                system("cls||clear"); //PORTABLE

                int currentline = 0;

                for (int currentchar = 1; (buffer = fgetc(myFile)) != EOF; currentchar++) {
                    if (buffer == '\n') {
                        ++currentline;
                        currentchar = 0;
                    }

                    if (currentchar == x - offsetx && currentline == y - offsety) {

                        if (buffer != ' ') {
                            DrawMaze();
                        }
                        else if (y - offsety == 0) { // al posto di stampare il "personaggio" sulla prima riga del mio file,stampo testo "vittoria".
                            printWin();
                            return 1;
                        }
                        else {
                            x -= offsetx;
                            y -= offsety;

                            offsetx = 0;
                            offsety = 0;

                            cout << KYEL << "X" << RST;
                            //MODIFICA CARATTERE RAPPRESENTANTE IL GIOCATORE
                        }

                    }
                    else {
                        cout << KMAG << buffer << RST;
                    }
                }
                return 0;
            }

        };

#endif
