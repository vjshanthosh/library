#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void add_user (map<string, string>& users, map<string, vector<string> >& user_book) {
    string name, pass;
    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    users[name] = pass;
    user_book[name] = {};
}

void remove_user(map<string, string>& users, map<string, vector<string> >& user_book) {
    string name;
    cout << "User to remove: ";
    cin >> name;
    if (users.count(name)) {
        users.erase(name);
        user_book.erase(name);
    }
}

void add_book (map<string, int>& books) {
    string book;
    cout << "Name of the book: ";
    cin >> book;
    int num;
    cout << "How many books: ";
    cin >> num;
    if (books.count(book)) {
        books[book] += num;
    } else {
        books[book] = num;
    }
}

void remove_book (map<string, int>& books) {
    string book;
    cout << "What book to remove: ";
    cin >> book;
    int num;
    cout << "How many to remove: ";
    cin >> num;
    if (books.count(book) && books[book] > num) {
        books[book] -= num;
    } else if (books.count(book) && books[book] <= num) {
        books.erase(book);
    }
}

void login(string& current, map<string, string> users) {
    string name, pass;
    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    if (users.count(name) && users[name] == pass) {
        current = name;
        cout << "Login successful!\n";
    } else {
        cout << "Invalid login.\n";
    }
}

void get_book (string current, map<string, vector<string> >& user_book, map<string, int>& books) {
    string book;
    cout << "What book would you like: ";
    cin >> book;
    if (books.count(book)) {
        books[book]--;
        if (books[book] == 0) {
            books.erase(book);
        }
        user_book[current].push_back(book);
        cout << "Success!\n";
    } else {
        cout << "Book unavailable.\n";
    }
}

void see_books (map<string, int> books) {
    for (auto book : books) {
        cout << book.first << " x" << book.second << endl;
    }
}

void see_users (map<string, string> users, map<string, vector<string> > user_book) {
    for (auto user : users) {
        cout << "Username: " << user.first << " Password: " << user.second << " Books: ";
        for (auto book : user_book[user.first]) {
            cout << book;
        }
        cout << endl;
    }
}

void return_book (string current, map<string, vector<string> >& user_book, map<string, int>& books) {
    string book;
    cout << "What book to return: ";
    cin >> book;
    auto f = find(user_book[current].begin(), user_book[current].end(), book);
    if (f != user_book[current].end()) {
        user_book[current].erase(f);
        if (books.count(book)) {
            books[book]++;
        } else {
            books[book] = 1;
        }
    }
}

int main() {
    map<string, string> users;
    users["Admin"] = "Admin@123";
    map<string, int> books;
    map<string, vector<string> > user_book;
    string current = "";
    while (true) {
        if (current == "") {
            string input;
            cout << "Type l to login or q to quit: ";
            cin >> input;
            if (input == "l") {
                login(current, users);
            } else if (input == "q") {
                break;
            }
        } else if (current == "Admin") {
            string input;
            cout << "Type ab to add book, rb to remove book, au to add user, ru to remove user, sb to see books, su to see users, l to logout, or q to quit: ";
            cin >> input;
            if (input == "ab") {
                add_book(books);
            } else if (input == "rb") {
                remove_book(books);
            } else if (input == "au") {
                add_user(users, user_book);
            } else if (input == "ru") {
                remove_user(users, user_book);
            } else if (input == "sb") {
                see_books(books);
            } else if (input == "su") {
                see_users(users, user_book);
            } else if (input == "l") {
                current = "";
            } else if (input == "q") {
                break;
            }
        } else {
            string input;
            cout << "Type g to get book, r to return book, s to see books, l to logout, or q to quit: ";
            cin >> input;
            if (input == "g") {
                get_book(current, user_book, books);
            } else if (input == "r") {
                return_book(current, user_book, books);
            } else if (input == "s") {
                see_books(books);
            } else if (input == "l") {
                current = "";
            } else if (input == "q") {
                break;
            }
        }
    }
    return 0;
}