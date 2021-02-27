#include <iostream>
#include <cstdlib>
#include <string> 
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void givereport();                //function prototyping 
string printName(ifstream&, string);
int printID(ifstream&, string);
void printgrades(ifstream&, string, int);
int getcredit(ifstream&, string); 
int getgradevalue(ifstream&, string);
void calculate(string, int, float, float); 
void calculatecredittotal(string, int, float, float);

int main()
{
    int id1 = 2333021;
    int id2 = 2574063;
    int id3 = 2663628;
    string name1 = "Bokow, R.";
    string name2 = "Fallin, D.";
    string name3 = "Kingsley, M.";      //declaration of variables for each student
    int credits1 = 0;
    int credits2 = 0;
    int credits3 = 0;
    float GPA1 = 0;
    float GPA2 = 0;
    float GPA3 = 3;

    string class1[3][3] = { { "NS201", "MG342", "FA302" },                  // first variable are ROWS
                            {   "3",     "3",     "1"},                     // second variable are COLUMNS 
                            {   "A",     "A",     "A"} };

    string class2[3][4] = { { "MK106", "MA208", "CM201", "CP101" },
                            {   "3",     "3",     "3",     "2"},
                            {   "C",     "B",     "C",     "B"} };
    string class3[3][5] = { { "QA140", "CM245", "EQ521", "MK341", "CP101"},
                            {   "3",     "3",     "3",     "3",     "2"},
                            {   "A",     "B",     "A",     "A",     "B"}, };

    ofstream outFile;               //creating file output stream and opening file
    outFile.open("grades.dat");
    if (outFile.fail())             //check for successful file access
    {
        cout << "The File was not successully opened" << endl;
        exit(1);
    }

    outFile << setiosflags(ios::fixed)  // file formatting 
        << setiosflags(ios::showpoint)
        << setprecision(2);

    outFile << id1 << "\n" << name1 << "\n" << class1[0][0] << "\n" << class1[1][0] << "\n" << class1[2][0] << "\n" <<  // newline characters are used here to ensure that the getline() function can be used later in the program to great effect.
               id1 << "\n" << name1 << "\n" << class1[0][1] << "\n" << class1[1][1] << "\n" << class1[2][1] << "\n" << 
               id1 << "\n" << name1 << "\n" << class1[0][2] << "\n" << class1[1][2] << "\n" << class1[2][2] << "\n" << 

               id2 << "\n" << name2 << "\n" << class2[0][0] << "\n" << class2[1][0] << "\n" << class2[2][0] << "\n" <<
               id2 << "\n" << name2 << "\n" << class2[0][1] << "\n" << class2[1][1] << "\n" << class2[2][1] << "\n" <<
               id2 << "\n" << name2 << "\n" << class2[0][2] << "\n" << class2[1][2] << "\n" << class2[2][2] << "\n" <<
               id2 << "\n" << name2 << "\n" << class2[0][3] << "\n" << class2[1][3] << "\n" << class2[2][3] << "\n" <<

               id3 << "\n" << name3 << "\n" << class3[0][0] << "\n" << class3[1][0] << "\n" << class3[2][0] << "\n" <<
               id3 << "\n" << name3 << "\n" << class3[0][1] << "\n" << class3[1][1] << "\n" << class3[2][1] << "\n" <<
               id3 << "\n" << name3 << "\n" << class3[0][2] << "\n" << class3[1][2] << "\n" << class3[2][2] << "\n" <<
               id3 << "\n" << name3 << "\n" << class3[0][3] << "\n" << class3[1][3] << "\n" << class3[2][3] << "\n" <<
               id3 << "\n" << name3 << "\n" << class3[0][4] << "\n" << class3[1][4] << "\n" << class3[2][4] << "\n";

    outFile.close();    //close file for security 

    givereport();       
}
void givereport()       // a 'driver' function that calls the rest of the functions in the program for printing report cards. 
{
    ifstream inFile;    //inital filestream creation 
    inFile.open("grades.dat");
    string key;         //this variable holds the requested name and is passed to *every* function within this driver function 
    cout << "Please enter the name for the report card you'd like to view: ";
    getline(cin, key);  //getline is used instead of 'cin' so that more than one token is retrieved from stdin
    cout << "\n";

    cout << "Student Name: " << printName(inFile, key) << endl;
    cout << "Student ID: " << printID(inFile, key) << endl
        << "Course Code\t\bCourse Credits\t\bCourse Grade" << endl
        << "=============================================" << endl;
    inFile.seekg(0L, ios::beg);     //file cursor is sent to the beginning of the file so that 'printgrades' function can search file stream from the beginning 
    printgrades(inFile, key, 1);
    cout << "\n";
    cout << "Total Semester Course Credits Completed: ";
    inFile.close();     //filestream is closed for security
    calculatecredittotal(key, 0, 0, 0);
    cout << "Total GPA: ";
    calculate(key, 0, 0, 0);
}

