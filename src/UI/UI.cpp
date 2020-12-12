#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "UI.h"
#include "utils.h"


int index = 0;

/**
 * Will check is the string passed is a integer
 * @param str The string to confirm if is a integer
 * @return Bool if the string is a integer, false otherwise
 */

bool isNumeric(std::string& str)
{
    if (str.empty()) return false;
    return std::all_of(str.begin(),str.end(),[](char i){return isdigit(i);});
}

/**
 * Will check is the string passed is a float
 * @param str The string to confirm if is a float
 * @return Bool if the string is a float, false otherwise
 */

bool isFloat(std::string& str) {
    std::istringstream iss(str);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

/**
 * Will print to the screen an Error message in red colour
 */

void errorMessage()
{
    std::cin.clear();
    std::cerr << RED << "Error! Choose a valid input." << NO_COLOR << std::endl;
}

/**
 * Will print to the screen every book's category possible
 */

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

/**
 * Will print to the screen the owned books passed by reference
 * @param ownedBooks Vector containing the books to be printed to the screen
 */

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

/**
 * Will print to the screen the borrowed books passed by reference
 * @param borrowedBooks Vector containing the books to be printed to the screen
 */

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

/**
 * Will print to the screen every possible operation by the user,
 * and then ask the user to input an operation and check if it is a valid input
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

void mainMenu(Club &c){

    std::cout << ".________________________." << std::endl;
    std::cout << "|         WELCOME        |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    std::string value;
    std::cout << "Show costumers          |1" << std::endl;
    std::cout << "Show catalog            |2" << std::endl;
    std::cout << "Add a new costumer      |3" << std::endl;
    std::cout << "Add a new book          |4" << std::endl;
    std::cout << "Borrow a book           |5" << std::endl;
    std::cout << "Renew loan              |6" << std::endl;
    std::cout << "Return a book           |7" << std::endl;
    std::cout << "Claim loan book         |8" << std::endl;
    std::cout << "View Borrowed Books     |9" << std::endl;
    std::cout << "Remove a book           |10" << std::endl;
    std::cout << "Report a book loss      |11" << std::endl;
    std::cout << "Exit                    |-1" << std::endl << std::endl;

    std::cout << "Choose: ";
    while(std::getline(std::cin, value))
    {
        if (isNumeric(value) || value == "-1")
        {
            index = std::stoi(value);
            if(index == -1 || (index >=0 && index <= 11))
            {
                break;
            }
            else
            {
                errorMessage();
                std::cout << "Choose: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Choose: ";
        }
    }
    std::cout << CLEAR_SCREEN;
}

/**
 * Will print to the screen every costumer (people) from the club
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

void showCostumersMenu(Club &c){
    std::string value;
    std::cout << ".________________________." << std::endl;
    std::cout << "|        COSTUMERS       |" << std::endl;
    std::cout << ".________________________." << std::endl << std::endl;

    const char separator = ' ';
    for(const auto& person : c.getPeople())
        std::cout << "Id: " << std::left << std::setw(40) << std::setfill(separator) << person->getID()
                  << "Name: " << person->getName() << std::endl << std::endl;



    std::cout << "Press ENTER to return...";
    std::getline(std::cin, value); //only to acknowledge that the user pressed a key
    std::cout << CLEAR_SCREEN;
    index = 0;
}

/**
 * Will print to the screen every book from the club
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
                  << "Is Borrowed: " << book->getIsBorrowed() << std::endl;
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

/**
 * Will ask the user to input every book specs and then create a book and finally add it to the catalog
 * @param c The club is passed to this function, so that the function can use is methods
 * @param i If i = -1, function will ask the user to input the ID of book's owner, if i != -1, function will assume this value as the ID of book's owner
 * @return True if the book was successfully created and added to the catalog, false otherwise
 */

bool addBookMenu(Club &c, int i){
    std::string title;
    std::string category;
    std::string owner;
    std::string value;
    std::string days;
    Member* ptrMember;
    Book* book;
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
            else
            {
                errorMessage();
                std::cout << "Book's category (from 1-18): ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book's category (from 1-18): ";
        }
    }
    if(i==-1){
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
                for(const auto& person : c.getPeople())
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
                else
                {
                    errorMessage();
                    std::cout << "Book's owner by ID: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Book's owner by ID: ";
            }
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
            else
            {
                errorMessage();
                std::cout << "Book's value in euros: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book's value in euros: ";
        }
    }
    std::cout << "How many days can be borrowed: ";
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
            std::cout << "How many days can be borrowed: ";
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
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, value);
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
    return success;
}

