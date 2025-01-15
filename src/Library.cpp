#include "Library.h"

namespace lms
{
    void Library::Add(const std::string& title, const std::string& author, const unsigned int year)
    {
        unsigned int id = static_cast<unsigned int>(m_books.size());
        m_books.emplace_back(std::make_shared<Book>(id, title, author, year, true));
    }

    bool Library::Remove(const unsigned int id)
    {
        if (m_books.size() <= id)
            return false;

        m_books.erase(m_books.begin() + id);
        return true;
    }

    void Library::RemoveAll()
    {
        m_books.clear();
    }

    std::shared_ptr<Book> Library::FindByID(const unsigned int id) const
    {
        if (m_books.size() <= id)
            return nullptr;

        return m_books.at(id);
    }

    std::shared_ptr<Book> Library::FindByTitle(const std::string& title) const
    {
        for (auto& book : m_books)
            if (book->title == title)
                return book;

        return nullptr;
    }

    std::shared_ptr<Book> Library::FindByAuthor(const std::string& author) const
    {
        for (auto& book : m_books)
            if (book->author == author)
                return book;

        return nullptr;
    }

    bool Library::Borrow(const unsigned int id)
    {
        auto book = this->FindByID(id);

        if (!book)
            return false;

        if (!book->available)
        {
            std::cerr << "[Library] This book is not available" << std::endl;
            return false;
        }

        book->available = false;

        return true;
    }

    bool Library::Return(const unsigned int id)
    {
        auto book = this->FindByID(id);

        if (!book)
        {
            std::cerr << "[Library] This book does not exist" << std::endl;
            return false;
        }

        if (book->available)
            return false;

        book->available = true;

        return true;
    }

    void Library::List()
    {

        for (int i = 0; i < m_books.size(); i++)
        {
            const auto& book = m_books[i];
            std::cout << book->str() << std::endl;
        }
    }

    void Library::Read(const std::filesystem::path& path)
    {
        using namespace rapidjson;

        FILE* file = fopen(path.string().c_str(), "r");
        if (!file)
        {
            std::cerr << "[Library] Error opening file: " << path.string() << std::endl;
            return;
        }

        char readBuffer[65536];
        FileReadStream is(file, readBuffer, sizeof(readBuffer));
        Document document;
        document.ParseStream(is);
        fclose(file);

        if (!document.IsArray())
        {
            std::cerr << "[Library] JSON format error: expected an array" << std::endl;
            return;
        }

        m_books.clear();
        for (const auto& bookObject : document.GetArray())
        {
            if (!bookObject.IsObject())
            {
                std::cerr << "[Library] JSON format error: expected an object" << std::endl;
                return;
            }

            std::string title = bookObject["title"].GetString();
            std::string author = bookObject["author"].GetString();
            int year = bookObject["year"].GetInt();

            this->Add(title, author, year);
        }

        std::cout << "[Library] Library loaded from " << path.string() << std::endl;
    }

    void Library::Write(const std::filesystem::path& path)
    {
        using namespace rapidjson;
        Document document;
        document.SetArray();

        Document::AllocatorType& allocator = document.GetAllocator();

        for (const auto& book : m_books)
        {
            Value bookObject(kObjectType);
            bookObject.AddMember("title", Value(book->title.c_str(), allocator).Move(), allocator);
            bookObject.AddMember("author", Value(book->author.c_str(), allocator).Move(), allocator);
            bookObject.AddMember("year", book->year, allocator);

            document.PushBack(bookObject, allocator);
        }

        FILE* file = fopen(path.string().c_str(), "w");
        if (!file)
        {
            std::cerr << "[Library] Error opening file: " << path.string() << std::endl;
            return;
        }

        char writeBuffer[65536];
        FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        document.Accept(writer);

        fclose(file);
        std::cout << "[Library] Library saved to " << path.string() << std::endl;
    }
}
