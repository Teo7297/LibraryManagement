**DESCRIPTION**\
This is a small project created for a job interview. The project requirements are described in the file `cpp-TI-library-management.pdf`.

**NOTE**\
The following directives work on windows systems.

**REQUIREMENTS**
- Cmake
- Git
- Visual Studio / MSVC (with C++ version 17+)
- An internet connection (download repo + dependencies)

**SETUP**\
To get started first of all you need to clone the repository into any location on your pc:
```
git clone https://github.com/Teo7297/LibraryManagement.git
```

Then setup the work environment and configuration:

```
cd LibraryManagement
mkdir build
cd build
cmake ..
```

After configuration is complete, it will be possible to build the application:
```
cmake --build ./ --config Release --target ALL_BUILD -j 22 --
```

and run:
```
cd ..
.\build\Release\LibraryManagementSystem.exe
```
Note: Running the app from outside the build directory will make it possible to load the pre-made library.json file.
Otherwise the file will be created in the CWD the first time added books are saved.

The application will then show a list of available commands that implement the requested features and a couple of extra ones.


**DEPENDENCIES**\
The only external dependency in this project is the library RapidJSON, an open source JSON library developed by a big company (Tencent). Used to save/load books to/from disk.

Dependencies are automatically downloaded during CMake configuration thanks to FetchContent.

**REQUIRED FEATURES**
- Add a book to the library {title, author, pubblication year} (id and status are assigned automatically, it is assumed that an added book is available right away)
- Search for a book by id, title or author
- Borrow a book (after selecting it, it's possible to borrow it, marking it unavailable)
- Return a borrowed book (marked available)
- Display a list of all the books in the library
- Save/Load the list of books to disk with JSON format

**EXTRA FEATURES**
- Remove a book from the library
- Remove all the books from the library

**SIDE NOTE**\
The project satisfies the requirements as they are described in the above mentioned PDF.
This includes being able to search for a (single) book by author. Of course an author can
write multiple books and the system supports that, but the search will stop at the first 
result. The search by ID is better suited for selecting a specific book in case there are 
multiple written by the same authors.