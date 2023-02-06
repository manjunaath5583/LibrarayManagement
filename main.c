#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// own data type -- boolen
enum Bool
{
    true,
    false,
};
typedef enum Bool bool;

// structers  book and student;
struct Book
{
    int Id;
    char Name[100];
    char Author[100];
    bool Issued;
    struct Book *Next;
    int studentID;
};

struct Student
{
    int Id;
    char Name[100];
    int Book_ID;
    char Book_name[100];
    char Issued_date[10];
    char Due_date[10];
    char Return_date[10];
    bool returned;
    struct Student *Next;
};

// creating heads;
struct Student *Student_table;
struct Book *Book_table;
struct Student *Temp_student;
struct Book *Temp_Book;
struct Book *Temp_Book_insert;
struct Student *Temp_student_insert;
struct Book *Temp_Book_Check;
struct Student *Temp_Student_Check;

// creating methos
int addNewBook();                  // adds new book to the libraray
int issueBook();                   // issues new book
int returnBook();                  // takes the returned book
int pendingBooks();                // shows pending books
int displayStudentRecord();        // displays student table
int displayBookRecord();           // displays book table
bool bookIssuedOrNot(int Book_ID); // checks if book is issued or not
bool isUnique(int Book_ID);        // checks uniqueness of the book

// creating Global variables
int Student_ID; // asks for students ID
int Book_ID;    // asks for Book ID

int main()
{

    int choice;
    while (1)
    {
        printf("MENU\n");
        printf("1. Add new book\n");
        printf("2. Issue new book\n");
        printf("3. Return the book\n");
        printf("4. Show all pending books\n");
        printf("5. Display Student Record\n");
        printf("6. Display Books Record\n");
        printf("7. EXIT\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addNewBook();
            break;
        case 2:
            issueBook();
            break;
        case 3:
            returnBook();
            break;
        case 4:
            pendingBooks();
            break;
        case 5:
            displayStudentRecord();
            break;
        case 6:
            displayBookRecord();
            break;
        case 7:
            exit(1);
        default:
            printf("INVALID CHOICE\n");
            break;
        };
    }

    return 0;
}

int addNewBook()
{
    // creating a temporary node which adds new row to books list
    Temp_Book = (struct Book *)malloc(sizeof(struct Book));

    printf("Enter the following details:\n");
    printf("Enter ID of the book: ");
    scanf("%d", &(Temp_Book->Id));
    if (isUnique(Temp_Book->Id) == false)
    {
        printf("Conflicting Book Id's\n");
        return 0;
    }
    printf("Enter Name of the book: ");
    scanf(" %[^\n]", (Temp_Book->Name));
    printf("Enter Name of the Author:");
    scanf(" %[^\n]", (Temp_Book->Author));
    Temp_Book->Issued = false;
    Temp_Book->studentID = 0;

    // if table is empty, Node is added at start
    if (Book_table == NULL)
    {
        Book_table = Temp_Book;
        Temp_Book->Next = NULL;
        printf("Book successfully added\n");
        return 0;
    }
    // if Node is not empty its added at last
    Temp_Book_insert = Book_table;
    while (Temp_Book_insert->Next != NULL)
    {
        Temp_Book_insert = Temp_Book_insert->Next;
    }
    Temp_Book_insert->Next = Temp_Book;
    Temp_Book->Next = NULL;
    return 0;
}

int issueBook()
{

    printf("Enter book ID to check for avalibility\n");
    scanf("%d", &Book_ID);

    if (bookIssuedOrNot(Book_ID) == true)
    {
        printf("Sorry! Book is not avalible return after few days\n");
        return 0;
    }

    // creating a temporary student details node
    Temp_student = (struct Student *)malloc(sizeof(struct Student));

    printf("Book is avalible\nEnter Student details\n");
    printf("Student ID : ");
    scanf("%d", &(Temp_student->Id));
    printf("Student Name : ");
    scanf(" %[^\n]", (Temp_student->Name));
    printf("Book ID : ");
    scanf("%d", &(Temp_student->Book_ID));
    printf("Book Name : ");
    scanf(" %[^\n]", (Temp_student->Book_name));
    printf("Issued Date(dd/mm/yy): ");
    scanf("%s", (Temp_student->Issued_date));
    printf("Due Date(dd/mm/yy): ");
    scanf("%s", (Temp_student->Due_date));
    Temp_student->returned = false;
    Temp_student->Next = NULL;

    // adding student id to the book
    Temp_Book = Book_table;
    while (Temp_Book->Id != Temp_student->Book_ID)
    {
        Temp_Book = Temp_Book->Next;
    }

    // checks if book is exisiting in the library
    if (Temp_Book == NULL)
    {
        printf("No such book in library with id %d\n", (Temp_student->Book_ID));
        return 0;
    }
    Temp_Book->studentID = Temp_student->Id;
    Temp_Book->Issued = true;

    // checking if table is empty or not
    if (Student_table == NULL)
    {
        Student_table = Temp_student;
        return 0;
    }

    // adding new row to student table
    Temp_student_insert = Student_table;
    while (Temp_student_insert->Next != NULL)
    {
        Temp_student_insert = Temp_student_insert->Next;
    }
    Temp_student_insert->Next = Temp_student;
    return 0;
}