/**
 * Will ask the user to input every person specs and then create add that person to the costumer's vector
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

void addCostumerMenu(Club &c)
{
    std::string name;
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
        std::cout << "How many books: ";
        while(std::getline(std::cin, nrBooks))
        {
            if (nrBooks == "-1")
            {
                delete m;
                goto END;
            }
            if (isNumeric(nrBooks))
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
            delete m;
        }
        goto END;
    }
    else
    {
        NonMember *nm = new NonMember();
        c.addPerson(nm);
        nm->setIsMember(false);
        nm->setName(name);
    }
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, name); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

/**
 * Will add to a requested person a book if the inputs were correctly added and book is not currently borrowed
 * or add the person to the Waiting List
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
            else
            {
                errorMessage();
                std::cout << "Person ID that will borrow the book: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Person ID that will borrow the book: ";
        }
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

/**
 * Will renew the loan of a book from a member if the book's loan wasn't already asked by the same member
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
                else
                {
                    errorMessage();
                    std::cout << "Person ID to renew loan time: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Person ID to renew loan time: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Person ID to renew loan time: ";
        }
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

/**
 * Will return a book to the club and check if the delivery is delayed, and print to the screen how much the person as to pay
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
                else
                {
                    errorMessage();
                    std::cout << "Person ID that will return the book: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Person ID that will return the book: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Person ID that will return the book: ";
        }
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
            else
            {
                errorMessage();
                std::cout << "Book ID that will be returned: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book ID that will be returned: ";
        }
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
        else
        {
            errorMessage();
            std::cout << "Add a rating to the book(0-5). Press Enter for no rating: ";
        }
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
        else
        {
            errorMessage();
            std::cout << "Add a rating to the book(max 100 characters). Press Enter for no comment: ";
        }
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

/**
 * Will add a book to the a person if that same person was on the from of the Waiting List
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
            else
            {
                errorMessage();
                std::cout << "Person ID to claim the book loan: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Person ID to claim the book loan: ";
        }
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
                if (ptrBook->getQueueMFront() == ptrPerson->getID())
                {
                    break;
                }
                else if (ptrBook->getQueueNMFront() == ptrPerson->getID() &&
                         (ptrBook->getQueueMSize() == 0) && !ptrBook->getIsBorrowed())
                {
                    break;
                }
                else
                {
                    errorMessage();
                    std::cout << "Book ID to be claimed: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Book ID to be claimed: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book ID to be claimed: ";
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
                if(!ptrPerson->getIsMember())
                    std::cout << "Value to pay:" << c.getLoanFee()*ptrBook->getValue() << std::endl;
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

/**
 * Will call the function PrintBorrowedBooks with the borrowed books from a person asked by the function
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
                    errorMessage();
                    std::cout << "Person ID to view borrowed books: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Person ID to view borrowed books: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Person ID to view borrowed books: ";
        }
    }
    std::cout << CLEAR_SCREEN;
    printBorrowedBooks(borrowedBooks);
    std::cout << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

/**
 * Will remove a member's book from the catalog
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
            ptrMember = dynamic_cast<Member*>(c.getPersonById(std::stoi(personID)));
            if (ptrMember != nullptr)
            {
                break;
            }
            else
            {
                errorMessage();
                std::cout << "Person ID that wants to remove the book: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Person ID that wants to remove the book: ";
        }
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
                else
                {
                    errorMessage();
                    std::cout << "Book ID to be removed: ";
                }
            }
            else
            {
                errorMessage();
                std::cout << "Book ID to be removed: ";
            }
        }
        else
        {
            errorMessage();
            std::cout << "Book ID to be removed: ";
        }
    }
    c.updateBookID(ptrMember->removeOwnedBook(ptrBook));
    c.removeBook(ptrBook);
    delete ptrBook;
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, personID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

/**
 * Will remove the lost book from the catalog and print to the screen the book's owner and the book's value to be payed to the owner
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

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
            else
            {
                errorMessage();
                std::cout << "Book ID that was lost: ";

            }
        }
        else
        {
            errorMessage();
            std::cout << "Book ID that was lost: ";
        }
    }
    valueToPay = ptrBook->getValue();
    ptrPerson = c.getPersonById(ptrBook->getOwner());
    ptrMember = dynamic_cast<Member*>(ptrPerson);
    ptrMember->removeOwnedBook(ptrBook);
    c.removeBook(ptrBook);
    delete ptrBook;
    std::cout << std::endl << "Book value was " << valueToPay << " . This value must be payed to owner with ID: " << ptrMember->getID() << std::endl;
    std::cout << std::endl << std::endl << "Press ENTER to return...";
    std::getline(std::cin, bookID); //only to acknowledge that the user pressed a key
    END:
    std::cout << CLEAR_SCREEN;
    index = 0;
}

/**
 * "Mother" function that will call the other function according to the user input
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */

void menu(Club &c){
    if(index == 0) mainMenu(c);
    if(index == 1) showCostumersMenu(c);
    if(index == 2) showCatalogMenu(c);
    if(index == 3) addCostumerMenu(c);
    if(index == 4) addBookMenu(c,-1);
    if(index == 5) borrowBookMenu(c);
    if(index == 6) renewLoanTimeMenu(c);
    if(index == 7) returnBookMenu(c);
    if(index == 8) claimBookLoanMenu(c);
    if(index == 9) viewBorrowedBooksMenu(c);
    if(index == 10) removeBookMenu(c);
    if (index == 11) reportBookLostMenu(c);
}

/**
 * Initial function containing a loop until user doesn´t press -1
 * Will also close the club if input = -1
 */

void MenuBeginning()
{
    Club club(5, 15);
    while(index != -1)
        menu(club);
    club.close();
}

