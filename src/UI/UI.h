#ifndef _UI_H
#define _UI_H

#include<iostream>
#include "../Book/Book.h"
#include <vector>

/**
 * Will print to the screen an Error message in red colour
 */
void errorMessage();

/**
 * Will print to the screen every book's category possible
 */
void printBooksCategory();

/**
 * Will print to the screen the owned books passed by reference
 * @param ownedBooks Vector containing the books to be printed to the screen
 */

void printOwnedBooks(const std::vector<Book*>& ownedBooks);

/**
 * Will print to the screen the borrowed books passed by reference
 * @param borrowedBooks Vector containing the books to be printed to the screen
 */

void printBorrowedBooks(const std::vector<Book*>& borrowedBooks);

/**
 * Will print to the screen every possible operation by the user,
 * and then ask the user to input an operation and check if it is a valid input
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void mainMenu(Club &c);

/**
 * Will print to the screen every costumer (people) from the club
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void showCostumersMenu(Club &c);

/**
 * Will print to the screen every book from the club
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void showCatalogMenu(Club &c);

/**
 * Will print to the screen every book store from the club
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void showBookStoresMenu(Club &c);

/**
 * Will ask the user to input every book specs and then create a book and add it to the catalog
 * @param c The club is passed to this function, so that the function can use is methods
 * @param i If i = -1, function will ask the user to input the ID of book's owner, if i != -1, function will assume this value as the ID of book's owner
 * @return True if the book was successfully created and added to the catalog, false otherwise
 */
bool addBookMenu(Club &c, int i);

/**
 * Will ask the user to input every person specs and then create and add that person to the costumer's vector
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void addCostumerMenu(Club &c);

/**
 * Will ask the user to input every book store specs and then create and add that person to the book store's BST
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void addBookStoreMenu(Club &c);

/**
 * Will show a mini Menu with all the options available to do with the BST elements
 * @param c The club is passed by reference to this function, so that the function can use is methods
 * @param bookStore The new book store to be "edited" and then added to the BST
 * @param bookStoreFound The old book store that contains all the information to be added to the new book store
 */
void showMenuBookStores(Club &c, BookStore &bookStore, BookStore &bookStoreFound);

/**
 * Will ask the user to input the book store information to then be edited in "showMenuBookStores" function
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void MenuBookStore(Club &c);

/**
 * Will add to a requested person a book if the inputs were correctly added and book is not currently borrowed
 * or add the person to the Waiting List
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void borrowBookMenu(Club &c);

/**
 * Will renew the loan of a book from a member if the book's loan wasn't already asked by the same member
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void renewLoanTimeMenu(Club &c);

/**
 * Will return a book to the club and check if the delivery is delayed, and print to the screen how much the person as to pay
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void returnBookMenu(Club &c);

/**
 * Will add a book to the a person if that same person was on the from of the Waiting List
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void claimBookLoanMenu(Club &c);

/**
 * Will call the function PrintBorrowedBooks with the borrowed books from a person asked by the function
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void viewBorrowedBooksMenu(Club &c);

/**
 * Will remove a member's book from the catalog
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void removeBookMenu(Club &c);

/**
 * Will remove the lost book from the catalog and print to the screen the book's owner and the book's value to be payed to the owner
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void reportBookLostMenu(Club& c);

/**
 * Will read the info file and see if the others files exists and weren't edited outside the program, will also read the loan fee and delay penalty from the club
 * If the file is empty, means that it's the first time that the program is opened
 * Will catch exceptions if either one of the files were edited or don't exist
 * @param loanFee loanFee variable to be updated with file information
 * @param delayPenalty variable to be updated with file information
 * @return 1 if the file is empty, 2 if reading the file was a success
 */
unsigned int readInfoFile(double &loanFee, double &delayPenalty);

/**
 * Will show the waiting list from a book
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void BookQueueMenu(Club &c);

/**
 * Will show a mini Menu with all the options available to do with the hash table from person preferences
 * @param c The club is passed by reference to this function, so that the function can use is methods
 * @param person The person to be edited
 */
void showMenuPreferences(Club &c, Person* person);

/**
 * Will ask the user to input the person information to then be edited in "showMenuPreferences" function
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void MenuPreferences(Club &c);

/**
 * Will try to call the club function to save the info to files, and catch exceptions if a problem occurs
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void saveInfo(Club& c);

/**
 * "Mother" function that will call the other function according to the user input
 * @param c The club is passed by reference to this function, so that the function can use is methods
 */
void menu(Club &c);

/**
 * Initial function containing a loop until user doesn't press -1
 * Will also close the club if input = -1
 */
void MenuBeginning();

#endif //_UI_H
