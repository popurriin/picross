#include "picross.h"
#include "board_answers.h"
#include "picture_arrays.h"
#include "sound_array.h"

void sound(double win_buffer[], int BUF_SIZE, bool deadLoop) {
	volatile int * audio_ptr = (int *) AUDIO_BASE;
	volatile int * ledr_ptr	 = (int *) LEDR_BASE;
    
	/* used for audio record/playback */
	int fifospace;
	int play = 1, buffer_index = 0;
	int left_buffer[BUF_SIZE];
	int right_buffer[BUF_SIZE];
	 	
	while (play) {
        // read the audio port fifospace register
        fifospace = *(audio_ptr + 1);	 		
        
            // output data until the buffer is empty or the audio-out FIFO is full
            while ( (fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE)) {
                *(audio_ptr + 2) = win_buffer[buffer_index];
                *(audio_ptr + 3) = win_buffer[buffer_index];
                ++buffer_index;
                *(ledr_ptr) = 1;

                if (buffer_index == BUF_SIZE) {
                    play = 0;
                }
                
                fifospace = *(audio_ptr + 1);	// read the audio port fifospace register
            }
        
    }
}