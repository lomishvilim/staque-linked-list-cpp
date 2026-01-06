#include "staque.h"
#include <stdexcept>

// Default constructor
Staque::Staque() : frontPtr(nullptr), backPtr(nullptr), elementCount(0) {}

// Copy constructor with validation
Staque::Staque(const Staque& otherStaque) : frontPtr(nullptr), backPtr(nullptr), elementCount(0) {
    if (&otherStaque == nullptr) {
        throw invalid_argument("Cannot copy from a null staque");
    }
    
    // If the other Staque is empty, return
    if (otherStaque.frontPtr == nullptr) {
        return;
    }
    
    // Create the first node
    frontPtr = new Staque_Node(otherStaque.frontPtr->element);
    backPtr = frontPtr;
    elementCount = 1;
    
    // Copy rest of the nodes
    Staque_Node* currentSourceNode = otherStaque.frontPtr->nextPtr;
    Staque_Node* previousNode = frontPtr;
    
    while (currentSourceNode != nullptr) {
        // Create a new node
        Staque_Node* newNode = new Staque_Node(currentSourceNode->element);
        
        // Set up doubly-linked connections
        newNode->prevPtr = previousNode;
        previousNode->nextPtr = newNode;
        
        // Update backPtr and previous node for next iteration
        backPtr = newNode;
        previousNode = newNode;
        
        elementCount++;
        currentSourceNode = currentSourceNode->nextPtr;
    }
}
// Destructor
Staque::~Staque() {
    clear();
}

// Assignment operator with validation
Staque& Staque::operator=(const Staque& otherStaque) {
    try {
        // Self-assignment check
        if (this == &otherStaque) {
            return *this;
        }
        
        // Null check
        if (&otherStaque == nullptr) {
            throw invalid_argument("Cannot assign from null Staque");
        }
        
        // Clear existing elements
        clear();
        
        // Copy elements with validation
        Staque_Node* currentNode = otherStaque.frontPtr;
        while (currentNode != nullptr) {
            if (!push(currentNode->element)) {
                clear(); // Cleanup on failure
                throw runtime_error("Assignment failed - push operation unsuccessful");
            }
            currentNode = currentNode->nextPtr;
        }
        
        return *this;
    }
    catch (...) {
        clear(); // Ensure no memory leaks on any exception
        throw;   // Re-throw the exception
    }
}
// Push element with comprehensive validation
bool Staque::push(int value) {
    
    try {
        Staque_Node* newNode = new Staque_Node(value);
        
        if (isEmpty()) {
            frontPtr = backPtr = newNode;
        }
        else if (isEven(value)) {  // Even number - insert at front
            newNode->nextPtr = frontPtr;
            frontPtr->prevPtr = newNode;
            frontPtr = newNode;
        }
        else {  // Odd number - insert at back
            newNode->prevPtr = backPtr;
            backPtr->nextPtr = newNode;
            backPtr = newNode;
        }
        
        elementCount++;
        return true;
    }
    catch (const bad_alloc& e) {
        return false;  // in case memory allocation failed
    }
}

// Remove from front following LIFO
bool Staque::removeFromFront() {
    if (isEmpty()) {
        return false;
    }

    Staque_Node* temp = frontPtr;
    
    if (frontPtr == backPtr) {  // Only one element
        frontPtr = backPtr = nullptr;
    }
    else {
        frontPtr = frontPtr->nextPtr;
        frontPtr->prevPtr = nullptr;
    }
    
    delete temp;
    elementCount--;
    return true;
}

// Remove from back following LIFO
bool Staque::removeFromBack() {
    if (isEmpty()) {
        return false;
    }

    Staque_Node* temp = backPtr;
    
    if (frontPtr == backPtr) {  // Only one element
        frontPtr = backPtr = nullptr;
    }
    else {
        backPtr = backPtr->prevPtr;
        backPtr->nextPtr = nullptr;
    }
    
    delete temp;
    elementCount--;
    return true;
}

