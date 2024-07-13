#include "tinyfb.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

TinyFB::TinyFB() : firstName("Caspar"), lastName("Caspar"), email("caspar@caspar.com"), password("0123"), sex("FM") {
    // 确保初始文件和目录存在
    CreateDirectory("Mini_FB", NULL);
    CreateDirectory("Mini_FB/Files_loaded_for_options", NULL);
    CreateDirectory("Mini_FB/User_Data_base", NULL);

    // 创建Pages_Names.txt文件，如果不存在
    ofstream pagesFile("Mini_FB/Files_loaded_for_options/Pages_Names.txt", ios::app);
    pagesFile.close();

    // 创建User_info.txt文件，如果不存在
    ofstream userInfoFile("User_info.txt", ios::app);
    userInfoFile.close();
}

void TinyFB::createAccount() {
    ofstream fout("User_info.txt", ios::app);
    if (!fout) {
        cout << "Error opening User_info.txt" << endl;
        return;
    }

    system("cls");
    cout << "----------Create an Account----------" << endl;
    cout << "Enter First Name: ";
    getline(cin >> ws, firstName);
    cout << "Enter Last Name: ";
    getline(cin, lastName);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Password: ";
    getline(cin, password);
    cout << "For Male press M or Press F for Female: ";
    getline(cin, sex);
    cout << "Creating Your Account";
    for (int j = 0; j < 5; ++j) {
        cout << " ";
        for (int i = 0; i < 5; ++i) {
            cout << ".";
            Sleep(300);
        }
    }
    cout << "\nYour Account is Successfully Created" << endl;
    fout << firstName << " " << lastName << " " << email << " " << password << " " << sex << endl;
    fout.close();

    string userDir = "Mini_FB/User_Data_base/" + firstName + "_" + lastName;
    if (CreateDirectory(userDir.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        cout << "User directory created or already exists." << endl;
    } else {
        cout << "Failed to create directory for user data." << endl;
    }
    system("cls");
}

LoginAccount::LoginAccount() = default;

void LoginAccount::login() {
    ifstream readFile("User_info.txt");
    if (!readFile) {
        cout << "Error opening User_info.txt" << endl;
        return;
    }

    bool flag = false;
    system("cls");
    cout << "Enter Your Email: ";
    cin >> ph;
    cout << "Enter Your Account Password: ";
    cin >> pswd;

    while (readFile >> str1 >> str2 >> str3 >> str4 >> str5 >> str6) {
        if (ph == str3 && pswd == str4) {
            flag = true;
            break;
        }
    }
    readFile.close();

    if (flag) {
        cout << "You are successfully logged into your account" << endl;
        cout << "Logging into your account";
        for (int j = 0; j < 2; ++j) {
            cout << " ";
            for (int i = 0; i < 2; ++i) {
                cout << ".";
                Sleep(300);
            }
        }
        system("cls");
        accountMenu();
    } else {
        cout << "Mail Address or Password is Incorrect!" << endl;
        cout << "Try again" << endl;
    }
}

void LoginAccount::accountMenu() {
    while (true) {
        cout << "Welcome: " << str1 << " " << str2 << endl;
        cout << "\n|------------Please Choose an Option------------------|" << endl;
        cout << "|-> Press (1) To Post an article                     |" << endl;
        cout << "|-> Press (2) To Send Friend Request                 |" << endl;
        cout << "|-> Press (3) To Like a Page                         |" << endl;
        cout << "|-> Press (4) To delete a friend                     |" << endl;
        cout << "|-> Press (5) To show Friends                        |" << endl;
        cout << "|-> Press (6) To show Pages You like                 |" << endl;
        cout << "|-> Press (7) To show Delete List                    |" << endl;
        cout << "|-> Press (8) To Show Your Articles                  |" << endl;
        cout << "|-> Press (9) To exit                                |" << endl;
        cout << "Choose a function: ";
        char choice = _getch();

        switch (choice) {
            case '1': postArticle(); break;
            case '2': sendFriendRequest(); break;
            case '3': likePage(); break;
            case '4': deleteFriend(); break;
            case '5': showFriends(); break;
            case '6': showLikedPages(); break;
            case '7': showDeletedList(); break;
            case '8': showArticles(); break;
            case '9': logout(); return;
            default: cout << "Invalid option, please try again." << endl;
        }
    }
}

void LoginAccount::postArticle() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    string userDir = "Mini_FB/User_Data_base/" + str1 + "_" + str2;
    string path = userDir + "/posts.txt";
    if (!CreateDirectory(userDir.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        cout << "Failed to create user directory." << endl;
        return;
    }
    ofstream out(path, ios::app);
    if (!out) {
        cout << "Failed to open file for writing: " << path << endl;
        return;
    }
    cout << "Write something to post an article: ";
    cin.ignore();
    string paragraph;
    getline(cin, paragraph);
    out << paragraph << endl;
    cout << "Posting on your home: ";
    loadingAnimation();
    out.close();
}

void LoginAccount::sendFriendRequest() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    cout << "Enter the name of the person you want to add as a friend: ";
    cin.ignore();
    string friendRequest;
    getline(cin, friendRequest);
    cout << "The friend request is sent to: " << friendRequest << endl;
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/friends.txt";
    ofstream out(path, ios::app);
    if (!out) {
        cout << "Failed to open file for writing: " << path << endl;
        return;
    }
    out << friendRequest << endl;
    cout << "Saving changes: ";
    loadingAnimation();
    out.close();
}

