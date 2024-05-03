// Anjali Sambhaji Tambe
// MemberList.cpp
// April 16, 2024
// Purpose: Implementation file for MemberList class described in MemberList.h
#include "MemberList.h"
#include "fstream"
#include <limits>

using namespace std;

//Constructor for memberList class
MemberList::MemberList() {
    numMembers = 0;      // initialize the number of member to zero
}

//Destructor for memberList class
MemberList::~MemberList() {
    delete[] members;    // deallocate all the memory taken by members array
}

// copy constructor
MemberList::MemberList(const MemberList &obj) {
    // assign numMembers and index from obj
    numMembers = obj.numMembers;
    initialNumMembers = obj.initialNumMembers;
    index = obj.index;

    // allocate memory based on new capacity
    members = new Member[initialNumMembers];

    // copy over elements (from obj)
    for (int i = 0; i < numMembers; i++) {
        members[i] = obj.members[i];
    }
}

//Method to add a new member to the list
void MemberList::add(string name) {
    if (index >= initialNumMembers) {
        resize();              //if it needs to resize call this resize function.
    }
    myMember.name = name;      //set the name of the new member
    numMembers++;              //increment the number of members
    members[index] = myMember; // add the member to member array
    index++;                   //increment the index
}

//Method to resize the member list
void MemberList::resize() {
    initialNumMembers *= 2;           // double the size of the array
    Member *tempArr = new Member[initialNumMembers];   // create a temporary array with the new size
    for (int i = 0; i < index; i++) {
        tempArr[i] = members[i];         // copy element from the old array to temp array
    }
    delete[] members;               // delete the old array
    members = tempArr;             // assign the temp array to members
}

//Method to get the total number of members in the list
int MemberList::getTotalMembers() const {
    return numMembers;     // return the total number of members
}

//Method to get the name of the member by their account id
string MemberList::get(int account) {
    return members[account].name;       // return the name of the member at the specified index
}

//Method to load the members data from a file
void MemberList::loadData(const string &fileName) {
    ifstream infile;
    infile.open(fileName);                 // open the inout file here
    string memberName;
    while (getline(infile, memberName)) {    // read data from the file line by line
        infile.ignore(numeric_limits<std::streamsize>::max(), '\n');    // ignore remaining characters int the line
        add(memberName);   // add the member to the list
    }
}
