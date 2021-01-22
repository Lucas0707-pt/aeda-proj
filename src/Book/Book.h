#ifndef _BOOK_H
#define _BOOK_H

#include "../Person/Person.h"
#include <iostream>
#include <vector>
#include <queue>

class Person;
class Member;

/**
 * This enumeration hols the categories that are used on Book Class to store the book's category
 */

enum Category{Adventure, Arts, Biography, Comics, Cooking, Crime, Entertainment, Health, History, Horror, Kids, Medical,
    Romance, SciFi, Science, Sports, Suspense, Other};

/**
 * Class used to store all the information from a book of the club
 */

class Book
{
public:
    /**
     * Book default constructor, that will set the book ID based on a counter id initialized in the beginning as 1, and then increment it
     */
    Book();
    /**
     * Destructor of class Book
     */
    ~Book();
    /**
     * Sets the book's title to the specified one
     * @param title The book's title
     */
    void setTitle(std::string title);
    /**
     * Returns the book's name
     * @return The book's name
     */
    std::string getTitle() const;
    /**
     * Sets the book's ID to the specified one
     * @param bookId The book's ID
     */
    void setBookId(unsigned int bookId);
    /**
     * Decrement the static id from the book, will be used when a book was removed
     */
    void updateBookStaticId();
    /**
      * Returns the book's ID
      * @return The book's ID
      */
    unsigned int getBookId() const;
    /**
     * Sets the owner ID to the specified one
     * @param owner The ID of the book's owner
     */
    void setOwner(unsigned int owner);
    /**
     * Returns the book's owner
     * @return The book's owner
     */
    unsigned int getOwner() const;
    /**
     * Sets the book's category to the specified number
     * @param number The enumeration value for the book's category
     */
    void setCategory(unsigned int number);
    /**
     * Retuns the book's category
     * @return The book's category
     */
    std::string getCategory() const;
    /**
     * Returns the book category number
     * @return The book category number
     */
    Category getCategoryNumber() const;
    /**
     * Sets the book's value to the specified one
     * @param value The book's value
     */
    void setValue(float value);
    /**
     * Returns the book's value
     * @return The book's value
     */
    float getValue() const;
    /**
     * Sets if the book is borrowed or not, by the specified boolean
     * @param isBorrowed True if the book is borrowed, false otherwise
     */
    void setIsBorrowed(bool isBorrowed);
    /**
     * Returns if the book is borrowed or not
     * @return True if the book is borrowed, false otherwise
     */
    bool getIsBorrowed() const;
    /**
     * Sets if a book's loan was already renewed by some member
     * @param loanRenew True if the book's loan was already renewed, false otherwise
     */
    void setLoanRenew(bool loanRenew);
    /**
     * Returns if the book's loan was already renewed by some member
     * @return True if the book's loan was already renewed, false otherwise
     */
    bool getLoanRenew() const;
    /**
     * Sets the book's begin of loan to the specified one
     * @param beginOfLoan The book's begin of loan
     */
    void setBeginOfLoan(unsigned long long int beginOfLoan);
    /**
     * Returns the book's begin of loan
     * @return The book's begin of loan, will be 0 if the book is not loaned
     */
    unsigned long long int getBeginOfLoan() const;
    /**
     * Sets the book's maximum loan time to the specified one
     * @param maximumLoanTime The book's maximum loan time
     */
    void setMaximumLoanTime(unsigned long long int maximumLoanTime);
    /**
     * Returns the book's maximum loan time
     * @return The book's maximum loan time
     */
    unsigned long long int getMaximumLoanTime() const;
    /**
    * Sets the book's end of loan to the specified one
    * @param endOfLoan The book's end of loan
    */
    void setEndOfLoan(unsigned long long int endOfLoan);
    /**
     * Returns the book's end of loan
     * @return The book's end of loan, will be 0 if the book is not loaned
     */
    unsigned long long int getEndOfLoan() const;
    /**
     * Returns the loan time remaining of the book
     * @return The loan time remaining of the book
     */
    long long int getLoanTimeRemaining() const;
    /**
     * Adds a rating to the book's ratings
     * @param rating The rating to be added
     */
    void addRating(unsigned int rating);
    /**
     * Returns all the ratings from the book
     * @return Vector containing all the ratings from the book
     */
    float getRating() const;
    /**
     * Returns the book's average rating
     * @return The book's average rating
     */
    std::vector<unsigned int> getRatings() const;
    /**
     * Adds a comments to the book's comments
     * @param comment The comment to be added
     */
    void addComment(std::string comment);
    /**
     * Returns all the book's comments
     * @return Vector containing all the book's comments
     */
    std::vector<std::string> getComments() const;
    /**
     * Adds a person to the book's waiting list
     * @param p The person to be added to the waiting list
     */
    void addToWaitingList(Person p);
    /**
     * Returns the book's waiting list
     * @return The book's waiting list
     */
    std::priority_queue<Person> getWaitingList() const;
    /**
     * Removes the front person from the waiting list
     */
    void manageQueue();
    /**
     * Returns the front person from the waiting list
     * @return The front person from the waiting list
     */
    Person getQueueFront() const;
    /**
     * Returns the size of the waiting list
     * @return The size of the waiting list
     */
    unsigned int getQueueSize() const;
    /**
     * Returns the current waiting list from the book
     * @return The current waiting list from the book
     */
    std::priority_queue<Person> getQueue() const;

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
    std::priority_queue<Person> waitingList; /**<Priority queue that hold the order from the person that want to borrow the book*/
};

#endif //_BOOK_H
