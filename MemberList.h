//Anjali Sambhaji Tambe
//MemberList.h
//April 16, 2024
//Purpose: MemberList class used to manage a list of members

#include "string"

using namespace std;

class MemberList {
private:
    int numMembers = 1;             //number of member in the list
    int initialNumMembers = 55;     // initialize capacity of memberList
    int index = 1;
    struct Member {
        string name;
    } myMember;
    Member *members = new Member[initialNumMembers];     // array to store the members
public:
    MemberList();
    //constructor
    //precondition: none
    //postcondition: initializes a new memberList object with default values

    ~MemberList();
    //Destructor
    //precondition:none
    //postcondition: deallocate all the memory taken by members array

    MemberList(const MemberList& obj);
    //copy constructor declaration
    //precondition: none
    //postcondition:creates a new MemberList object that is a deep copy of the object 'obj'.

    void add(string name);
    // add a new member in the list
    // precondition: none
    // postcondition: a new member with the given name is added to the list

    string get(int index);
    //Returns the name of a  member by their index in the list
    // precondition: the index is valid
    // postcondition: the name of a member at the specified index will return.

    int getTotalMembers() const;
    // return the total numbers of member in the list
    // precondition:none
    //postcondition: return the total number of member in the list

    void resize();
    //resizes the member array to accommodate more members
    //precondition:none
    // postcondition:the size of the memberList array will increase after resize.

    void loadData(const string& fileName);
    // loads member data from a file into the member array
    // precondition:the file exits, contains the member data
    // postcondition: member  data from a file is loaded into the member array
};