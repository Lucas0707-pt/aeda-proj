#include "../Club_BookStore/Club_BookStore.h"
#include <algorithm>
#include <unordered_set>

BookStore::BookStore(){}

BookStore::BookStore(std::string n, std::string p) : name(n), place(p){}

BookStore::~BookStore()
{
    std::vector<std::tuple<unsigned int, Book*>>::iterator it;
    for(it = stock.begin(); it != stock.end(); ++it) delete std::get<1>(*it);
}

void BookStore::setName(std::string name) {this->name = name;}

std::string BookStore::getName() const {return name;}

void BookStore::setPlace(std::string place) {this->place = place;}

std::string BookStore::getPlace() const {return place;}

void BookStore::addBook(unsigned int copies, Book* book) {stock.push_back(std::make_tuple(copies, book));}

std::vector<std::tuple<unsigned int, Book*>> BookStore::getStock() const {return stock;}

void BookStore::removeBook(Book* book)
{
    auto it = std::find_if(stock.begin(), stock.end(), [&book](const auto& bookTuple){return std::get<1>(bookTuple) == book;});
    stock.erase(it);
}

void BookStore::setPromotion(float promotion) {this->promotion = promotion;}

float BookStore::getPromotion() const {return promotion;}

void BookStore::setDiscountCode(std::string discountCode) {this->discountCode = discountCode;}

std::string BookStore::getDiscountCode() const {return discountCode;}

void BookStore::addRating(unsigned int rating) {ratings.push_back(rating);}

std::vector<unsigned int> BookStore::getRatings() const {return ratings;}

float BookStore::getRating() const
{
    if (ratings.empty()) return -1;
    float finalRating = 0;
    for (auto& rating : ratings)
        finalRating += (float) rating;
    return finalRating / ratings.size();
}

unsigned int BookStore::getVarietyOfBooks() const
{
    if (stock.empty()) return 0;
    std::unordered_set<std::string> differentTypes;
    for (const auto& bookTuple : stock)
    {
        differentTypes.insert(std::get<1>(bookTuple)->getCategory());
    }
    return differentTypes.size();
}

bool BookStore::operator<(const BookStore& bookStore2) const
{
    if (this->getRating() < bookStore2.getRating())
        return true;
    if (this->getRating() > bookStore2.getRating())
        return false;
    if(this->getVarietyOfBooks() < bookStore2.getVarietyOfBooks())
        return true;
    if (this->getVarietyOfBooks() > bookStore2.getVarietyOfBooks())
        return false;
    else return name < bookStore2.name;
}

bool BookStore::operator!=(const BookStore& bookStore2) const
{
    if ((this->getName() != bookStore2.getName()) || (this->getPlace() != bookStore2.getPlace()))
        return true;
    else
        return false;
}