#ifndef _UI_H
#define _UI_H

#include<iostream>
#include "../Book/Book.h"
#include <vector>


void errorMessage();

void printBooksCategory();

void printOwnedBooks(const std::vector<Book*>& ownedBooks);

void printBorrowedBooks(const std::vector<Book*>& borrowedBooks);

void mainMenu(Club &c);

void showCostumersMenu(Club &c);

void showCatalogMenu(Club &c);

void showBookStoresMenu(Club &c);

bool addBookMenu(Club &c, int i);

void addCostumerMenu(Club &c);

void addBookStoreMenu(Club &c);

void borrowBookMenu(Club &c);

void renewLoanTimeMenu(Club &c);

void returnBookMenu(Club &c);

void claimBookLoanMenu(Club &c);

void viewBorrowedBooksMenu(Club &c);

void removeBookMenu(Club &c);

void reportBookLostMenu(Club& c);

unsigned int readInfoFile(double &loanFee, double &delayPenalty);

void saveInfo(Club& c);


void menu(Club &c);

void MenuBeginning();

#endif //_UI_H
