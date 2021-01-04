#ifndef _PERSON_H
#define _PERSON_H
#include "../Book/Book.h"
#include "../Club_BookStore/Club_BookStore.h"
#include <iostream>
#include <vector>

class Book;
class Club;

/**
 * Class used to store all the information from a person of the club
 */

class Person
{
public:
    /**
    * Person default constructor, will set the person ID to the current value of global ID and then increment it
    */
    Person();
    /**
    * Destructor of class Person
    */
    virtual ~Person();
    /**
    * Sets the person name
    * @param name The name of the person to be added
    */
    void setName(std::string name);
    /**
    * Returns the person name
    * @return The name of the person
    */
    std::string getName() const;
    /**
     * Sets the person id
    * @param id The id of the person
    */
    void setId(unsigned int id);
    /**
    * Returns the person id
    * @return The id of the person
    */
    unsigned int getID() const;
    /**
    * Decrement the static id from the person
    */
    void updatePersonStaticId();
    /**
    * Sets the email address from the person
    * @param emailAddress The email address
    */
    void setEmailAddress(std::string emailAddress);
    /**
    * Returns the email address from the person
     * @return the email address from the person
    */
    std::string getEmailAddress() const;
    /**
    * Sets if a person is a member or not from the lecture club
    * @param isMember Boolean containing true for members, and false for non-members
    */
    void setIsMember(bool isMember);
    /**
    * Returns a boolean for if the person is a member or not from the lecture club
    * @return True for members and false for non-members
    */
    bool getIsMember() const;
    /**
     * Checks if a book is available to be borrowed
     * if yes, this function will also check if the loan days asked are smaller than the predefined, by book owner, maximum loan time,
     * the book's "isBorrowed", "beginOfLoan" and "endOfLoan" variables, are set to the correct values,
     * if not, function will add the person to the queue of members or non members, depending on her status
     * @param book The book that the person wants to borrow
     * @param loanDays The amount of the days that the person want's to borrow the book
     * @return Can return 3 different unsigned int values, 0 for sucess, 1 for loan days exceed maximum allowed and
     * 2 for person added to the waiting List
     */
    unsigned int borrowBook(Book* book, unsigned int loanDays);
    /**
    * Adds a book to the person borrowed books
    * @param book The book that will be added to the borrowed books
    */
    void addBorrowedBook(Book* book);
    /**
    * Searh the book on the person's borrowed books
    * @param book The book that will be searched
    * @return True if the book was found, false otherwise
    */
    bool searchBorrowedBook(Book* book);
    /**
    * Returns a vector containing all borrowed books from one person
    * @return Vector containing all the pointers for the member's borrowed books
    */
    std::vector<Book*> getBorrowedBooks() const;
    /**
    * Will search on the person's borrowed books if a book with specified id exists
    * @param id Person's ID
    * @return Pointer to the book if the book was found, nullptr otherwise
    */
    Book* getBookFromBorrowedBooks(unsigned int id) const;
    /**
     * Will check if the book was returned in time, if that isn't the case this function will also calculate the value to be payed,
     * than will remove the book from person's borrowed books
     * @param club Reference to the club
     * @param book The book that will be returned
     * @return 0 if the person as nothing to pay, value to pay otherwise (will be the double for non-members)
     */
    double returnBook(Club &club, Book* book);
    void setOwnedBooksSize(unsigned int size){ownedBooksSize = size;}
    unsigned int getOwnedBooksSize() const {return ownedBooksSize;}
    /**
     * Operator to help choosing the priority in the priority_queue
     */
    bool operator<(const Person& p) const ;

protected:
    std::string name; /**<Person name*/
    static int id; /**<Id counter, to be increment in Person Constructor*/
    unsigned int unique_id; /**<Person ID in the club, even non members, must have at least an id to identify them */
    std::string emailAddress;
    bool isMember; /**<Boolean containing true for member and false for non member*/
    std::vector<Book*> borrowedBooks; /**<Vector containing all the borrowed books by the person*/
    unsigned int ownedBooksSize;
};

/**
 * Derivative class from Person, this class stores exclusive proprieties that only members have
 */

class Member : public Person
{
public:
    /**
    * Default constructor of Member class
    */
    Member();
    /**
     * Destructor of MemberClass
     */
    ~Member();
    /**
     * Returns a vector of pointers to the member's owned books
     * @return Vector containing all the pointers to the member's owned books
     */
    std::vector<Book*> getOwnedBooks() const;
    /**
     * Will add to the member's owned books the book specified
     * @param book The book to be added to member's owned books
     */
    void addOwnedBook(Book *book);
    /**
     * Will search the book specified in the member's owned books
     * @param book The book to be search on the member's owned books
     * @return True if the book was found, false otherwise
     */
    bool searchOwnedBook(Book* book) const;
    /**
     * Will remove from the member's owned books the book specified
     * @param book The book to be removed from the member's owned books
     * @return The Id from the book removed
     */
    unsigned int removeOwnedBook(Book *book);
private:
    std::vector<Book*> ownedBooks; /**<Vector containing all the borrowed books by the member*/
};

/**
 * Derivative class from Person, this class is used to differ from the class Member
 */
class NonMember : public Person
{
public:
    /**
     * Default constructor of NonMember class
     */
    NonMember();
    /**
     * Destructor of NonMember class
     */
    ~NonMember();
};

#endif //_PERSON_H