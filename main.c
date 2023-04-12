#include "picross.h"
#include "board_answers.h"
#include "picture_arrays.h"
#include "sound_array.h"

int main(void) {
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    /* set front pixel buffer to start of FPGA On-chip memory */
    *(pixel_ctrl_ptr + 1) = 0xC8000000; // first store the address in the 
                                        // back buffer

    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();

    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    print_board(); // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer

    // pixel_buffer_start points to the pixel buffer
    print_board();

    // Set up first stage:
    copy_arrays(answer_grid, board1);
    initialize_grid();

    int cursor_x = 0;
    int cursor_y = 0;
    int click = 0;

    int* PS2_ptr = (int *) PS2_ADDRESS; // PS/2 port address
    int PS2_data, RVALID;

    // PS/2 mouse needs to be reset (must be already plugged in)
    *(PS2_ptr) = 0xFF;

    // Set up timer:

    // Configure the timeout period to maximum
    *(TimerTimeoutL) = 0x0a3d;
    *(TimerTimeoutH) = 0x0a3d;

    while (1) {
        print_board();
        print_boxes();
        print_numbers();

        // Print cursor:
        int x_delay = 0;
        int y_delay = 0;

        if (cursor_x > 3) {
            x_delay = 4;
        }

        for (int x = 0; x < 20; x++) {
	        for (int y = 0; y < 2; y++) {
		        plot_pixel(x + 142 + 20*cursor_x + x_delay, y*20 + 62 + 21*cursor_y, 0x0000);
            }
    	}

        for (int y = 0; y < 20; y++) {
	        for (int x = 0; x < 2; x++) {
		        plot_pixel(x*20 + 142 + 20*cursor_x + x_delay, y + 62 + 21*cursor_y, 0x0000);
            }
    	}

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer

        // Read data from keyboard:
        PS2_data = *(PS2_ptr); // Read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000; // Extract RVALID field

        if (RVALID) {
            byte_packet[2] = byte_packet[1];
            byte_packet[1] = byte_packet[0];
            byte_packet[0] = PS2_data & 0xFF;
        }

        if (byte_packet[1] != 240) {
            switch (byte_packet[0]) {
                case 0x1D: // W pressed
                    cursor_y--;
                    break;

                case 0x1C: // A pressed
                    cursor_x--;
                    break;

                case 0x1B: // S pressed
                    cursor_y++;
                    break;

                case 0x23: // D pressed
                    cursor_x++;
                    break;

                case 0x29: // Spacebar
                    click = 1;
                    break;
            }
        }

        if (click == 1) {
            click = 0;
            switch (board[cursor_y][cursor_x])  {
                case 0:
                    board[cursor_y][cursor_x] = 1;
                    break;
                case 1:
                    board[cursor_y][cursor_x] = -1;
                    break;
                case -1: 
                    board[cursor_y][cursor_x] = 0;
                    break;
            }
        }

        // Restrict the cursor to the screen:
        if (cursor_x < 0) {
            cursor_x = 0;
        } else if (cursor_x > 7) {
            cursor_x = 7;
        }

        if (cursor_y < 0) {
            cursor_y = 0;
        } else if (cursor_y > 7) {
            cursor_y = 7;
        }

        check_finished();
    }
}