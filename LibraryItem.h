#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QString>

class LibraryItem {
private:
    QString title;
    QString author;
    int id;
    bool isBorrowed;

public:
    LibraryItem(const QString& title, const QString& author, int id);

    // Getters
    QString getTitle() const;
    QString getAuthor() const;
    int getId() const;
    bool getIsBorrowed() const;

    // Setters
    void setIsBorrowed(bool status);

    // Virtual display function for polymorphism
    virtual void displayInfo() const;

    // Virtual destructor for inheritance
    virtual ~LibraryItem() {}
};

#endif // LIBRARYITEM_H
