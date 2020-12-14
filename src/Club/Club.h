#ifndef _CLUB_H
#define _CLUB_H
#include "../Person/Person.h"
#include "../Book/Book.h"
#include <vector>
#include <string>

class Person;
class Book;

/**
 * Class used to store all the information from the club, i.e books, members, non-members, delay penalty and loan fee.
 * As the methods to add and delete a book, and also to add the book.
 * This class can't delete a person, because since a person is added to the club can't be deleted, even if he goes inactive
 */

class Club
{
public:
    Club(float loanFee, float delayPenalty);
    ~Club();
    unsigned int readFile();
    void writeFile();
    float getDelayPenalty() const;
    float getLoanFee() const;
    void addPerson(Person* person);
    void removePerson(Person* person);
    void addBook(Book* book);
    void removeBook(Book* book);
    std::vector<Book*> getCatalog() const;
    std::vector<Person*> getPeople() const;
    Person* getPersonById(unsigned int id);
    Book* getBookById(unsigned int id);
    void updateBookID(unsigned int id);
    void close();

private:
    float loanFee; /**<Loan fee for Non-Members*/
    float delayPenalty; /**<Delay penalty for people that return the book after end of loan time */
    std::vector<Person*> people; /**<Vector containing all the club's people */
    std::vector<Book*> catalog; /**<Vector  containing all the club's books*/


};

#endif //_CLUB_H
