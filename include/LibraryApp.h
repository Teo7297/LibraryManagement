#pragma once

#include <string>
#include <memory>

namespace lms
{
    struct Book;
    class Library;
}

/// @brief Static App class which only exposes a static method Run().
/// This will initiate the application loop and interact with the underlying library.
class LibraryApp
{
public:
    LibraryApp() = delete;

    /// @brief Start the application.
    static void Run();

private:
    /// @brief Print the available commands to the console.
    static void PrintAvailableCommands();
    /// @brief Get an unsigned integer from the console input.
    static unsigned int GetInputUInt(const std::string& message);
    /// @brief Get a string from the console input.
    static std::string GetInputString(const std::string& message);

    // Command functions, these are the actions that the user can perform
    // and directly interact with the library.
    static bool TryBorrow(std::shared_ptr<lms::Book> book);
    static void TryReturn();
    static void BorrowById();
    static void BorrowByTitle();
    static void BorrowByAuthor();
    static void AddBook();
    static void RemoveBook();
    static void RemoveAllBooks();


private:
    static std::unique_ptr<lms::Library> s_library;
};

