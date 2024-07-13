#include "tinyfb.h"
#include <iostream>
#include <conio.h>

using namespace std;

int main() {
    LoginAccount loginObj;
    TinyFB accountObj;
    while (true) {
        cout << "\n*------------Please Choose an Option-----------*" << endl;
        cout << "|-> Press (1) To Login to Existing Account     |" << endl;
        cout << "|-> Press (2) To Create New Account            |" << endl;
        cout << "|-> Press (3) To Exit                          |" << endl;
        cout << "Select an Option: ";
        char choice = _getch();

        switch (choice) {
            case '1': loginObj.login(); break;
            case '2': accountObj.createAccount(); break;
            case '3': exit(0); break;
            default: system("cls"); break;
        }
    }
    return 0;
}
