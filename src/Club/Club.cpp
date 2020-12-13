#include "Club.h"
#include "../Exception/FileException/FileException.h"
#include "../Utils/utils.h"
#include <fstream>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

/**
 * Will initialize an object of Club and read from the files all books and people from the club that already exists
 * @param loanFee The club loan fee
 * @param delayPenalty The club default penalty
 */

Club::Club(float loanFee, float delayPenalty)
{
    this->loanFee = loanFee;
    this->delayPenalty = delayPenalty;
}

/**
 * Club Destructor that will delete every person and book dynamically created
 */

Club::~Club()
{
    std::vector<Person*>::iterator it1;
    std::vector<Book*>::iterator it2;
    for(it1 = people.begin(); it1 != people.end(); ++it1) delete *it1;
    for(it2 = catalog.begin(); it2 != catalog.end(); ++it2) delete *it2;
}

unsigned int Club::readFile()
{
    std::string input;
    Book* ptrBook;
    Member* ptrMember;
    NonMember* ptrNonMember;
    std::string booksFileString = "../Files/Books.txt";
    std::string peopleFileString = "../Files/People.txt";
    std::string infoFileString = "../Files/Info.txt";
    unsigned long long int  modTimeBooks;
    unsigned long long int  modTimePeople;
    unsigned long long int  modTimeInfo;
    struct stat result;

    std::ifstream infoFile(infoFileString);
    std::ifstream booksFile(booksFileString);
    std::ifstream peopleFile(peopleFileString);

    if (!infoFile.is_open())
        throw FileNotFound("Info.txt");
    if (!booksFile.is_open())
        throw FileNotFound("Books.txt");
    if(!peopleFile.is_open())
        throw FileNotFound("People.txt");

    //getting the last modification time of the files
    if(!stat(infoFileString.c_str(), &result))
        modTimeInfo = result.st_mtime;
    if(!stat(booksFileString.c_str(), &result))
        modTimeBooks = result.st_mtime;
    if(!stat(peopleFileString.c_str(), &result))
        modTimePeople = result.st_mtime;


    //reading the infoFile, checking if any of the files was edited, and getting the loanFee and delayPenalty
    if (infoFile.peek() == std::ifstream::traits_type::eof()) //check if the file as any content, if not, means that the programs is being opened for the first time
        return 1;

    std::getline(infoFile, input);
    if (isNumeric(input))
    {
        if (!(std::stoi(input) == modTimeInfo))
            throw FileWasModified("Info.txt");
    }
    else
    {
        throw FileWasModified("Info.txt");
    }
    if (!(std::stoi(input) == modTimeBooks))
        throw FileWasModified("Books.txt");
    if (!(std::stoi(input) == modTimePeople))
        throw FileWasModified("People.txt");
    std::getline(infoFile,input);
    loanFee = std::stoi(input);
    std::getline(infoFile,input);
    delayPenalty = std::stoi(input);

    //adding books to the catalog
    while(!booksFile.eof()) {

        Book *book = new Book();
        std::getline(booksFile,input);
        book->setTitle(input);
        std::getline(booksFile, input);
        book->setOwner(std::stoi(input));
        std::getline(booksFile, input);
        if(input=="1") book->setIsBorrowed(true);
        else book->setIsBorrowed(false);
        std::getline(booksFile, input);
        if(input=="1") book->setLoanRenew(true);
        else book->setLoanRenew(false);
        std::getline(booksFile, input);
        book->setCategory(std::stoi(input));
        std::getline(booksFile, input);
        book->setValue(std::stof(input));
        std::getline(booksFile, input);
        book->setBeginOfLoan(std::stoi(input));
        std::getline(booksFile, input);
        book->setMaximumLoanTime(std::stoi(input));
        std::getline(booksFile, input);
        book->setEndOfLoan(std::stoi(input));
        while(std::getline(booksFile,input))
        {
            if(input == "endRatings")
                break;
            else
                book->addRating(std::stoi(input));
        }
        while(std::getline(booksFile,input))
        {
            if(input == "endComments")
                break;
            else
                book->addComment(input);
        }
        while(std::getline(booksFile,input))
        {
            if(input == "endBorrowedMember")
                break;
            else
                book->addToWaitingListM(std::stoi(input));
        }
        while(std::getline(booksFile,input))
        {
            if(input == "endBorrowedNonMember")
                break;
            else
                book->addToWaitingListNM(std::stoi(input));
        }
        catalog.push_back(book);
    }

    booksFile.close();

    // a adicionar person's para people
    while(!peopleFile.eof())
    {
        std::getline(peopleFile, input);
        if(input == "0")
        {
            ptrNonMember = new NonMember();
            ptrNonMember->setIsMember(false);
            std::getline(peopleFile, input);
            ptrNonMember->setName(input);
            while(std::getline(peopleFile,input)) {
                if(input == "endBorrowedBooks")
                {
                    break;
                }
                else
                {
                    ptrBook = getBookById(std::stoi(input));
                    ptrNonMember->addBorrowedBook(ptrBook);
                }
            }
            people.push_back(ptrNonMember);
        }
        else
        {
            ptrMember = new Member();
            ptrMember->setIsMember(true);
            std::getline(peopleFile, input);
            ptrMember->setName(input);
            while(std::getline(peopleFile,input))
            {
                if(input == "endBorrowedBooks")
                {
                    break;
                }
                else
                {
                    ptrBook = getBookById(std::stoi(input));
                    ptrMember->addBorrowedBook(ptrBook);
                }
            }
            people.push_back(ptrMember);
        }
    }
    peopleFile.close();

    // a adicionar Books aos seus correspondentes owners
    for(const auto& book : catalog)
    {
        for (const auto &person : people)
        {
            if (book->getOwner() == person->getID())
            {
                ptrMember = dynamic_cast<Member *>(person);
                ptrMember->addOwnedBook(book);
                break;
            }
        }
    }
}

