//Anjali Sambhaji Tambe
//BookList.h
//April 16, 2024
//Purpose: BookList class used to manage a list of books

#include <iostream>
#include <string>
#include "sstream"

using namespace std;

class BookList {
private :
    int numberOfBooks;  // number of books
    int size = 55;      //Initial size of the bookList array
    int index = 1;
public:
    struct Book {
        string author;
        string title;
        int year;
        int isbn = 0;
    };

    Book *bookList = new Book[size];   // array to store books

    BookList();
    // constructor
    // precondition: none
    // postcondition: initializes a new bookList object with default values

    ~BookList();
    //Destructor
    //precondition:none
    //postcondition: deallocate all the memory taken by bookList array

    BookList(const BookList &);
    //copy constructor declaration
    //precondition:none
    //postcondition: creates a new BookList object that is a deep copy of the object 'obj'.

    void add(string author, string title, int year);
    // add a new book to the list
    // precondition: none
    // postcondition: a new book with the given author, title, year will be added to the bookList

    void resize();

    //resize the bookList array to accommodate more books
    // precondition: none
    // postcondition:the size of the bookList array will increase after resize.
    Book get(int isbn);
    //Retrieves a books from bookList by its isbn
    // precondition: isbn number exits in the list
    // postcondition: the book with the given isbn is returned

    void loadData(string fileName);
    // load book data from a file into the bookList
    // precondition:the file exits, contains the book data
    // postcondition: book  data from a file is loaded into the bookList

    int getNumberOfBooks();
    // return the total numbers of books in the list
    // precondition:none
    //postcondition: return the total number of books in the list

    Book *getBookList();
    // return the bookList array
    //precondition:none
    //postcondition: the bookList array will return

    string getBookAuthor(int);
    // return the author of the book by its index in the list
    //precondition: the index is valid
    //postcondition: the author of the book at the specified index is returned

    string getBookTitle(int);
    // return the title of the book by its index in the list
    //precondition: the index is valid
    //postcondition: the title of the book at the specified index is returned

    int getBookYear(int);
    // return the year of the book by its index in the list
    //precondition: the index is valid
    //postcondition: the year of the book at the specified index is returned

    int getBookIsbn(int);
    // return the isbn of the book by its index in the list
    //precondition: the index is valid
    //postcondition: the isbn of the book at the specified index is returned
};





