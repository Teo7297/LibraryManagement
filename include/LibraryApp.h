#pragma once

#include <string>
#include <memory>

namespace lms
{
    struct Book;
    class Library;
}

/// @brief Static App class which only exposes a static method Run().
/// This will initiate the application loop.
class LibraryApp
{
public:
    LibraryApp() = delete;

    /// @brief Start the application.
    static void Run();

private:
    static bool TryBorrow(std::shared_ptr<lms::Book> book);
    static void TryReturn();
    static void PrintAvailableCommands();
    static void FindById();
    static void FindByTitle();
    static void FindByAuthor();
    static void AddBook();
    static void RemoveBook();
    static void RemoveAllBooks();

    // Some utility functions
    static unsigned int GetInputUInt(const std::string& message);
    static std::string GetInputString(const std::string& message);

private:
    static std::unique_ptr<lms::Library> s_library;
};

