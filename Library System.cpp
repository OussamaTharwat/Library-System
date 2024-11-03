#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct User {
    int user_id;
    string user_name;

    User() {
        user_id = 0;
        user_name = "";
    }
    void read() {
        cout << "Enter user name, id: ";
        cin >> user_name >> user_id;
    }
    int books_borrowed = 0;
    int books[100];
};

struct Book {
    int book_id;
    string book_title;
    int book_quantity;

    Book() {
        book_id = 0;
        book_title = "";
        book_quantity = 0;
    }
    void read() {
        cout << "Enter Book id, title, quantity" << endl;
        cin >> book_id >> book_title >> book_quantity;
    }
    int borrowers_count = 0;
    User Borrowers[100];
};

Book books[100];
User users[100];
int book_idx = 0, user_idx = 0;

void print_users() {
    for (int i = 0; i < user_idx; i++) {
        cout << users[i].user_name << ' ' << users[i].user_id << ' ';
        for (int j = 0; j < users[i].books_borrowed; j++) cout << users[i].books[j] << ' ';
        cout << endl;
    }
}

void user_returns_book() {
    cout << "Enter user name: " << endl;
    string user_title; cin >> user_title;
    cout << "Enter book name: " << endl;
    string book_title; cin >> book_title;

    int book = 0;
    int user = 0;
    for (int i = 0; i < book_idx; i++) {
        if (books[i].book_title == book_title) {
            book = i;
        }
    }
    for (int i = 0; i < user_idx; i++) {
        if (users[i].user_name == user_title) {
            user = i;
        }
    }
    books[book].book_quantity++;
    books[book].borrowers_count--;

    for (int i = 0; i < users[user].books_borrowed; i++) {
        if (users[user].books[i] == books[book].book_id) {
            for (int j = i; j < users[user].books_borrowed; j++) {
                for (int k = j + 1; k < users[user].books_borrowed; k++) {
                    swap(users[user].books[j], users[user].books[k]);
                }
            }
        }
    }
    users[user].books_borrowed--;

}
void user_borrow_book() {
    cout << "Enter user name: ";
    string user_title; cin >> user_title;
    cout << "enter book name: ";
    string book_title; cin >> book_title;
    int book = 0;
    int user = 0;
    for (int i = 0; i < book_idx; i++) {
        if (books[i].book_title == book_title) {
            book = i;
        }
    }
    for (int i = 0; i < user_idx; i++) {
        if (users[i].user_name == user_title) {
            user = i;
        }
    }
    if (books[book].book_quantity) {
        books[book].book_quantity--;
        books[book].Borrowers[books[book].borrowers_count]=users[user];
        books[book].borrowers_count++;

        users[user].books[users[user].books_borrowed]=books[book].book_id;
        users[user].books_borrowed++;
    }
    else {
        cout << "No Available books" << endl;
    }
}

void add_user() {
    users[user_idx] = User();
    users[user_idx].read();
    user_idx++;
}
void print_library_by_name() {
    for (int i = 0; i < book_idx; i++) {
        for (int j = i+1; j < book_idx; j++) {
            if (books[i].book_title > books[j].book_title) swap(books[i], books[j]);
        }
    }
    for (int i = 0; i < book_idx; i++)
        cout << books[i].book_id << ' ' << books[i].book_title << endl;

}

void print_library_by_id() {
    for (int i = 0; i < book_idx; i++) {
        for (int j = i+1; j < book_idx; j++) {
            if (books[i].book_id > books[j].book_id) swap(books[i], books[j]);
        }
    }
    for (int i = 0; i < book_idx; i++)
        cout << books[i].book_id << ' ' << books[i].book_title<< ' ' << books[i].book_quantity << ' ' << books[i].borrowers_count << endl;

}
void who_borrowed_book_by_name() {
    cout << "Please Enter Name: ";
    string book_name; cin >> book_name;
    bool flag = false;
    for (int i = 0; i < book_idx; i++) {
        if (books[i].book_title == book_name) {
            for (int j = 0; j < books[i].borrowers_count; j++) {
                flag = true;
                cout << books[i].Borrowers[j].user_name;
            }
        }
    }
    if (flag == true) cout << "No borrowers" << endl;
}
void search_books_by_prefix() {
    cout << "Enter book prefix: ";
    string prefix; cin >> prefix;
    bool flag = false;
    for (int i = 0; i < book_idx; i++) {
        if(books[i].book_title.substr(0,prefix.size()) == prefix) {
            cout << books[i].book_title << endl;
            flag = true;
        }
    }
    if (flag == true) cout << "Not found" << endl;
}
void add_book() {
    books[book_idx] = Book();
    books[book_idx].read();
    book_idx++;
}
void menu() {
    while (true){
        cout << "Enter Your Choice: " << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search Books By prefix" << endl;
        cout << "3. Print Who Borrowed Book By Name" << endl;
        cout << "4. Print Library by ID" << endl;
        cout << "5. Print Library by Name" << endl;
        cout << "6. Add User" << endl;
        cout << "7. User Borrow Book" << endl;
        cout << "8. User Return Book" << endl;
        cout << "9. Print Users" << endl;
        cout << "10. Exit" << endl;

        int choice; cin >> choice;
        if (choice == 1) add_book();
        else if (choice == 2) search_books_by_prefix();
        else if (choice == 3) who_borrowed_book_by_name();
        else if (choice == 4) print_library_by_id();
        else if (choice == 5) print_library_by_name();
        else if (choice == 6) add_user();
        else if (choice == 7) user_borrow_book();
        else if (choice == 8) user_returns_book();
        else if (choice == 9) print_users();
        else if (choice == 10) break;
        else cout << "Invalid Choice" << endl;
    }
}
int main() {
    menu();
}
