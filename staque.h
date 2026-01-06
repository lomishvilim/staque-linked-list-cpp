#ifndef STAQUE_H
#define STAQUE_H

#include <iostream>
using namespace std;

class Staque_Node {
private:
    int element;
    Staque_Node* nextPtr;
    Staque_Node* prevPtr;
    
    // Constructor for node with validation
    Staque_Node(int value, Staque_Node* next = nullptr, Staque_Node* prev = nullptr) 
        : element(value), nextPtr(next), prevPtr(prev) {}
    
    friend class Staque;
};

class Staque {
private:
    Staque_Node* frontPtr;
    Staque_Node* backPtr;
    size_t elementCount;
    
public:
    // Default constructor
    Staque();
    
    // Copy constructor (required by assignment)
    Staque(const Staque& otherStaque);
    
    // Destructor (required by assignment)
    ~Staque();
    
    // Assignment operator overload (required by assignment)
    Staque& operator=(const Staque& otherStaque);
    
    // Main operations
    bool push(int value);  // Changed name to be more intuitive
    
    // Three different removal methods as required
    bool removeFromFront();  // Removes following LIFO from front
    bool removeFromBack();   // Removes following LIFO from back
    bool removeEvenOdd(int evenCount, int oddCount);  // Removes specified number of even/odd numbers
    
    // Display methods (required by assignment)
    void display() const;  // Displays in format: (front) elements (back)
    friend ostream& operator<<(ostream& output, const Staque& staqueObj);
    
    // Utility methods
    bool isEmpty() const { return elementCount == 0; }
    size_t size() const { return elementCount; }
    
    //added later, due to << causing issues
    Staque_Node* getCurrentNode() const {
        return frontPtr; }
    Staque_Node* getNextNode(Staque_Node* current) const {
         return current ? current->nextPtr : nullptr; }
    int getNodeElement(Staque_Node* current) const {
        return current ? current->element : 0; }
private:
    // Helper methods
    void clear();  // Used by destructor and assignment operator
    bool isEven(const int value) const { return value % 2 == 0; }
};

#endif // STAQUE_H