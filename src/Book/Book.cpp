#include "Book.h"
#include <ctime>

int Book::id = 1;

/**
 * Book default constructor, that will set the book ID based on a counter id initialized in the beginning as 1, and then increment it
 */

Book::Book() {setBookId(this->id++);}

/**
 * Destructor of class Book
 */

Book::~Book() = default;

/**
 * Sets the book's title to the specified one
 * @param title The book's title
 */

void Book::setTitle(std::string title){this->title = title;}

/**
 * Returns the book's name
 * @return The book's name
 */

std::string Book::getTitle() const {return title;}

/**
 * Sets the book's ID to the specified one
 * @param bookId The book's ID
 */

void Book::setBookId(unsigned int bookId) {this->unique_ID = bookId;}

/**
 * Decrement the static id from the book, will be used when a book was removed
 */

void Book::updateBookStaticId(){id--;}

/**
 * Returns the book's ID
 * @return The book's ID
 */

unsigned int Book::getBookId() const {return unique_ID;}

/**
 * Sets the owner ID to the specified one
 * @param owner The ID of the book's owner
 */

void Book::setOwner(unsigned int owner) {this->owner = owner;}

/**
 * Returns the book's owner
 * @return The book's owner
 */

unsigned int Book::getOwner() const {return owner;}

/**
 * Sets the book's category to the specified number
 * @param number The enumeration value for the book's category
 */

void Book::setCategory(unsigned int number)
{
    switch(number)
    {
        case 0:
            category = Adventure;
            break;
        case 1:
            category = Arts;
            break;
        case 2:
            category = Biography;
            break;
        case 3:
            category = Comics;
            break;
        case 4:
            category = Cooking;
            break;
        case 5:
            category = Crime;
            break;
        case 6:
            category = Entertainment;
            break;
        case 7:
            category = Health;
            break;
        case 8:
            category = History;
            break;
        case 9:
            category = Horror;
            break;
        case 10:
            category = Kids;
        case 11:
            category = Medical;
            break;
        case 12:
            category = Romance;
            break;
        case 13:
            category = SciFi;
            break;
        case 14:
            category = Science;
            break;
        case 15:
            category = Sports;
            break;
        case 16:
            category = Suspense;
            break;
        case 17:
            category = Other;
            break;
    }
}
/**
 * Retuns the book's category
 * @return The book's category
 */
std::string Book::getCategory() const
{
    switch(category)
    {
        case 0:
            return "Adventure";
        case 1:
            return "Arts";
        case 2:
            return "Biography";
        case 3:
            return "Comics";
        case 4:
            return "Cooking";
        case 5:
            return "Crime";
        case 6:
            return "Entertainment";
        case 7:
            return "Health";
        case 8:
            return "History";
        case 9:
            return "Horror";
        case 10:
            return "Kids";
        case 11:
            return "Medical";
        case 12:
            return "Romance";
        case 13:
            return "SciFi";
        case 14:
            return "Science";
        case 15:
            return "Sports";
        case 16:
            return "Suspense";
        case 17:
            return "Other";
    }
}

/**
 * Returns the book category number
 * @return The book category number
 */

Category Book::getCategoryNumber() const {return category;}

/**
 * Sets the book's value to the specified one
 * @param value The book's value
 */

void Book::setValue(float value) {this->value = value;}

/**
 * Returns the book's value
 * @return The book's value
 */
float Book::getValue() const {return value;}

/**
 * Sets if the book is borrowed or not, by the specified boolean
 * @param isBorrowed True if the book is borrowed, false otherwise
 */

void Book::setIsBorrowed(bool isBorrowed) {this->isBorrowed = isBorrowed;}

/**
 * Returns if the book is borrowed or not
 * @return True if the book is borrowed, false otherwise
 */

bool Book::getIsBorrowed() const {return isBorrowed;}

/**
 * Sets if a book's loan was already renewed by some member
 * @param loanRenew True if the book's loan was already renewed, false otherwise
 */

void Book::setLoanRenew(bool loanRenew) {this->loanRenew = loanRenew;}

/**
 * Returns if the book's loan was already renewed by some member
 * @return True if the book's loan was already renewed, false otherwise
 */

