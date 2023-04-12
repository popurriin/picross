#ifndef PICROSS_H
#define PICROSS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define PICROSS_BOARD_HEIGHT 8
#define PICROSS_BOARD_WIDTH 8

#define SDRAM_BASE            0xC0000000
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_CHAR_BASE        0xC9000000

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define TIMER_BASE            0xFF202000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030

/* Screen Dimensions */
#define RESOLUTION_X          320
#define RESOLUTION_Y          240

/* PS/2 Address*/
#define PS2_ADDRESS           0xFF200100

/* Sound */
#define AUDIO_BASE            0xFF203040
#define LEDR_BASE             0xFF200000
#define BUF_THRESHOLD         200

/* Timer */
#define TimerControl ((volatile int*) (TIMER_BASE+4))
#define TimerTimeoutL ((volatile int*) (TIMER_BASE+8))
#define TimerTimeoutH ((volatile int*) (TIMER_BASE+12))
#define TimerStatus ((volatile int*) (TIMER_BASE))

/* Function Definitions */
void wait_for_vsync();
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void print_boxes();
void print_board();
void check_finished();
void copy_arrays(int array1[8][8], int array2[8][8]);
void append_2D_array(int *Array, int value, int size);
void Add_to_lastElem_2D_Array(int *Array, int size);
void initialize_grid();
void print2DArray(int nrows, int ncols, int Array[nrows][ncols]);
short int * get_number_pixels(int number);
void print_numbers();
void sound(double*,int, bool);

/* Global Variables */
int board[8][8];
int answer_grid [8][8];

int row_info[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_HEIGHT/2];
int col_info[PICROSS_BOARD_WIDTH][PICROSS_BOARD_WIDTH/2];

volatile int pixel_buffer_start = FPGA_ONCHIP_BASE;
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
short byte_packet[3];

int finished = 0;
int stage = 0;

#endif // PICROSS_H