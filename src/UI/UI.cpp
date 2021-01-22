#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <sys/stat.h>
#include "UI.h"
#include "../Utils/utils.h"
#include "../Exception/FileException/FileException.h"
#ifndef WIN32
#include <unistd.h>
#endif
#ifdef WIN32
#include <windows.h>
#define stat _stat
#endif

//----------------------------------------------------------------------------------------------------------------

int index = 0;

//----------------------------------------------------------------------------------------------------------------

void errorMessage()
{
    std::cin.clear();
    std::cerr << RED << "Error! Choose a valid input." << NO_COLOR << std::endl;
}

//----------------------------------------------------------------------------------------------------------------

void printBooksCategory()
{
    const char separator    = ' ';
    std::cout << std::left << std::setw(40)   << "1: Adventure"  << std::setw(40) << std::setfill(separator) << "10: Horror" << std::endl;
    std::cout << std::left << std::setw(40)  << "2: Arts" << std::setw(40) << std::setfill(separator) << "11: Kids" << std::endl;
    std::cout << std::left << std::setw(40)  << "3: Biography" << std::setw(40) << std::setfill(separator) << "12: Medical" << std::endl;
    std::cout << std::left << std::setw(40)  << "4: Comics" << std::setw(40) << std::setfill(separator) << "13: Romance" << std::endl;
    std::cout << std::left << std::setw(40) << "5: Cooking" << std::setw(40) << std::setfill(separator) << "14: Sci-Fi" << std::endl;
    std::cout << std::left << std::setw(40)  << "6: Crime" << std::setw(40) << std::setfill(separator) << "15: Science" << std::endl;
    std::cout << std::left << std::setw(40) << "7: Entertainment" << std::setw(40) << std::setfill(separator) << "16: Sports" << std::endl;
    std::cout << std::left << std::setw(40) << "8: Health" << std::setw(40) << std::setfill(separator) << "17: Suspense" << std::endl;
    std::cout << std::left << std::setw(40) << "9: History" << std::setw(40) << std::setfill(separator) << "18: Other" << std::endl << std::endl;
}

//----------------------------------------------------------------------------------------------------------------

