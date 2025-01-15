#pragma once

#include "LmsDefines.h"

namespace lms
{
    /// @brief Simple struct that represents a book in the library.
    /// It only offers a basic constructor for in-place initialization 
    /// and a str() method to print the book information.
    struct Book
    {
        Book(unsigned int id_, const std::string& title_, const std::string& author_, unsigned int year_, bool available_)
            : id{ id_ }, title{ title_ }, author{ author_ }, year{ year_ }, available{ available_ }
        {
        }
        ~Book() = default;

        unsigned int id;
        std::string title;
        std::string author;
        unsigned int year;
        bool available;

        std::string str() const
        {
            std::stringstream ss;
            std::string availableMsg = available ? "\033[32mAvailable\033[0m" : "\033[31mUnavailable\033[0m";
            ss << availableMsg << "\t| " << "[ " << id << " ] " << title << " by " << author;
            return ss.str();
        }
    };

    /// @brief Library class that manages a collection of books.
    class Library
    {
    public:
        /// @brief Add a book to the library. The class design allows for multiple copies of the same book.
        /// @param title Title of the book
        /// @param author Author of the book
        /// @param year Year of pubblication
        void Add(const std::string& title, const std::string& author, const unsigned int year);

        /// @brief Remove a book from the library by its ID.
        /// @param id ID of the book
        bool Remove(const unsigned int id);

        /// @brief Remove all books from the library.
        void RemoveAll();

        /// @brief Find a book by its title. IDs can be visualized using the List command.
        /// Since IDs correspond to the index of the books vector, this search will run with O(1) time.
        /// @param id ID of the book
        /// @return shared_ptr<Book>
        std::shared_ptr<Book> FindByID(const unsigned int id) const;

        /// @brief Find a book by its title. This search method requires to iterate over all books in the worst case scenario.
        /// (Max computation time: O(n))
        /// @param title Title of the book
        /// @return shared_ptr<Book>
        std::shared_ptr<Book> FindByTitle(const std::string& title) const;

        /// @brief Find a book by its author. This search method requires to iterate over all books in the worst case scenario.
        /// (Max computation time: O(n))
        /// @param author Author of the book
        /// @return shared_ptr<Book>
        std::shared_ptr<Book> FindByAuthor(const std::string& author) const;

        /// @brief Try to borrow the book with the given ID. Success is granted if the book is available.
        /// @param id ID of the book
        /// @return bool (success)
        bool Borrow(const unsigned int id);

        /// @brief Return a book to the library. The book will be marked as available.
        /// @param id ID of the book
        /// @return bool (success)
        bool Return(const unsigned int id);

        /// @brief Print a list of all the books registered in the library. Each line will also show if a book is available at the moment.
        void List() const;

        /// @brief Loads the books from a JSON file
        /// @param path File path
        void Read(const std::filesystem::path& path);

        /// @brief Writes the books to a JSON file
        /// @param path File path
        void Write(const std::filesystem::path& path) const;

    private:
        /// @brief Collection of books
        std::vector<std::shared_ptr<Book>> m_books;
    };
}
