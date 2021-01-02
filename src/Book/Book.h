#ifndef _BOOK_H
#define _BOOK_H

#include "../Person/Person.h"
#include <iostream>
#include <vector>
#include <queue>

class Person;
class Member;

/**
 * This categories are used on Book Class to store the book's category
 */

enum Category{Adventure, Arts, Biography, Comics, Cooking, Crime, Entertainment, Health, History, Horror, Kids, Medical,
    Romance, SciFi, Science, Sports, Suspense, Other};

/**
 * Class used to store all the information from a book of the club
 */

class Book
{
public:
    Book();
    ~Book();
    void setTitle(std::string title);
    std::string getTitle() const;
    void setBookId(unsigned int bookId);
    unsigned int getBookId() const;
    void updateBookStaticId();
    void setOwner(unsigned int owner);
    unsigned int getOwner() const;
    void setCategory(unsigned int number);
    std::string getCategory() const;
    Category getCategoryNumber() const;
    void setValue(float value);
    float getValue() const;
    void setIsBorrowed(bool isBorrowed);
    bool getIsBorrowed() const;
    void setLoanRenew(bool loanRenew);
    bool getLoanRenew() const;
    void setBeginOfLoan(unsigned long long int beginOfLoan);
    unsigned long long int getBeginOfLoan() const;
    void setMaximumLoanTime(unsigned long long int maximumLoanTime);
    unsigned long long int getMaximumLoanTime() const;
    void setEndOfLoan(unsigned long long int endOfLoan);
    unsigned long long int getEndOfLoan() const;
    long long int getLoanTimeRemaining() const;
    void addRating(unsigned int rating);
    float getRating() const;
    std::vector<unsigned int> getRatings() const;
    void addComment(std::string comment);
    std::vector<std::string> getComments() const;
    void addToWaitingList(Person p);
    std::priority_queue<Person> getWaitingList() const;
    void manageQueue();
    Person getQueueFront() const;

private:
    std::string title; /**<Book title*/
    unsigned int unique_ID; /**<Book id*/
    static int id; /**<Id Counter*/
    Category category;  /**<Book category */
    unsigned int owner; /**<Id from the book owner*/
    float value; /**<Book value*/
    bool isBorrowed; /**<Boolean variable containing if the book is borrowed or not, true if yes, no otherwise*/
    bool loanRenew; /**<Boolean variable containing if the loan was already renewed by some member of the club*/
    unsigned long long int beginOfLoan=0; /**<Will be set to 0 if book is not loaned in the moment */
    unsigned long long int maximumLoanTime; /**<Max time that a book should be loaned, should be defined by the book owner*/
    unsigned long long int endOfLoan=0; /**<Will be set to 0 if book is not loaned in the moment */
    std::vector<unsigned int> ratings; /**<Vector containing all the ratings given by the readers*/
    std::vector<std::string> comments; /**<Vector containing all the comments given by the readers*/
    std::priority_queue<Person> waitingList;
};

#endif //_BOOK_H
