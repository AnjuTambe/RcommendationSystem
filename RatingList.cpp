// Anjali Sambhaji Tambe
// RatingList.cpp
// April 16, 2024
// Purpose: Implementation file for ratingList class described in ratingList.h
#include"RatingList.h"
#include "MemberList.h"
#include "BookList.h"
#include "fstream"

using namespace std;

//Constructor for ratingList class
RatingList::RatingList() {
    numOfMembers = 100;    // number of members
    numOfBooks = 100;      // number of books
    ratings = new int *[numOfMembers];          // allocate memory for the 2D array of ratings
    for (int i = 0; i < numOfMembers; i++) {
        ratings[i] = new int[numOfBooks];        // allocate memory for each row of the 2D array
    }
}

// destructor for ratingList class
RatingList::~RatingList() {
    for (int i = 0; i < numOfMembers; i++) {
        delete[] ratings[i];
    }
    delete[] ratings;    // deallocate all the memory taken by ratings array
}

//copy constructor declaration
RatingList::RatingList(const RatingList &obj) {
    //Copy the number of members from the original object
    numOfMembers = obj.numOfMembers;
    //Allocate memory for the ratings array
    ratings = new int *[numOfMembers];
    for (int i = 0; i < numOfMembers; i++) {
        if (obj.ratings[i] != nullptr) {
            ratings[i] = new int[obj.ratings[i][0] + 1];
            //copy the numbers of rating for the current numbers
            ratings[i][0] = obj.ratings[i][0];

            //iterate over each individual rating for the current member
            for (int j = 1; j < obj.ratings[i][0]; j++) {
                ratings[i][j] = obj.ratings[i][j];
            }
        } else {
            ratings[i] = nullptr;
        }
    }
}

// Method to add rating for a book by a member
void RatingList::add(int isbn, int loggedInUserId, int rating) {
    // Resize if there are more books rating than capacity
    if (isbn > numOfBooks) {
        resize(numOfMembers, 2 * numOfBooks);
    }
    // Resize
    if (loggedInUserId > numOfMembers) {
        resize(2 * numOfMembers, numOfBooks);
    }
    ratings[loggedInUserId][isbn] = rating;     // assign the rating to the specified book and member
}

// Method to load the rating data from a file
void RatingList::loadData(const string &fileName) {
    ifstream infile;
    infile.open(fileName);    // open the input file

    int i = 1;
    int j = 1;
    string name;
    string memberRating;
    while (getline(infile, name)) {        // read the data from a file line by line
        getline(infile, name);
        stringstream ratingStream(name);
        while (ratingStream >> memberRating) {
            ratings[i][j] = stoi(memberRating);  // convert member rating to integer and assign o array
            j++;     // move to next column
        }
        j = 1;     // reset column index
        i++;       // move to the next row
    }
}

//Method to get ratings array
int **RatingList::getRatings() {
    return ratings;           // return the 2D array of ratings
}

void RatingList::resize(int newNumMembers, int newNumOfBooks) {
    // Allocate the new ratings array with the new size
    int **newRatings = new int *[newNumMembers];

    for (int i = 0; i < numOfBooks; i++) {
        newRatings[i] = ratings[i];  //copy the existing ratings with the new array
    }
    delete[] ratings;  // delete the old ratings

    numOfMembers = newNumMembers; // update the numOfMember variable
    numOfBooks = newNumOfBooks;    //  update numOfBook
    ratings = newRatings;     // assign the new ratings array to member variable
}