#define PICROSS_BOARD_HEIGHT 8
#define PICROSS_BOARD_WIDTH 8
int player_grid[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_WIDTH] = {0}
bool player_grid_clicked[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_WIDTH];
bool answer_grid[PICROSS_BOARD_HEIGHT][PICROSS_BOARD_WIDTH];
enum grid_state {empty, correct, crossed, selected};