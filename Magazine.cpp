#include "Magazine.h"
#include <QTextStream>

//This calls the libraryItem constructor (Constructor for magazine)
Magazine::Magazine(const QString& title, const QString& author, int id, int issueNumber)
    : LibraryItem(title, author, id), issueNumber(issueNumber) {}

//This gets the issue number
int Magazine::getIssueNumber() const { return issueNumber; }

//This shows/display the details of the magazine.
void Magazine::displayInfo() const {
    QTextStream out(stdout);
    out << "[Magazine] ";
    LibraryItem::displayInfo();
    out << "    Issue Number: " << issueNumber << "\n";
}
