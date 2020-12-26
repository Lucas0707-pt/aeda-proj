#include "BookStore.h"
#include <algorithm>
#include <unordered_set>

void BookStore::setName(std::string name) {this->name = name;}

std::string BookStore::getName() const {return name;}

void BookStore::setPlace(std::string place) {this->place = place;}

std::string BookStore::getPlace() const {return place;}

void BookStore::addBook(Book* book) {stock.push_back(book);}

std::vector<Book*> BookStore::getStock() {return stock;}

void BookStore::removeBook(Book* book)
{
    auto it = std::find(stock.begin(), stock.end(), book);
    stock.erase(it);
}

void BookStore::setPromotion(float promotion) {this->promotion = promotion;}

float BookStore::getPromotion() const {return promotion;}

void BookStore::setDiscountCode(std::string discountCode) {this->discountCode = discountCode;}

std::string BookStore::getDiscountCode() const {return discountCode;}

void BookStore::addRating(unsigned int rating) {ratings.push_back(rating);}

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
    for (const auto& book : stock)
    {
        differentTypes.insert(book->getCategory());
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
