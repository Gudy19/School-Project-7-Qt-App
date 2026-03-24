#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"
#include <QString>

class Book : public LibraryItem {
private:
    QString genre;

public:
    Book(const QString& title, const QString& author, int id, const QString& genre);

    QString getGenre() const;

    void displayInfo() const override;
};

#endif // BOOK_H
