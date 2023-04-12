#include "picross.h"
#include "board_answers.h"
#include "picture_arrays.h"
#include "sound_array.h"

void plot_pixel(int x, int y, short int line_color) {
    if (y >= 240) {
        return;
    }
    if (x >= 320) {
        return;
    }
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void clear_screen() {
    for (int x = 0; x < 320; x++) {
        for (int y = 0; y < 240; y++) {
            plot_pixel(x, y, 0x0000);
        }
    }
}

void print_boxes() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int x_delay = 0;
            int y_delay = 0;

            if (col > 3) {
                x_delay = 4;
            }

            if (row > 3) {
                y_delay = 1;
            }

            // If the current box has been selected:
            if (board[row][col] == 1) {

                // Print box:
                for (int y = 0; y < 21; y++) {
                    for (int x = 0; x < 21; x++) {
                        plot_pixel(x + 142 + 20*col + x_delay, y + 61 + 21*row + y_delay, 0x6af2);
                    }
                }
            }

            if (col > 3) {
                x_delay = 3;
            }
            if (row > 3) {
                y_delay = 4;
            }

            // If the current box has been X'ed out:
            if (board[row][col] == -1) {
                int index = 0;
                // Print X:
                for (int y = 0; y < 20; y++) {
                    for (int x = 0; x < 20; x++) {
                        if (Xed[index] != (short int)0xffff) {
                            plot_pixel(x + 142 + 20*col + x_delay, y + 63 + 20*row + y_delay, Xed[index]);
                        }
                        index++;
                    }
                }
            }
        }
    }
}

void print_board() {
    int index = 0;
    for (int y = 0; y < RESOLUTION_Y; y++) {
        for (int x = 0; x < RESOLUTION_X; x++) {
            plot_pixel(x, y, Picross_Board[index]);
            index++;
        }
    }
}

void print_numbers() {
	short int * number_pixels;
    int col;
    for (int row = 0; row < 8; row++) {
        col = row;
		int space_row = 0;
        int space_col = 0;
		for(int index = 0; index < 4; index ++){
            int x_delay = 0;
            int y_delay = 0;

            if (row >= PICROSS_BOARD_WIDTH/2) {
                y_delay = 1;
            }
            if (col >= PICROSS_BOARD_WIDTH/2) {
                x_delay = 1;
            }

            // Current number in array
            if (row_info[row][index] > 0) {
				number_pixels = get_number_pixels(row_info[row][index]);
                space_row++;
                // Print number:
                int num_index = 0;
                for (int y = 0; y < 10; y++) {
                    for (int x = 0; x < 10; x++) {
                        if(number_pixels[num_index]!=(short int)0xffff){
                            plot_pixel(x + 90 + x_delay+space_row*10, y + 68 + 21*row +  y_delay,number_pixels[num_index]);
                        }
                        num_index ++;
                    }
				
                }
            }
            
            if(col_info[col][index] > 0){
                number_pixels = get_number_pixels(col_info[row][index]);
                number_pixels = get_number_pixels(col_info[col][index]);
                space_col ++;
                //Print number

                int num_index_col = 0;
                for(int y = 0; y < 10; y ++){
                    for(int x = 0; x < 10; x++){
                        if(number_pixels[num_index_col]!=(short int)0xffff){
                            plot_pixel(x + 147 + 21*col + x_delay, y + 3+ y_delay +space_col*12,number_pixels[num_index_col]);
                        }
                        num_index_col++;
                    }
                }
            }
		}
    }
}

short int * get_number_pixels(int number){
	switch (number)
    {
    case 1:
        return ONE;
        break;
    case 2:
        return TWO;
        break;
    case 3:
        return  THREE;
        break;
    case 4:
        return  FOUR;
        break;
    case 5:
        return  FIVE;
        break; 
    case 6:
        return  SIX;
        break;
    case 7:
        return  SEVEN;
        break;
    case 8:
        return  EIGHT;
        break;
    default: return  ONE;
        break;
    }
}