// Remove specified number of even and odd numbers
bool Staque::removeEvenOdd(int evenCount, int oddCount) {
    try{
    // Input validation
    if (evenCount < 0 || oddCount < 0) {
        throw invalid_argument("Removal counts cannot be negative");
    }
    
    if (isEmpty()) {
        return false;
    }
    
    // If both counts are 0, consider it successful
    if (evenCount == 0 && oddCount == 0) {
        return true;
    }
    
    // First pass: count available numbers
    int availableEven = 0;
    int availableOdd = 0;
    Staque_Node* current = frontPtr;
    
    while (current != nullptr) {
        if (isEven(current->element)) {
            availableEven++;
        } else {
            availableOdd++;
        }
        current = current->nextPtr;
    }
    
    // Validate if we have enough numbers to remove
    if (availableEven < evenCount || availableOdd < oddCount) {
        return false;
    }
    
    // Remove even numbers
    int removedEven = 0;
    while (removedEven < evenCount) {
        // Try to remove from front first (LIFO)
        if (frontPtr != nullptr && isEven(frontPtr->element)) {
            removeFromFront();
            removedEven++;
            continue;
        }
        
        // Then try from back
        if (backPtr != nullptr && isEven(backPtr->element)) {
            removeFromBack();
            removedEven++;
            continue;
        }
        
        // If neither front nor back is even, find the first even number
        current = frontPtr;
        while (current != nullptr) {
            if (isEven(current->element)) {
                // Remove from middle
                if (current->prevPtr) {
                    current->prevPtr->nextPtr = current->nextPtr;
                } else {
                    frontPtr = current->nextPtr;
                }
                
                if (current->nextPtr) {
                    current->nextPtr->prevPtr = current->prevPtr;
                } else {
                    backPtr = current->prevPtr;
                }
                
                Staque_Node* temp = current;
                current = current->nextPtr;
                delete temp;
                elementCount--;
                removedEven++;
                break;
            }
            current = current->nextPtr;
        }
    }
    
    // Remove odd numbers
    int removedOdd = 0;
    while (removedOdd < oddCount) {
        // Try to remove from back first (LIFO)
        if (backPtr != nullptr && !isEven(backPtr->element)) {
            removeFromBack();
            removedOdd++;
            continue;
        }
        
        // Then try from front
        if (frontPtr != nullptr && !isEven(frontPtr->element)) {
            removeFromFront();
            removedOdd++;
            continue;
        }
        
        // If neither front nor back is odd, find the first odd number
        current = backPtr;
        while (current != nullptr) {
            if (!isEven(current->element)) {
                // Remove from middle
                if (current->prevPtr) {
                    current->prevPtr->nextPtr = current->nextPtr;
                } else {
                    frontPtr = current->nextPtr;
                }
                
                if (current->nextPtr) {
                    current->nextPtr->prevPtr = current->prevPtr;
                } else {
                    backPtr = current->prevPtr;
                }
                
                Staque_Node* temp = current;
                current = current->prevPtr;
                delete temp;
                elementCount--;
                removedOdd++;
                break;
            }
            current = current->prevPtr;
        }
    }
    
    return true;
    }catch(const exception& e) {
        clear();
        throw;
    }
}

// Display with strict format adherence
void Staque::display() const {
    if (isEmpty()) { //handle the case when the staque is empty
        cout << "(front) (back)" << endl;
        return;
    }
    cout << *this;
}

// Stream operator with proper formatting
//getters are used in place of current->nextPtr here
ostream& operator<<(ostream& output, const Staque& staqueObj) {
    output << "(front)";
    
    // Use Staque's interface to access the elements
    Staque_Node* current = staqueObj.getCurrentNode();
    while (current != nullptr) {
        output << " " << staqueObj.getNodeElement(current);
        current = staqueObj.getNextNode(current);
    }
    
    output << " (back)";
    return output;
}

// Clear all elements
void Staque::clear() {
    while (!isEmpty()) {
        removeFromFront();
    }
}