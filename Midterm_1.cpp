// Midterm_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    int quantity;

    void display() const {
        cout << "Title: " << title
            << ", Author: " << author
            << ", Available: " << quantity << endl;
    }

    bool checkout() {
        if (quantity > 0) {
            quantity--;
            return true;
        }
        else {
            return false;
        }
    }
};
//-----------------------------
class Library {
private:
    Book* books[50];
    int count;

public:
    Library() : count(0) {}

    ~Library() {
        clearInventory();
    }

    void clearInventory() {
        for (int i = 0; i < count; ++i) {
            delete books[i];
            books[i] = nullptr;
        }
        count = 0;
    }

    void addBook(string t, string a, int q) {
        if (count < 50) {
            books[count] = new Book{ t, a, q };
            count++;
        }
    }

    void saveToFile(const string& filename) {
        ofstream out(filename);
        for (int i = 0; i < count; ++i) {
            out << books[i]->title << ","
                << books[i]->author << ","
                << books[i]->quantity << endl;
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        clearInventory();
        ifstream in(filename);
        string t, a;
        int q;
        while (getline(in, t, ',') && getline(in, a, ',') && in >> q) {
            in.ignore();
            addBook(t, a, q);
        }
        in.close();
    }
    //the display
    void listBooks() const {
        cout << "Library's Book Inventory:\n";
        for (int i = 0; i < count; ++i)
            books[i]->display();
    }

    int binarySearch(string title) const {
        int left = 0, right = count - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (books[mid]->title == title)
                return mid;
            else if (books[mid]->title < title)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    void checkoutBook(string title) {
        int index = binarySearch(title);
        if (index != -1) {
            bool success = books[index]->checkout();
            if (success) {
                cout << "Successfully checked out \"" << title << "\".\n";
            }
            else {
                cout << "Error sorry, \"" << title << "\" is currently unavailable.\n"; 
            }
        }
        else {
            cout << "Book not found in the catalog.\n";
        }
    }
};

int main() {
    Library lib;
    lib.addBook("Wonder", "R. J. Palacio", 3);
    lib.addBook("Lives of the Saints", "Alexander Egger & Natalia Sheniloff", 4);
    lib.addBook("Green Eggs & Ham", "Dr.Seuss", 2);

    lib.saveToFile("library.txt");

    lib.loadFromFile("library.txt");
    lib.listBooks();

    string searchTitle;
    cout << "\nEnter the book title to check out: ";
    getline(cin, searchTitle);
    lib.checkoutBook(searchTitle);

    lib.listBooks(); // show updated quantities

    return 0;
}
/*Library's Book Inventory:
Title: Wonder, Author: R. J. Palacio, Available: 3
Title: Lives of the Saints, Author: Alexander Egger & Natalia Sheniloff, Available: 4
Title: Green Eggs & Ham, Author: Dr.Seuss, Available: 2

Enter the book title to check out: Lives of the Saints
Successfully checked out "Lives of the Saints".
Library's Book Inventory:
Title: Wonder, Author: R. J. Palacio, Available: 3
Title: Lives of the Saints, Author: Alexander Egger & Natalia Sheniloff, Available: 3
Title: Green Eggs & Ham, Author: Dr.Seuss, Available: 2

C:\CIS-25\Midterm_1\x64\Debug\Midterm_1.exe (process 14264) exited with code 0 (0x0).
Press any key to close this window . . .*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