string printName(ifstream& inFile, string key)  //function searches filestream for a single instance of the name held within 'key'
{
    string s; 
    getline(inFile, s);     //initalize 's'
    while (s.compare(key) != 0)     //this loop gets new lines from the filestream so long as the line grabbed (held in 's') does not match the requested name held in 'key'
    {
        getline(inFile, s);
        if (inFile.eof())   //if end of file is reached, program will stop searching 
        {
            break; 
        }
    }
    if (s.compare(key) == 0)
    {
        return s;
    }
    else                //this condition will only be met if the 'while' loop above ends prematurely via the break;
    {
        cout << "Whoops! Not name like that in my memory...";
        exit(1);
    }
} 

int printID(ifstream& inFile, string key)  //function searches filestream for a single instance of the name held in 'key,' then prints the associated ID number
{
    string s;
    getline(inFile, s); //initialize 's'
    while (s.compare(key) != 0) //loop gets new lines from the filestream so long as the line grabbed (held in 's') does not match the requested name held in 'key'
    {
        getline(inFile, s);
        if (inFile.eof())   //if eof() returns 'true,' program ends
        {
            cout << "Name not found!";
            exit(1);
        }
    }
    inFile.seekg(0L, ios::beg); //once a name is found, the cursor returns to the beginning of the file
    string real;
    getline(inFile, s); //feeds the first line of code into 's,' just like at the beginning of the function 
    while (s.compare(key) != 0) //searches through the program, once again looking for the name held in 'key' and comparing it to 's'
    {
        real = s;           //the difference is that 'real' is used to store the line of data before 's'. Because we know that the ID of the student is held in the line before the name of the student, 
        getline(inFile, s); //we know that 'real' will always store the ID of the student that is held in 's'. 
        if (inFile.eof())   //eof() check for safety, but this condition would never be met, since a similar check appears at the beginning of the program
        {
            break;
        }
    }

    stringstream temp(real);    //stringstream is used here to stream the string of numbers into an int variable
    int ID;
    temp >> ID;
    return ID;

}

void printgrades(ifstream& inFile, string key, int iterator) //takes the name of the student (held in 'key') and the filestream to search through the file for instances of the student's name,                                          
{               //with that information, we can grab the class ID's of whichever courses they took                                
    string s;   //once the proper class ID is found, the rest of the information is in the following lines, and can be easily attained.
    string d;
    string f;
    int placeholder = 1;    //placeholder variable keeps track of which iteration this recursive function is on 
    getline(inFile, s);     //initialize 's' with the first line from the filestream
    while (s.compare(key) != 0) //loop makes sure that the given student name exists within the file
    {
        getline(inFile, s);
        if (inFile.eof())
        {
            cout << "Guh! No students with that name found!";
            exit(1);
        }
    }
    while ((placeholder < iterator))    //because *every* line of text in the file starts with the students name, this while loop check to see if the current instance of the student's name has already been used to 
    {                                   //print grades by comparing the 'placeholder' variable with the current iteration of the recursive function 
        if (iterator > 1)               //this 'if' statement ensures that no instances of a student's name are skipped on the first iteration of this function
        {
            for (int i = 1; i <= 5; i++) //we know that if the cursor is on an instance of a student's name (which, thanks to the while loop above, we know to be true), then another student's name will appear five lines down in the text file;
            {                            //thus, if we are on a new iteration of the recurtsive function, we skip ahead five lines to avoid repeating the same line of grades 
                getline(inFile, s);
                if (inFile.eof())       //if eof() == true, then we simply set placeholder = 100, ensuring the while loop will not execute again. If this program were designed for an *actual* school system, this number could be increased to accomodate for an 
                {                       //increased volume of students
                    placeholder = 100;
                }
            }
        }
        if (s.compare(key) == 0 || s.compare(""))   // if we find that the new student's name (found after the above 'for' loop) is equal to the name stored in 'key', then we increment 'placeholder' signalling that we have already printed this student's name 
        {                                           //in a previous iteration of the function 
            placeholder++;  
        }
    }
    if (s.compare(key) == 0)
    {
        getline(inFile, s); //stores a class ID in 's'
        getline(inFile, d); //stores a class credit value in 'd'
        getline(inFile, f); //stores a class grade in 'f'
        cout  << s << "\t\t" << d << "\t\t" << f << endl;   //prints all of the string variables in sequence to create a well organized report card
        while (s.compare(key) != 0) //this loop searches the rest of the file for a new occurence of the student's name, if one is found, then we know that the function must be recursively called 
        {
            getline(inFile, s);
            
            if (inFile.eof())   //if eof() == true, then we break and exit the 'if' statments, ending the function
            {
                break;
            }
        }
        
        if (s.compare(key) == 0)    // if an occurence of the student's name held in 'key' occurs, this statement recursively calls the current function in order to print the new class and grade 
        {
            inFile.seekg(0L, ios::beg); //for the filestream to behave properly, the cursor must be set back to the beginning 
            iterator++;                 //iterator is incremented, ensuring that the grade just printed is not printed a second time 
            printgrades(inFile, key, iterator); //recursive call 
        }
    }
    else
    {
        cout << "Whoops! Not name like that in my memory...";
    }

}