void LoginAccount::likePage() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    cout << "\nPages List: " << endl;
    ifstream in("Mini_FB/Files_loaded_for_options/Pages_Names.txt");
    if (!in) {
        cout << "Failed to open file for reading: Mini_FB/Files_loaded_for_options/Pages_Names.txt" << endl;
        return;
    }
    string page;
    while (getline(in, page)) {
        cout << "|->" << page << endl;
    }
    in.close();
    cout << "Enter the name of the page you like: ";
    cin.ignore();
    string pageName;
    getline(cin, pageName);
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/pagelike.txt";
    ofstream out(path, ios::app);
    if (!out) {
        cout << "Failed to open file for writing: " << path << endl;
        return;
    }
    out << pageName << endl;
    cout << "Saving changes: ";
    loadingAnimation();
    out.close();
}

void LoginAccount::deleteFriend() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    cout << "Delete People: " << endl;
    cout << "Enter the name of the person you want to delete: ";
    cin.ignore();
    string deletePerson;
    getline(cin, deletePerson);
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/blockedpeople.txt";
    ofstream out(path, ios::app);
    if (!out) {
        cout << "Failed to open file for writing: " << path << endl;
        return;
    }
    out << "->" << deletePerson << endl;
    cout << "Adding person to delete list: ";
    loadingAnimation();
    out.close();
}

void LoginAccount::showFriends() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    cout << "All Friends: " << endl;
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/friends.txt";
    ifstream in(path);
    if (!in) {
        cout << "Failed to open file for reading: " << path << endl;
        return;
    }
    string friendName;
    int count = 0;
    while (getline(in, friendName)) {
        cout << "->" << friendName << endl;
        ++count;
    }
    in.close();
    cout << "Total number of friends: " << count << endl;
    cout << "Closing file: ";
    loadingAnimation();
}

void LoginAccount::showLikedPages() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    cout << "\nPages List: " << endl;
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/pagelike.txt";
    ifstream in(path);
    if (!in) {
        cout << "Failed to open file for reading: " << path << endl;
        return;
    }
    string pageName;
    while (getline(in, pageName)) {
        cout << "->" << pageName << endl;
    }
    in.close();
    cout << "Closing: ";
    loadingAnimation();
}

void LoginAccount::showDeletedList() {
    cout << "Loading";
    loadingAnimation();
    system("cls");
    cout << "Deleted People: " << endl;
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/blockedpeople.txt";
    ifstream in(path);
    if (!in) {
        cout << "Failed to open file for reading: " << path << endl;
        return;
    }
    string deletePerson;
    while (getline(in, deletePerson)) {
        cout << deletePerson << endl;
    }
    in.close();
    cout << "Closing: ";
    loadingAnimation();
}

void LoginAccount::showArticles() {
    system("cls");
    cout << "Articles: " << endl;
    string path = "Mini_FB/User_Data_base/" + str1 + "_" + str2 + "/posts.txt";
    ifstream in(path);
    if (!in) {
        cout << "Failed to open file for reading: " << path << endl;
        return;
    }
    string article;
    while (getline(in, article)) {
        cout << article << endl;
    }
    in.close();
}

void LoginAccount::logout() {
    system("cls");
    cout << "Logging you out";
    loadingAnimation();
    cout << "Have a nice day: " << str1 << " " << str2 << endl;
    cout << "You are logged out from your account" << endl;
}

void LoginAccount::loadingAnimation() {
    for (int j = 0; j < 2; ++j) {
        cout << " ";
        for (int i = 0; i < 2; ++i) {
            cout << ".";
            Sleep(300);
        }
    }
    cout << endl;
}
