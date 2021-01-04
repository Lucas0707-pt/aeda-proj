#include "Person.h"
#include <ctime>
#include <cmath>
#include <algorithm>

int Person::id = 1;

Person::Person() {setId(this->id++);}

Person::~Person() = default;

void Person::setName(std::string name) {this->name = name;}

std::string Person::getName() const {return name;}

void Person::setId(unsigned int id) {this->unique_id = id;}

unsigned int Person::getID() const {return unique_id;}

void Person::updatePersonStaticId() {this->id--;}

void Person::setEmailAddress(std::string emailAddress) {this->emailAddress = emailAddress;}

std::string Person::getEmailAddress() const {return emailAddress;}

void Person::setIsMember(bool isMember) {this->isMember = isMember;}

bool Person::getIsMember() const {return isMember;}

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
        book->addToWaitingList(*this);
        return 2;
    }
}

void Person::addBorrowedBook(Book* book) {borrowedBooks.push_back(book);}

bool Person::searchBorrowedBook(Book* book)
{
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end())
        return true;
    else
        return false;
}

std::vector<Book*> Person::getBorrowedBooks() const {return borrowedBooks;}

Book* Person::getBookFromBorrowedBooks(unsigned int id) const
{
    auto it = std::find_if(borrowedBooks.begin(), borrowedBooks.end(), [&id](Book* book){return book->getBookId() == id;});
    if (it != borrowedBooks.end())
        return *it;
    else
        return nullptr;
}

double Person::returnBook(Club &club, Book* book)
{
    unsigned int delay;
    double valueToPay = 0;
    unsigned int returnTime = time(nullptr);
    if (returnTime > book->getEndOfLoan())
    {
        delay = returnTime-book->getEndOfLoan()/86400;
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

bool Person::operator<(const Person &p) const {
    if(this->isMember && !p.isMember) return false;
    if(this->isMember && p.isMember)
    {
        if (this->getOwnedBooksSize()/(this->getBorrowedBooks().size()+1) < p.getOwnedBooksSize()/(this->getBorrowedBooks().size()+1))
            return true;
    }
    return false;
}

Member::Member() : Person() {}

Member::~Member() = default;

std::vector<Book*> Member::getOwnedBooks() const { return ownedBooks; }

void Member::addOwnedBook(Book *book) {ownedBooks.push_back(book);}

bool Member::searchOwnedBook(Book *book) const
{
    auto it = std::find(ownedBooks.begin(), ownedBooks.end(), book);
    if (it != ownedBooks.end())
    {
        return true;
    }
    return false;
}

unsigned int Member::removeOwnedBook(Book *book)
{
    unsigned int bookID = book->getBookId();
    book->updateBookStaticId();
    auto it = std::find(ownedBooks.begin(), ownedBooks.end(), book);
    ownedBooks.erase(it);
    return bookID;
}

NonMember::NonMember() : Person() {}

NonMember::~ NonMember() = default;

