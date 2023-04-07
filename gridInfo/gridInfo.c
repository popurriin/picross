#include <stdbool.h>
#include <stdio.h>
#define PICROSS_BOARD_HEIGHT 8
#define PICROSS_BOARD_WIDTH 8

enum grid_state {correct, crossed, empty};
int row_info[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_HEIGHT/2] = {0};
int col_info[PICROSS_BOARD_WIDTH][PICROSS_BOARD_WIDTH/2] = {0};

bool player_grid[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_WIDTH];
bool answer_grid[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_WIDTH]=  
    {               {true,   true,  true,   false,  true,    true,  false,   true},
                    {false,  false, true,   false,  true,   true,   false,  true},
                    {true,   true,  true,   true,   false,  false,  false,  false},
                    {true,   false, true,   false,  true,   false,  true,   false},
                    {true,   true,  true,   false,  true,   true,   false,  true},
                    {false,  false, true,   false,  true,   true,   false,  true},
                    {true,   true,  true,   true,   false,  false,  false,  false},
                    {true,   false, true,   false,  true,   false,  true,   false}
    };
void append_2D_array(int *Array, int value, int size){
    for(int index = 0; index < size; index++){
        if(Array[index] == 0){
            Array[index] = value;
            return;
        }
    }
    return; //array is full
}

void Add_to_lastElem_2D_Array(int *Array, int size){
    for(int index = 0; index < size; index++){
        if(index == size -1){
            Array[index] +=1;
            return;
        }
        else if(Array[index+1] == 0){
            Array[index] += 1;
            return;
        }
    }
    return; //array is full
}


void initialize_grid(){
    for(int row = 0; row < PICROSS_BOARD_HEIGHT; row++){
        int row_streak = 0;
        int row_info_i = 0;
        for (int col = 0; col< PICROSS_BOARD_WIDTH; col++){
            if(answer_grid[row][col] == true){
                row_streak++;
                if (answer_grid[row-1][col] == 1){
                    Add_to_lastElem_2D_Array(col_info[col], PICROSS_BOARD_WIDTH/2);
                }
                else{
                    append_2D_array(col_info[col], 1, PICROSS_BOARD_WIDTH/2);
                }
            }
            else if(row_streak!=0){
                row_info[row][row_info_i] = row_streak;
                row_info_i++;
                row_streak = 0;
            }
            if(col == PICROSS_BOARD_HEIGHT-1){
                row_info[row][row_info_i] = row_streak;
            }
        }
    }
}

void print2DArray(int nrows, int ncols, int Array[nrows][ncols]){
    printf("Two Dimensional array elements:\n");
    for(int i=0; i<nrows; i++) {
        for(int j=0;j<ncols;j++) {
            printf("%d ", Array[i][j]);
            if(j== ncols-1){
                printf("\n");
            }
        }
    }
    return;
}

int main(){
    initialize_grid();
    print2DArray(PICROSS_BOARD_WIDTH, PICROSS_BOARD_WIDTH/2, col_info);
    printf("\n");
    print2DArray(PICROSS_BOARD_HEIGHT, PICROSS_BOARD_HEIGHT/2, row_info);
    return 0;


}
