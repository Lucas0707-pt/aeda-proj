#ifndef _PERSONRECORDS_H
#define _PERSONRECORDS_H

#include <iostream>
#include <vector>

class PersonRecords
{
public:
    PersonRecords(std::string email);
    void setEmailAddress(std::string emailAddress);
    std::string getEmailAddress() const;
    void addFavoriteCategory(unsigned int category);
    std::vector<unsigned int> getFavoritesCategories() const;
private:
    std::string emailAddress;
    std::vector<unsigned int> favoriteCategories;
};


#endif //_PERSONRECORDS_H
