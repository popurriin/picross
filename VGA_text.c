void printText(int x, int y, char * text_ptr)//Ekrana yazi yazar
{
	int offset;
  	volatile char * character_buffer = (char *) FPGA_CHAR_BASE;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

void clear_screen_text() {
  int x, y;
  for (x = 0; x < 80; x++) {
    for (y = 0; y < 60; y++) {
	  printText(x, y, " ");
	}
  }
}