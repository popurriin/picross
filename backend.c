#include "picross.h"
#include "board_answers.h"
#include "picture_arrays.h"
#include "sound_array.h"

void check_finished() {
    // Check if stage is done:
    finished = 1;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
	    if ((board[y][x] == -1) && (answer_grid[y][x] == 0)) {
		continue;
	    }
            if (board[y][x] != answer_grid[y][x]) {
                finished = 0;
            }
        }
    }

    if (finished) {
        // Clear board
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                board[y][x] = 0;
            }
        }

        // Print finished picture
        int index = 0;
        if (stage == 0) {
            for (int y = 0; y < 165; y++) {
                for (int x = 0; x < 165; x++) {
                    plot_pixel(x + 142, y + 63, complete1[index]);
                    index++;
                }
            }
        } else if (stage == 1) {
            for (int y = 0; y < 165; y++) {
                for (int x = 0; x < 165; x++) {
                    plot_pixel(x + 142, y + 63, complete2[index]);
                    index++;
                }
            }
        } else if (stage == 2) {
            for (int y = 0; y < 165; y++) {
                for (int x = 0; x < 165; x++) {
                    plot_pixel(x + 142, y + 63, complete3[index]);
                    index++;
                }
            }
        }

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

        // Change stage:
        stage++;
        if (stage > 2) {
            stage = 0;
        }

        switch (stage) {
            case 0:
                copy_arrays(answer_grid, board1);
                break;
            case 1:
                copy_arrays(answer_grid, board2);
                break;
            case 2:
                copy_arrays(answer_grid, board3);
                break;
        }
        initialize_grid();

        // Configure timer to start counting
        *(TimerControl) = 4;

        while (*(TimerStatus) != 1) {
        }

        sound(eat_buffer,eat_buf_size/2,false);
    }
}

void copy_arrays(int array1[8][8], int array2[8][8]){
    for(int i = 0; i< PICROSS_BOARD_WIDTH; i++){
        for(int j = 0; j <PICROSS_BOARD_HEIGHT;j++){
            array1[i][j]=array2[i][j];
        }
    }
}

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
    // Empty arrays:
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            row_info[i][j] = 0;
            col_info[i][j] = 0;
        }
    }
    
    for(int row = 0; row < PICROSS_BOARD_HEIGHT; row++){
        int row_streak = 0;
        int row_info_i = 0;
        for (int col = 0; col< PICROSS_BOARD_WIDTH; col++){
            if(answer_grid[row][col] == 1){
                row_streak++;
                if (row!=0&&answer_grid[row-1][col] == 1){
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