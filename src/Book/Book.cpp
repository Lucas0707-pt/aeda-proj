#include "Book.h"
#include <ctime>

//----------------------------------------------------------------------------------------------------------------

int Book::id = 1;

//----------------------------------------------------------------------------------------------------------------

Book::Book() {setBookId(this->id++);}

//----------------------------------------------------------------------------------------------------------------

Book::~Book() = default;

//----------------------------------------------------------------------------------------------------------------

void Book::setTitle(std::string title){this->title = title;}

//----------------------------------------------------------------------------------------------------------------

std::string Book::getTitle() const {return title;}

//----------------------------------------------------------------------------------------------------------------

void Book::setBookId(unsigned int bookId) {this->unique_ID = bookId;}

//----------------------------------------------------------------------------------------------------------------

void Book::updateBookStaticId(){id--;}

//----------------------------------------------------------------------------------------------------------------

unsigned int Book::getBookId() const {return unique_ID;}

//----------------------------------------------------------------------------------------------------------------

void Book::setOwner(unsigned int owner) {this->owner = owner;}

//----------------------------------------------------------------------------------------------------------------

unsigned int Book::getOwner() const {return owner;}

//----------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------

Category Book::getCategoryNumber() const {return category;}

//----------------------------------------------------------------------------------------------------------------

void Book::setValue(float value) {this->value = value;}

//----------------------------------------------------------------------------------------------------------------

float Book::getValue() const {return value;}

//----------------------------------------------------------------------------------------------------------------

void Book::setIsBorrowed(bool isBorrowed) {this->isBorrowed = isBorrowed;}

//----------------------------------------------------------------------------------------------------------------

bool Book::getIsBorrowed() const {return isBorrowed;}

//----------------------------------------------------------------------------------------------------------------

void Book::setLoanRenew(bool loanRenew) {this->loanRenew = loanRenew;}

//----------------------------------------------------------------------------------------------------------------

bool Book::getLoanRenew() const {return loanRenew;}

//----------------------------------------------------------------------------------------------------------------

void Book::setBeginOfLoan(unsigned long long int beginOfLoan){this->beginOfLoan = beginOfLoan;}

//----------------------------------------------------------------------------------------------------------------

unsigned long long int Book::getBeginOfLoan() const {return beginOfLoan;}

//----------------------------------------------------------------------------------------------------------------

void Book::setMaximumLoanTime(unsigned long long int maximumLoantime) {this->maximumLoanTime = maximumLoantime;}

//----------------------------------------------------------------------------------------------------------------

unsigned long long int Book::getMaximumLoanTime() const { return maximumLoanTime;}

//----------------------------------------------------------------------------------------------------------------

void Book::setEndOfLoan(unsigned long long int endOfLoan) {this->endOfLoan = endOfLoan;}

//----------------------------------------------------------------------------------------------------------------

unsigned long long int Book::getEndOfLoan() const {return endOfLoan;}

//----------------------------------------------------------------------------------------------------------------

long long int Book::getLoanTimeRemaining() const {return endOfLoan - time(nullptr);}

//----------------------------------------------------------------------------------------------------------------

void Book::addRating(unsigned int rating) {ratings.push_back(rating);}

//----------------------------------------------------------------------------------------------------------------

std::vector<unsigned int> Book::getRatings() const {return this->ratings;}

//----------------------------------------------------------------------------------------------------------------

float Book::getRating() const
{
    if (ratings.empty())
        return -1;
    float sum = 0;
    for(size_t i=0; i<ratings.size(); ++i)
        sum += ratings[i];
    return sum/ratings.size();
}

//----------------------------------------------------------------------------------------------------------------

void Book::addComment(std::string comment) {comments.push_back(comment);}

//----------------------------------------------------------------------------------------------------------------

std::vector<std::string> Book::getComments() const {return comments;}

//----------------------------------------------------------------------------------------------------------------

void Book::addToWaitingList(Person p) {waitingList.push(p);}

//----------------------------------------------------------------------------------------------------------------

std::priority_queue<Person> Book::getWaitingList() const {return waitingList;}

//----------------------------------------------------------------------------------------------------------------

void Book::manageQueue() {waitingList.pop();}

//----------------------------------------------------------------------------------------------------------------

Person Book::getQueueFront() const {return waitingList.top();}

//----------------------------------------------------------------------------------------------------------------

unsigned int Book::getQueueSize() const {return waitingList.size();}

//----------------------------------------------------------------------------------------------------------------

std::priority_queue<Person> Book::getQueue() const {return waitingList;}

//----------------------------------------------------------------------------------------------------------------