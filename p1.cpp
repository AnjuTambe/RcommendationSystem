// AUTHOR: Anjali Tambe
// PROGRAM: p1.cpp
// DATE: April 16, 2024
// PURPOSE: Build recommendation system in which users are able to add member, add book and rate book. Based on the rating,
// our program recommends which book they might like.
// INPUT: files
// PROCESS: BookList.h is header file for BookList.cpp. This class are responsible for storing the books from file or user input.
// MemberList.h is header file for MemberList.cpp which stores members. RatingList.h is header file for RatingList.cpp which
// contains user ratings for books
// OUTPUT: Program displays various output like recommended books, which book they added, what book they rated.

#include <iostream>
#include "MemberList.h"
#include "BookList.h"
#include "RatingList.h"

using namespace std;

class Login {
public:
    int account;

    void login(int acc, MemberList *memberList) {
        account = acc;
        string memberName = memberList->get(acc);
        cout << memberName + ", you are logged in! \n";
    }

    void logout() {
        account = 0;
    }
};

void recommendBook(int, int **, BookList *, MemberList *);
// Recommends books to the member based on ratings from other members
// IN: member id - the ID of the member for whom recommendations are generated
//     ratings - a 2D array representing ratings of books by members
//     books - pointer to the BookList object containing book information
//     members - pointer to the MemberList object containing member information
// MODIFY: None
// OUT: None

void loggedOutUserMenu(MemberList *, BookList *, RatingList *);
// This function displays the menu options for a logged-out user and handles the user interactions
// IN: memberList - pointer to the MemberList object containing member information
//     bookList - pointer to the BookList object containing book information
//     ratingList - pointer to the RatingList object containing rating information
// MODIFY: None
// OUT: None

void addMember(MemberList *);
// This function adds a new member to the system
// IN: memberList - pointer to the MemberList object
// MODIFY: Updates the memberList object with the new member information
// OUT: None

void addBook(BookList *);
// This function adds a new book to the system
// IN: bookList - pointer to the BookList object
// MODIFY: Updates the bookList object with the new book information
// OUT: None

void addRating(BookList *, RatingList *, Login);
// This function adds a rating for a book given by a specific member
// IN: bookList - pointer to the BookList object containing book information
//     ratingList - pointer to the RatingList object containing rating information
//     login - the Login object representing the currently logged-in user
// MODIFY: Updates the ratingList object with the new rating information
// OUT: None

void viewRatings(RatingList *, BookList *, MemberList *, int);
// This function displays ratings for a specific member
// IN: ratingList - pointer to the RatingList object containing rating information
//     bookList - pointer to the BookList object containing book information
//     memberList - pointer to the MemberList object containing member information
//     id - the ID of the member whose ratings are to be displayed
// MODIFY: None
// OUT: None

void loggedInUserMenu(Login, MemberList *, BookList *, RatingList *);
// This function displays the menu options for a logged-in user and handles user interactions
// IN: login - the Login object representing the currently logged-in user
//     memberList - pointer to the MemberList object containing member information
//     bookList - pointer to the BookList object containing book information
//     ratingList - pointer to the RatingList object containing rating information
// MODIFY: None
// OUT: None

int main() {
    MemberList *members = new MemberList();
    BookList *books = new BookList();
    RatingList *ratings = new RatingList();

    cout << "\nWelcome to the Book Recommendation Program.";
    cout << "\nThis application allows you to get new recommendations"
            "\nbased on historical ratings. Also, you can"
            "\nrate a book, add new books and view your all previous ratings.\n";

    cout << "\nEnter books file: ";
    string bookFileName;
    cin >> bookFileName;
    books->loadData(bookFileName);

    cout << "Enter rating file: ";
    string ratingFileName;
    cin >> ratingFileName;
    ratings->loadData(ratingFileName);
    members->loadData(ratingFileName);

    cout << "\n# of books: " << books->getNumberOfBooks() << endl;
    cout << "# of memberList: " << members->getTotalMembers() << endl;

    loggedOutUserMenu(members, books, ratings);
    return 0;
}

