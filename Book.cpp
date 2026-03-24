#include "Book.h"
#include <QTextStream>

//This calls libraryItem constructor (Constructor for books)
Book::Book(const QString& title, const QString& author, int id, const QString& genre)
    : LibraryItem(title, author, id), genre(genre) {}

//This gets the genre of the book
QString Book::getGenre() const { return genre; }

//This shows/display all the details for the book
void Book::displayInfo() const {
    QTextStream out(stdout);
    out << "[Book] ";
    LibraryItem::displayInfo();
    out << "    Genre: " << genre << "\n";
}
