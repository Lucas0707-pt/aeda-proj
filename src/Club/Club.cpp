#include <algorithm>
#include "Club.h"
#include <fstream>

/**
 * Will initialize an object of Club and read from the files all books and people from the club that already exists
 * @param loanFee The club loan fee
 * @param delayPenalty The club default penalty
 */

Club::Club(float loanFee, float delayPenalty)
{
    this->loanFee = loanFee;
    this->delayPenalty = delayPenalty;
    std::string input;
    Book* ptrBook;
    Member* ptrMember;
    NonMember* ptrNonMember;

    std::ifstream books_file ("Books.txt");
    std::ifstream people_file ("People.txt");
    // a adicionar books para o catalog
    while(!books_file.eof()) {
        std::getline(books_file, input);
        if (input.empty()) break;
        Book *book = new Book();
        book->setTitle(input);
        std::getline(books_file, input);
        book->setOwner(std::stoi(input));
        std::getline(books_file, input);
        if(input=="1") book->setIsBorrowed(true);
        else book->setIsBorrowed(false);
        std::getline(books_file, input);
        if(input=="1") book->setLoanRenew(true);
        else book->setLoanRenew(false);
        std::getline(books_file, input);
        book->setCategory(std::stoi(input));
        std::getline(books_file, input);
        book->setValue(std::stof(input));
        std::getline(books_file, input);
        book->setBeginOfLoan(std::stoi(input));
        std::getline(books_file, input);
        book->setMaximumLoanTime(std::stoi(input));
        std::getline(books_file, input);
        book->setEndOfLoan(std::stoi(input));
        while(std::getline(books_file,input))
        {
            if(input == "endRatings")
                break;
            else
                book->addRating(std::stoi(input));
        }
        while(std::getline(books_file,input))
        {
            if(input == "endComments")
                break;
            else
                book->addComment(input);
        }
        while(std::getline(books_file,input))
        {
            if(input == "endBorrowedMember")
                break;
            else
                book->addToWaitingListM(std::stoi(input));
        }
        while(std::getline(books_file,input))
        {
            if(input == "endBorrowedNonMember")
                break;
            else
                book->addToWaitingListNM(std::stoi(input));
        }
        catalog.push_back(book);
    }

    books_file.close();

    // a adicionar person's para people
    while(!people_file.eof())
    {
        std::getline(people_file, input);
        if(input.empty()) break;
        if(input == "0")
        {
            ptrNonMember = new NonMember();
            ptrNonMember->setIsMember(false);
            std::getline(people_file, input);
            ptrNonMember->setName(input);
            while(std::getline(people_file,input)) {
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
            std::getline(people_file, input);
            ptrMember->setName(input);
            while(std::getline(people_file,input))
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
    people_file.close();

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

void Club::close() {
    std::ofstream books_file("Books.txt", std::ios::trunc);
    std::ofstream people_file("People.txt", std::ios::trunc);

    for(const auto &book : catalog){
        books_file << book->getTitle() << std::endl;
        books_file << book->getOwner() << std::endl;
        if(book->getIsBorrowed()) books_file << "1" << std::endl;
        else books_file << "0" << std::endl;
        if (book->getLoanRenew()) books_file << "1" << std::endl;
        else books_file << "0" << std::endl;
        books_file << book->getCategoryNumber() << std::endl;
        books_file << book->getValue() << std::endl;
        books_file << std::to_string(book->getBeginOfLoan()) << std::endl;
        books_file << std::to_string(book->getMaximumLoanTime()) << std::endl;
        books_file << std::to_string(book->getEndOfLoan()) << std::endl;
        for (const auto &rating : book->getRatings())
            books_file << rating << std::endl;
        books_file << "endRatings" << std::endl;
        for(const auto &comment : book->getComments())
            books_file << comment << std::endl;
        books_file << "endComments" << std::endl;
        while(book->getQueueMSize())
        {
            books_file << book->getQueueMFront() << std::endl;
            book->manageQueue();
        }
        books_file << "endBorrowedMember" << std::endl;
        while(book->getQueueNMSize())
        {
            books_file << book->getQueueNMFront() << std::endl;
            book->manageQueue();
        }
        books_file << "endBorrowedNonMember" << std::endl;
    }
    for(const auto &person : people){
        if(person->getIsMember()) people_file << "1" << std::endl;
        else people_file << "0" << std::endl;
        people_file << person->getName() << std::endl;

        for(const auto &book : person->getBorrowedBooks())
            people_file << book->getBookId() << std::endl;
        people_file << "endBorrowedBooks" << std::endl;

    }

    books_file.close();
    people_file.close();
}