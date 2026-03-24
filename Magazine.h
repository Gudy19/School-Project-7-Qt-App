#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "LibraryItem.h"
#include <QString>

class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(const QString& title, const QString& author, int id, int issueNumber);

    int getIssueNumber() const;

    void displayInfo() const override;
};

#endif
