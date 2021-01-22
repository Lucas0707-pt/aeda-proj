#include "Club_BookStore.h"
#include "../Exception/FileException/FileException.h"
#include <fstream>
#include <algorithm>
#include <ctime>
#include <tuple>

//----------------------------------------------------------------------------------------------------------------

Club::Club(float lf, float dp) : loanFee(lf), delayPenalty(dp), bookStores(BookStore("", "")) {}

//----------------------------------------------------------------------------------------------------------------

Club::~Club()
{
    std::vector<Person*>::iterator it1;
    std::vector<Book*>::iterator it2;
    for(it1 = people.begin(); it1 != people.end(); ++it1) delete *it1;
    for(it2 = catalog.begin(); it2 != catalog.end(); ++it2) delete *it2;
}

//----------------------------------------------------------------------------------------------------------------

void Club::readFile()
{
    std::string input;
    Book* ptrBook;
    Member* ptrMember;
    NonMember* ptrNonMember;
    std::vector<std::vector<unsigned int>> waitingListTemp;
    unsigned int idTemp = 1;
    std::ifstream booksFile("../src/Files/Books.txt");
    std::ifstream peopleFile("../src/Files/People.txt");
    std::ifstream storesFile("../src/Files/BookStores.txt");
    if (!booksFile.is_open())
        throw FileNotFound("Books.txt");
    if(!peopleFile.is_open())
        throw FileNotFound("People.txt");
    if(!storesFile.is_open())
        throw FileNotFound("BookStores.txt");

    //adding books to the catalog
    while(!booksFile.eof()) {
        std::getline(booksFile, input);
        if (input.empty()) break;
        Book *book = new Book();
        waitingListTemp.push_back({idTemp++});
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
            if(input == "endBorrowedQueue")
                break;
            else
                waitingListTemp[idTemp-2].push_back(std::stoi(input));
        }
        catalog.push_back(book);
    }

    booksFile.close();

    // a adicionar person's para people
    while(!peopleFile.eof())
    {
        std::getline(peopleFile, input);
        if(input.empty()) break;
        if(input == "0")
        {
            ptrNonMember = new NonMember();
            ptrNonMember->setIsMember(false);
            std::getline(peopleFile, input);
            ptrNonMember->setName(input);
            std::getline(peopleFile, input);
            ptrNonMember->setEmailAddress(input);
            PersonRecords personRecord(input);
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
            while(std::getline(peopleFile,input)) {
                if(input == "endPreferences")
                {
                    break;
                }
                else
                {
                    personRecord.addFavoriteCategory(std::stoi(input));
                }
            }
            personPreferences.insert(personRecord);
            people.push_back(ptrNonMember);
        }
        else
        {
            ptrMember = new Member();
            ptrMember->setIsMember(true);
            std::getline(peopleFile, input);
            ptrMember->setName(input);
            std::getline(peopleFile, input);
            ptrMember->setEmailAddress(input);
            PersonRecords personRecord(input);
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
            while(std::getline(peopleFile,input)) {
                if(input == "endPreferences")
                {
                    break;
                }
                else
                {
                    personRecord.addFavoriteCategory(std::stoi(input));
                }
            }
            personPreferences.insert(personRecord);
            people.push_back(ptrMember);
        }
    }
    peopleFile.close();

    // a adicionar BookStores para o club
    while(!storesFile.eof()){
        std::getline(storesFile, input);
        if(input.empty()) break;
        BookStore* b = new BookStore("","");
        b->setName(input);
        std::getline(storesFile, input);
        b->setPlace(input);
        std::getline(storesFile, input);
        b->setPromotion(stof(input));
        std::getline(storesFile, input);
        b->setDiscountCode(input);
        while(std::getline(storesFile,input)) {
            if(input == "endBooks")
            {
                break;
            }
            else
            {
                Book *book = new Book();
                book->setTitle(input);
                book->updateBookStaticId();
                std::getline(storesFile,input);
                book->setCategory(std::stoi(input));
                std::getline(storesFile,input);
                book->setValue(std::stoi(input));
                std::getline(storesFile,input);
                b->addBook(std::stoi(input),book);
            }
        }
        while(std::getline(storesFile,input)) {
            if(input == "endRatings")
            {
                break;
            }
            else
            {
                b->addRating(stoi(input));
            }
        }
        bookStores.insert(*b);
    }
    storesFile.close();

    // a adicionar Books aos seus correspondentes owners
    for(const auto& book : catalog)
    {
        for (const auto &person : people)
        {
            if (book->getOwner() == person->getID())
            {
                ptrMember = dynamic_cast<Member *>(person);
                ptrMember->addOwnedBook(book);
                ptrMember->setOwnedBooksSize(ptrMember->getOwnedBooks().size());
                break;
            }
        }
    }
    for (const auto& bookVector : waitingListTemp)
    {
        Book* ptrTemp = getBookById(bookVector[0]);
        for (int i = 1; i < bookVector.size(); ++i)
        {
            ptrTemp->addToWaitingList(*getPersonById(bookVector[i]));
        }
    }
}

