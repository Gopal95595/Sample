#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include <iomanip>
using namespace std;
class IIITD
{
public:
    int budget = 1000;
    int requests;
    string most_requested_journal = "IEEE Transactions on Reliability";
    // string subscribed_journal = most_requested_journal;
};
class Library : public IIITD
{
public:
    // Define data structures to store library items, user data, and borrowing records.

    // Method to add items to the library from a CSV file.
    void addItemsFromCSV(const std::string &csvFileName, string userName, string userType);

    void student();
    void faculty();
    IIITD obj;
    int budget = obj.budget;
    string subscribed_journal = obj.most_requested_journal;
    // Method to borrow items based on user type, update due dates, and maintain records.
    void borrowItem(const std::string &userName, string &userType, const std::string &itemTitle, bool isonLoan, bool iselectronic);

    // Starting method
    void get();

    void fetchBookDetails(string userName, string userType, string *book_idcolumn, string *isbn_column, string *book_title, string *authors_column);
    // Method to purchase new items for the library's collection.
    void purchaseItem(const std::string &userName, string &userType, const std::string &itemTitle);
    // void purchaseItem(const LibraryItem &newItem);
    void borrowonLoan(const std::string &userName, string &userType);
};
void Library ::addItemsFromCSV(const std::string &csvFileName, string userName, string userType)
{
    if (csvFileName == "Books.csv")
    {
        const int maxRows = 99; // Maximum number of rows

        std::ifstream inputFile("Books.csv"); // Open the CSV file

        std::string book_idcolumn[maxRows];
        std::string isbn_column[maxRows];              // Array to store values of index
        std::string authors_column[maxRows];           // Array to store values of year
        std::string original_publicationyear[maxRows]; // Array to store values of interest rate
        std::string book_title[maxRows];               // Array to store values of inflation

        std::string line;
        // std::getline(inputFile, line); // Read the first line (header) and discard

        int row = 0, i, k;
        string book_name = "";
        // Read each line of the file
        while (std::getline(inputFile, line) && row < maxRows)
        {
            std::stringstream ss(line);
            std::string value;

            std::getline(ss, value, ','); // Read value from column 1
            book_idcolumn[row] = value;

            // discarding unnecessary values
            for (int i = 0; i <= 3; i++)
            {
                std::getline(ss, value, ',');
            }

            // Read each value (comma-separated) from the line
            std::getline(ss, value, ','); // Read value from column 1
            isbn_column[row] = value;

            std::getline(ss, value, ','); // discarding isbn+

            std::getline(ss, value, ','); // Read value from column 2
            authors_column[row] = value;

            std::getline(ss, value, ','); // Read value from column 3
            original_publicationyear[row] = value;

            std::getline(ss, value, ','); // Read value from column 3
            book_title[row] = value;

            row++;
        }
        for (int i = 0; i <= 90; i++)
        {
            cout << book_idcolumn[i] << "\t\t" << isbn_column[i] << "\t\t " << book_title[i] << endl;
        }
        fetchBookDetails(userName, userType, book_idcolumn, isbn_column, book_title, authors_column);
    }
    if (csvFileName == "magazines.csv")
    {
        const int maxRows = 81; // Maximum number of rows

        std::ifstream inputFile("magazines.csv"); // Open the CSV file

        std::string publication[maxRows];
        std::string rank_no[maxRows];   // Array to store values of rank
        std::string totalPaid[maxRows]; // Array to store values of totalpaid
        std::string wordRate[maxRows];  // Array to store values of wordRate

        std::string line;

        int row = 0, i, k;
        string magazine_name = "";
        // Read each line of the file
        while (std::getline(inputFile, line) && row < maxRows)
        {
            std::stringstream ss(line);
            std::string value;

            std::getline(ss, value, ','); // Read value from column 1
            publication[row] = value;

            // Read each value (comma-separated) from the line
            std::getline(ss, value, ','); // Read value from column 1
            rank_no[row] = value;

            std::getline(ss, value, ','); // Read value from column 2
            totalPaid[row] = value;

            std::getline(ss, value, ','); // Read value from column 3
            wordRate[row] = value;

            row++;
        }
        for (int i = 0; i <= 79; i++)
        {
            cout << publication[i] << "\t\t\t\t " << rank_no[i] << endl;
        }
        cout << "\n\n\t Select the Magazine u want to borrow from above list\n";
        cout << "\n\n\t select which one u want to Enter\n\n\t1.Publication\n\n\t2.Rank ";
        cout << "\n\n\tEnter your choice : ";
        cin >> k;
        if (k == 1)
        {
            cout << "\n\n\t Enter the Publication name :: ";
            string pub;
            cin >> pub;
            cout << "\n\n\t Do You Want to Borrow it : \n\n\t1.Borrow\n\n\t2.No Go TO HOME ";
            int in;
            cin >> in;
            if (in == 1)
            {
                borrowItem(userName, userType, pub, false, false);
            }
            else
            {
                get();
            }
        }
        if (k == 2)
        {
            cout << "\n\n\t Enter the Rank :: ";
            string r = "";
            string pub_name = "";
            int p = 0;
            cin >> r;
            string quotedStr = "\"" + r + "\"";
            for (int i = 0; i <= 79; i++)
            {
                if (quotedStr == rank_no[i])
                {
                    p = i;
                }
            }
            pub_name = publication[p];
            cout << "\n\n\t Do You Want to Borrow it : \n\n\t1.Borrow\n\n\t2.No Go TO HOME ";
            int in;
            cin >> in;
            if (in == 1)
            {
                borrowItem(userName, userType, pub_name, false, false);
            }
            else
            {
                get();
            }
        }
    }
    if (csvFileName == "journals.csv")
    {
        const int maxRows = 99; // Maximum number of rows

        std::ifstream inputFile("journals.csv"); // Open the CSV file

        std::string journals[maxRows];

        std::string line;
        string journalName = "";
        int row = 0;
        // Read each line of the file
        while (std::getline(inputFile, line) && row < maxRows)
        {
            std::stringstream ss(line);
            std::string value;

            std::getline(ss, value, ','); // Read value from column 1
            journals[row] = value;

            row++;
        }
        for (int i = 0; i <= 98; i++)
        {
            cout << journals[i] << endl;
        }
        cout << "\n\n\t Enter the name of journal you want Borrow :: ";
        cin.ignore();
        getline(cin, journalName);
        borrowItem(userName, userType, journalName, false, true);
    }
};
void Library ::student()
{
    int i, o;
    cout << "\n\t************ WELCOME STUDENT ************\n";
    cout << "\n\t\t>>Please Choose One Option:\n";
    cout << "\n\t\t1.Existing_user\n\n\t\t2.New_User\n\n\t\t3.Close Application";
    cout << "\n\t\tEnter your choice : ";
    cin >> o;
    string userName;
    string userType;
    if (o == 1)
    {
        cout << "\n\t\t Enter your userName :: ";
        cin >> userName;
        userType = "student";
    }
    else if (o == 2)
    {
        cout << "\n\t\t Create your userName :: ";
        cin >> userName;
        userType = "student";
        cout << "\n\t\t userType is intialized : : " << userType;
    }
    else if (o == 3)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        student();
    }
    cout << "\n\t\t>>Please Choose the item which you want to view from below :\n";
    cout << "\n\t\t1.Books\n\n\t\t2.magazines\n\n\t\t3.News Paper\n\n\t\t4.Journals\n\n\t\t5.Subscribed Journal\n\n\t\t6.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
    {
        addItemsFromCSV("Books.csv", userName, userType);
    }
    else if (i == 2)
    {
        addItemsFromCSV("magazines.csv", userName, userType);
    }
    else if (i == 3)
    {
        int k;
        // cout << "Currently not Not Available please Comeback later";
        cout << "\n\n\t Do you Want Borrow it \n\n\t1.Yes \n\n\t2.No Go To Home";
        cout << "\n\n\tEnter your choice : :  ";
        cin >> k;
        if (k == 1)
        {
            borrowItem(userName, userType, "News_Paper", false, true);
        }
        else
        {
            get();
        }
    }
    else if (i == 4)
    {
        addItemsFromCSV("journals.csv", userName, userType);
    }
    else if (i == 5)
    {
        int k;
        cout << "\n\n\tThe Library Subscribed Journal is :: " << subscribed_journal;
        cout << "\n\n\t Do you Want Borrow it \n\n\t1.Yes \n\n\t2.No Go To Home";
        cout << "\n\n\tEnter your choice : :  ";
        cin >> k;
        if (k == 1)
        {
            borrowItem(userName, userType, subscribed_journal, false, true);
        }
        else
        {
            get();
        }
    }
    else if (i == 6)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        student();
    }
};
void Library ::faculty()
{
    int i, o;
    cout << "\n\t************ WELCOME FACULTY ************\n";
    cout << "\n\t\t>>Please Choose One Option:\n";
    cout << "\n\t\t1.Existing_user\n\n\t\t2.New_User\n\n\t\t3.Close Application";
    cout << "\n\t\tEnter your choice : ";
    cin >> o;
    string userName;
    string userType;
    if (o == 1)
    {
        cout << "\n\t\t Enter your userName :: ";
        cin >> userName;
        userType = "faculty";
    }
    else if (o == 2)
    {
        cout << "\n\t\t Create your userName :: ";
        cin >> userName;
        userType = "faculty";
        cout << "\n\t\t userType is intialized : : " << userType;
    }
    else if (o == 3)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        faculty();
    }
    cout << "\n\t\t>>Please Choose the item which you want to view from below :\n";
    cout << "\n\t\t1.Books\n\n\t\t2.magazines\n\n\t\t3.News Paper\n\n\t\t4.Journals\n\n\t\t5.Subscribed Journal\n\n\t\t6.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
    {
        addItemsFromCSV("Books.csv", userName, userType);
    }
    else if (i == 2)
    {
        addItemsFromCSV("magazines.csv", userName, userType);
    }
    else if (i == 3)
    {
        int k;
        cout << "\n\n\t Do you Want Borrow it \n\n\t1.Yes \n\n\t2.No Go To Home";
        cout << "\n\n\tEnter your choice : :  ";
        cin >> k;
        if (k == 1)
        {
            borrowItem(userName, userType, "News_Paper", false, true);
        }
        else
        {
            get();
        }
    }
    else if (i == 4)
    {
        addItemsFromCSV("journals.csv", userName, userType);
    }
    else if (i == 5)
    {
        int k;
        cout << "\n\n\tThe Library Subscribed Journal is :: " << subscribed_journal;
        cout << "\n\n\t Do you Want Borrow it \n\n\t1.Yes \n\n\t2.No Go To Home";
        cout << "\n\n\tEnter your choice : :  ";
        cin >> k;
        if (k == 1)
        {
            borrowItem(userName, userType, subscribed_journal, false, true);
        }
        else
        {
            get();
        }
    }
    else if (i == 6)
    {
        exit(0);
    }
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        student();
    }
}
void Library ::borrowItem(const std::string &userName, string &userType, const std::string &itemTitle, bool isonLoan, bool iselectronic)
{
    // Get the current date
    std::time_t currentTime = std::time(nullptr);
    if (isonLoan)
    {
        // Calculate the return date (30 days from the issue date)
        const int secondsPerDay = 24 * 60 * 60; // Number of seconds in a day
        std::time_t returnTime = currentTime + 7 * secondsPerDay;

        struct tm *returnDate = std::localtime(&returnTime);

        cout << "\n\n\t Borrowing Details\n";
        cout << "\n\t userName is : : " << userName;
        cout << "\n\n\t userType is  : :" << userType;
        cout << "\n\n\t Borrowing item is : :" << itemTitle;
        // Print the issue date and return date
        std::cout << "\n\n\t Issue Date: " << std::put_time(std::localtime(&currentTime), "%Y-%m-%d");
        std::cout << "\n\n\t Due Date: " << std::put_time(localtime(&returnTime), "%Y-%m-%d");

        // storing record in a file
        std::ofstream outputFile("borrowing_details.txt");

        // Check if the file was successfully opened
        if (!outputFile.is_open())
        {
            std::cerr << "Error: Cannot open the file for writing." << std::endl;
            // return 1;
        }

        // Write the borrowing details to the file
        outputFile << "Borrowing Details" << std::endl;
        outputFile << "userName is : " << userName << std::endl;
        outputFile << "userType is : " << userType << std::endl;
        outputFile << "Borrowing item is : " << itemTitle << std::endl;
        outputFile << "Issue Date: " << put_time(std::localtime(&currentTime), "%Y-%m-%d") << std::endl;
        outputFile << "Due Date: " << put_time(localtime(&returnTime), "%Y-%m-%d") << std::endl;

        // Close the file
        outputFile.close();
    }
    else if (userType == "student")
    {
        const int secondsPerDay = 24 * 60 * 60; // Number of seconds in a day
        std::time_t returnTime = currentTime + 30 * secondsPerDay;

        struct tm *returnDate = std::localtime(&returnTime);

        cout << "\n\n\t Borrowing Details\n";
        cout << "\n\t userName is : : " << userName;
        cout << "\n\n\t userType is  : :" << userType;
        cout << "\n\n\t Borrowing item is : :" << itemTitle;
        // Print the issue date and return date
        std::cout << "\n\n\t Issue Date: " << std::put_time(std::localtime(&currentTime), "%Y-%m-%d");
        if (!iselectronic)
        {
            std::cout << "\n\n\t Due Date: " << std::put_time(localtime(&returnTime), "%Y-%m-%d");
        }
        // storing record in a file
        std::ofstream outputFile("borrowing_details.txt");

        // Check if the file was successfully opened
        if (!outputFile.is_open())
        {
            std::cerr << "Error: Cannot open the file for writing." << std::endl;
        }

        // Write the borrowing details to the file
        outputFile << "Borrowing Details" << std::endl;
        outputFile << "userName is : " << userName << std::endl;
        outputFile << "userType is : " << userType << std::endl;
        outputFile << "Borrowing item is : " << itemTitle << std::endl;
        outputFile << "Issue Date: " << put_time(std::localtime(&currentTime), "%Y-%m-%d") << std::endl;
        if (!iselectronic)
        {
            outputFile << "Due Date: " << put_time(localtime(&returnTime), "%Y-%m-%d") << std::endl;
        }
        // Close the file
        outputFile.close();
    }
    else
    {
        const int secondsPerDay = 24 * 60 * 60; // Number of seconds in a day
        std::time_t returnTime = currentTime + 6 * 30 * secondsPerDay;

        struct tm *returnDate = std::localtime(&returnTime);

        cout << "\n\n\t Borrowing Details\n";
        cout << "\n\t userName is : : " << userName;
        cout << "\n\n\t userType is  : :" << userType;
        cout << "\n\n\t Borrowing item is : :" << itemTitle;
        // Print the issue date and return date
        std::cout << "\n\n\t Issue Date: " << std::put_time(std::localtime(&currentTime), "%Y-%m-%d");
        if (!iselectronic)
        {
            std::cout << "\n\n\t Due Date: " << std::put_time(localtime(&returnTime), "%Y-%m-%d");
        }
        // storing record in a file
        std::ofstream outputFile("borrowing_details.txt");

        // Check if the file was successfully opened
        if (!outputFile.is_open())
        {
            std::cerr << "Error: Cannot open the file for writing." << std::endl;
        }

        // Write the borrowing details to the file
        outputFile << "Borrowing Details" << std::endl;
        outputFile << "userName is : " << userName << std::endl;
        outputFile << "userType is : " << userType << std::endl;
        outputFile << "Borrowing item is : " << itemTitle << std::endl;
        outputFile << "Issue Date: " << put_time(std::localtime(&currentTime), "%Y-%m-%d") << std::endl;
        if (!iselectronic)
        {
            std::cout << "\n\n\t Due Date: " << std::put_time(localtime(&returnTime), "%Y-%m-%d");
        }
        // Close the file
        outputFile.close();
    }
    std::cout << "Borrowing details saved to 'borrowing_details.txt'." << std::endl;
}
void Library ::purchaseItem(const std::string &userName, string &userType, const std::string &itemTitle)
{
    // Get the current date
    std::time_t currentTime = std::time(nullptr);

    // Calculate the return date (30 days from the issue date)
    const int secondsPerDay = 24 * 60 * 60; // Number of seconds in a day
    std::time_t returnTime = currentTime + 30 * secondsPerDay;

    struct tm *returnDate = std::localtime(&returnTime);

    cout << "\n\n\t Purchase Details\n";
    cout << "\n\t userName is : : " << userName;
    cout << "\n\n\t userType is  : :" << userType;
    cout << "\n\n\t Purchase item is : :" << itemTitle;
    // Print the issue date and return date
    std::cout << "\n\n\t Purchase Date: " << std::put_time(std::localtime(&currentTime), "%Y-%m-%d");

    // storing record in a file
    std::ofstream outputFile("purchase_details.txt");

    // Check if the file was successfully opened
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Cannot open the file for writing." << std::endl;
    }

    // Write the borrowing details to the file
    outputFile << "Purchase Details" << std::endl;
    outputFile << "userName is : " << userName << std::endl;
    outputFile << "userType is : " << userType << std::endl;
    outputFile << "Purchase item is : " << itemTitle << std::endl;
    outputFile << "Purchase Date: " << put_time(std::localtime(&currentTime), "%Y-%m-%d") << std::endl;

    // Close the file
    outputFile.close();

    std::cout << "Purchase details saved to 'purchase_details.txt'." << std::endl;
}
void Library ::borrowonLoan(const std::string &userName, string &userType)
{
    string book_title;
    int j = 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "\n\n\t Enter the Book Title you are looking for :: ";
    std::getline(std::cin, book_title);
    string nearbylibraries[] = {"ikigai", "wings of fire", "godfather"};
    for (int i = 0; i < size(nearbylibraries); i++)
    {
        if (book_title == nearbylibraries[i])
        {
            cout << "\n\n\t book found in the nearby Library ";
            cout << "\n\t you can Borrow it for 7 Days Enter\n\n\t1.Borrow\n\n\t2.Go To Home";
            cout << "\n\t Enter Your choice : : ";
            cin >> j;
            if (j == 1)
            {
                borrowItem(userName, userType, book_title, true, false);
            }
            else
            {
                get();
            }
        }
    }
    if (j == 0) // if book is not found in nearby libraries
    {
        cout << "Sorry Book Not Found :(";
    }
}
void Library ::fetchBookDetails(string userName, string userType, string *book_idcolumn, string *isbn_column, string *book_title, string *authors_column)
{
    int i, k;
    string book_name = "";
    string isbn = "";
    string author_name = "";
    cout << "\n\n\t Select the book u want to borrow from above list\n";
    cout << "\n\n\t select which one u want to Enter\n\n\t1.book_id\n\n\t2.isbn\n\n\t3.Book_Title\n\n\t4.Book_Not_Found ";
    cout << "\n\t\tEnter your choice : ";
    cin >> k;
    if (k == 1)
    {
        cout << "\n\n\t Enter the book_id :: ";
        int book_id;
        cin >> book_id;
        book_name = book_title[book_id];
        isbn = isbn_column[book_id];
        author_name = authors_column[book_id];
        cout << "\n\n\t Book Details :: ";
        cout << "\n\n\t Book Name :: " << book_name;
        cout << "\n\n\t ISBN No : : " << isbn;
        cout << "\n\n\t Author Name : : " << author_name;
        cout << "\n\n\t Book Location : : Shelf No-" << book_id;
        cout << "\n\n\t select ::\n\n\t1.Borrow\n\n\t2.Purchase\n\n\t3.Go To Home ";
        cout << "\n\t\tEnter your choice : ";
        int in;
        cin >> in;
        if (in == 1)
        {
            borrowItem(userName, userType, book_name, false, false);
        }
        else if (in == 2)
        {
            purchaseItem(userName, userType, book_name);
        }
        else
        {
            get();
        }
    }
    else if (k == 2)
    {
        string n;
        int k;
        cout << "\n\n\t Enter the isbn_id :: ";
        cin >> n;
        for (int i = 0; i <= 90; i++)
        {
            if (n == isbn_column[i])
                k = i;
        }
        book_name = book_title[k];
        isbn = isbn_column[k];
        author_name = authors_column[k];
        cout << "\n\n\t Book Details :: ";
        cout << "\n\n\t Book Name :: " << book_name;
        cout << "\n\n\t ISBN No : : " << isbn;
        cout << "\n\n\t Author Name : : " << author_name;
        cout << "\n\n\t Book Location : : Shelf No-" << k;
        cout << "\n\n\t select ::\n\n\t1.Borrow\n\n\t2.Purchase\n\n\t3.Go To Home ";
        cout << "\n\t\tEnter your choice : ";
        int in;
        cin >> in;
        if (in == 1)
        {
            borrowItem(userName, userType, book_name, false, false);
        }
        else if (in == 2)
        {
            purchaseItem(userName, userType, book_name);
        }
        else
        {
            get();
        }
    }
    else if (k == 3)
    {
        int j = 0;
        string bt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\n\t Enter the book_title :: ";
        std::getline(std::cin, bt);
        for (int i = 0; i <= 90; i++)
        {
            if (bt == book_title[i])
            {
                j = i;
            }
        }
        book_name = book_title[j];
        isbn = isbn_column[j];
        author_name = authors_column[j];
        cout << "\n\n\t Book Details :: ";
        cout << "\n\n\t Book Name :: " << book_name;
        cout << "\n\n\t ISBN No : : " << isbn;
        cout << "\n\n\t Author Name : : " << author_name;
        cout << "\n\n\t Book Location : : Shelf No-" << j;
        cout << "\n\n\t select ::\n\n\t1.Borrow\n\n\t2.Purchase\n\n\t3.Go To Home ";
        cout << "\n\t\tEnter your choice : ";
        int o;
        cin >> o;
        if (o == 1)
        {
            borrowItem(userName, userType, book_name, false, false);
        }
        else if (o == 2)
        {
            purchaseItem(userName, userType, book_name);
        }
        else
        {
            get();
        }
    }
    else if (k == 4)
    {
        int i = 0;
        cout << "\n\n\t Do You want to search Book in nearby libraries::\n\n\t1.Yes\n\n\t2.No Go To Home";
        cout << "\n\n\tEnter your choice : :  ";
        cin >> i;
        if (i == 1)
        {
            borrowonLoan(userName, userType);
        }
        else
        {
            get();
        }
    }
    else
    {
        cout << "invalid input";
        exit(0);
    }
}
void Library ::get()
{
    int i;
    cout << "\n\t*********** LIBRARY MANAGEMENT SYSTEM ***********\n"
         << "\n\t\t\t    L M S C++\n";
    cout << "\n\t\t>>Please Choose Any Option To login \n";
    cout << "\n\t\t1.Student\n\n\t\t2.Faculty\n\n\t\t3.Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
    {
        student();
    }
    else if (i == 2)
        faculty();

    else if (i == 3)
        exit(0);
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        get();
    }
}
int main()
{
    Library obj;
    obj.get();
    return 0;
}
