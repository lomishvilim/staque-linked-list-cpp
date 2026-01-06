#include "staque.h"
#include <iostream>
#include <iomanip>

// Helper function to print test headers
void printTestHeader(const string& testName) {
    cout << "\n" << string(50, '=') << "\n";
    cout << "TEST: " << testName << "\n";
    cout << string(50, '=') << "\n";
}

int main() {
    // TEST SERIES 1: Basic Operations as per assignment example
    printTestHeader("Series 1 - Assignment Example");
    {
        Staque s1;
        cout << "Inserting: 1, 3, 2, 4, 6, 8, 9\n";
        s1.push(1);
        s1.push(3);
        s1.push(2);
        s1.push(4);
        s1.push(6);
        s1.push(8);
        s1.push(9);
        
        cout << "Current Staque: " << s1 << "\n";
        // Should show: (front) 8 6 4 2 1 3 9 (back)
        
        cout << "Removing 2 even numbers and 1 odd number\n";
        s1.removeFromFront(); // removes 8
        s1.removeFromFront(); // removes 6
        s1.removeFromBack();  // removes 9
        
        cout << "After removal: " << s1 << "\n";
        // Should show: (front) 4 2 1 3 (back)
    }

    // TEST SERIES 2: Copy Constructor and Assignment Operator
    printTestHeader("Series 2 - Copy Operations");
    {
        Staque s1;
        cout << "Creating first Staque with: 5, 2, 7, 4, 1\n";
        s1.push(5);
        s1.push(2);
        s1.push(7);
        s1.push(4);
        s1.push(1);
        cout << "Original Staque: " << s1 << "\n";
        
        // Test copy constructor
        cout << "Testing copy constructor...\n";
        Staque s2(s1);
        cout << "Copied Staque: " << s2 << "\n";
        
        //ensure that it's a deep copy, so changing s1 doesnt change s2
        s1.push(9);
        cout << "After editing original Staque: " << s1 << endl;
        cout << "Copied Staque (should be unchanged): " << s2 << endl;

        // Test assignment operator
        cout << "Testing assignment operator...\n";
        Staque s3;
        s3 = s1;
        cout << "Assigned Staque: " << s3 << "\n";
        
        // Modify original to prove deep copy
        cout << "Removing elements from original...\n";
        s1.removeFromFront();
        s1.removeFromBack();
        cout << "Original after removal: " << s1 << "\n";
        cout << "Copy should be unchanged: " << s2 << "\n";
        cout << "Assignment should be unchanged: " << s3 << "\n";
    }

    // TEST SERIES 3: Even/Odd Removal and Edge Cases
    printTestHeader("Series 3 - Complex Removal Operations");
    {
        Staque s1;
        cout << "Creating Staque with: 10, 3, 8, 5, 6, 7, 4, 1\n";
        s1.push(10);
        s1.push(3);
        s1.push(8);
        s1.push(5);
        s1.push(6);
        s1.push(7);
        s1.push(4);
        s1.push(1);
        cout << "Initial Staque: " << s1 << "\n";
        
        // Test removeEvenOdd
        cout << "Removing 2 even and 1 odd numbers...\n";
        s1.removeEvenOdd(2, 1);
        cout << "After removal: " << s1 << "\n";
        
        // Test edge cases
        cout << "\nTesting edge cases:\n";
        
        // Try to remove more than available
        cout << "Attempting to remove more numbers than available...\n";
        bool result = s1.removeEvenOdd(10, 10);
        cout << "Operation " << (result ? "succeeded" : "failed") << " (should fail)\n";
        
        // Try to remove from empty Staque
        Staque emptyStaque;
        cout << "Attempting to remove from empty Staque...\n";
        result = emptyStaque.removeFromFront();
        cout << "Operation " << (result ? "succeeded" : "failed") << " (should fail)\n";
    }

    // TEST SERIES 4: Single Element Operations
    printTestHeader("Series 4 - Single Element Operations");
    {
        Staque s1;
        cout << "Testing single element operations:\n";
        
        // Add and remove single element
        cout << "Adding single even number (2)...\n";
        s1.push(2);
        cout << "Staque: " << s1 << "\n";
        
        cout << "Removing from front...\n";
        s1.removeFromFront();
        cout << "Staque should be empty: " << s1 << "\n";
        
        // Add and remove single odd number
        cout << "Adding single odd number (3)...\n";
        s1.push(3);
        cout << "Staque: " << s1 << "\n";
        
        cout << "Removing from back...\n";
        s1.removeFromBack();
        cout << "Staque should be empty: " << s1 << "\n";
    }

     // TEST SERIES 5: Additional Test Cases
    printTestHeader("Series 5 - Additional Test Cases");
    {
        // Staque with many elements
        Staque s1;
        for (int i = 1; i <= 20; ++i) {
            s1.push(i);
        }
        cout << "Staque with many elements: " << s1 << "\n";
        s1.removeEvenOdd(5, 5);
        cout << "After removing 5 even and 5 odd: " << s1 << "\n";

        // Staque with alternating even and odd numbers
        Staque s2;
        for (int i = 1; i <= 10; ++i) {
            s2.push(2 * i - 1);
            s2.push(2 * i);
        }
        cout << "Staque with alternating even and odd numbers: " << s2 << "\n";
        s2.removeEvenOdd(3, 3);
        cout << "After removing 3 even and 3 odd: " << s2 << "\n";

        // Staque with only even numbers
        Staque s3;
        for (int i = 2; i <= 10; i += 2) {
            s3.push(i);
        }
        cout << "Staque with only even numbers: " << s3 << "\n";
        s3.removeEvenOdd(3, 0);
        cout << "After removing 3 even numbers: " << s3 << "\n";

        // Staque with only odd numbers
        Staque s4;
        for (int i = 1; i <= 9; i += 2) {
            s4.push(i);
        }
        cout << "Staque with only odd numbers: " << s4 << "\n";
        s4.removeEvenOdd(0, 3);
        cout << "After removing 3 odd numbers: " << s4 << "\n";

        // Staque with repeated numbers
        Staque s5;
        s5.push(2);
        s5.push(3);
        s5.push(2);
        s5.push(4);
        s5.push(3);
        cout << "Staque with repeated numbers: " << s5 << "\n";
        s5.removeEvenOdd(2, 2);
        cout << "After removing 2 even and 2 odd: " << s5 << "\n";
    }


    cout << "\nAll tests completed successfully!\n";
    return 0;
}