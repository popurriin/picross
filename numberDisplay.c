#include "backend/gridInfo.h"

static const short int ONE[];
static const short int TWO[];
static const short int THREE[];
static const short int FOUR[];
static const short int FIVE[];
static const short int SIX[];
static const short int SEVEN[];
static const short int EIGHT[];
static const short int NINE[];
static const short int ZERO[];

void print_numbers() {
    int index = 0;
    for (int row = 0; row < PICROSS_BOARD_HEIGHT; row++) {
            for(int col = 0; col < PICROSS_BOARD_WIDTH; col++){
            int x_delay = 0;
            int y_delay = 0;

            if (row >= PICROSS_BOARD_WIDTH/2) {
                y_delay = 1;
            }

            // Current number in array
            if (row_info[row][index] > 0) {

                // Print number:
                for (int y = 0; y < 21; y++) {
                    for (int x = 0; x < 21; x++) {
                        plot_pixel(x + 142 + 20*col + x_delay, y + 61 + 21*row + index y_delay, 0x6af2);
                    }
                }
            }
        }
    }
}