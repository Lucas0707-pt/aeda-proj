#ifndef _PERSON_H
#define _PERSON_H
#include "../Book/Book.h"
#include "../Club/Club.h"
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
    Person();
    virtual ~Person();
    void setName(std::string name);
    std::string getName() const;
    void setId(unsigned int id);
    unsigned int getID() const;
    void setIsMember(bool isMember);
    bool getIsMember() const;
    unsigned int borrowBook(Book* book, unsigned int loanDays);
    void addBorrowedBook(Book* book);
    bool searchBorrowedBook(Book* book);
    std::vector<Book*> getBorrowedBooks() const;
    Book* getBookFromBorrowedBooks(unsigned int id) const;
    double returnBook(Club &club, Book* book);

protected:
    std::string name; /**<Person name*/
    static int id; /**<Id counter, to be increment in Person Constructor*/
    unsigned int unique_id; /**<Person ID in the club, even non members, must have at least an id to identify them */
    bool isMember; /**<Boolean containing true for member and false for non member*/
    std::vector<Book*> borrowedBooks; /**<Vector containing all the borrowed books by the person*/
};

/**
 * Derivative class from Person, this class stores exclusive proprieties that only members have
 */

class Member : public Person
{
public:
    Member();
    ~Member();
    std::vector<Book*> getOwnedBooks() const;
    void addOwnedBook(Book *book);
    bool searchOwnedBook(Book* book) const;
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
    NonMember();
    ~NonMember();
};

#endif //_PERSON_H