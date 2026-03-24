#include "LibraryItem.h"
#include <QTextStream>

//Constructor
LibraryItem::LibraryItem(const QString& title, const QString& author, int id)
    : title(title), author(author), id(id), isBorrowed(false) {}

//This gets the title, author, id, checks if item is borrowed, and also sets the status of the borrowed item)
QString LibraryItem::getTitle() const { return title; }
QString LibraryItem::getAuthor() const { return author; }
int LibraryItem::getId() const { return id; }
bool LibraryItem::getIsBorrowed() const { return isBorrowed; }
void LibraryItem::setIsBorrowed(bool status) { isBorrowed = status; }

//This shows/display the information of the item, and can also be overidden by a derived class
void LibraryItem::displayInfo() const {
    QTextStream out(stdout);
    out << "ID: " << id << ", Title: " << title << ", Author: " << author;
    out << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << "\n";
}