void recommendBook(int memberId, int **ratings, BookList *books, MemberList *members) {
    int maxSimilarMember = -1;     // Save max similar member index
    int maxSimilarityScore = 0;    // Max similarity score
    int *loggedMemberRating = ratings[memberId];
    int i = 0;
    while (i < members->getTotalMembers()) {
        int similarityScore = 0;
        if (i == memberId) {
            i++;
            continue;
        }
        for (int j = 0; j <= books->getNumberOfBooks(); j++) {
            if (loggedMemberRating[j] == 0 || ratings[i][j] == 0) { // Filter out non-rated books
                continue;
            }
            similarityScore = similarityScore + loggedMemberRating[j] * ratings[i][j];
        }
        if (maxSimilarityScore < similarityScore) {
            maxSimilarityScore = similarityScore;
            maxSimilarMember = i;
        }
        i++;
    }

    cout << "\nYou have similar taste in books as " + members->get(maxSimilarMember) + "!";

    if (maxSimilarMember == -1) {
        cout << "No recommendations found!!!!";
        return;
    }

    int *reallyLikedBooks = new int[10];
    int *likedBooks = new int[15];
    int numReallyLikedBook = 0;
    int numLikedBooks = 0;
    for (int isbn = 0; isbn < books->getNumberOfBooks(); isbn++) {
        //Filter out read book by logged member and most similar member
        if (ratings[memberId][isbn] == 0 && ratings[maxSimilarMember][isbn] != 0) {
            if (ratings[maxSimilarMember][isbn] == 5) {
                reallyLikedBooks[numReallyLikedBook] = isbn;
                numReallyLikedBook++;
            } else if (ratings[maxSimilarMember][isbn] == 3) {
                likedBooks[numLikedBooks] = isbn;
                numLikedBooks++;
            }
        }
    }

    cout << "\n\nHere are the books they really liked: \n";
    for (int k = 0; k < numReallyLikedBook; k++) {
        int id = reallyLikedBooks[k];
        BookList::Book book = books->get(id);
        cout << to_string(book.isbn) + ", " + book.author + ", " + book.title + ", " + to_string(book.year) << endl;
    }

    cout << "\nAnd here are the books they liked: \n";
    for (int l = 0; l < numLikedBooks; l++) {
        int id = likedBooks[l];
        BookList::Book book = books->get(id);
        cout << to_string(book.isbn) + ", " + book.author + ", " + book.title + ", " + to_string(book.year) << endl;
    }
}

void addMember(MemberList *memberList) {
    string name;
    cout << "\nEnter the name of the new member: ";
    cin >> name;
    memberList->add(name);
    cout << name + " (account #:" + to_string(memberList->getTotalMembers()) + ") was added";
}

void addBook(BookList *booklist) {
    string name;
    int year;
    cout << "\nEnter the author of the new book: ";
    cin.ignore();
    getline(cin, name);

    char s[100];
    cout << "\nEnter the title of the new book: ";
    cin.ignore();
    cin.getline(s, 100);

    cout << "\nEnter the year (or range of years) of the new book: ";
    cin >> year;

    booklist->add(name, s, year);
    cout << booklist->getNumberOfBooks() << ", " << name + ", " + s + ", " + to_string(year) + " was added";
}

