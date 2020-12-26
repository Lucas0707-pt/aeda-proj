#ifndef _BOOK_STORE_H
#define _BOOK_STORE_H
#include <iostream>
#include <vector>
#include "../Book/Book.h"

class Book;

/**
 * This class holds on the information about a book store, to witch the lecture club offers promotions to its clients
 */

class BookStore
{
public:
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
     * Adds a book to the stock
     * @param book The book to the added to the stock
     */
    void addBook(Book* book);
    /**
     * Returns the stock
     * @return The stock
     */
    std::vector<Book*> getStock();
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
    std::vector<Book*> stock; /**All the books available in the book store*/
    float promotion; /**The promotion that is offered from the lecture club*/
    std::string discountCode; /**The code to be used in the book store to receive a discount*/
    std::vector<unsigned int> ratings; /**All the ratings from the book store given by clients*/
};

#endif //_BOOK_STORE_H
