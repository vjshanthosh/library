#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void add_user (map<int, pair<string, string> >& users, map<int, vector<string> >& user_book) {
    int id;
    string name, pass;
    cout << "Enter ID (natural number): ";
    cin >> id;
    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;
    users[id] = {name, pass};
    user_book[id] = {};
}

void remove_user(map<int, pair<string, string> >& users, map<int, vector<string> >& user_book) {
    int id;
    cout << "User ID to remove: ";
    cin >> id;
    if (users.count(id)) {
        users.erase(id);
        user_book.erase(id);
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

void login(int& current, map<int, pair<string, string> > users) {
    int id;
    string pass;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter password: ";
    cin >> pass;
    if (users.count(id) && users[id].second == pass) {
        current = id;
        cout << "Login successful!\n";
    } else {
        cout << "Invalid login.\n";
    }
}

void get_book (int current, map<int, vector<string> >& user_book, map<string, int>& books) {
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

void see_users (map<int, pair<string, string> > users) {
    for (auto it : users) {
        cout << it.second.first << endl;
    }
}

void user_info (map<int, pair<string, string> > users, map<int, vector<string> > user_book) {
    for (auto user : users) {
        cout << "ID: "  << user.first << "\nUsername: " << user.second.first << "\nPassword: " << user.second.second << "\nBooks:\n";
        for (auto book : user_book[user.first]) {
            cout << book << "\n";
        }
        cout << endl;
    }
}

void set_default (map<int, pair<string, string> >& users, map<string, int>& books, map<int, vector<string> >& user_book) {
    users[1] = {"John", "John#25"};
    users[2] = {"Sam", "Sam&42"};
    users[3] = {"George", "George$77"};
    books["Magic"] = 10;
    books["Harry Potter"] = 10;
    books["Quantum Physics"] = 10;
    books["C++"] = 10;
    user_book[1] = {"Magic", "Harry Potter"};
    user_book[2] = {};
    user_book[3] = {"Quantum Physics", "C++"};
}

void return_book (int current, map<int, vector<string> >& user_book, map<string, int>& books) {
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
    map<int, pair<string, string> > users;
    users[0] = {0, "Admin@123"};
    map<string, int> books;
    map<int, vector<string> > user_book;
    set_default(users, books, user_book);
    int current = -1;
    while (true) {
        if (current == -1) {
            string input;
            cout << "Type l to login or q to quit: ";
            cin >> input;
            if (input == "l") {
                login(current, users);
            } else if (input == "q") {
                break;
            }
        } else if (current == 0) {
            string input;
            cout << "Type ab to add book\n rb to remove book\n au to add user\n ru to remove user\n sb to see books\n su to see users\n ui to see user info\n l to logout\n or q to quit: ";
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
                see_users(users);
            } else if (input == "ui") {
                user_info(users, user_book);
            } else if (input == "l") {
                current = -1;
            } else if (input == "q") {
                break;
            }
        } else {
            string input;
            cout << "Type g to get book\n r to return book\n s to see books\n l to logout\n or q to quit: ";
            cin >> input;
            if (input == "g") {
                get_book(current, user_book, books);
            } else if (input == "r") {
                return_book(current, user_book, books);
            } else if (input == "s") {
                see_books(books);
            } else if (input == "l") {
                current = -1;
            } else if (input == "q") {
                break;
            }
        }
        cout << endl;
    }
    return 0;
}