void addRating(BookList *bookList, RatingList *ratinglist, Login login) {
    int isbn;
    cout << "\nEnter the ISBN for the book you'd like to rate: ";
    cin >> isbn;
    BookList::Book book = bookList->get(isbn);
    int currentRating = ratinglist->getRatings()[login.account][isbn];
    int rating;
    if (currentRating != 0) {
        cout << "\nYour current rating for " + to_string(isbn) + " " + book.author + ", " + book.title + ", " +
                to_string(book.year) + " => rating: " + to_string(currentRating);

        string option;
        cout << "\nWould you like to re-rate this book (y/n)? ";
        cin >> option;
        if (option == "y") {
            cout << "\nEnter your rating: ";
            cin >> rating;

            ratinglist->add(isbn, login.account, rating);

            int newRating = ratinglist->getRatings()[login.account][isbn];

            cout << "Your new rating for " + to_string(isbn) + ", " + book.author + ", " + book.title + ", " +
                    to_string(book.year) + " => rating: " + to_string(newRating);
        }
    } else {
        cout << "\nEnter your rating: ";
        cin >> rating;
        ratinglist->add(isbn, login.account, rating);
        int newRating = ratinglist->getRatings()[login.account][isbn];
        cout << "Your new rating for " + to_string(isbn) + ", " + book.author + ", " + book.title + ", " +
                to_string(book.year) + " => rating: " + to_string(newRating);
    }
}

void viewRatings(RatingList *ratinglist, BookList *booklist, MemberList *memberlist, int id) {
    cout << memberlist->get(id) << "'s ratings..." << endl;
    for (int i = 1; i <= booklist->getNumberOfBooks(); i++) {
        int rating = ratinglist->getRatings()[id][i];
        BookList::Book book = booklist->get(i);
        cout << to_string(book.isbn) + ", " + book.author + ", " + book.title + ", " + to_string(book.year) +
                " => ratings: " +
                to_string(rating) << endl;
    }
}

void loggedInUserMenu(Login login, MemberList* memberList, BookList *booklist, RatingList *ratinglist) {
    cout << "\n************** MENU **************\n"
            "* 1. Add a new member            *\n"
            "* 2. Add a new book              *\n"
            "* 3. Rate book                   *\n"
            "* 4. View ratings                *\n"
            "* 5. See recommendations         *\n"
            "* 6. Logout                      *\n"
            "**********************************\n\n";

    cout << "Enter a menu option: ";
    int option;
    cin >> option;

    switch (option) {
        case 1:
            addMember(memberList);
            loggedInUserMenu(login, memberList, booklist, ratinglist);
            break;
        case 2:
            addBook(booklist);
            loggedInUserMenu(login, memberList, booklist, ratinglist);
            break;
        case 3:
            addRating(booklist, ratinglist, login);
            loggedInUserMenu(login, memberList, booklist, ratinglist);
            break;
        case 4:
            viewRatings(ratinglist, booklist, memberList, login.account);
            loggedInUserMenu(login, memberList, booklist, ratinglist);
            break;
        case 5:
            recommendBook(login.account, ratinglist->getRatings(), booklist, memberList);
            loggedInUserMenu(login, memberList, booklist, ratinglist);
            break;
        case 6:
            login.logout();
            loggedOutUserMenu(memberList, booklist, ratinglist);
            break;
    }
}

void loggedOutUserMenu(MemberList *memberList, BookList *booklist, RatingList *ratinglist) {
    cout << "\n************** MENU ************\n"
            "* 1. Add a new member            *\n"
            "* 2. Add a new book              *\n"
            "* 3. Login                       *\n"
            "* 4. Quit                        *\n"
            "**********************************\n\n";

    cout << "Enter a menu option: ";

    int option;
    cin >> option;
    Login login;
    switch (option) {
        case 1:
            //Add member
            addMember(memberList);
            loggedOutUserMenu(memberList, booklist, ratinglist);
            break;
        case 2:
            //Add book
            addBook(booklist);
            loggedOutUserMenu(memberList, booklist, ratinglist);
            break;
        case 3:
            //Login
            int account;
            cout << "Enter member account: ";
            cin >> account;
            login.login(account, memberList);
            loggedInUserMenu(login, memberList, booklist, ratinglist);
            break;
        case 4:
            cout << "Thank you for using the Book Recommendation Program!" << endl;
            break;
    }
}
