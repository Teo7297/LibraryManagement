**DESCRIPTION**\
This is a small project created for a job interview. The project requirements are described in the file `cpp-TI-library-management.pdf`.

**NOTE**:\
The following directives work on windows systems.

**REQUIREMENTS**\
- Cmake
- Git
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
.\Release\LibraryManagementSystem.exe
```

The application will then show a list of available commands that implement the requested features and a couple of extra ones.


**DEPENDENCIES**\
The only external dependency in this project is the library RapidJSON, an open source JSON library developed by a big company (Tencent). Used to save/load books to/from disk.

Dependencies are automatically downloaded during CMake configuration thanks to FetchContent.

