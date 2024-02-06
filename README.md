# Student Database Management

## Overview
The Student Database Management Software is a command-line application built in C that allows users to manage student records efficiently. It adheres to good coding practices and provides functionalities to create, display, update, delete, and sort student records stored in a text-based database file.

## Features
- **Create/Append Records:** Users can add new student records to the database, including student ID, forename, surname, enrolled courses, and grades.
- **Display Records:** The system allows users to view student records, including detailed information such as semester grades and averages.
- **Update Records:** Users can modify existing student records, including student ID, forename, surname, and enrolled courses and grades.
- **Delete Records:** The system provides functionality to delete specific student records from the database.
- **Sort Records:** Users can sort student records based on average grades or surnames, with options to display or save the sorted results.

## Getting Started
To run the Student Database Management System, follow these steps:
1. Clone the repository to your local machine.
2. Compile the C code using a C compiler such as GCC.
3. Run the compiled executable to start the application.

## Usage
- Upon launching the application, users are presented with a menu offering various options to manage student records.
- Users can select options to create, display, update, delete, or sort student records based on their requirements.
- Input validation is implemented to ensure the integrity of student data and prevent erroneous entries.

## Technologies Used
- C programming language
- File I/O for database operations
- Standard input/output for user interaction

## Good Coding Practices
- **Modular Design:** The application is modularized into separate functions for each feature, enhancing readability and maintainability.
- **Attempted Input Validation:** Input from users is validated to prevent invalid data entry and ensure data integrity.
- **Memory Management:** Dynamic memory allocation is used efficiently, with proper freeing of allocated memory to prevent memory leaks.
- **Error Handling:** The application handles errors gracefully, providing informative messages to users and preventing crashes.
- **Code Comments:** Code is well-commented to explain functionality and aid understanding for future maintenance or collaboration.

## Future Enhancements
- Implement a graphical user interface (GUI) for a more user-friendly experience.
- Integrate a relational database management system (RDBMS) for scalable and efficient data storage.
- Enhance error handling and input validation to improve robustness.

## Contributors
- Cristian Soare (https://github.com/CristianSoare) - Lead Developer

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

