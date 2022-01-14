#define _CRT_SECURE_NO_WARNINGS

#include "MazeGame.h"

using namespace std;

int main()
{

   int offsetx = 0;
   int offsety = 0;

   MazeGame Labirinto;

   Labirinto.DrawMaze(); //prima visualizzazione file labirinto.

   //handle arrows input
   do{
        offsetx = 0;
        offsety = 0;

        _getch(); //al primo input,_getch() restituisce -32,che va scartato
        switch (_getch()) { 
            case UP_ARROW:
               ++offsety;
               break;

            case DOWN_ARROW: 
                --offsety;
                break;

            case LEFT_ARROW:
                ++offsetx;
                break;

            case RIGHT_ARROW:
                --offsetx;
                break;
        }
        
   }while (Labirinto.DrawMaze(offsetx, offsety) != 1);

    return 0;
}
