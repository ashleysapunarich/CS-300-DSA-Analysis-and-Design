//************************************
// ASHLEY SAPUNARICH
// PROJECT TWO
// SOUTHERN NEW HAMPSHIRE UNIVERSITY
// CS 300 ANALYSIS AND DESIGN
// MICHAEL SUSALLA
// APRIL 19 2025
//************************************



#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

vector<string> tokenize(const string& s, const string& del = ",") {
    vector<string> tokens;
    size_t start = 0, end = s.find(del);
    while (end != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    tokens.push_back(s.substr(start, end - start));
    return tokens;
}

vector<Course> loadCoursesFromFile() {
    //used file as a .txt instead of a .csv

    ifstream fin("ProjectCourseFile.txt", ios::in);
    vector<Course> courses;
    string line;

    while (getline(fin, line)) {
        if (line == "-1") break;

        Course course;
        vector<string> tokenizedInformation = tokenize(line);

        course.courseNumber = tokenizedInformation[0];
        course.name = tokenizedInformation[1];

        for (int i = 2; i < tokenizedInformation.size(); ++i) {
            course.prerequisites.push_back(tokenizedInformation[i]);
        }

        courses.push_back(course);
    }

    //close file and display message to ensure file was loaded 
    fin.close();
    cout << "\nFile Loaded Successfully\n";
    return courses;
}

void printCourse(const Course& course) {
    cout << "Course Number: " << course.courseNumber << endl;
    cout << "Course Name: " << course.name << endl;
    cout << "Prerequisites: ";
    for (const auto& prerequisite : course.prerequisites) {
        cout << prerequisite << " ";
    }
    cout << "\n\n";
}

void printCourseList(vector<Course>& courses) {
    //sort and print course information

    sort(courses.begin(), courses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });

    for (const auto& course : courses) {
        printCourse(course);
    }
}

void searchCourse(const vector<Course>& courses) {
    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;

    //boolean set to false by default
    bool found = false;

    //is course number is found set boolean to true and print information
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            found = true;
            printCourse(course);
            break;
        }
    }

    //message if not found 
    if (!found) {
        cout << "\nCourse number was not found, please try again\n";
    }
}


// Main for console application
int main() {
    vector<Course> courses;

    //Choosing to only print once at the beginning
    cout << "Welcome to the course planner!\n";
  

    int choice;
    do {
        //Menu displays every time and prompts for user input
        cout << "\n1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course\n";
        cout << "9. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            //call argument to load file
            courses = loadCoursesFromFile();
            break;
        case 2:
            //call argument to print courses
            printCourseList(courses);
            break;
        case 3:
            //call argument to search for course
            searchCourse(courses);
            break;
        case 9:
            //exit message displayed
            cout << "\nThank you for using the course planner!\n";
            break;
        default:
            //default message for any other input
            cout << "\nInvalid Choice\n";
        }

      //continue to loop through the menu until the option 9 is selected
    } while (choice != 9);

    return 0;
}