void Club::writeFile()
{
    std::ofstream infoFile("../Files/Info.txt", std::ios::trunc);
    std::ofstream booksFile("../Files/Books.txt", std::ios::trunc);
    std::ofstream peopleFile("../Files/People.txt", std::ios::trunc);
    unsigned long long int  modTimeBooks;
    unsigned long long int  modTimePeople;
    unsigned long long int  modTimeInfo;

    for(const auto &book : catalog){
        booksFile << book->getTitle() << std::endl;
        booksFile << book->getOwner() << std::endl;
        if(book->getIsBorrowed()) booksFile << "1" << std::endl;
        else booksFile << "0" << std::endl;
        if (book->getLoanRenew()) booksFile << "1" << std::endl;
        else booksFile << "0" << std::endl;
        booksFile << book->getCategoryNumber() << std::endl;
        booksFile << book->getValue() << std::endl;
        booksFile << std::to_string(book->getBeginOfLoan()) << std::endl;
        booksFile << std::to_string(book->getMaximumLoanTime()) << std::endl;
        booksFile << std::to_string(book->getEndOfLoan()) << std::endl;
        for (const auto &rating : book->getRatings())
            booksFile << rating << std::endl;
        booksFile << "endRatings" << std::endl;
        for(const auto &comment : book->getComments())
            booksFile << comment << std::endl;
        booksFile << "endComments" << std::endl;
        while(book->getQueueMSize())
        {
            booksFile << book->getQueueMFront() << std::endl;
            book->manageQueue();
        }
        booksFile << "endBorrowedMember" << std::endl;
        while(book->getQueueNMSize())
        {
            booksFile << book->getQueueNMFront() << std::endl;
            book->manageQueue();
        }
        booksFile << "endBorrowedNonMember" << std::endl;
    }
    booksFile.close();
    modTimeBooks = time(nullptr);

    for(const auto &person : people){
        if(person->getIsMember()) peopleFile << "1" << std::endl;
        else peopleFile << "0" << std::endl;
        peopleFile << person->getName() << std::endl;

        for(const auto &book : person->getBorrowedBooks())
            peopleFile << book->getBookId() << std::endl;
        peopleFile << "endBorrowedBooks" << std::endl;

    }
    modTimePeople = time(nullptr);
    peopleFile.close();
    modTimeInfo = time(nullptr);
    infoFile << modTimeInfo << std::endl
             << modTimeBooks << std::endl
             << modTimePeople << std::endl
             << loanFee << std::endl
             << delayPenalty << std::endl;
    infoFile.close();
}

/**
 * Will add the person specified to the club's people
 * @param person The person to be added to the club
 */

void Club::addPerson(Person *person) {people.push_back(person);}

/**
 * Will remove from the people of the club the specified person
 * @param person The person to be removed from people
 */

void Club::removePerson(Person *person)
{
    auto it = std::find(people.begin(), people.end(), person);
    people.erase(it);
}

/**
 * Will add to the catalog the specified book
 * @param book The book to be added to the catalog
 */

void Club::addBook(Book *book) {catalog.push_back(book);}

/**
 * Will remove from the catalog the specified book
 * @param book The book to be removed from catalog
 */

void Club::removeBook(Book *book) {
    auto it = std::find(catalog.begin(), catalog.end(), book);
    catalog.erase(it);

}

/**
 * Will return the club's delay penalty
 * @return The club's delay penalty
 */

float Club::getDelayPenalty() const {return delayPenalty;}

/**
 * Will return the club's loan fee
 * @return The club's loan fee
 */

float Club::getLoanFee() const {return loanFee;}

/**
 * Will return a vector of the club's catalog
 * @return Vector of pointers to the club's catalog
 */

std::vector<Book*> Club::getCatalog() const {return catalog;}

/**
 * Will return a vector of the club's people
 * @return Vector of pointers to the club's people
 */

std::vector<Person*> Club::getPeople() const {return people;}

/**
 * Will search on the club's people if it exists a person with the specified id
 * @param id The person's id
 * @return The pointer to the person if he was found, nullptr otherwise
 */

Person * Club::getPersonById(unsigned int id) {
    for(const auto& person : people)
        if(person->getID() == id) return person;
    return nullptr;
}

/**
 * Will search on the club's catalog if it exists a book with the specified id
 * @param id The id of the book to be returned as a pointer
 * @return The pointer of the book if it was found, nullptr otherwise
 */

Book * Club::getBookById(unsigned int id) {
    for(const auto& book : catalog)
        if(book->getBookId() == id) return book;
    return nullptr;
}

/**
 * Will update every id from the book's
 * @param id The id from the book that was removed
 */

void Club::updateBookID(unsigned int id)
{
    for (const auto &book : catalog )
    {
        if (book->getBookId() > id)
            book->setBookId(book->getBookId()-1);
    }
}

/**
 * Will write to the files all the existing books and the people from the club in trunc mode
 */

void Club::close()
{
    writeFile();
}