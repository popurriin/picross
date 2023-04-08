#include "gridInfo.h"
#include <stdbool.h>
void act_on_click(int row, int col){

    switch (player_grid[row][col])
    {
    case empty:
        player_grid[row][col] = selected;
        break;

    case selected:
        player_grid[row][col] = crossed;
        break;
    case crossed:
        player_grid[row][col] = empty;
        break;    
    default:
        break;
    }
    
}

bool check_win(){
    for(int row = 0; row < PICROSS_BOARD_HEIGHT; row++){
        for(int col = 0; col < PICROSS_BOARD_WIDTH; col++){

            if((player_grid[row][col] == selected && answer_grid[row][col] == true)
                || (player_grid[row][col] == crossed && player_grid[row][col] == empty)){
                    continue;
                }
            else return false;
        }
    }
    return true;
}