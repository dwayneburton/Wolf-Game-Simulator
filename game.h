// Node class definition
class Node {
    // Private member variables
    private:
    double x;               // X coordinate of the player
    double y;               // Y coordinate of the player
    double distance;        // Distance away from the Wolf
    Node* next = nullptr;   // Pointer to the next node in the linked list

    // Public member functions
    public:
    Node(double x, double y);       // Constructor that creates a new player node using the user inputed (x,y) coordinates
    double get_x();                 // Returns the x coordinate of the given player
    double get_y();                 // Returns the y coordinate of the given player
    double get_distance();          // Returns the distance of the given player
    void update_location(double t); // Updates the given player location with the user-inputted time
    Node* get_next();               // Returns the next node in the linked list after the given player
    void set_next(Node* node);      // Sets the next node in the linked list after the given player
};

// “What Time Is It, Mr. Wolf?” Game class definition
class Game {
    // Private member variables
    private:
    Node* head; // Pointer to the head of the linked list

    // Public member functions
    public:
    Game();                         // Constructor that assigns the head of the linked list to nullptr
    ~Game();                        // Destructor that deletes all nodes in the linked list
    void spawn(double x, double y); // Creates a new player node and adds them to the linked list
    int time(double t);             // Updates player locations using a specified time and removes players outside the bounds
    int lunch();                    // Removes players that are within a distance of <1 from the wolf
    void print(double d);           // Prints the location of all players within a specified distance
};