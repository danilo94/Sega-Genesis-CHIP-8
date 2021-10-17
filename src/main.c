#include <genesis.h>
#include "gamecontroller.h"

int main()
{
    initGameController();

    while(1)
    {
        if(myGameController.gameInProgress == FALSE){
              SPR_update();
        }
        else{
              runGame();
        }
    }
    return (0);
}

