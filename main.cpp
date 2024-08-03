#include <iostream>
#include <cctype>

// Define the structure for a graph node
struct Node {
    int status;        // Status of the node: 0 = unvisited, 1 = visited
    char data;         // Data stored in the node (e.g., character representing the node)
    Node *next;        // Pointer to the next node in the list (for linked nodes)
    Node *adjacent;    // Pointer to the first adjacent node (for links)
};

Node *currentNode, *lastNode, *graphStart, *adjNode, *previousAdjNode;

// Function to create the graph
void createGraph() {
    int isFirstNode = 0; // Flag to indicate if it's the first node being added
    char inputChar;      // Character input for node and link creation
    graphStart = nullptr; // Initialize the start of the graph as null

    std::cout << "Enter the nodes in the graph (press x to exit): ";

    // Loop to input nodes
    while (true) {
        std::cin >> inputChar;
        if (inputChar == 'x') {
            break; // Exit loop if 'x' is entered
        }
        // Create a new node
        currentNode = new Node;
        currentNode->data = inputChar;
        currentNode->status = 0; // Set status to unvisited
        currentNode->next = nullptr;
        currentNode->adjacent = nullptr;

        // Link nodes together
        if (isFirstNode == 0) {
            graphStart = currentNode; // Set start of the graph
            lastNode = currentNode;   // Initialize last node
            isFirstNode++;
        } else {
            lastNode->next = currentNode; // Link previous node to current node
            lastNode = currentNode;       // Update last node
        }
    }

    currentNode = graphStart;
    // Loop to input links for each node
    while (currentNode != nullptr) {
        std::cout << "Enter the links to " << currentNode->data << " (x to exit): ";
        isFirstNode = 0; // Reset flag for adjacency list
        while (true) {
            std::cin >> inputChar;
            if (inputChar == 'x') {
                break; // Exit loop if 'x' is entered
            }
            // Create a new adjacency node
            adjNode = new Node;
            adjNode->adjacent = nullptr;

            // Add node to adjacency list
            if (isFirstNode == 0) {
                currentNode->adjacent = adjNode; // Set first adjacent node
                previousAdjNode = adjNode;
                isFirstNode++;
            } else {
                previousAdjNode->adjacent = adjNode; // Link previous adjacent node
                previousAdjNode = adjNode;
            }

            // Find the node in the graph to link to
            lastNode = graphStart;
            while (lastNode != nullptr) {
                if (lastNode->data == inputChar) {
                    adjNode->next = lastNode; // Link adjacency node to the found node
                    lastNode = lastNode->next;
                    break; // Exit loop once node is found
                }
                lastNode = lastNode->next; // Move to the next node
            }
        }
        currentNode = currentNode->next; // Move to the next node in the graph
    }
}

// Function for depth-first search (DFS) utility
void depthFirstSearchUtil(Node *startNode) {
    int stackPointer = -1; // Pointer for the stack
    Node *stack[100]; // Stack for DFS
    currentNode = startNode;
    std::cout << currentNode->data; // Print the starting node
    currentNode->status = -1; // Mark the node as visited
    adjNode = currentNode->adjacent; // Start with the adjacent nodes

    while (true) {
        if (adjNode != nullptr) {
            stackPointer++; // Push to stack
            stack[stackPointer] = adjNode;
            lastNode = adjNode->next; // Check the next node

            if (lastNode != nullptr && lastNode->status == 0) {
                std::cout << " " << lastNode->data; // Print the node data
                lastNode->status = 1; // Mark node as visited
                adjNode = lastNode->adjacent; // Move to the next adjacent node
            } else {
                adjNode = adjNode->adjacent; // Continue with the current adjacent node
            }
        } else {
            if (stackPointer >= 0) {
                adjNode = stack[stackPointer]; // Pop from stack
                stackPointer--;
                adjNode = adjNode->adjacent; // Continue with the next node
            } else {
                break; // Exit if stack is empty
            }
        }
    }
}

// Function to perform depth-first search (DFS)
void depthFirstSearch() {
    currentNode = graphStart;
    // Reset the status of all nodes to unvisited
    while (currentNode != nullptr) {
        currentNode->status = 0;
        currentNode = currentNode->next;
    }

    currentNode = graphStart;
    // Perform DFS starting from each unvisited node
    while (currentNode != nullptr) {
        if (currentNode->status == 0) {
            depthFirstSearchUtil(currentNode); // Call DFS utility
        }
        currentNode = currentNode->next; // Move to the next node in the graph
    }
}

int main() {
    createGraph(); // Create the graph
    std::cout << "\n\nDFS for graph: ";
    depthFirstSearch(); // Perform DFS
    std::cin.get(); // Wait for user input before closing
    return 0;
}
