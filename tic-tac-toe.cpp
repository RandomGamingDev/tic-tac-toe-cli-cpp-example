// These are just C++ imports
#include <iostream>
#include <cstdlib>
#include <array>
#include <cstddef>
#include <string>

// The piece enum values (just use the chars directly for your project)
enum Piece {
    Empty,
    X,
    O
};

// An array containing the corresponding characters for each enum
const std::array<char, 3> piece_to_char = {{ ' ', 'X', 'O' }};

// The board's dimensions
const int width = 3;
const int height = 3;
// The board (A 2D array)
std::array<std::array<Piece, 3>, 3> board = {{
    { Piece::Empty, Piece::Empty, Piece::Empty },
    { Piece::Empty, Piece::Empty, Piece::Empty },
    { Piece::Empty, Piece::Empty, Piece::Empty }
}};

// If this is true it's o's, but it's x's turn if it's false (in this case x goes first)
bool o_turn = false;

// This clears the board
void clear_board() {
    board = {{
        { Piece::Empty, Piece::Empty, Piece::Empty },
        { Piece::Empty, Piece::Empty, Piece::Empty },
        { Piece::Empty, Piece::Empty, Piece::Empty }
    }};
}

// Converts the board to a string
std::string board_to_str() {
    std::string toReturn = "";
    
    // Iterate over the first array which contains the rows
    for (size_t y = 0; y < height; y++) {
        // Iterate over the pieces in the row
        for (size_t x = 0; x < width; x++) {
            // Get the piece
            const Piece piece = board[y][x];
            // Get the character of the piece and add it to the string
            toReturn += piece_to_char[piece];
        }
        // Go to the next line when going to the next row
        toReturn += '\n';
    }
    
    // Return the value
    return toReturn;
}

// Converts o_turn aka the current turn into its piece
Piece get_current_piece() {
    if (o_turn)
        return Piece::O;
    else
        return Piece::X;
}

// Get a piece on the board
Piece get_piece(size_t x, size_t y) {
    return board[y][x];
}

// Set a piece on the board
void set_piece(size_t x, size_t y, Piece piece) {
    board[y][x] = piece;
}

// Check whether they've won (returns a boolean with whether or not they've won)
// You only need to check the row and column where the piece was placed
bool has_won(size_t x, size_t y, Piece piece) {
    // Check the row by looping over it and checking whether all of them are the same
    bool row_win = true;
    for (size_t i = 0; i < width; i++)
        // Check whether or not the row is made of the same piece
        if (get_piece(i, y) != piece) {
            // Mark the fact that there's no row win
            row_win = false;
            // Break out of the loop to avoid doing unnecessary calculations
            break;
        }
    // If you detect a row win return true
    if (row_win)
        return true;
    
    // Check the column by looping over it
    bool column_win = true;
    for (size_t i = 0; i < width; i++)
        // Check whether or not the column is made of the same piece
        if (get_piece(x, i) != piece) {
            // Mark the fact that there's no column win
            column_win = false;
            // Break out of the loop to avoid doing unnecessary calculations
            break;
        }
    // If you detect a row win return true
    if (column_win)
        return true;
    
    // Check the diagnols by looping over them
    // It's always a diagnol if x == y or the distance between x & y's 2
    // Check the top left to bottom right diagnol
    if (x == y) {
        bool tl_to_br_diagnol_win = true;
        
        for (size_t i = 0; i < width; i++)
            // Check whether or not the diagnol is made of the same piece
            if (get_piece(i, i) != piece) {
                // Mark the fact that there's no diagnol win
                tl_to_br_diagnol_win = false;
                // Break out of the loop to avoid doing unnecessary calculations
                break;
            }
        
        // If you detect a top left to bottom right diagnol win return true
        if (tl_to_br_diagnol_win)
            return true;
    }
        
    // Check the top right to bottom left diagnol
    // The (x == 1 && y == 1) is there so that we do it if the piece is in the center
    if ((x == 1 && y == 1) || std::abs((int)x - (int)y) == 2) {
        bool tr_to_bl_diagnol_win = true;
        
        for (size_t i = 0; i < width; i++)
            // Check whether or not the diagnol is made of the same piece
            // Use (width - 1) - i for the x so that it flips over the y axis checking the other diagnol
            if (get_piece((width - 1) - i, i) != piece) {
                // Mark the fact that there's no diagnol win
                tr_to_bl_diagnol_win = false;
                // Break out of the loop to avoid doing unnecessary calculations
                break;
            }
            
        // If you detect a top right to bottom left diagnol win return true
        if (tr_to_bl_diagnol_win)
            return true;
    }
    
    // If none of them detect a win then the piece hasn't won
    return false;
}

// Check whether or not the game's drawn
bool has_drawn() {
    // Loop over all pieces and if one is empty the game isn't drawn
    for (size_t x = 0; x < width; x++)
        for (size_t y = 0; y < height; y++)
            if (get_piece(x, y) == Piece::Empty)
                return false;
    // If they are all empty it is
    return true;
}

// const just means that a variable won't change and is thus constant
// std::cout << "This prints the value input into it!" << std::endl
// (the ending part just moves to the next line);

// std::cin >> var gets input and automatically converts it to the type needed
// (you will need to convert the type manually in python)

// std::abs() is just absolute value
// (I cast to int by doing: (int) since size_t can't be negative)

// In C++ & many other languages the main function is just where execution starts
int main() {
    // The game loop
    while (true) {
        // Display the board
        std::cout << board_to_str();
        
        
        // Get the current piece
        const Piece current_piece = get_current_piece();
        // The corresponding character for the current piece
        const char current_char = piece_to_char[current_piece];
        // Display the current piece/char
        std::cout << "It's " << current_char << "'s turn!" << std::endl;
        
        
        // Get the user's input and subtract by 1 for each coordinate
        //  so that: 1 -> 0, 2 -> 1, 3 -> 2, when indexing the array
        std::cout << "Enter the x: " << std::endl;
        size_t x = 0;
        std::cin >> x;
        x--;
        
        std::cout << "Enter the y: " << std::endl;
        size_t y = 0;
        std::cin >> y;
        y--;
        
        // If there's a piece there warn the user and then
        //  skip over everything after this with continue
        //  that way the user can make their move again
        // Otherwise set the piece and continue on as normal
        if (get_piece(x, y) != Piece::Empty) {
            std::cout << "There's already a piece there!" << std::endl;
            continue;
        }
        else
            set_piece(x, y, current_piece);
        
        // If the user's won
        if (has_won(x, y, current_piece)) {
            // Display the final winning board
            std::cout << board_to_str();
            // Display which piece won
            std::cout << current_char << "'s won!" << std::endl;
            // Clear the board for the next game
            clear_board();
        }
        
        // If the game's drawed
        if (has_drawn()) {
            // Display the final drawn board
            std::cout << board_to_str();
            // Display the fact that the game's drawn
            std::cout << "The game's ended in a draw!" << std::endl;
            // Clear the board for the next game
            clear_board();
        }
        
        // Switch whose turn it is by making it the opposite of itself
        o_turn = !o_turn;
    }

    // Returning 0 just means that no errors happened in C++
    return 0;
}