//----------------------------------------------------------------------------------------------------------------

void Club::writeFile()
{
    std::ofstream infoFile("../src/Files/Info.txt", std::ios::trunc);
    std::ofstream booksFile("../src/Files/Books.txt", std::ios::trunc);
    std::ofstream bookStoresFile("../src/Files/BookStores.txt", std::ios::trunc);
    std::ofstream peopleFile("../src/Files/People.txt", std::ios::trunc);
    unsigned long long int  modTimeInfo;
    unsigned long long int  modTimeBooks;
    unsigned long long int  modTimeBookStores;
    unsigned long long int  modTimePeople;

    if (!infoFile.is_open())
        throw FileNotFound("Info.txt");
    if (!booksFile.is_open())
        throw FileNotFound("Books.txt");
    if (!bookStoresFile.is_open())
        throw FileNotFound("BookStores.txt");
    if (!peopleFile.is_open())
        throw FileNotFound("People.txt");

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
        while(book->getWaitingList().size())
        {
            booksFile << book->getQueueFront().getID() << std::endl;
            book->manageQueue();
        }
        booksFile << "endBorrowedQueue" << std::endl;
    }
    booksFile.close();
    modTimeBooks = time(nullptr);

    for(const auto &person : people){
        if(person->getIsMember()) peopleFile << "1" << std::endl;
        else peopleFile << "0" << std::endl;
        peopleFile << person->getName() << std::endl;
        peopleFile << person->getEmailAddress() << std::endl;
        for(const auto &book : person->getBorrowedBooks())
            peopleFile << book->getBookId() << std::endl;
        peopleFile << "endBorrowedBooks" << std::endl;
        auto person2 = personPreferences.find(PersonRecords(person->getEmailAddress()));
        for (const auto &preference : person2->getFavoritesCategories())
            peopleFile << preference << std::endl;
        peopleFile << "endPreferences" << std::endl;

    }
    modTimePeople = time(nullptr);
    peopleFile.close();

    BSTItrIn<BookStore> it(bookStores);
    while(!it.isAtEnd())
    {
        bookStoresFile << it.retrieve().getName() << std::endl;
        bookStoresFile << it.retrieve().getPlace() << std::endl;
        bookStoresFile << it.retrieve().getPromotion() << std::endl;
        bookStoresFile << it.retrieve().getDiscountCode() << std::endl;
        for (const auto& bookTuple : it.retrieve().getStock())
        {
            bookStoresFile << std::get<1>(bookTuple)->getTitle() << std::endl;
            bookStoresFile << std::get<1>(bookTuple)->getCategoryNumber() << std::endl;
            bookStoresFile << std::get<1>(bookTuple)->getValue() << std::endl;
            bookStoresFile << std::get<0>(bookTuple) << std::endl;
        }
        bookStoresFile << "endBooks" << std::endl;

        for (const auto& rating : it.retrieve().getRatings())
            bookStoresFile << rating << std::endl;
        bookStoresFile << "endRatings" << std::endl;

        it.advance();
    }
    modTimeBookStores = time(nullptr);
    bookStoresFile.close();

    modTimeInfo = time(nullptr);
    infoFile << std::to_string(modTimeInfo) << std::endl
             << std::to_string(modTimeBooks) << std::endl
             << std::to_string(modTimeBookStores) << std::endl
             << std::to_string(modTimePeople) << std::endl
             << std::to_string(loanFee) << std::endl
             << std::to_string(delayPenalty) << std::endl;
    infoFile.close();
}

//----------------------------------------------------------------------------------------------------------------

float Club::getDelayPenalty() const {return delayPenalty;}

//----------------------------------------------------------------------------------------------------------------

float Club::getLoanFee() const {return loanFee;}

//----------------------------------------------------------------------------------------------------------------

void Club::addPerson(Person *person) {people.push_back(person);}

//----------------------------------------------------------------------------------------------------------------

