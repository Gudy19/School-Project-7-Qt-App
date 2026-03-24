#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "Book.h"
#include "Magazine.h"

QVector<LibraryItem*> libraryItems;

// This loads library data from a file
void loadLibraryData(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream(stdout) << "Could not open " << filename << " for reading.\n";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split('|');
        if (parts[0] == "Book" && parts.size() == 6) {
            Book* book = new Book(parts[1], parts[2], parts[3].toInt(), parts[4]);
            book->setIsBorrowed(parts[5] == "1");
            libraryItems.push_back(book);
        } else if (parts[0] == "Magazine" && parts.size() == 6) {
            Magazine* mag = new Magazine(parts[1], parts[2], parts[3].toInt(), parts[4].toInt());
            mag->setIsBorrowed(parts[5] == "1");
            libraryItems.push_back(mag);
        }
    }
    file.close();
}

// This saves data to the library file
void saveLibraryData(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream(stdout) << "Could not open " << filename << " for writing.\n";
        return;
    }
    QTextStream out(&file);
    for (auto *item : libraryItems) {
        const Book* book = dynamic_cast<Book*>(item);
        const Magazine* mag = dynamic_cast<Magazine*>(item);
        if (book) {
            out << "Book|" << book->getTitle() << "|" << book->getAuthor() << "|"
                << book->getId() << "|" << book->getGenre() << "|"
                << (book->getIsBorrowed() ? "1" : "0") << "\n";
        } else if (mag) {
            out << "Magazine|" << mag->getTitle() << "|" << mag->getAuthor() << "|"
                << mag->getId() << "|" << mag->getIssueNumber() << "|"
                << (mag->getIsBorrowed() ? "1" : "0") << "\n";
        }
    }
    file.close();
}

// This shows/displays all the library items
void displayAllItems() {
    QTextStream out(stdout);
    out << "=== Library Items ===\n";
    for (auto *item : libraryItems)
        item->displayInfo();
}

// This adds a book (from the user's input)
void addBook() {
    QTextStream in(stdin);
    QTextStream out(stdout);
    out << "Enter book title: "; out.flush();
    QString title = in.readLine();
    out << "Enter author: "; out.flush();
    QString author = in.readLine();
    out << "Enter ID (number): "; out.flush();
    int id = in.readLine().toInt();
    out << "Enter genre: "; out.flush();
    QString genre = in.readLine();
    Book* book = new Book(title, author, id, genre);
    libraryItems.push_back(book);
    out << "Book added.\n";
}

// This adds a magazine (from the user's input)
void addMagazine() {
    QTextStream in(stdin);
    QTextStream out(stdout);
    out << "Enter magazine title: "; out.flush();
    QString title = in.readLine();
    out << "Enter author: "; out.flush();
    QString author = in.readLine();
    out << "Enter ID (number): "; out.flush();
    int id = in.readLine().toInt();
    out << "Enter issue number: "; out.flush();
    int issue = in.readLine().toInt();
    Magazine* mag = new Magazine(title, author, id, issue);
    libraryItems.push_back(mag);
    out << "Magazine added.\n";
}

// This borrows an item by using ID
void borrowItem() {
    QTextStream in(stdin);
    QTextStream out(stdout);
    out << "Enter ID of item to borrow: "; out.flush();
    int id = in.readLine().toInt();
    for (auto *item : libraryItems) {
        if (item->getId() == id) {
            if (!item->getIsBorrowed()) {
                item->setIsBorrowed(true);
                out << "Item borrowed successfully.\n";
            } else {
                out << "Item is already borrowed.\n";
            }
            return;
        }
    }
    out << "Item not found.\n";
}

// This returns an item by using ID
void returnItem() {
    QTextStream in(stdin);
    QTextStream out(stdout);
    out << "Enter ID of item to return: "; out.flush();
    int id = in.readLine().toInt();
    for (auto *item : libraryItems) {
        if (item->getId() == id) {
            if (item->getIsBorrowed()) {
                item->setIsBorrowed(false);
                out << "Item returned successfully.\n";
            } else {
                out << "Item was not borrowed.\n";
            }
            return;
        }
    }
    out << "Item not found.\n";
}

// Main program
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);

    QString filename = "library_data.txt";
    loadLibraryData(filename);

    int choice = 0;
    do {
        out << "\n=== Library Management System ===\n";
        out << "1. Display all items\n";
        out << "2. Add Book\n";
        out << "3. Add Magazine\n";
        out << "4. Borrow Item\n";
        out << "5. Return Item\n";
        out << "6. Save and Exit\n";
        out << "Enter choice: "; out.flush();

        QString line = in.readLine();
        choice = line.toInt();

        switch (choice) {
        case 1:
            displayAllItems();
            break;
        case 2:
            addBook();
            break;
        case 3:
            addMagazine();
            break;
        case 4:
            borrowItem();
            break;
        case 5:
            returnItem();
            break;
        case 6:
            saveLibraryData(filename);
            out << "Goodbye!\n";
            break;
        default:
            out << "Invalid choice.\n";
        }
    } while (choice != 6);

    // Clean up memory
    for (auto *item : libraryItems) delete item;
    return 0;
}
