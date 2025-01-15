#include "LibraryApp.h"

#include "Library.h"

std::unique_ptr<lms::Library> LibraryApp::s_library = std::make_unique<lms::Library>();

void LibraryApp::Run()
{
    PrintAvailableCommands();

    std::unordered_map<std::string, std::function<void()>> commands = {
        {"list", [&]() { s_library->List(); }},
        {"select1", [&]() { LibraryApp::BorrowById(); }},
        {"select2", [&]() { LibraryApp::BorrowByTitle(); }},
        {"select3", [&]() { LibraryApp::BorrowByAuthor(); }},
        {"add", [&]() { LibraryApp::AddBook(); }},
        {"remove", [&]() { LibraryApp::RemoveBook(); }},
        {"clear", [&]() { LibraryApp::RemoveAllBooks(); }},
        {"return", [&]() { LibraryApp::TryReturn(); }},
        {"save", [&]() { s_library->Write("library.json"); }},
        {"load", [&]() { s_library->Read("library.json"); }},
        {"help", [&]() { PrintAvailableCommands(); }},
        {"quit", [&]() { std::cout << "Exiting program.\n"; exit(0); }},
    };

    while (true)
    {
        const std::string command = GetInputString("Enter command: ");

        auto it = commands.find(command);
        if (it != commands.cend())
            it->second();
        else
            std::cout << "Unknown command. Type 'help' for a list of commands.\n";
    }
}

bool LibraryApp::TryBorrow(std::shared_ptr<lms::Book> book)
{
    std::string borrow;
    while (true)
    {
        std::string borrow = GetInputString("Do you want to borrow this book? [y/n]: ");
        if (borrow == "y")
        {
            bool success = s_library->Borrow(book->id);
            return success;
        }
        else if (borrow == "n")
            return false;
    }
    return false;
}

void LibraryApp::TryReturn()
{
    unsigned int id = GetInputUInt("Insert the book id: ");
    if (s_library->Return(id))
        std::cout << "Book returned successfully" << std::endl;
    else
        std::cerr << "You didn't borrow this book" << std::endl;
}

void LibraryApp::PrintAvailableCommands()
{
    std::string commandList = R"(
Welcome to the Library Management System!
Here is a list of available commands:
list    -> List all books
select1 -> Select a book by id
select2 -> Select a book by title
select3 -> Select a book by author
add     -> Add a new book
remove  -> Remove a book
clear   -> Remove all books
return  -> Return a book
save    -> Save the library to a file
load    -> Load the library from a file
quit    -> Close the app
help    -> Show commands
    )";
    std::cout << "\n\n" << commandList << std::endl;
}

void LibraryApp::BorrowById()
{
    unsigned int id = GetInputUInt("Insert the book id: ");

    auto book = s_library->FindByID(id);
    if (!book)
    {
        std::cerr << "This book does not exist" << std::endl;
        return;
    }

    std::cout << "Selected: " << book->title << std::endl;
    if (!book->available)
    {
        std::cout << "Unfortunately this book is not available at the moment" << std::endl;
        return;
    }

    bool borrowed = TryBorrow(book);
    if (borrowed)
        std::cout << "Book successfully borrowed, have a good read!" << std::endl;
}

void LibraryApp::BorrowByTitle()
{
    std::string title = GetInputString("Insert the book title: ");

    auto book = s_library->FindByTitle(title);
    if (!book)
    {
        std::cerr << "This book does not exist" << std::endl;
        return;
    }

    std::cout << "Selected: " << book->title << std::endl;
    if (!book->available)
    {
        std::cout << "Unfortunately this book is not available at the moment" << std::endl;
        return;
    }

    bool borrowed = TryBorrow(book);
    if (borrowed)
        std::cout << "Book successfully borrowed, have a good read!" << std::endl;
}

void LibraryApp::BorrowByAuthor()
{
    std::string author = GetInputString("Insert the author name: ");

    auto book = s_library->FindByAuthor(author);
    if (!book)
    {
        std::cerr << "This book does not exist" << std::endl;
        return;
    }

    std::cout << "Selected: " << book->title << std::endl;
    if (!book->available)
    {
        std::cout << "Unfortunately this book is not available at the moment" << std::endl;
        return;
    }

    bool borrowed = TryBorrow(book);
    if (borrowed)
        std::cout << "Book successfully borrowed, have a good read!" << std::endl;
}

void LibraryApp::AddBook()
{
    const std::string title = GetInputString("Insert the book title: ");
    const std::string author = GetInputString("Insert the author name: ");
    const unsigned int year = GetInputUInt("Insert the year of pubblication: ");

    s_library->Add(title, author, year);

    std::cout << "Thanks for submitting this book!" << std::endl;
}

void LibraryApp::RemoveBook()
{
    unsigned int id = GetInputUInt("Insert the book id: ");
    if (s_library->Remove(id))
        std::cout << "Book removed successfully" << std::endl;
    else
        std::cerr << "This book does not exist" << std::endl;
}

void LibraryApp::RemoveAllBooks()
{
    s_library->RemoveAll();
    std::cout << "All books removed successfully" << std::endl;
}

unsigned int LibraryApp::GetInputUInt(const std::string& message)
{
    unsigned int value = -1;
    std::string input;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, input);

        try
        {
            value = std::stoi(input);
            break;
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
        }
        catch (const std::out_of_range&)
        {
            std::cout << "The number entered is out of range. Please enter a valid number." << std::endl;
        }
    }

    return value;
}

std::string LibraryApp::GetInputString(const std::string& message)
{
    std::string input;
    std::cout << message;

    while (std::cin.peek() == '\n')
        std::cin.ignore();
    std::getline(std::cin, input);
    return input;
}
