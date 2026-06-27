// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Stores course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Binary search tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary search tree class
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Course search(Node* node, string courseNumber);
    void destroy(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    void Insert(Course course);
    void PrintCourseList();
    Course Search(string courseNumber);
};

// Constructor
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
    destroy(root);
}

void BinarySearchTree::destroy(Node* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}


// Insert wrapper
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

// Inserts course into correct location
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

// inOrder traversal
void BinarySearchTree::PrintCourseList() {
    inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);

        cout << node->course.courseNumber
            << ", "
            << node->course.courseTitle
            << endl;

        inOrder(node->right);
    }
}

// Search wrapper 
Course BinarySearchTree::Search(string courseNumber) {
    return search(root, courseNumber);
}

// Searches binary search tree for matching course number
Course BinarySearchTree::search(Node* node, string courseNumber) {
    Course emptyCourse;

    if (node == nullptr) {
        return emptyCourse;
    }
    if (node->course.courseNumber == courseNumber) {
        return node->course;
    }
    if (courseNumber < node->course.courseNumber) {
        return search(node->left, courseNumber);
    }

    return search(node->right, courseNumber);
}



// Load Course Data by reading CSV file
void loadCourses(string fileName, BinarySearchTree* bst) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Problem opening the file." << endl;
        return;
    }

    vector<Course> courses;
    vector<string> validCourseNumbers;

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        vector<string> items;

        while (getline(ss, token, ',')) {
            items.push_back(token);
        }

        if (items.size() < 2) {
            cout << "Invalid entry in file." << endl;
            continue;
        }

        Course course;

        course.courseNumber = items[0];
        course.courseTitle = items[1];

        validCourseNumbers.push_back(course.courseNumber);

        for (size_t i = 2; i < items.size(); i++) {
            if (!items[i].empty()) {
                course.prerequisites.push_back(items[i]);
            }
        }

        courses.push_back(course);
    }

    file.close();

    // Validate prerequisites before inserting them
    for (Course course : courses) {
        bool valid = true;

        for (string prereq : course.prerequisites) {
            if (find(validCourseNumbers.begin(), validCourseNumbers.end(), prereq) == validCourseNumbers.end()) {
                cout << "Invalid prerequisite "
                    << prereq
                    << " found for "
                    << course.courseNumber << endl;
                valid = false;
            }
        }

        if (valid) {
            bst->Insert(course);
        }
    }
    cout << "Courses loaded successfully." << endl;
}

// Print individual courses
void printCourse(BinarySearchTree* bst) {
    string courseNumber;

    cout << "Enter course number: ";
    cin >> courseNumber;

    transform(courseNumber.begin(), 
        courseNumber.end(), 
        courseNumber.begin(),
        ::toupper);

    Course course = bst->Search(courseNumber);

    if (course.courseNumber.empty()) {
        cout << "Course not found." << endl;
        return;
    }

    cout << endl << course.courseNumber
        << ", " << course.courseTitle
        << endl;


    cout << endl << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None";
    }
    else {
        cout << endl;

        for (size_t i = 0; i < course.prerequisites.size(); i++) {

            Course prereqCourse = bst->Search(course.prerequisites[i]);

            if (!prereqCourse.courseNumber.empty()) {
                cout << prereqCourse.courseNumber << ", "
                    << prereqCourse.courseTitle << endl;
            }
        }
    }
    cout << endl;
}


// main program function
int main() {
    BinarySearchTree bst;

    string fileName;
    int choice = 0;

    cout << "Welcome to the course planner tool." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit Program." << endl;
        cout << endl;

        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;

            loadCourses(fileName, &bst);
            break;
        case 2:
            cout << endl;
            cout << "Here is a sample schedule:" << endl;

            bst.PrintCourseList();

            break;
        case 3:
            printCourse(&bst);
            break;
        case 9:
            cout << "Good bye." << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
