#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

// ================== Utility for Dates ==================
string currentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(1900 + ltm->tm_year) + "-" +
           to_string(1 + ltm->tm_mon) + "-" +
           to_string(ltm->tm_mday);
}

// ================== Base Class: Book ==================
class Book {
protected:
    string id, title, author;
    bool isIssued;
    string issuedTo;
    string issueDate;

public:
    Book(string id, string title, string author)
        : id(id), title(title), author(author), isIssued(false) {}

    virtual void showInfo() {
        cout << "ID: " << id << " | Title: " << title
             << " | Author: " << author
             << " | Status: " << (isIssued ? "Issued" : "Available") << endl;
    }

    string getId() { return id; }
    string getTitle() { return title; }
    bool getIssued() { return isIssued; }
    string getIssuedTo() { return issuedTo; }
    string getIssueDate() { return issueDate; }

    void issueBook(string studentName) {
        isIssued = true;
        issuedTo = studentName;
        issueDate = currentDate();
    }

    void returnBook() {
        isIssued = false;
        issuedTo = "";
        issueDate = "";
    }
};

// ================== Child Class: Digital Book ==================
class DigitalBook : public Book {
    float fileSizeMB;

public:
    DigitalBook(string id, string title, string author, float size)
        : Book(id, title, author), fileSizeMB(size) {}

    void showInfo() override {
        cout << "[Digital] ID: " << id << " | Title: " << title
             << " | Author: " << author
             << " | Size: " << fileSizeMB << "MB"
             << " | Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

// ================== Student Class ==================
class Student {
    string name;
    string roll;

public:
    Student(string name, string roll) : name(name), roll(roll) {}

    string getName() { return name; }
    string getRoll() { return roll; }
};

// ================== Library System ==================
class Library {
    vector<Book*> books;
    vector<Student> students;

public:
    // Add normal book
    void addBook() {
        string id, title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);

        books.push_back(new Book(id, title, author));
        cout << "Book Added Successfully!\n";
    }

    // Add digital book
    void addDigitalBook() {
        string id, title, author;
        float size;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter File Size (MB): ";
        cin >> size;

        books.push_back(new DigitalBook(id, title, author, size));
        cout << "Digital Book Added Successfully!\n";
    }

    // Add student
    void addStudent() {
        string name, roll;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Roll No: ";
        cin >> roll;

        students.push_back(Student(name, roll));
        cout << "Student Added Successfully!\n";
    }

    // Search book by title or id
    void searchBook() {
        string key;
        cin.ignore();
        cout << "Enter Book ID or Title: ";
        getline(cin, key);

        bool found = false;
        for (auto b : books) {
            if (b->getId() == key || b->getTitle() == key) {
                b->showInfo();
                found = true;
            }
        }

        if (!found) cout << "No book found.\n";
    }

    // Issue book
    void issueBook() {
        string id, studentName;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, studentName);

        for (auto b : books) {
            if (b->getId() == id) {
                if (!b->getIssued()) {
                    b->issueBook(studentName);
                    cout << "Book Issued on: " << b->getIssueDate() << "\n";
                    return;
                } else {
                    cout << "Already Issued to " << b->getIssuedTo() << "\n";
                    return;
                }
            }
        }
        cout << "Book not found.\n";
    }

    // Return book + fine system
    void returnBook() {
        string id;
        cout << "Enter Book ID: ";
        cin >> id;

        for (auto b : books) {
            if (b->getId() == id) {
                if (b->getIssued()) {
                    cout << "Enter Days Late: ";
                    int days; cin >> days;
                    int fine = days * 20;

                    b->returnBook();
                    cout << "Returned Successfully!\n";
                    cout << "Fine: " << fine << " PKR\n";
                    return;
                } else {
                    cout << "Book is not issued.\n";
                    return;
                }
            }
        }
        cout << "Book not found.\n";
    }

    // Show all books
    void showAllBooks() {
        cout << "\n===== Library Books =====\n";
        for (auto b : books) b->showInfo();
    }
};

// ================== MAIN MENU ==================
int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n==============================\n";
        cout << "   Library Management System\n";
        cout << "==============================\n";
        cout << "1. Add Book\n";
        cout << "2. Add Digital Book\n";
        cout << "3. Add Student\n";
        cout << "4. Search Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Show All Books\n";
        cout << "8. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.addDigitalBook(); break;
            case 3: lib.addStudent(); break;
            case 4: lib.searchBook(); break;
            case 5: lib.issueBook(); break;
            case 6: lib.returnBook(); break;
            case 7: lib.showAllBooks(); break;
            case 8: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid Choice!\n";
        }
    }
}