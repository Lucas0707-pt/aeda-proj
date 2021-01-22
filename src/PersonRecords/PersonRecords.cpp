#include "PersonRecords.h"

//----------------------------------------------------------------------------------------------------------------

PersonRecords::PersonRecords(std::string email) : emailAddress(email) { favoriteCategories = {};}

//----------------------------------------------------------------------------------------------------------------

void PersonRecords::setEmailAddress(std::string emailAddress) {this->emailAddress = emailAddress;}

//----------------------------------------------------------------------------------------------------------------

std::string PersonRecords::getEmailAddress() const {return emailAddress;}

//----------------------------------------------------------------------------------------------------------------

void PersonRecords::addFavoriteCategory(unsigned int category) {favoriteCategories.push_back(category);}

//----------------------------------------------------------------------------------------------------------------

std::vector<unsigned int> PersonRecords::getFavoritesCategories() const {return favoriteCategories;}

//----------------------------------------------------------------------------------------------------------------