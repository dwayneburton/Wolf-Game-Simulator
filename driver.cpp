// Including the necessary header files
#include <iostream>
#include <string>
#include "game.h"

int main() { 
    // Variable initializations and declarations 
    unsigned int player_count = 0;
    bool run = true;
    std::string input;
    Game Wolf;

    // Loop that runs until the user enters the "OVER" command
    while (run) {
        // Stores user input
        std::getline(std::cin, input);

        // Spawns a new player given the "SPAWN" command
        if (input.substr(0,5) == "SPAWN") {
            // Stores user-inputted (x,y) coordinates
            double x = stod(input.substr(6, input.substr(6).find(" ")));
            double y = stod(input.substr(6).substr(input.substr(6).find(" ") + 1));

            // Checks if the user entered coordinates in the first quadrant
            if (x > 0 && y > 0) {
                Wolf.spawn(x, y);
                player_count++;
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        // Updates player locations given the "TIME" command and prints the number of remaining players
        } else if (input.substr(0,4) == "TIME") {
            player_count -= Wolf.time(stod(input.substr(5)));
            std::cout << "num of players: " << player_count << std::endl;
        // Removes players that are within a distance of <1 from the wolf given the "LUNCH" command and prints the number of remaining players
        } else if (input.substr(0,5) == "LUNCH") {
            player_count -= Wolf.lunch();
            std::cout << "num of players: " << player_count << std::endl;
        // Prints the number of remaining players given the "NUM" command
        } else if (input.substr(0,3) == "NUM") {
            std::cout << "num of players: " << player_count << std::endl;
        // Prints the coordinates of all remaining players within a specified distance given the "PRT" command
        } else if (input.substr(0,3) == "PRT") {
            Wolf.print(stod(input.substr(4)));
        // Determines if the wolf or players win and ends the program given the "OVER" command
        } else if (input.substr(0,4) == "OVER") {
            if (player_count) {
                std::cout << "players win" << std::endl;
            } else {
                std::cout << "wolf wins" << std::endl;
            }
            run = false;
        }
    }
}