void calculate(string key, int iterator, float passedcredits, float passedgrades) //takes a student's name (held in 'key') as input so that it may calculate the student's GPA
{
    ifstream inFile;    //previous iterations of this program did not function properly if the filestream was passed into this function, so a new one is created within the function instead
    inFile.open("grades.txt");
    string s;
    int placeholder = 0; //this variable fulfils the same purpose as in the 'printgrades' function. because this function will be called recursively, it is important to keep track of how many times it has iterated 
    string credit;
    string grade;
    float creditstotal = passedcredits;
    float GPA = passedgrades;
    bool finalanswer = false;
    getline(inFile, s); //initialize 's' with the first line of the filestream 
    if (inFile.good())  //precautionary measure to ensure the file opens correctly. if it does not, infinite loops will often occur within the while() statements 
    {
        while (s.compare(key) != 0) //this loops searches for an occurence of the student's name held within 'key' by comparing it to the string from the file held within 's'
        {
            getline(inFile, s);
            if (inFile.eof())
            {
                inFile.seekg(0L, ios::beg);
            }
        }
        while ((placeholder < iterator))    //like the 'printgrades' function, this 'while' statement ensures that grades being calculated into the GPA have not been calculated on previous iterations
        {
            for (int i = 1; i <= 5; i++)//Like the previous function, we know that if the cursor is on an instance of a student's name (which, thanks to the while loop above, we know to be true), then another student's name will appear five lines down in the text file;                             
            {                           //thus, if we are on a new iteration of the recurtsive function, we skip ahead five lines to avoid repeating the same line of grades
                getline(inFile, s);
                if (inFile.eof())    //if eof() == true, then we simply set placeholder = 100, ensuring the while loop will not execute again. If this program were designed for an *actual* school system, this number could be increased to accomodate for an                     
                {                    //increased volume of students
                    placeholder = 100;
                }
            }
            if (s.compare(key) == 0 || s.compare(""))   // if we find that the new student's name (found after the above 'for' loop) is equal to the name stored in 'key', then we increment 'placeholder' signalling that we have already printed this student's name 
            {                                           //in a previous iteration of the function 
                placeholder++;
            }
        }

        if (s.compare(key) == 0)
        {
            getline(inFile, s); //stores the class ID in 's'
            getline(inFile, credit);    //stores the credit for the course in 'credit'
            getline(inFile, grade); //stores the grade of the course in 'grade'

            creditstotal = creditstotal + getcredit(inFile, s); //this function simply takes the string that holds the amount of credits the course is worth and returns it as an integer. The total amount of credits are needed to calculate GPA
            inFile.seekg(0L, ios::beg);                         //sends the cursor for the file stream back to the beginning so that it can function properly within the following functions 
            GPA = GPA + (getgradevalue(inFile, s) * getcredit(inFile, s));  //takes in information from the value of the grade earned for the given course and the credits said course was worth and uses them to calculate GPA

            while (s.compare(key) != 0) //this statement searches the filestream for other instances of the student's name, if one is found, then this function must be recursively called to account for additional classes taken by the student held in 'key'
            {
                getline(inFile, s);
                if (inFile.eof())   //if eof() == true, then we know that there are no more occurences of the student's name within the file stream, thus we set 'finalanswer' to be true so that the function prints its result and exits 
                {
                    finalanswer = true;
                    break;
                }
                else if (s.compare(key) == 0)   //if a new occurence of the student's name (held in 'key') is found in the file, then the function is recursively called and iterator is incremented, ensuring the class just counted into the GPA is not 
                {                               //taken into account again. 
                    iterator++;
                    inFile.seekg(0L, ios::beg);
                    calculate(key, iterator, creditstotal, GPA);
                }
            }
        }
        if (finalanswer || placeholder > iterator)
        {
            cout << fixed << setprecision(2) << GPA/creditstotal << endl;
        }
    }
}
void calculatecredittotal (/*ifstream& inFile,*/ string key, int iterator, float passedcredits, float passedgrades) //This function operateds *exactly* the same at the 'calculate' function, except that it calculates the total number of credits taken by the student
{
    ifstream inFile;
    inFile.open("grades.txt");
    if (inFile.fail())
    {
        cout << "kys";
    }
    string s = " ";
    int placeholder = 0;
    string credit;
    string grade;
    float creditstotal = passedcredits;
    float GPA = passedgrades;
    bool finalanswer = false;
    getline(inFile, s);
    while (s.compare(key) != 0)
    {
        getline(inFile, s);
        if (inFile.eof())
        {
            cout << "No Students with that name found!";
            exit(1);
        }
    }
    while ((placeholder < iterator))
    {
        for (int i = 1; i <= 5; i++)
        {
            getline(inFile, s);
            if (inFile.eof())
            {
                placeholder = 100;
            }
        }
        if (s.compare(key) == 0 || s.compare(""))
        {
            placeholder++;

        }
    }

        if (s.compare(key) == 0)
        {
            getline(inFile, s);
            getline(inFile, credit);
            getline(inFile, grade);

            creditstotal = creditstotal + getcredit(inFile, s);
            inFile.seekg(0L, ios::beg);
            GPA = GPA + (getgradevalue(inFile, s) * getcredit(inFile, s));

            while (s.compare(key) != 0)
            {
                getline(inFile, s);
                if (inFile.eof())
                {
                    finalanswer = true;
                    break;
                }
                else if (s.compare(key) == 0)
                {
                    iterator++;
                    inFile.seekg(0L, ios::beg);
                    calculatecredittotal(key, iterator, creditstotal, GPA);
                }
            }
        }
        if (finalanswer || placeholder > iterator)
        {
            cout << creditstotal << endl;
        }
    
}
int getcredit (ifstream& inFile, string key) // takes the CLASS ID as input and returns the weight, in credits, of that class
{
    inFile.seekg(0L, ios::beg); //filestream cursor must be brought back to the beginning of the file for this function to work correctly 
    string s;
    string d;
    int credit;
    getline(inFile, s);
    
    while (s.compare(key) != 0) //searches filestream for the correct class ID
    {
        getline(inFile, s);
        if (inFile.eof()) //this if statement is very unlikely to occurr, in fact I'm pretty sure its impossible to get this far in the program and have the name not show up in the file stream 
        {
            cout << "uhhhh, I can explain. *dashes out of room*\n *distant car door slams shut*\n *tires squeal out of parking lot*";
            exit(1);
        }
    }
    if (s.compare(key) == 0)
    {
        getline(inFile, d);
        stringstream temp(d); //stringstream is used here to convert the string holding the number of credits a class is worth to an int
        temp >> credit;
        return credit;
    }
    else
    {
        return -1;
    }
}

