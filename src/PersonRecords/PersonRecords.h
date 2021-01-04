#ifndef _PERSONRECORDS_H
#define _PERSONRECORDS_H

#include <iostream>
#include <vector>

/**
 * Class used to hold the information from a user (email address and favorites categories)
 */
class PersonRecords
{
public:
    /**
     * Constructor of the class that initializes the emailAddress variable passed by argument
     * @param email The person's email address
     */
    PersonRecords(std::string email);
    /**
    * Seets the person email to the specified one
    * @param email The person's email address
    */
    void setEmailAddress(std::string emailAddress);
    /**
     * Returns the person's email address
     * @return The person's email address
     */
    std::string getEmailAddress() const;
    /**
     * Adds the category passed by argument to the favorite categories vector
     * @param category The category number to be added to the favorite ones
     */
    void addFavoriteCategory(unsigned int category);
    /**
     * Returns the vectors containing all the person's favorite categories
     * @return The vectors containing all the person's favorite categories
     */
    std::vector<unsigned int> getFavoritesCategories() const;
private:
    std::string emailAddress; /**<The person's email address*/
    std::vector<unsigned int> favoriteCategories; /**<The person favorite book categories*/
};

#endif //_PERSONRECORDS_H