int returnBook()
{
    printf("Enter the following details\n");
    printf("Student Id : ");
    scanf("%d", &Student_ID);
    printf("\nBook ID : ");
    scanf("%d", &Book_ID);

    Temp_student = Student_table;
    Temp_Book = Book_table;
    while (Temp_student->Id != Student_ID && Temp_student->Book_ID != Book_ID && Temp_student != NULL && Temp_student != NULL)
    {
        Temp_Book = Temp_Book->Next;
        Temp_student = Temp_student->Next;
    }

    if (Temp_student == NULL)
    {
        printf("NO student with the given student id %d\n", Student_ID);
        return 0;
    }
    else if (Temp_Book == NULL)
    {
        printf("NO book was issued  with the given book id %d\n", Book_ID);
        return 0;
    }

    printf("Return Date(dd/mm/yy) : ");
    scanf("%s", (Temp_student->Return_date));

    Temp_student->returned = true;
    Temp_Book->Issued = false;
    return 0;
}

int pendingBooks()
{
    int count = 0;
    printf("Enter Student Id:");
    scanf("%d", &Student_ID);

    Temp_student = Student_table;
    while (Temp_student != NULL)
    {
        if (Temp_student->Id == Student_ID && Temp_student->returned == false)
        {
            count++;
            printf("| %s | %d | %s | %s (Issued Date) | %s (Due Date) |", Temp_student->Name, Temp_student->Book_ID, Temp_student->Book_name, Temp_student->Issued_date, Temp_student->Due_date);
        }
        Temp_student = Temp_student->Next;
    }

    if (count == 0)
    {
        printf("NO RECORDS FOUND\n");
        return 0;
    }

    return 0;
}

int displayStudentRecord()
{

    Temp_student = Student_table;

    while (Temp_student != NULL)
    {
        if (Temp_student->returned == false)
        {
            printf("| %d      | %s        | %d       | %s            | %s (Issued Date) | %s (Due Date) | Didnt Return Yet | Pending   |", Temp_student->Id, Temp_student->Name, Temp_student->Book_ID, Temp_student->Book_name, Temp_student->Issued_date, Temp_student->Due_date);
        }
        else
        {
            printf("| %d      | %s        | %d       | %s            | %s (Issued Date) | %s (Due Date) | %s (Return Date) | Submitted |", Temp_student->Id, Temp_student->Name, Temp_student->Book_ID, Temp_student->Book_name, Temp_student->Issued_date, Temp_student->Due_date, Temp_student->Return_date);
        }
        Temp_student = Temp_student->Next;
    }

    return 0;
}

int displayBookRecord()
{

    Temp_Book = Book_table;

    while (Temp_Book != NULL)
    {
        if (Temp_Book->Issued == true)
        {
            printf("| %d    | %s    (Name)| %s      (Author)|  Issued     |", Temp_Book->Id, Temp_Book->Name, Temp_Book->Author);
        }
        else
        {
            printf("| %d    | %s    (Name)| %s      (Author)|  NOT Issued |", Temp_Book->Id, Temp_Book->Name, Temp_Book->Author);
        }
        Temp_Book = Temp_Book->Next;
    }

    return 0;
}

bool bookIssuedOrNot(int Book_ID)
{
    Temp_Book_Check = Book_table;

    if (Temp_Book_Check == NULL)
    {
        return true;
    }
    while (Temp_Book_Check != NULL)
    {
        if (Temp_Book_Check->Id == Book_ID)
        {
            if (Temp_Book_Check->Issued == true)
            {
                return true;
            }
        }
        Temp_Book_Check = Temp_Book_Check->Next;
    }

    if (Temp_Book_Check == NULL)
    {
        return false;
    }
}

bool isUnique(int Book_ID)
{
    Temp_Book_Check = Book_table;
    if (Temp_Book_Check == NULL)
    {
        return true;
    }
    while (Temp_Book_Check != NULL)
    {
        if (Temp_Book_Check->Id == Book_ID)
        {
            return false;
            break;
        }
        Temp_Book_Check = Temp_Book_Check->Next;
    }
    if (Temp_Book_Check == NULL)
    {
        return true;
    }
}