int getgradevalue(ifstream& inFile, string key) //tales the class ID as input and returns a value associated with a letter grade for the purposes of calculating weight and GPA
{
    string s;
    string d;
    inFile.seekg(0L, ios::beg);  //filestream cursor must be brought back to the beginning of the file for this function to work correctly 
    char grade;
    getline(inFile, s);
    while (s.compare(key) != 0) //searches filestream for the correct class ID 
    {
        
        if (inFile.eof())
        {
            inFile.seekg(0L, ios::beg);
        }
        else
        {
            getline(inFile, s);
        }
        //cout << "B";
    }
    if (s.compare(key) == 0) 
    {
        getline(inFile, d);
        getline(inFile, d);
        stringstream temp(d); //stringstream is used here to convert strings of grades into 'char'
        temp >> grade;

        if (grade == 'A')   //this loop is also doable with a 'switch' statment 
        {
            return 4;
        }
        else if (grade == 'B')
        {
            return 3;
        }
        else if (grade == 'C')
        {
            return 2;
        }
        else if (grade == 'D')
        {
            return 1;
        }
        else if (grade == 'F')
        {
            return 0;
        }
        else
        {
            cout << "I don't know what to say. This makes no sense...";
            exit(1);
        }
    }
    else
    {
        return -1;
    }
}