bool Book::getLoanRenew() const {return loanRenew;}

/**
 * Sets the book's begin of loan to the specified one
 * @param beginOfLoan The book's begin of loan
 */

void Book::setBeginOfLoan(unsigned long long int beginOfLoan){this->beginOfLoan = beginOfLoan;}

/**
 * Returns the book's begin of loan
 * @return The book's begin of loan, will be 0 if the book is not loaned
 */

unsigned long long int Book::getBeginOfLoan() const {return beginOfLoan;}

/**
 * Sets the book's maximum loan time to the specified one
 * @param maximumLoantime The book's maximum loan time
 */

void Book::setMaximumLoanTime(unsigned long long int maximumLoantime) {this->maximumLoanTime = maximumLoantime;}

/**
 * Returns the book's maximum loan time
 * @return The book's maximum loan time
 */

unsigned long long int Book::getMaximumLoanTime() const { return maximumLoanTime;}

/**
* Sets the book's end of loan to the specified one
* @param endOfLoan The book's end of loan
*/

void Book::setEndOfLoan(unsigned long long int endOfLoan) {this->endOfLoan = endOfLoan;}

/**
 * Returns the book's end of loan
 * @return The book's end of loan, will be 0 if the book is not loaned
 */

unsigned long long int Book::getEndOfLoan() const {return endOfLoan;}

/**
 * Returns the loan time remaining of the book
 * @return The loan time remaining of the book
 */

long long int Book::getLoanTimeRemaining() const {return endOfLoan - time(nullptr);}

/**
 * Adds a rating to the book's ratings
 * @param rating The rating to be added
 */

void Book::addRating(unsigned int rating) {ratings.push_back(rating);}

/**
 * Returns all the ratings from the book
 * @return Vector containing all the ratings from the book
 */

std::vector<unsigned int> Book::getRatings() const { return this->ratings; }

/**
 * Returns the book's average rating
 * @return The book's average rating
 */

float Book::getRating() const
{
    if (ratings.empty())
        return -1;
    float sum = 0;
    for(size_t i=0; i<ratings.size(); ++i)
        sum += ratings[i];
    return sum/ratings.size();
}

/**
 * Adds a comments to the book's comments
 * @param comment The comment to be added
 */

void Book::addComment(std::string comment) {comments.push_back(comment);}

/**
 * Returns all the book's comments
 * @return Vector containing all the book's comments
 */

std::vector<std::string> Book::getComments() const {return comments;}

/**
 * Will add to the members queue the specified member ID
 * @param m The member ID
 */

void Book::addToWaitingListM(unsigned int m) {waitingListM.push(m);}

/**
 * Will add to the non-members queue the specified non-member ID
 * @param nm The non-member ID
 */

void Book::addToWaitingListNM(unsigned int nm) {waitingListNM.push(nm);}
void Book::addToWaitingList(Person p) {waitingList.push(p);}
/**
 * Will return the ID of the first member in the queue
 * @return The ID of the top one, or -1 if the queue is empty
 */

int Book::getQueueMFront() const
{
    if (!waitingListM.empty())
        return waitingListM.front();
    else
        return -1;
}

/**
 * Will return the members queue size
 * @return The members queue size
 */

unsigned int Book::getQueueMSize() {return waitingListM.size();}

/**
 * Will return the ID from the first non members in the queue
 * @return The ID of the top one, or -1 if the queue is empty
 */

int Book::getQueueNMFront() const
{
    if(!waitingListNM.empty())
        return waitingListNM.front();
    else
        return -1;
}

/**
 * Will return the non-members queue size
 * @return The non-members queue size
 */

unsigned int Book::getQueueNMSize() {return waitingListNM.size();}

/**
 * Will manage the queue, by first checking if members queue is empty, if not removes the top one and finishes,
 * if the queue is empty, then will check if the non-memebers checks is empty, is not removes the top one
 */

void Book::manageQueue()
{
    if(!waitingListM.empty())
    {
        waitingListM.pop();
    }
    else if (!waitingListNM.empty())
    {
        waitingListNM.pop();
    }
}