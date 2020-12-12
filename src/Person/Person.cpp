#include "Person.h"
#include <ctime>
#include <cmath>
#include <algorithm>

int Person::id = 1;

/**
 * Person default constructor, will set the person ID to the current value of global ID and then increment it
 */

Person::Person() {setId(this->id++);}

/**
 * Destructor of class Person
 */

Person::~Person() = default;

/**
 * Sets the person name
 * @param name The name of the person to be added
 */

void Person::setName(std::string name) {this->name = name;}

/**
 * Returns the person name
 * @return The name of the person
 */

std::string Person::getName() const {return name;}

/**
 * Sets the person id
 * @param id The id of the person
 */

void Person::setId(unsigned int id) {this->unique_id = id;}

/**
 * Returns the person id
 * @return The id of the person
 */

unsigned int Person::getID() const {return unique_id;}

/**
 * Sets if a person is a member or not from the lecture club
 * @param isMember Boolean containing true for members, and false for non-members
 */

void Person::setIsMember(bool isMember) {this->isMember = isMember;}

/**
 * Returns a boolean for if the person is a member or not from the lecture club
 * @return True for members and false for non-members
 */

bool Person::getIsMember() const {return isMember;}

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

unsigned int Person::borrowBook(Book* book, unsigned int loanDays)
{
    if (!book->getIsBorrowed())
    {
        if (loanDays*86400 <= book->getMaximumLoanTime())
        {
            book->setIsBorrowed(true);
            book->setBeginOfLoan(time(nullptr));
            book->setEndOfLoan(time(nullptr) + loanDays * 86400);
            this->borrowedBooks.push_back(book);
            return 0;
        }
        else {return 1;}
    }
    else
    {
        if (this->getIsMember()) {
            book->addToWaitingListM(this->unique_id);
        }
        else {
            book->addToWaitingListNM(this->unique_id);
        }
        return 2;
    }
}

/**
 * Adds a book to the person borrowed books
 * @param book The book that will be added to the borrowed books
 */

void Person::addBorrowedBook(Book* book) {borrowedBooks.push_back(book);}

/**
 * Searh the book on the person's borrowed books
 * @param book The book that will be searched
 * @return True if the book was found, false otherwise
 */

bool Person::searchBorrowedBook(Book* book)
{
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end())
    {
        return true;
    }
    return false;
}

/**
 *  Returns a vector containing all borrowed books from one person
 * @return Vector containing all the pointers for the member's borrowed books
 */

std::vector<Book*> Person::getBorrowedBooks() const {return borrowedBooks;}

/**
 *  Will search on the person's borrowed books if a book with specified id exists
 * @param id Person's ID
 * @return Pointer to the book if the book was found, nullptr otherwise
 */

Book* Person::getBookFromBorrowedBooks(unsigned int id) const
{
    auto it = std::find_if(borrowedBooks.begin(), borrowedBooks.end(), [&id](Book* book){return book->getBookId() == id;});
    if (it != borrowedBooks.end())
        return *it;
    else
        return nullptr;
}

/**
 * Will check if the book was returned in time, if that isn't the case this function will also calculate the value to be payed,
 * than will remove the book from person's borrowed books
 * @param club Reference to the club
 * @param book The book that will be returned
 * @return 0 if the person as nothing to pay, value to pay otherwise (will be the double for non-members)
 */

double Person::returnBook(Club &club, Book* book)
{
    int delay;
    double valueToPay = 0;
    int returnTime = time(nullptr);
    if (returnTime > book->getEndOfLoan())
    {
        delay = floor((returnTime-book->getEndOfLoan())/86400);
        valueToPay = (book->getValue()*club.getDelayPenalty()*delay);

    }
    book->setBeginOfLoan(0);
    book->setEndOfLoan(0);
    book->setIsBorrowed(false);
    book->setLoanRenew(false);
    borrowedBooks.erase(std::find(borrowedBooks.begin(),borrowedBooks.end(),book));
    if(this->isMember) {return valueToPay;}
    else {return 2*valueToPay;}
}

/**
 * Default constructor of Member class
 */

Member::Member() : Person() {}

/**
 * Destructor of MemberClass
 */
Member::~Member() = default;

/**
 * Returns a vector of pointers to the member's owned books
 * @return Vector containing all the pointers to the member's owned books
 */

std::vector<Book*> Member::getOwnedBooks() const { return ownedBooks; }

/**
 * Will add to the member's owned books the book specified
 * @param book The book to be added to member's owned books
 */

void Member::addOwnedBook(Book *book) {ownedBooks.push_back(book);}

/**
 * Will search the book specified in the member's owned books
 * @param book The book to be search on the member's owned books
 * @return True if the book was found, false otherwise
 */

bool Member::searchOwnedBook(Book *book) const
{
    auto it = std::find(ownedBooks.begin(), ownedBooks.end(), book);
    if (it != ownedBooks.end())
    {
        return true;
    }
    return false;
}

/**
 * Will remove from the member's owned books the book specified
 * @param book The book to be removed from the member's owned books
 */

unsigned int Member::removeOwnedBook(Book *book)
{
    unsigned int bookID = book->getBookId();
    book->updateBookStaticId();
    auto it = std::find(ownedBooks.begin(), ownedBooks.end(), book);
    ownedBooks.erase(it);
    return bookID;
}

/**
 * Default constructor of NonMember class
 */

NonMember::NonMember() : Person() {}

/**
 * Destructor of NonMember class
 */

NonMember::~ NonMember() = default;