void Club::removePerson(Person *person)
{
    auto it = std::find(people.begin(), people.end(), person);
    people.erase(it);
}

//----------------------------------------------------------------------------------------------------------------

void Club::addBook(Book *book) {catalog.push_back(book);}

//----------------------------------------------------------------------------------------------------------------

void Club::removeBook(Book *book)
{
    auto it = std::find(catalog.begin(), catalog.end(), book);
    catalog.erase(it);
}

//----------------------------------------------------------------------------------------------------------------

std::vector<Book*> Club::getCatalog() const {return catalog;}

//----------------------------------------------------------------------------------------------------------------

std::vector<Person*> Club::getPeople() const {return people;}

//----------------------------------------------------------------------------------------------------------------

Person * Club::getPersonById(unsigned int id)
{
    auto it = std::find_if(people.begin(), people.end(), [&id](Person *person){return person->getID() == id;});
    if (it != people.end())
        return *it;
    else
        return nullptr;
}

//----------------------------------------------------------------------------------------------------------------

Book * Club::getBookById(unsigned int id)
{
    auto it = std::find_if(catalog.begin(), catalog.end(), [&id](Book *book){return book->getBookId() == id;});
    if (it != catalog.end())
        return *it;
    else
        return nullptr;
}

//----------------------------------------------------------------------------------------------------------------

void Club::updateBookID(unsigned int id)
{
    for (auto &book : catalog )
    {
        if (book->getBookId() > id)
            book->setBookId(book->getBookId()-1);
    }
}

//----------------------------------------------------------------------------------------------------------------

void Club::addBookStore(BookStore* b){ bookStores.insert(*b);}

//----------------------------------------------------------------------------------------------------------------

BookStore Club::findBookStore(BookStore *b)
{
    BSTItrIn<BookStore> itr(bookStores);
    while(!itr.isAtEnd())
    {
        if (itr.retrieve().getName() == b->getName() && itr.retrieve().getPlace() == b->getPlace())
        {
            return itr.retrieve();
        }
        itr.advance();
    }
    return BookStore("","");
}

//----------------------------------------------------------------------------------------------------------------

BST<BookStore> Club::getBookStores(){ return bookStores; }

//----------------------------------------------------------------------------------------------------------------

void Club::removeBookStore(BookStore* b) {bookStores.remove(*b);}

//----------------------------------------------------------------------------------------------------------------

void Club::addPersonRecord(PersonRecords personRecord) {personPreferences.insert(personRecord);}

//----------------------------------------------------------------------------------------------------------------

void Club::updateEmailPersonRecord(std::string oldEmail, std::string newEmail)
{
    PersonRecords newPerson(newEmail);
    auto oldPerson = personPreferences.find(PersonRecords(oldEmail));
    for (const auto& category : oldPerson->getFavoritesCategories())
    {
        newPerson.addFavoriteCategory(category);
    }
    personPreferences.erase(oldPerson);
    personPreferences.insert(newPerson);
}

//----------------------------------------------------------------------------------------------------------------

unordered_set<PersonRecords, PersonRecordsHash, PersonRecordsHash> Club::getPersonPreferences() const {return personPreferences;}

//----------------------------------------------------------------------------------------------------------------

void Club::addPreference(unsigned int preference, std::string email)
{
    PersonRecords newPerson(email);
    auto oldPerson = personPreferences.find(PersonRecords(email));
    for (const auto& category : oldPerson->getFavoritesCategories())
    {
        newPerson.addFavoriteCategory(category);
    }
    newPerson.addFavoriteCategory(preference);
    personPreferences.erase(oldPerson);
    personPreferences.insert(newPerson);
}

//----------------------------------------------------------------------------------------------------------------

void Club::removePreference(unsigned int preference, std::string email)
{
    PersonRecords newPerson(email);
    auto oldPerson = personPreferences.find(PersonRecords(email));
    for (const auto& category : oldPerson->getFavoritesCategories())
    {
        if (category != preference)
            newPerson.addFavoriteCategory(category);
    }
    personPreferences.erase(oldPerson);
    personPreferences.insert(newPerson);
}

//----------------------------------------------------------------------------------------------------------------

bool Club::preferenceExists(unsigned int preferenceToSearch, std::string email)
{
    PersonRecords personSearch(email);
    auto personFound = personPreferences.find(PersonRecords(email));
    for (const auto& preference : personFound->getFavoritesCategories())
    {
        if (preference == preferenceToSearch)
            return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------
