#include <iostream>
#include <string>
#include <list>
using namespace std;

class Book;
class BorrowerRecord;
class Library;

class Book {
    private:
        string theCatalogueNumber;
        string theAuthor;
        string theTitle;
        BorrowerRecord* theBorrower = NULL;
    public:
        Book(): Book("N/A", "N/A", "N/A"){}
        Book(string theTitle): Book("N/A", theTitle, "N/A"){}
        Book (string theCatalogueNumber, string theTitle, string theAuthor){
            this -> setCatalogueNumber(theCatalogueNumber);
            this -> setAuthor(theAuthor);
            this -> setTitle(theTitle);
        }
        void setCatalogueNumber (string theCatalogueNumber){
            this -> theCatalogueNumber = theCatalogueNumber;
        }
        void setAuthor (string theAuthor){
            this -> theAuthor = theAuthor;
        }
        void setTitle (string theTitle){
            this -> theTitle = theTitle;
        }
        void setBorrower (BorrowerRecord* Borrower){
            this -> theBorrower = Borrower;
        }
        string getCatalogueNumber(){
            return this -> theCatalogueNumber;
        }
        string getAuthor(){
            return this ->theAuthor;
        }
        string getTitle(){
            return this -> theTitle;
        }
        BorrowerRecord* getBorrower(){
            return this -> theBorrower;
        }
        void attachBorrower(BorrowerRecord* borrower);
        void detachBorrower();
        void displayBook();
        bool isAvailableForLoan(){
            if (this -> getBorrower() == NULL){
                return true;
            }
            return false;
        }
};
class BorrowerRecord{
    private:
        string theName;
        list<Book*> theBorrowedBooks;
    public:
        BorrowerRecord(): BorrowerRecord("N/A"){}
        BorrowerRecord (string theName){
            this -> setName (theName);
        }
        void setName (string theName){
            this -> theName = theName;
        }
        string getName(){
            return this -> theName;
        }
        void attachBook (Book* aBook);
        void detachBook(Book* aBook);
        void displayBorrowerRecord();
        void displayAttachedBooks();
        list <Book*> getAttachedBooks(){
            return this -> theBorrowedBooks;
        }
};
class Library{
    private:
        string theName;
        list <Book*> theLoanStock;
        list <BorrowerRecord*> theBorrowers;
    public:
        Library(): Library("N/A"){}
        Library (string theName){
            this -> setName(theName);
        }
        void setName (string theName){
            this -> theName = theName;
        }
        string getName(){
            return this -> theName;
        }
        void addOneBook (Book* aBook);
        void registerOneBorrower (string aBorrowerName);
        void displayLibrary();
        void displayStock();
        void displayBorrowers();
        void displayBooksAvailableForLoan();
        void displayBooksOnLoan();
        void lendOneBook (string aCataLogueNumber, string aBorrowerName);
        void returnOneBook (string aCatalogueNumber);
        list <Book*> getStock(){
            return this -> theLoanStock;
        }
        list <BorrowerRecord*> getBorrowers(){
            return this -> theBorrowers;
        }
        ~Library(){
            for (auto i: this -> getBorrowers()){
                delete i;
            }
        }
 };

 // Functions in Book's class
 void Book::displayBook(){
    cout << "Catalogue number: " << this -> getCatalogueNumber() << endl;
    cout << "Title: " << this -> getTitle() << endl;
    cout << "Author: " << this -> getAuthor() << endl;
 }
 void Book::attachBorrower(BorrowerRecord* borrower){
    this -> setBorrower(borrower);
    borrower -> attachBook(this);
 }
 void Book::detachBorrower(){
    BorrowerRecord* borrower = this -> getBorrower();
    if (borrower){
        this -> setBorrower(NULL);
        borrower -> detachBook(this);
    }
 }
 // Functions in BorrowerRecord's class
 void BorrowerRecord::displayBorrowerRecord(){
    cout << "Borrower's name: " << this -> getName() << endl;
 }
 void BorrowerRecord::attachBook(Book* aBook){
    this -> theBorrowedBooks.push_back(aBook);
 }
 void BorrowerRecord::detachBook(Book* aBook){
    this -> theBorrowedBooks.remove(aBook);
 }
 void BorrowerRecord::displayAttachedBooks(){
    int j = 1;
    cout<<"List of books attached to this borrower: "<<endl;
    for (auto i: this -> getAttachedBooks()){
        cout << "Book " << j << ": " << endl;
        i -> displayBook();
        j++;
    }
 }

 // Functions in Library's class
 void Library::displayLibrary(){
    cout<<"Library name: " << this -> getName() << endl;
 }
 void Library::addOneBook(Book* aBook){
    this -> theLoanStock.push_back(aBook);
 }
 void Library::registerOneBorrower(string aBorrowerName){
    // BorrowerRecord* br = new BorrowerRecord (aBorrowerName);
    // this -> theBorrowers.push_back(br);
    this -> theBorrowers.push_back(new BorrowerRecord(aBorrowerName));
 }
 void Library::displayStock(){
    int j=1;
    cout<<"List of books in stock: "<<endl;
    for (auto i: this -> getStock()){
        cout << "Book "<<j<< ": "<< endl;
        i -> displayBook();
        j++;
    }
 }
 void Library::displayBorrowers(){
    cout<<"\nList of borrowers: "<<endl;
    int j=1;
    for (auto i: this -> getBorrowers()){
        cout << "Borrower " << j << ": ";
        i -> displayBorrowerRecord();
        j++;
    }
 }
 void Library::displayBooksAvailableForLoan(){
    cout<<"\nList of books available for loan: "<<endl;
    int j=1;
    for (auto i: this -> getStock()){
        if (i -> isAvailableForLoan()){
            cout << "Book " << j << ": "<< endl;
            i -> displayBook();
            j++;
        }
    }
 }
 void Library::displayBooksOnLoan(){
    cout<<"\nList of books on loan: "<< endl;
    int j=1;
    for (auto i: this -> getStock()){
        if (!i -> isAvailableForLoan()){
            cout << "Book " << j << ": "<< endl;
            i -> displayBook();
            j++;
        }
    }
 }
 void Library::lendOneBook(string aCatalogueNumber, string aBorrowerName){
    Book* book = nullptr;
    BorrowerRecord* borrower = nullptr;
    for (auto i: this -> getStock()){
        if (i -> getCatalogueNumber() == aCatalogueNumber){
            book = i;
            break;
        }
    }
    if(!book){
        cout<<"Book not found"<<endl;
        return;
    }
    if(!book -> isAvailableForLoan()){
        cout<<"Book on loan!"<<endl;
        return;
    }
    for (auto i: this -> getBorrowers()){
        if (i -> getName() == aBorrowerName){
            borrower = i;
            break;
        }
    }
    if (!borrower){
        cout<<"Borrower not found"<<endl;
        return;
    }
    book -> attachBorrower(borrower);
    cout<<"\nBook "<< book -> getTitle() << ", " << book -> getCatalogueNumber() << " lent to "<< borrower -> getName()<<endl;
 }
 void Library::returnOneBook(string aCatalogueNumber){
    Book* book = nullptr;
    for (auto i: this -> getStock()){
        if (i -> getCatalogueNumber() == aCatalogueNumber){
            book = i;
            break;
        }
    }
    if (!book){
        cout<<"Book not found"<<endl;
        return;
    }
    if (book -> isAvailableForLoan()){
        cout<<"Book not on loan!"<<endl;
        return;
    }
    book -> detachBorrower();
    cout<<"\nBook "<< book -> getTitle() << " returned"<<endl;
 }