void printOwnedBooks(const std::vector<Book*>& ownedBooks)
{
    std::cout << ".________________________." << std::endl;
    std::cout << "|     OWNED BOOKS        |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    for(const auto &book : ownedBooks)
    {
        const char separator = ' ';
        std::cout << "Id: " << std::left << std::setw(40) << std::setfill(separator) << book->getBookId()
                  <<"Title: " << book->getTitle() << std::endl
                  << "Is borrowed : " << book->getIsBorrowed() << std::endl << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------------

void printBorrowedBooks(const std::vector<Book*>& borrowedBooks)
{
    std::cout << ".________________________." << std::endl;
    std::cout << "|     BORROWED BOOKS     |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    for(const auto &book : borrowedBooks)
    {
        const char separator = ' ';
        std::cout << "Id: " << std::left << std::setw(40) << std::setfill(separator) << book->getBookId()
                  <<"Title: " << book->getTitle() << std::endl;
        if (book->getLoanTimeRemaining() >= 0)
            std::cout << "Loan days remaining: " << std::setprecision(0) << book->getLoanTimeRemaining()/86400 << std::endl << std::endl;
        else
            std::cout << "Loan days remaining: " << 0 << std::endl << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------------

void mainMenu(Club &c){

    std::cout << ".________________________." << std::endl;
    std::cout << "|         WELCOME        |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    std::string value;
    std::cout << "Show costumers              |1" << std::endl;
    std::cout << "Show catalog                |2" << std::endl;
    std::cout << "Show stores                 |3" << std::endl;
    std::cout << "Add a new costumer          |4" << std::endl;
    std::cout << "Add a new book              |5" << std::endl;
    std::cout << "Add a new book store        |6" << std::endl;
    std::cout << "Menu Book Store             |7" << std::endl;
    std::cout << "Borrow a book               |8" << std::endl;
    std::cout << "Renew loan                  |9" << std::endl;
    std::cout << "Return a book               |10" << std::endl;
    std::cout << "Claim loan book             |11" << std::endl;
    std::cout << "View Borrowed Books         |12" << std::endl;
    std::cout << "Remove a book               |13" << std::endl;
    std::cout << "Report a book loss          |14" << std::endl;
    std::cout << "Show Book Queue             |15" << std::endl;
    std::cout << "Menu Preferences            |16" << std::endl;
    std::cout << "Save info                   |17" << std::endl;
    std::cout << "Exit                        |-1" << std::endl << std::endl;
    std::cout << "Choose: ";
    while(std::getline(std::cin, value))
    {
        if (isNumeric(value) || value == "-1")
        {
            index = std::stoi(value);
            if(index == -1 || (index >=1 && index <= 17))
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Choose: ";
    }
    std::cout << CLEAR_SCREEN;
}

//----------------------------------------------------------------------------------------------------------------

void showBookQueue(Book* book){
    std::string value;
    auto queueTemp = book->getQueue();
    std::cout << ".________________________." << std::endl;
    std::cout << "|      WAITING LIST      |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    const char separator = ' ';
    while(queueTemp.size())
    {
        std::cout << "Id: " << std::left << std::setw(40) << std::setfill(separator) << queueTemp.top().getID()
                  << "Name: " << queueTemp.top().getName() << std::endl << "Is member: ";
        if (queueTemp.top().getIsMember())
            std::cout << "Yes" << std::endl << std::endl;
        else
            std::cout << "No" << std::endl << std::endl;
        queueTemp.pop();
    }
}

//----------------------------------------------------------------------------------------------------------------

void showPersonPreferences(Club& c, Person* person){
    std::string value;
    auto personPreferences = c.getPersonPreferences();
    auto personRecords = personPreferences.find(PersonRecords(person->getEmailAddress()));
    if (!personRecords->getFavoritesCategories().size())
    {
        std::cout << "This person has no preferences yet." << std::endl;
    }
    else
    {
        std::cout << ".________________________." << std::endl;
        std::cout << "|      Preferences       |" << std::endl;
        std::cout << ".________________________." << std::endl << std::endl;
        for (const auto& preference : personRecords->getFavoritesCategories())
        {
            switch(preference)
            {
                case 0:
                    std::cout << "1: Adventure" << std::endl;
                    break;
                case 1:
                    std::cout << "2: Arts" << std::endl;
                    break;
                case 2:
                    std::cout << "3: Biography" << std::endl;
                    break;
                case 3:
                    std::cout << "4: Comics" << std::endl;
                    break;
                case 4:
                    std::cout << "5: Cooking" << std::endl;
                    break;
                case 5:
                    std::cout << "6: Crime" << std::endl;
                    break;
                case 6:
                    std::cout << "7: Entertainment" << std::endl;
                    break;
                case 7:
                    std::cout << "8: Health" << std::endl;
                    break;
                case 8:
                    std::cout << "9: History" << std::endl;
                    break;
                case 9:
                    std::cout << "10: Horror" << std::endl;
                    break;
                case 10:
                    std::cout << "11: Kids" << std::endl;
                    break;
                case 11:
                    std::cout << "12: Medical" << std::endl;
                    break;
                case 12:
                    std::cout << "13: Romance" << std::endl;
                    break;
                case 13:
                    std::cout << "14: SciFi" << std::endl;
                    break;
                case 14:
                    std::cout << "15: Science" << std::endl;
                    break;
                case 15:
                    std::cout << "16: Sports" << std::endl;
                    break;
                case 16:
                    std::cout << "17: Suspense" << std::endl;
                    break;
                case 17:
                    std::cout << "18: Other" << std::endl;
                    break;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------

void showCostumersMenu(Club &c){
    std::string value;
    std::cout << ".________________________." << std::endl;
    std::cout << "|        COSTUMERS       |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    const char separator = ' ';
    for(const auto& person : c.getPeople())
    {
        std::cout << "Id: " << std::left << std::setw(40) << std::setfill(separator) << person->getID()
                  << "Name: " << person->getName()<< std::endl << "Is member: ";
        if (person->getIsMember())
            std::cout << "Yes" << std::endl;
        else
            std::cout << "No" << std::endl;
        std::cout << "Email: " << person->getEmailAddress() << std::endl << std::endl;
    }

    std::cout << "Press ENTER to return...";
    std::getline(std::cin, value); //only to acknowledge that the user pressed a key
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void showCatalogMenu(Club &c){
    std::cout << ".________________________." << std::endl;
    std::cout << "|         CATALOG        |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    std::string value;
    unsigned int count = 0;
    for(const auto& book : c.getCatalog())
    {
        const char separator = ' ';
        std::cout << "Id: "  << std::left << std::setw(40) << std::setfill(separator) << book->getBookId()
                  << "Title: " << book->getTitle() << std::endl;
        std::cout << "Category: " << std::left << std::setw(34) << std::setfill(separator) << book->getCategory();
        if (book->getRating() == -1)
            std::cout << "Rating: " << std::fixed << "No Rating" << std::endl;
        else
            std::cout << "Rating: " << std::fixed << std::setprecision(1) << book->getRating() << std::endl;
        std::cout << "Maximum loan time: " << std::left << std::setw(25) << std::setfill(separator)
                  << std::setprecision(0) << book->getMaximumLoanTime()/86400
                  << "Is Borrowed: ";
        if(book->getIsBorrowed())
            std::cout << "Yes" << std::endl;
        else
            std::cout << "No" << std::endl;
        if(!book->getComments().empty())
        {
            std::cout << "Comments: " << std::endl;
            std::vector<std::string> comments = book->getComments();
            for (std::vector<std::string>::const_reverse_iterator it = comments.rbegin(); it!= comments.rend(); ++it)
            {
                if (count < 10)
                {
                    std::cout << *(it) << std::endl;
                    count++;
                }
                else
                {
                    break;
                }
            }
            count = 0;
        }
        std::cout << std::endl;
    }
    std::cout << "Press ENTER to return...";
    std::getline(std::cin, value);
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void showBookStoresMenu(Club &c){
    std::cout << ".________________________." << std::endl;
    std::cout << "|         STORES         |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    std::string value;
    BST<BookStore> bs = c.getBookStores();
    BSTItrIn<BookStore> it(bs);
    const char separator = ' ';
    while(!it.isAtEnd())
    {
        std::cout << "Name: "  << std::left << std::setw(40) << std::setfill(separator) << it.retrieve().getName()
                  << "Location: " << it.retrieve().getPlace() << std::endl;
        std::cout << "Promotion: "  << std::left << std::setw(35) << std::setfill(separator) << it.retrieve().getPromotion()
                  << "Discount Code: " << it.retrieve().getDiscountCode() << std::endl;
        if (it.retrieve().getRating() == -1)
            std::cout << "Rating: " << std::fixed << "No Rating" << std::endl << std::endl;
        else
            std::cout << "Rating: " << std::fixed << std::setprecision(1) << it.retrieve().getRating() << std::endl << std::endl;
        std::cout << "Available Books:" << std::endl << std::endl;
        for (const auto& bookTuple : it.retrieve().getStock())
        {
            std::cout << "Title: "  << std::left << std::setw(40) << std::setfill(separator) << std::get<1>(bookTuple)->getTitle()
                      << "Category: " << std::get<1>(bookTuple)->getCategory() << std::endl;
            std::cout << "Price: "  << std::left << std::setw(40) << std::setfill(separator) << std::fixed << std::setprecision(2) << std::get<1>(bookTuple)->getValue()
                      << "Copies: " << std::get<0>(bookTuple) << std::endl << std::endl;
        }
        it.advance();
    }
    std::cout << "Press ENTER to return...";
    std::getline(std::cin, value);
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

bool addBookMenu(Club &c, int i){
    std::string title;
    std::string category;
    std::string owner;
    std::string value;
    std::string days;
    Member* ptrMember;
    Book* book;
    unsigned int newSize;
    bool success = false;
    std::cout << "Book's title: ";
    while(std::getline(std::cin, title))
    {
        if (title == "-1")
        {
            goto END;
        }
        if (!title.empty() && title.size() <= 30)
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Book's title: ";
        }
    }
    std::cout << std::endl;
    printBooksCategory();
    std::cout << "Book's category (from 1-18): ";
    while(std::getline(std::cin, category))
    {
        if (category == "-1")
        {
            goto END;
        }
        if (isNumeric(category))
        {
            if(std::stoi(category) >= 1 && std::stoi(category) <= 18)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Book's category (from 1-18): ";
    }
    if(i==-1){
        std::cout << CLEAR_SCREEN;
        showCostumersMenu(c);
        std::cout << "Book's owner by ID: ";
        bool found = false;
        while(std::getline(std::cin, owner))
        {
            if (owner == "-1")
            {
                goto END;
            }
            if (isNumeric(owner))
            {
                for(auto& person : c.getPeople())
                {
                    if (person->getID() == std::stoi(owner))
                    {
                        ptrMember = dynamic_cast<Member*>(person);
                        if (ptrMember != nullptr)
                            found = true;
                    }
                }
                if (found)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's owner by ID: ";
        }
    } else {
        owner = std::to_string(i);
    }
    std::cout << "Book's value in euros: ";
    while(std::getline(std::cin, value))
    {
        if (value == "-1")
        {
            goto END;
        }
        if (isFloat(value))
        {
            if (std::stof(value) > 0)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Book's value in euros: ";
    }
    std::cout << "How many days can the book be borrowed: ";
    while(std::getline(std::cin, days))
    {
        if (days == "-1")
        {
            goto END;
        }
        if (isNumeric(days))
        {
            if (std::stoi(days) > 10)
            {
                break;
            }
            else
            {
                std::cin.clear();
                std::cerr << RED << "Error! Must have at least a 10 days loan." << NO_COLOR << std::endl;
                std::cout << "How many days can be borrowed: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "How many days can the book be borrowed: ";
        }
    }
    book = new Book();
    book->setTitle(title);
    book->setOwner(std::stoi(owner));
    book->setIsBorrowed(false);
    book->setLoanRenew(false);
    book->setValue(std::stof(value));
    book->setCategory(std::stoi(category)-1);
    book->setMaximumLoanTime(std::stoi(days)*86400);
    c.addBook(book);
    success = true;
    dynamic_cast<Member*>(c.getPersonById(std::stoi(owner)))->addOwnedBook(book);
    newSize = c.getPersonById(std::stoi(owner))->getOwnedBooksSize() + 1;
    c.getPersonById(std::stoi(owner))->setOwnedBooksSize(newSize);
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, value);
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
    return success;
}

//----------------------------------------------------------------------------------------------------------------

void addCostumerMenu(Club &c)
{
    std::string name;
    std::string email;
    std::string membership;
    std::string nrBooks;
    std::cout << "Costumer's name: ";
    while(std::getline(std::cin, name))
    {
        if (name == "-1")
        {
            goto END;
        }
        if (!name.empty() && name.size() < 30)
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Costumer's name: ";
        }
    }
    std::cout << "Costumer's email: ";
    while(std::getline(std::cin, email))
    {
        if (name == "-1")
        {
            goto END;
        }
        if (!email.empty() && email.size() < 50)
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Costumer's email: ";
        }
    }
    std::cout << "Is this costumer a member? (y/n): ";
    while(std::getline(std::cin, membership))
    {
        if (membership == "-1")
        {
            goto END;
        }
        if (membership == "yes" || membership == "y" || membership == "Yes"
            || membership == "no" || membership == "n" || membership == "No")
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Is this costumer a member? (y/n): ";
        }
    }
    if(membership == "y" || membership == "yes" || membership == "Yes"){
        Member *m = new Member();
        m->setIsMember(true);
        m->setName(name);
        m->setEmailAddress(email);
        std::cout << "How many books: ";
        while(std::getline(std::cin, nrBooks))
        {
            if (nrBooks == "-1")
            {
                delete m;
                goto END;
            }
            if (isNumeric(nrBooks) && !(nrBooks == "0"))
            {
                break;
            }
            else
            {
                errorMessage();
                std::cout << "How many books: ";
            }
        }
        bool atLeastOne = false;
        c.addPerson(m);
        for(int i=0; std::stoi(nrBooks) > i; ++i)
        {
            std::cout << CLEAR_SCREEN;
            bool returnValue = addBookMenu(c, m->getID());
            if (returnValue)
            {
                atLeastOne = true;
            }
        }
        if (!atLeastOne)
        {
            c.removePerson(m);
            m->updatePersonStaticId();
            delete m;
        }
        else
        {
            m->setOwnedBooksSize(m->getOwnedBooks().size());
            PersonRecords personRecord(email);
            c.addPersonRecord(personRecord);
        }
        goto END;
    }
    else
    {
        NonMember *nm = new NonMember();
        c.addPerson(nm);
        nm->setIsMember(false);
        nm->setName(name);
        nm->setEmailAddress(email);
        PersonRecords personRecord(email);
        c.addPersonRecord(personRecord);
    }
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, name); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void addBookStoreMenu(Club &c)
{
    std::string bookStoreInfo;
    std::string bookInfo;
    bool success = false;
    unordered_set<std::string> titles;
    BookStore* bookStore = new BookStore("", "");
    std::cout << "Book Store's name: ";
    while(std::getline(std::cin, bookStoreInfo))
    {
        if (bookStoreInfo == "-1")
        {
            goto END;
        }
        if (!bookStoreInfo.empty() && bookStoreInfo.size() < 30)
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Book Store's name: ";
        }
    }
    bookStore->setName(bookStoreInfo);
    std::cout << "Book Store's location: ";
    while(std::getline(std::cin, bookStoreInfo))
    {
        if (bookStoreInfo == "-1")
        {
            goto END;
        }
        if (!bookStoreInfo.empty() && bookStoreInfo.size() < 30)
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Book Store's location: ";
        }
    }
    bookStore->setPlace(bookStoreInfo);
    std::cout << "Book Store's promotion: ";
    while(getline(std::cin, bookStoreInfo))
    {
        if (isFloat(bookStoreInfo))
        {
            if (stof(bookStoreInfo) >= 0 && std::stof(bookStoreInfo) <= 1)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Book Store's promotion: ";
    }
    bookStore->setPromotion(std::stof(bookStoreInfo));
    std::cout << "Book Store's discount code: ";
    while(std::getline(std::cin, bookStoreInfo))
    {
        if (bookStoreInfo == "-1")
        {
            goto END;
        }
        if (!bookStoreInfo.empty() && bookStoreInfo.size() < 8)
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "Book Store's discount code: ";
        }
    }
    bookStore->setDiscountCode(bookStoreInfo);
    std::cout << "How many books (Copies doesn't count): ";
    while(std::getline(std::cin, bookStoreInfo))
    {
        if (bookStoreInfo == "-1")
        {
            goto END;
        }
        if (isNumeric(bookStoreInfo) && !(bookStoreInfo == "0"))
        {
            break;
        }
        else
        {
            errorMessage();
            std::cout << "How many books (Copies doesn't count): ";
        }
    }
    for (int i = 0; i < std::stoi(bookStoreInfo); ++i)
    {
        std::cout << CLEAR_SCREEN;
        Book* book = new Book();
        std::cout << "Book's Title: ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (!bookInfo.empty() && bookInfo.size() < 30)
            {
                if (titles.find(bookInfo) == titles.end())
                {
                    titles.insert(bookInfo);
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's Title: ";
        }
        book->setTitle(bookInfo);
        std::cout << std::endl;
        printBooksCategory();
        std::cout << "Book's category (from 1-18): ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (isNumeric(bookInfo))
            {
                if(std::stoi(bookInfo) >= 1 && std::stoi(bookInfo) <= 18)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's category (from 1-18): ";
        }
        book->setCategory(std::stoi(bookInfo));
        std::cout << "Book's value in euros: ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (isFloat(bookInfo))
            {
                if (std::stof(bookInfo) > 0)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's value in euros: ";
        }
        book->setValue(std::stof(bookInfo));
        std::cout << "Book's copies: ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (isNumeric(bookInfo))
            {
                if (std::stoi(bookInfo) > 0)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's copies: ";
        }
        bookStore->addBook(std::stoi(bookInfo),book);
    }
    success = true;
    END:
    if (success)
        c.addBookStore(bookStore);
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void showMenuBookStores(Club &c, BookStore &bookStore, BookStore &bookStoreFound)
{
    int index2 = 0;
    std::string input;
    std::string bookInfo;
    std::cout << ".________________________." << std::endl;
    std::cout << "|    Menu Book Store     |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    std::string value;
    std::cout << "Add Rating              |1" << std::endl;
    std::cout << "Edit stock from book    |2" << std::endl;
    std::cout << "Add Book                |3" << std::endl;
    std::cout << "Exit                    |-1" << std::endl << std::endl;

    std::cout << "Choose: ";
    while (std::getline(std::cin, value)) {
        if (isNumeric(value) || value == "-1") {
            index2 = std::stoi(value);
            if (index2 == -1 || (index2 >= 1 && index2 <= 3)) {
                break;
            }
        }
        errorMessage();
        std::cout << "Choose: ";
    }
    std::cout << CLEAR_SCREEN;
    if (index2 == 1) {
        std::cout << "Book Store's rating: ";
        while (std::getline(std::cin, input)) {
            if (input == "-1") {
                goto END;
            }
            if (isNumeric(input)) {
                if (std::stoi(input) >= 0 && std::stoi(input) <= 5) {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book Store's rating: ";
        }
        bookStore.addRating(std::stoi(input));
        c.removeBookStore(&bookStoreFound);
        c.addBookStore(&bookStore);
    }
    if (index2 == 2)
    {
        std::cout << "Book title to edit stock: ";
        while (std::getline(std::cin, bookInfo)) {
            if (input == "-1") {
                goto END;
            }
            if (!bookInfo.empty())
            {
                for (auto& tuple : bookStoreFound.getStock())
                {
                    if (std::get<1>(tuple)->getTitle() == bookInfo)
                    {
                        std::cout << "Book's new stock: ";
                        while(std::getline(std::cin, input))
                        {
                            if (input == "-1")
                            {
                                goto END;
                            }
                            if (isNumeric(input))
                            {
                                bookStore.editBookCopies(bookInfo,std::stoi(input));
                                c.removeBookStore(&bookStoreFound);
                                c.addBookStore(&bookStore);
                                goto END;
                            }
                            errorMessage();
                            std::cout << "Book's new stock: ";
                        }
                    }
                }
            }
            errorMessage();
            std::cout << "Book title to edit stock: ";
        }
    }
    if (index2 == 3)
    {
        std::cout << CLEAR_SCREEN;
        Book* book = new Book();
        std::cout << "Book's Title: ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (!bookInfo.empty() && bookInfo.size() < 30)
            {
                bool found = false;
                for (const auto& tuple : bookStoreFound.getStock())
                {
                    if (std::get<1>(tuple)->getTitle() == bookInfo)
                    {
                        found = true;
                    }
                }
                if (!found)
                {
                    break;
                }
            }
            else
            {
                errorMessage();
                std::cout << "Book's Title: ";
            }
        }
        book->setTitle(bookInfo);
        std::cout << std::endl;
        printBooksCategory();
        std::cout << "Book's category (from 1-18): ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (isNumeric(bookInfo))
            {
                if(std::stoi(bookInfo) >= 1 && std::stoi(bookInfo) <= 18)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's category (from 1-18): ";
        }
        book->setCategory(std::stoi(bookInfo));
        std::cout << "Book's value in euros: ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (isFloat(bookInfo))
            {
                if (std::stof(bookInfo) > 0)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's value in euros: ";
        }
        book->setValue(std::stof(bookInfo));
        std::cout << "Book's copies: ";
        while(std::getline(std::cin, bookInfo))
        {
            if (bookInfo == "-1")
            {
                goto END;
            }
            if (isNumeric(bookInfo))
            {
                if (std::stoi(bookInfo) > 0)
                {
                    break;
                }
            }
            errorMessage();
            std::cout << "Book's copies: ";
        }
        bookStore.addBook(std::stoi(bookInfo),book);
        c.removeBookStore(&bookStoreFound);
        c.addBookStore(&bookStore);
    }
    END:;
}

//----------------------------------------------------------------------------------------------------------------

void MenuBookStore(Club &c)
{
    std::string name;
    std::string location;
    BookStore bookStore;
    BookStore bookStoreNotFound("","");
    BookStore bookStoreFound;
    while(true) {
        std::cout << CLEAR_SCREEN;
        showBookStoresMenu(c);
        std::cout << "Book Store's name: ";
        while (std::getline(std::cin, name)) {
            if (name == "-1") {
                goto END;
            }
            if (name.size()) {
                break;
            }
            errorMessage();
            std::cout << "Book Store's name: ";
        }
        std::cout << "Book Store's location: ";
        while (std::getline(std::cin, location)) {
            if (name == "-1") {
                goto END;
            }
            if (location.size()) {
                break;
            }
            errorMessage();
            std::cout << "Book Store's location: ";
        }
        bookStore.setName(name);
        bookStore.setPlace(location);

        bookStoreFound = c.findBookStore(&bookStore);
        if (bookStoreFound != bookStoreNotFound) {
            bookStore.addStock(bookStoreFound.getStock());
            bookStore.setDiscountCode(bookStoreFound.getDiscountCode());
            bookStore.setPromotion(bookStoreFound.getPromotion());
            for (const auto &rating : bookStoreFound.getRatings())
                bookStore.addRating(rating);
            std::cout << CLEAR_SCREEN;
            showMenuBookStores(c, bookStore, bookStoreFound);
            break;
        }
        else
        {
            std::cout << RED << "The Book Store doesn't exist" << NO_COLOR << std::endl;
            #ifdef WIN32
            Sleep(5000);
            #else
            sleep(5);
            #endif
        }
    }
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void borrowBookMenu(Club &c)
{
    std::string personID;
    std::string bookID;
    std::string loanDays;
    Person* ptrPerson;
    Book* ptrBook;
    showCostumersMenu(c);
    std::cout << "Person ID that will borrow the book: ";
    while(std::getline(std::cin, personID))
    {
        if (personID == "-1")
        {
            goto END;
        }
        if (isNumeric(personID))
        {
            ptrPerson = c.getPersonById(std::stoi(personID));
            if (ptrPerson != nullptr)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Person ID that will borrow the book: ";
    }
    std::cout << CLEAR_SCREEN;
    showCatalogMenu(c);
    std::cout << "Book ID that will be borrowed: ";
    while(std::getline(std::cin, bookID))
    {
        if (bookID == "-1")
        {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = c.getBookById(std::stoi(bookID));
            if (ptrBook != nullptr)
                break;
            else
            {
                errorMessage();
                std::cout << "Book ID that will be borrowed: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book ID that will be borrowed: ";
        }
    }
    std::cout << "How many days does the person want to borrow the book: ";
    while(std::getline(std::cin, loanDays))
    {
        if (loanDays == "-1")
        {
            goto END;
        }
        if (isNumeric(loanDays))
        {
            unsigned int returnValue = ptrPerson->borrowBook(ptrBook, std::stoi(loanDays));
            if (returnValue == 0)
            {
                std::cout << "The book was successfully borrowed!" << std::endl;
                if (!ptrPerson->getIsMember())
                    std::cout << "Value to pay:" << c.getLoanFee()*ptrBook->getValue() << std::endl;
                break;
            }
            else if (returnValue == 1)
            {
                errorMessage();
                std::cout << "How many days does the person want to borrow the book: ";
            }
            else if (returnValue == 2)
            {
                std::cout << "The person was added to a waiting List! (Loan days were not saved)." << std::endl;
                break;
            }
        }
        else
        {
            errorMessage();
            std::cout << "How many days does the person want to borrow the book: ";
        }
    }
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void renewLoanTimeMenu(Club &c)
{
    std::string personID;
    std::string bookID;
    Person* ptrPerson;
    Member* ptrMember;
    Book* ptrBook;
    showCostumersMenu(c);
    std::cout << "Person ID to renew loan time: ";
    while(std::getline(std::cin, personID))
    {
        if (personID == "-1")
        {
            goto END;
        }
        if (isNumeric(personID))
        {
            ptrPerson = c.getPersonById(std::stoi(personID));
            if (ptrPerson != nullptr)
            {
                ptrMember = dynamic_cast<Member*>(ptrPerson);
                if (!ptrPerson->getBorrowedBooks().empty() && ptrMember != nullptr)
                {
                    break;
                }
            }
        }
        errorMessage();
        std::cout << "Person ID to renew loan time: ";
    }
    printBorrowedBooks(ptrMember->getBorrowedBooks());
    std::cout << "Book ID to renew loan time: ";
    while(std::getline(std::cin, bookID))
    {
        if (bookID == "-1")
        {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = c.getBookById(std::stoi(bookID));
            if(ptrBook != nullptr)
            {
                if (ptrMember->searchBorrowedBook(ptrBook))
                {
                    if (!ptrBook->getLoanRenew()) //loan wasn't already renewed
                    {
                        break;
                    }
                    else
                    {
                        std::cin.clear();
                        std::cerr << RED << "Error! Book loan was already renewed." << NO_COLOR << std::endl;
                        std::cout << "Book ID to renew loan time: ";
                    }
                }
                else
                {
                    errorMessage();
                    std::cout << "Book ID to renew loan time: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Book ID to renew loan time: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book ID to renew loan time: ";
        }
    }
    ptrBook->setEndOfLoan(ptrBook->getEndOfLoan() + 7*86400);
    ptrBook->setLoanRenew(true);
    std::cout << "Loan was successfully renewed." << std::endl;
    std::cout << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;

}

//----------------------------------------------------------------------------------------------------------------

void returnBookMenu(Club &c)
{
    std::string personID;
    std::string bookID;
    std::string rating;
    std::string comment;
    Person* ptrPerson;
    Book* ptrBook;
    std::vector<Book*> borrowedBooks;
    double valueToPay;
    showCostumersMenu(c);
    std::cout << "Person ID that will return the book: ";
    while(std::getline(std::cin, personID))
    {
        if (personID == "-1")
        {
            goto END;
        }
        if (isNumeric(personID))
        {
            ptrPerson = c.getPersonById(std::stoi(personID));
            if (ptrPerson != nullptr)
            {
                borrowedBooks = ptrPerson->getBorrowedBooks();
                if(!borrowedBooks.empty())
                {
                    break;
                }
            }
        }
        errorMessage();
        std::cout << "Person ID that will return the book: ";
    }
    std::cout << CLEAR_SCREEN;
    printBorrowedBooks(borrowedBooks);
    std::cout << "Book ID that will be returned: ";
    while(std::getline(std::cin, bookID))
    {
        if (bookID == "-1")
        {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = ptrPerson->getBookFromBorrowedBooks(std::stoi(bookID));
            if (ptrBook != nullptr)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Book ID that will be returned: ";
    }
    std::cout << "Add a rating to the book(0-5). Press Enter for no rating: ";
    while(std::getline(std::cin, rating)) {
        if (rating == "-1")
        {
            goto END;
        }
        if (rating.empty())
        {
            break;
        }
        if (rating == "0" || rating == "1" || rating == "2" || rating == "3" || rating == "4" || rating =="5")
        {
            ptrBook->addRating(std::stoi(rating));
            break;
        }
        errorMessage();
        std::cout << "Add a rating to the book(0-5). Press Enter for no rating: ";
    }
    std::cout << std::endl << "Add a comment to the book(max 100 characters). Press Enter for no comment: ";
    while(std::getline(std::cin, comment))
    {
        if (comment == "-1")
        {
            goto END;
        }
        if (comment.empty())
        {
            break;
        }
        if (comment.size() <= 100)
        {
            ptrBook->addComment(comment);
            break;
        }
        errorMessage();
        std::cout << "Add a rating to the book(max 100 characters). Press Enter for no comment: ";
    }
    valueToPay = ptrPerson->returnBook(c, ptrBook);
    if (valueToPay == 0.0)
    {
        std::cout << std::endl << "The book was returned in time. The person as nothing to pay." << std::endl << std::endl;
    }
    else
    {
        std::cout << std::endl << "The book was returned after the end time. The person as to pay " << valueToPay
                  << " €." << std::endl << std::endl;
    }
    std::cout << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void claimBookLoanMenu(Club &c)
{
    std::string personID;
    std::string bookID;
    Person* ptrPerson;
    Book* ptrBook;
    std::string loanDays;
    showCostumersMenu(c);
    std::cout << "Person ID to claim the book loan: ";
    while(std::getline(std::cin, personID))
    {
        if (personID == "-1")
        {
            goto END;
        }
        if (isNumeric(personID))
        {
            ptrPerson = c.getPersonById(std::stoi(personID));
            if (ptrPerson != nullptr)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Person ID to claim the book loan: ";
    }
    showCatalogMenu(c);
    std::cout << "Book ID to be claimed: ";
    while(std::getline(std::cin, bookID))
    {
        if (bookID == "-1")
        {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = c.getBookById(std::stoi(bookID));
            if (ptrBook != nullptr)
            {
                if (ptrBook->getQueueFront().getID() == ptrPerson->getID())
                {
                    break;
                }
            }
        }
        errorMessage();
        std::cout << "Book ID to be claimed: ";
    }
    std::cout << "How many days does the person want to borrow the book: ";
    while(std::getline(std::cin, loanDays))
    {
        if (loanDays == "-1")
        {
            goto END;
        }
        if (isNumeric(loanDays))
        {
            unsigned int returnValue = ptrPerson->borrowBook(ptrBook, std::stoi(loanDays));
            if (returnValue == 0)
            {
                std::cout << "The book was successfully borrowed!" << std::endl;
                if(!ptrPerson->getIsMember())
                    std::cout << "Value to pay: " << c.getLoanFee()*ptrBook->getValue() << std::endl;
                ptrBook->manageQueue();
                break;
            }
            else if (returnValue == 1)
            {
                errorMessage();
                std::cout << "How many days does the person want to borrow the book: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "How many days does the person want to borrow the book: ";
        }
    }
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void viewBorrowedBooksMenu(Club &c)
{
    std::string personID;
    Person* ptrPerson;
    std::vector<Book*> borrowedBooks;
    showCostumersMenu(c);
    std::cout << "Person ID to view borrowed books: ";
    while(std::getline(std::cin, personID))
    {
        if (personID == "-1")
        {
            goto END;
        }
        if (isNumeric(personID))
        {
            ptrPerson = c.getPersonById(std::stoi(personID));
            if (ptrPerson != nullptr)
            {
                borrowedBooks = ptrPerson->getBorrowedBooks();
                if (!borrowedBooks.empty())
                {
                    break;
                }
                else
                {
                    std::cout << RED << "This person doesn't have any borrowed book." << NO_COLOR << std::endl;
                    goto END2;
                }
            }
        }
        errorMessage();
        std::cout << "Person ID to view borrowed books: ";
    }
    std::cout << CLEAR_SCREEN;
    printBorrowedBooks(borrowedBooks);
    END2:
    std::cout << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void removeBookMenu(Club &c)
{
    std::string personID;
    std::string bookID;
    Member* ptrMember;
    Book* ptrBook;
    showCostumersMenu(c);
    std::cout << "Person ID that wants to remove the book: ";
    while(std::getline(std::cin, personID))
    {
        if (personID == "-1")
        {
            goto END;
        }
        if (isNumeric(personID))
        {
            ptrMember = dynamic_cast<Member *>(c.getPersonById(std::stoi(personID)));
            if (ptrMember != nullptr) {
                break;
            }
        }
        errorMessage();
        std::cout << "Person ID that wants to remove the book: ";
    }
    std::cout << CLEAR_SCREEN;
    printOwnedBooks(ptrMember->getOwnedBooks());
    std::cout << "Book ID to be removed: ";
    while(std::getline(std::cin, bookID))
    {
        if (bookID == "-1")
        {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = c.getBookById(std::stoi(bookID));
            if (ptrBook != nullptr)
            {
                if (!ptrBook->getIsBorrowed() && ptrMember->searchOwnedBook(ptrBook))
                {
                    break;
                }
            }
        }
        errorMessage();
        std::cout << "Book ID to be removed: ";
    }
    c.updateBookID(ptrMember->removeOwnedBook(ptrBook));
    ptrMember->setOwnedBooksSize(ptrMember->getOwnedBooksSize()-1);
    c.removeBook(ptrBook);
    delete ptrBook;
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void reportBookLostMenu(Club& c)
{
    std::string bookID;
    float valueToPay;
    Book *ptrBook;
    Person* ptrPerson;
    Member* ptrMember;
    showCatalogMenu(c);
    std::cout << "Book ID that was lost: ";
    while (std::getline(std::cin, bookID)) {
        if (bookID == "-1") {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = c.getBookById(std::stoi(bookID));
            if (ptrBook != nullptr)
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Book ID that was lost: ";
    }
    valueToPay = ptrBook->getValue();
    ptrPerson = c.getPersonById(ptrBook->getOwner());
    ptrMember = dynamic_cast<Member*>(ptrPerson);
    ptrMember->removeOwnedBook(ptrBook);
    ptrPerson->setOwnedBooksSize(ptrPerson->getOwnedBooksSize()-1);
    c.removeBook(ptrBook);
    delete ptrBook;
    std::cout << std::endl << "Book value was " << valueToPay << " . This value must be payed to owner with ID: " << ptrMember->getID() << std::endl;
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, bookID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

unsigned int readInfoFile(float &loanFee, float &delayPenalty)
{
    std::string input;
    std::string infoFileString = "../src/Files/Info.txt";
    std::string booksFileString = "../src/Files/Books.txt";
    std::string bookStoresFileString = "../src/Files/BookStores.txt";
    std::string peopleFileString = "../src/Files/People.txt";
    struct stat result;
    unsigned long long int  modTimeInfo;
    unsigned long long int  modTimeBooks;
    unsigned long long int  modTimeBookStores;
    unsigned long long int  modTimePeople;
    std::ifstream infoFile(infoFileString);
    std::ifstream booksFile(booksFileString);
    std::ifstream bookStoresFile(bookStoresFileString);
    std::ifstream peopleFile(peopleFileString);
    if (!infoFile.is_open())
        throw FileNotFound("Info.txt");
    if (!booksFile.is_open())
        throw FileNotFound("Books.txt");
    if(!bookStoresFile.is_open())
        throw FileNotFound("BookStores.txt");
    if(!peopleFile.is_open())
        throw FileNotFound("People.txt");

    //getting the last modification time of the files
    if(!stat(infoFileString.c_str(), &result))
        modTimeInfo = result.st_mtime;
    if(!stat(booksFileString.c_str(), &result))
        modTimeBooks = result.st_mtime;
    if(!stat(bookStoresFileString.c_str(), &result))
        modTimeBookStores = result.st_mtime;
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
    std::getline(infoFile, input);
    if (!(std::stoi(input) == modTimeBooks))
        throw FileWasModified("Books.txt");
    std::getline(infoFile, input);
    if (!(std::stoi(input) == modTimeBookStores))
        throw FileWasModified("BookStores.txt");
    std::getline(infoFile, input);
    if (!(std::stoi(input) == modTimePeople))
        throw FileWasModified("People.txt");
    std::getline(infoFile,input);
    loanFee = std::stof(input);
    std::getline(infoFile,input);
    delayPenalty = std::stof(input);
    infoFile.close();
    booksFile.close();
    bookStoresFile.close();
    peopleFile.close();
    return 2;
}

//----------------------------------------------------------------------------------------------------------------

void BookQueueMenu(Club &c){
    std::string bookID;
    Book* ptrBook;
    std::cout << "Book ID to see the waiting list: ";
    while (std::getline(std::cin, bookID)) {
        if (bookID == "-1") {
            goto END;
        }
        if (isNumeric(bookID))
        {
            ptrBook = c.getBookById(std::stoi(bookID));
            if (ptrBook != nullptr)
            {
                if (!ptrBook->getQueueSize())
                {
                    std::cout << CLEAR_SCREEN;
                    std::cout << "This book's waiting list is empty." << std::endl << std::endl;
                    goto END;
                }
                else
                {
                    break;
                }
            }
        }
        errorMessage();
        std::cout << "Book ID to see the waiting list: ";
    }
    showBookQueue(ptrBook);
    END:
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, bookID); //only to acknowledge that the user pressed a key
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void showMenuPreferences(Club &c, Person* person)
{
    int index2 = 0;
    std::cout << ".________________________." << std::endl;
    std::cout << "|    Menu Preferences    |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    std::string value;
    std::cout << "Edit Email              |1" << std::endl;
    std::cout << "View Preferences        |2" << std::endl;
    std::cout << "Add Preference          |3" << std::endl;
    std::cout << "Remove Preference       |4" << std::endl;
    std::cout << "Exit                    |-1" << std::endl << std::endl;

    std::cout << "Choose: ";
    while(std::getline(std::cin, value))
    {
        if (isNumeric(value) || value == "-1")
        {
            index2 = std::stoi(value);
            if(index2 == -1 || (index2 >=1 && index2 <= 4))
            {
                break;
            }
        }
        errorMessage();
        std::cout << "Choose: ";
    }
    std::cout << CLEAR_SCREEN;
    if (index2 == 1)
    {
        std::cout << "Costumer's new email: ";
        while(std::getline(std::cin, value))
        {
            if (value == "-1")
            {
                goto END;
            }
            if (!value.empty() && value.size() < 50)
            {
                c.updateEmailPersonRecord(person->getEmailAddress(), value);
                person->setEmailAddress(value);

                break;
            }
            else
            {
                errorMessage();
                std::cout << "Costumer's new email: ";
            }
        }
    }
    if (index2 == 2)
    {
        showPersonPreferences(c, person);
        std::cout << std::endl << "Press ENTER to return...";
        std::getline(std::cin, value); //only to acknowledge that the user pressed a key
        std::cout << CLEAR_SCREEN;
    }
    if (index2 == 3)
    {
        printBooksCategory();
        std::cout << "Costumer's new preference: ";
        while(std::getline(std::cin, value))
        {
            if (value == "-1")
            {
                goto END;
            }
            if (isNumeric(value))
            {
                if (std::stoi(value) >= 1 && std::stoi(value) <= 18)
                {
                    c.addPreference(std::stoi(value)-1,person->getEmailAddress());
                    break;
                }
            }
            errorMessage();
            std::cout << "Costumer's new preference: ";
        }
    }
    if (index2 == 4)
    {
        showPersonPreferences(c, person);
        std::cout << std::endl << "Costumer's preference to remove: ";
        while(std::getline(std::cin, value))
        {
            if (value == "-1")
            {
                goto END;
            }
            if (isNumeric(value))
            {
                if (std::stoi(value) >= 1 && std::stoi(value) <= 18 && c.preferenceExists(std::stoi(value)-1, person->getEmailAddress()))
                {
                    c.removePreference(std::stoi(value)-1,person->getEmailAddress());
                    break;
                }
            }
            errorMessage();
            std::cout << "Costumer's preference to remove: ";
        }
    }
    END:;
}

//----------------------------------------------------------------------------------------------------------------

void MenuPreferences(Club &c)
{
    std::string personID;
    Person* ptrPerson;
    std::cout << CLEAR_SCREEN;
    showCostumersMenu(c);
    std::cout << "Person ID: ";
    while (std::getline(std::cin, personID))
    {
        if (personID == "-1") {
            goto END;
        }
        if (isNumeric(personID)) {
            ptrPerson = c.getPersonById(std::stoi(personID));
            if (ptrPerson != nullptr) {
                break;
            }
        }
        errorMessage();
        std::cout << "Person ID: ";
    }
    std::cout << CLEAR_SCREEN;
    showMenuPreferences(c, ptrPerson);
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

//----------------------------------------------------------------------------------------------------------------

void saveInfo(Club& c)
{
    std::string answer;
    try
    {
        c.writeFile();
    }
    catch(FileNotFound &e)
    {
        std::cout << RED << "The file: " << e.getFileName() << " wasn't found." << NO_COLOR << std::endl;
        std::cout << "The program can't proceed while the file is not restored." << std::endl;
        std::cout << "(If yes, the program will create new blank files, if not, the program will close and you have to restore the file in the correct directory, i.e ../src/Files/)" << std::endl;
        std::cout << "Do you want the program to create new files: ";
        while(std::getline(std::cin,answer))
        {
            if (answer == "y" || answer == "yes" || answer == "Y" || answer == "Yes")
            { //opens files deleting every thing in them and if any of the files isn't opened it will create it
                std::ofstream infoFile("../src/Files/Info.txt", std::ios::trunc);
                std::ofstream booksFile("../src/Files/Books.txt", std::ios::trunc);
                std::ofstream peopleFile("../src/Files/People.txt", std::ios::trunc);
                std::ofstream bookStoreFile("../src/Files/BookStores.txt", std::ios::trunc);
                infoFile.close();
                booksFile.close();
                peopleFile.close();
                bookStoreFile.close();
                exit(-1);
            }
            else if (answer == "n" || answer == "no" || answer == "N" || answer == "No")
            {
                exit(-1);
            }
            else
            {
                errorMessage();
                std::cout << "Do you want the program to create new files: ";
            }
        }
    }
    std::cout << "Info was successfully saved into files." << std::endl;
    #ifdef WIN32
    Sleep(5000);
    #else
    sleep(5);
    #endif

    index = 0;
    std::cout << CLEAR_SCREEN;
}

//----------------------------------------------------------------------------------------------------------------

void menu(Club &c){
    if(index == 0) mainMenu(c);
    if(index == 1) showCostumersMenu(c);
    if(index == 2) showCatalogMenu(c);
    if(index == 3) showBookStoresMenu(c);
    if(index == 4) addCostumerMenu(c);
    if(index == 5) addBookMenu(c,-1);
    if (index == 6) addBookStoreMenu(c);
    if (index == 7) MenuBookStore(c);
    if(index == 8) borrowBookMenu(c);
    if(index == 9) renewLoanTimeMenu(c);
    if(index == 10) returnBookMenu(c);
    if(index == 11) claimBookLoanMenu(c);
    if(index == 12) viewBorrowedBooksMenu(c);
    if(index == 13) removeBookMenu(c);
    if (index == 14) reportBookLostMenu(c);
    if (index == 15) BookQueueMenu(c);
    if (index == 16) MenuPreferences(c);
    if (index == 17) saveInfo(c);
}

//----------------------------------------------------------------------------------------------------------------

void MenuBeginning()
{
    float loanFee;
    float delayPenalty;
    unsigned int returnValue;
    std::string answer;
    try
    {
        returnValue = readInfoFile(loanFee,delayPenalty);
    }
    catch(FileNotFound &e)
    {
        std::cout << RED << "The file: " << e.getFileName() << " wasn't found." << NO_COLOR << std::endl;
        std::cout << "The program can't proceed while the file is not restored." << std::endl;
        std::cout << "(If yes, the program will crate new blank files, if not, the program will close and you have to restore the file in the correct directory, i.e ../src/Files/)" << std::endl;
        std::cout << "Do you want the program to create new files: ";
        while(std::getline(std::cin,answer))
        {
            if (answer == "y" || answer == "yes" || answer == "Y" || answer == "Yes")
            { //opens files deleting every thing in them and if any of the files isn't opened it will create it
                std::ofstream infoFile("../src/Files/Info.txt", std::ios::trunc);
                std::ofstream booksFile("../src/Files/Books.txt", std::ios::trunc);
                std::ofstream booksStoresFile("../src/Files/BookStores.txt", std::ios::trunc);
                std::ofstream peopleFile("../src/Files/People.txt", std::ios::trunc);
                infoFile.close();
                booksFile.close();
                booksStoresFile.close();
                peopleFile.close();
                exit(-1);
            }
            else if (answer == "n" || answer == "no" || answer == "N" || answer == "No")
            {
                exit(-1);
            }
            else
            {
                errorMessage();
                std::cout << "Do you want the program to create new files: ";
            }
        }    std::cout << "Info was saved successfully to the files.";
    }
    catch(FileWasModified &e)
    {
        std::cout << RED <<  "The file: " << e.getFileModifiedName() << " was modified." << NO_COLOR << std::endl;
        std::cout << "The program would not be able to work again because one of the file doesn't have the right information.";
        std::cout << " New files will be created, but all the old info will be lost." << std::endl << std::endl;
        std::ofstream infoFile("../src/Files/Info.txt", std::ios::trunc);
        std::ofstream booksFile("../src/Files/Books.txt", std::ios::trunc);
        std::ofstream booksStoresFile("../src/Files/BookStores.txt", std::ios::trunc);
        std::ofstream peopleFile("../src/Files/People.txt", std::ios::trunc);
        infoFile.close();
        booksFile.close();
        booksStoresFile.close();
        peopleFile.close();
        std::cout << "Press ENTER to return...";
        std::getline(std::cin, answer); //only to acknowledge that the user pressed a key
        exit(-1);
    }
    if (returnValue == 1)
    {
        std::cout << CLEAR_SCREEN;
        std::cout << "Choose the club's loan fee: ";
        while(getline(std::cin, answer))
        {
            if (isFloat(answer))
            {
                if (stof(answer) >= 0 && std::stof(answer) <= 1)
                {
                    loanFee = std::stof(answer);
                     break;
                }
            }
            errorMessage();
            std::cout << "Choose the club's loan fee: ";
        }
        std::cout << "Choose the club's delay penalty: ";
        while(getline(std::cin, answer))
        {
            if (isFloat(answer))
            {
                if (stof(answer) >= 0 && std::stof(answer) <= 1)
                {
                    delayPenalty = std::stof(answer);
                    break;
                }
            }
            errorMessage();
            std::cout << "Choose the club's delay penalty: ";
        }
        std::cout << CLEAR_SCREEN;
    }
    Club club(loanFee,delayPenalty);
    club.readFile();
    std::cout << CLEAR_SCREEN;
    while(index != -1)
        menu(club);
    saveInfo(club);
}

//----------------------------------------------------------------------------------------------------------------
