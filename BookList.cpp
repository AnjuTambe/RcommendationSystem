// Anjali Sambhaji Tambe
// BookList.cpp
// April 16, 2024
// Purpose: Implementation file for BookList class described in BookList.h

#include<iostream>
#include "fstream"
#include "BookList.h"

// Constructor for BookList class
BookList::BookList() {
    numberOfBooks = 0;      // initialize number of books to zero
}

// destructor for BookList class
BookList::~BookList() {
    delete[] bookList;    // deallocate all the memory taken by bookList array
}

// copy constructor
BookList::BookList(const BookList &obj) {
    // assign numberOfBooks, size and index (from obj)
    numberOfBooks = obj.numberOfBooks;
    size = obj.size;
    index = obj.index;

    // allocate memory based on new capacity
    bookList = new Book[size];

    // copy over elements (from obj)
    for (int i = 0; i < size; i++)
        bookList[i] = obj.bookList[i];
}

//add function is used to add a new book to the list
void BookList::add(string author, string title, int year) {
    if (index >= size) {
        resize();          //if it needs to resize call this resize function.
    }
    Book book;
    book.year = year;
    book.title = title;
    book.author = author;
    numberOfBooks++;
    book.isbn = numberOfBooks;
    bookList[index] = book;     // add a book to the book list array
    index++;
}

// Method to load book data from a file.
void BookList::loadData(string fileName) {
    string author;
    string title;
    string year;
    ifstream infile;
    infile.open(fileName);    // open the input file

    //read data from file line by line
    while (getline(infile, author, ',')) {
        getline(infile, title, ',');
        getline(infile, year);
        add(author, title, stoi(year));
    }
}

//Method to resize the book List array
void BookList::resize() {
    size *= 2;
    Book *tempArr = new Book[size];   // create the temporary array with the new size
    for (int i = 0; i < index; i++) {
        tempArr[i] = bookList[i];     // copy all the elements from bookList to tempArr
    }
    delete[] bookList;
    bookList = tempArr;             //Assign the new array to bookList
}

//Method to retrieve the book by its isbn
BookList::Book BookList::get(int isbn) {
    return bookList[isbn];   // return the book by its specified index
}

//Method to get total number of books in the list
int BookList::getNumberOfBooks() {
    return numberOfBooks;        // return the total number of books
}

//Method to get BookList array
BookList::Book *BookList::getBookList() {
    return bookList;           // return the bookList array
}