int main(){
    Book * book1 = new Book("001", "The C++ Programming Language", "Bjarne Stroustrup");
    Book * book2 = new Book("002", "The C Programming Language", "Brian W. Kernighan and Dennis M. Ritchie");
    Book * book3 = new Book("003", "The Java Programming Language", "James Gosling");
    Book * book4 = new Book("004", "The Python Programming Language", "Guido van Rossum");
    Library *HCMUS_Library = new Library("HCMUS Library");
    HCMUS_Library -> displayLibrary();
    HCMUS_Library -> addOneBook(book1);
    HCMUS_Library -> addOneBook(book2);
    HCMUS_Library -> addOneBook(book3);
    HCMUS_Library -> addOneBook(book4);
    HCMUS_Library -> displayStock();
    HCMUS_Library -> registerOneBorrower("Ha Van Thao");
    HCMUS_Library -> registerOneBorrower("Pham Huy Lam");
    HCMUS_Library -> registerOneBorrower("Nguyen Hien Luong");
    HCMUS_Library -> displayBorrowers();
    HCMUS_Library -> lendOneBook("001", "Ha Van Thao");
    HCMUS_Library -> lendOneBook("002", "Pham Huy Lam");
    HCMUS_Library -> lendOneBook("004", "Nguyen Hien Luong");
    HCMUS_Library -> lendOneBook("005", "Nguyen Hien Luong");
    HCMUS_Library -> lendOneBook("003", "ABCDEF");
    HCMUS_Library -> displayBooksAvailableForLoan();
    HCMUS_Library -> displayBooksOnLoan();
    HCMUS_Library -> returnOneBook("001");
    HCMUS_Library -> displayBooksAvailableForLoan();
    HCMUS_Library -> displayBooksOnLoan();
    delete (book1);
    delete (book2);
    delete (book3);
    delete (book4);
    delete (HCMUS_Library);
    cout<<"\nEnd of the program"<<endl;
return 0;
}