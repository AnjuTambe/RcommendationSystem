//Anjali Sambhaji Tambe
//RatingList.h
//April 16, 2024
//Purpose: RatingList class used to manage the ratings of books
#include "iostream"
#include "string"

using namespace std;

class RatingList {

private:
    int **ratings;          // 2D array to store book rating
    string ratingString;
    string rating;
    int numOfMembers;
    int numOfBooks;
public:
    RatingList();
    //constructor
    //precondition: none
    //postcondition: initializes a new ratingList object with default values

    ~RatingList();
    //Destructor
    //precondition :none
    //postcondition : deallocate all the memory taken by ratings array

    RatingList(const RatingList& obj);
    //copy constructor declaration
    //precondition: none
    //postcondition:creates a new RatingList object that is a deep copy of the object 'obj'.

    void add(int isbn, int rating, int id);
    //add the ratings to the list
    // precondition: isbn, rating, id e valid
    //postcondition: the rating for the specified book and member is added to the list

    void resize(int, int);
    //resizes the rating array to accommodate more ratings
    //precondition:none
    //postcondition:the size of the ratingList array will increase after resize.

    void loadData(const string &fileName);
    // load rating data from a file into the ratingList
    // precondition:the file exits, contains the rating data
    // postcondition: rating  data from a file is loaded into the ratingList array

    int **getRatings();
    //returns the rating array
    //precondition: none
    //postcondition:the rating array is returned
};