#ifndef _CLUB_H
#define _CLUB_H
#include "../Person/Person.h"
#include "../Book/Book.h"
#include "../BST/Bst.h"
#include "../PersonRecords/PersonRecords.h"
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>

class Person;
class Book;

struct PersonRecordsHash
{
    int operator()(const PersonRecords& person) const {
        int v = 0;
        for (const auto & letter : person.getEmailAddress())
            v += letter;
        return 37*v;
    }

    bool operator()(const PersonRecords& person1, const PersonRecords& person2) const {
        return person1.getEmailAddress() == person2.getEmailAddress();
    }
};


/**
 * This class holds on the information about a book store, to witch the lecture club offers promotions to its clients
 */

class BookStore
{
public:
    /**
     * Book Store constructor, will set the name and the place, to n and p, respectively
     * @param n The name of the book store
     * @param p the location of the book store
     */
    BookStore(std::string n, std::string p);
    /**
     * Book Store destructor that will delete every book from the stock
     */
    ~BookStore();
    /**
     * Sets the name of the book store
     * @param name The name of the library
     */
    void setName(std::string name);
    /**
     * Returns the name of the book store
     * @return The name of the book store
     */
    std::string getName() const;
    /**
     * Sets the place where the book store is located
     * @param place The place where the book store is located
     */
    void setPlace(std::string place);
    /**
     * Returns the place where the book store is located
     * @return The place where the book store is located
     */
    std::string getPlace() const;
    /**
     * Adds a new book and all copies to the stock
     * @param copies The number of copies that the book store has from the book
     * @param book book The book to the added to the stock
     */
    void addBook(unsigned int copies, Book* book);
    /**
     * Returns the stock
     * @return The stock
     */
    std::vector<std::tuple<unsigned int, Book*>> getStock() const;
    /**
     * Removes a book from the stock
     * @param book The book to be removed
     */
    void removeBook(Book* book);
    /**
     *
     * @param promotion The promotion that is offered from the lecture club
     */
    void setPromotion(float promotion);
    /**
    * Returns the promotion that is offered from the lecture club
    * @return The promotion that is offered from the lecture club
    */
    float getPromotion() const;
    /**
     * Sets the discount code to be used in the book store
     * @param discountCode The code to be used in the book store to receive a discount
     */
    void setDiscountCode(std::string discountCode);
    /**
     * Returns the code to be used in the book store to receive a discount
     * @return The code to be used in the book store to receive a discount
     */
    std::string getDiscountCode() const;
    /**
     * Adds a rating to the book store's ratings
     * @param rating The rating to the added to the book store's ratings
     */
    void addRating(unsigned int rating);
    /**
     * Returns the vector containing all the ratings from the book store
     * @return The vector containing all the ratings from the book store
     */
    std::vector<unsigned int> getRatings() const;
    /**
     * Returns the mean rating from the book store
     * @return The mean rating from the book store
     */
    float getRating() const;
    /**
     * Returns the number of different book styles that exists in the book Store
     * @return The number of different book styles that exists in the book Store
     */
    unsigned int getVarietyOfBooks() const;
    /**
     * Will see if the book store1 is smaller than bookStore2
     * @param BookStore2 book store to be compared
     * @return True if the bookStore1 is smaller than the bookStore2, false otherwise
     */
    bool operator<(const BookStore& bookStore2) const;
private:
    std::string name; /**Book store name*/
    std::string place; /**The location of the book store*/
    std::vector<std::tuple<unsigned int, Book*>> stock; /**All the books available in the book store*/
    float promotion; /**The promotion that is offered from the lecture club*/
    std::string discountCode; /**The code to be used in the book store to receive a discount*/
    std::vector<unsigned int> ratings; /**All the ratings from the book store given by clients*/
};


/**
 * Class used to store all the information from the club, i.e books, members, non-members, delay penalty and loan fee.
 * As the methods to add and delete a book, and also to add the book.
 * This class can't delete a person, because since a person is added to the club can't be deleted, even if he goes inactive
 */

class Club
{
public:
    /**
     * Will initialize an object of Club and read from the files all books and people from the club that already exists
     * @param loanFee The club loan fee
     * @param delayPenalty The club default penalty
     */
    Club(float loanFee, float delayPenalty);
    /**
     * Club Destructor that will delete every person and book dynamically created
     */
    ~Club();
    /**
     * Will read from the
     */
    void readFile();
    void writeFile();
    /**
     * Will return the club's delay penalty
     * @return The club's delay penalty
     */
    float getDelayPenalty() const;
    /**
     * Will return the club's loan fee
     * @return The club's loan fee
     */
    float getLoanFee() const;
    /**
     * Will add the person specified to the club's people
     * @param person The person to be added to the club
     */
    void addPerson(Person* person);
    /**
     * Will remove from the people of the club the specified person
     * @param person The person to be removed from people
     */
    void removePerson(Person* person);
    /**
     * Will add to the catalog the specified book
     * @param book The book to be added to the catalog
     */
    void addBook(Book* book);
    /**
     * Will remove from the catalog the specified book
     * @param book The book to be removed from catalog
     */
    void removeBook(Book* book);
    /**
     * Will return a vector of the club's catalog
     * @return Vector of pointers to the club's catalog
     */
    std::vector<Book*> getCatalog() const;
    /**
     * Will return a vector of the club's people
     * @return Vector of pointers to the club's people
     */
    std::vector<Person*> getPeople() const;
    /**
     * Will search on the club's people if it exists a person with the specified id
     * @param id The person's id
     * @return The pointer to the person if he was found, nullptr otherwise
     */
    Person* getPersonById(unsigned int id);
    /**
     * Will search on the club's catalog if it exists a book with the specified id
     * @param id The id of the book to be returned as a pointer
     * @return The pointer of the book if it was found, nullptr otherwise
     */
    Book* getBookById(unsigned int id);
    /**
     * Will update all the ids that come after the id passed in the argument, decrementing 1 to each one
     * @param id The id from the book that was removed
     */
    void updateBookID(unsigned int id);
    void addBookStore(BookStore* b);
    BST<BookStore> getBookStores();
    void addPersonRecord(PersonRecords personRecord);
    void updateEmailPersonRecord(std::string oldEmail, std::string newEmail);
    unordered_set<PersonRecords, PersonRecordsHash, PersonRecordsHash> getPersonPreferences() const;
    void addPreference(unsigned int preference, std::string email);
    void removePreference(unsigned int preference, std::string email);
    bool preferenceExists(unsigned int preference, std::string email);

private:
    float loanFee; /**<Loan fee for Non-Members*/
    float delayPenalty; /**<Delay penalty for people that return the book after end of loan time */
    std::vector<Person*> people; /**<Vector containing all the club's people */
    std::vector<Book*> catalog; /**<Vector  containing all the club's books*/
    BST<BookStore> bookStores;
    unordered_set<PersonRecords, PersonRecordsHash, PersonRecordsHash> personPreferences;
};

#endif //_CLUB_H
