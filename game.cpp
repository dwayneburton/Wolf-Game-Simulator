// Including the necessary header files
#include "game.h"
#include "cmath"
#include <iostream>

// Node constructor that assigns the players' starting position
Node::Node(double x=0, double y=0) {
    this->x = x;
    this->y = y;
    this->distance = sqrt(x*x + y*y);
}

// Returns the x coordinate of the given player
double Node::get_x() {
    return x;
}

// Returns the y coordinate of the given player
double Node::get_y() {
    return y;
}

// Returns the distance of the given player
double Node::get_distance() {
    return distance;
}

// Updates the given player location with the user-inputted time
void Node::update_location(double t) {
    double x_temp = x;
    x -= t * cos(atan2(y, x));
    y -= t * sin(atan2(y, x_temp));
    distance = sqrt(x*x + y*y);
}

// Returns the next node in the linked list after the given player
Node* Node::get_next() {
    return next;
}

// Sets the next node in the linked list after the given player
void Node::set_next(Node* node) {
    next = node;
}

// Game constructor that sets head to nullptr
Game::Game() {
    head = nullptr;
}

// Game destructor that deletes all nodes in the linked list
Game::~Game() {
    // Loop that continues until the end of the linked list is reached
    while (head != nullptr) {
        // Deletes the current linked list node
        Node* next = head->get_next();
        delete head;
        head = next;
    }
}

// Adds a new player node to the linked list
void Game::spawn(double x, double y) {
    Node* new_player = new Node(x, y);
    new_player->set_next(head);
    head = new_player;
}

// Updates player locations using a user-inputted time
int Game::time(double t) {
    int cheating_players = 0;
    Node* current = head;
    Node* previous = nullptr;

    // Loop that continues until the end of the linked list is reached
    while (current != nullptr) {
        // Updating the position of the player based on a user-inputted time
        current->update_location(t);

        // Checks if the player is cheating (outside the first quadrant) and removes them from the game
        if (current->get_x() <= 0 || current->get_y() <= 0) {
            cheating_players++;
            // If the cheating player is a head node
            if (previous == nullptr) {
                head = current->get_next();
                delete current;
                current = head;
            // If the cheating player is a middle or end node
            } else {
                previous->set_next(current->get_next());
                delete current;
                current = previous->get_next();
            }
        } else {
            previous = current;
            current = current->get_next();
        }
    }
    // Returns the amount of cheating players (players removed from the linked list)
    return cheating_players;
}

// Removes players that are within a distance of <1 from the wolf
int Game::lunch() {
    int eliminated_players = 0;
    Node* current = head;
    Node* previous = nullptr;

    // Loop that continues until the end of the linked list is reached
    while (current != nullptr) {
        // Checks if the player is within a distance of <1 from the wolf and removes them from the game
        if (current->get_distance() < 1) {
            eliminated_players++;
            // If the eliminated player is a head node
            if (previous == nullptr) {
                head = current->get_next();
                delete current;
                current = head;
            // If the eliminated player is a middle or end node
            } else {
                previous->set_next(current->get_next());
                delete current;
                current = previous->get_next();
            }
        } else {
            previous = current;
            current = current->get_next();
        }
    }
    // Returns the amount of eliminated players (players removed from the linked list)
    return eliminated_players;
}

void Game::print(double d) {
    bool no_players_found = true;
    Node* current = head;

    // Loop that continues until the end of the linked list is reached
    while (current != nullptr) {
        // Prints the player's location if they are within the specified distance
        if (current->get_distance() < d) {
            std::cout << current->get_x() << " " << current->get_y() << " ";
            no_players_found = false;
        }
        current = current->get_next();
    }
    
    // If zero players were within the specified distance
    if (no_players_found) {
        std::cout << "no players found";
    }

    // End line needed for formatting
    std::cout << std::endl;
}