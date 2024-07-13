#ifndef TINYFB_H
#define TINYFB_H

#include <string>

class TinyFB {
public:
    TinyFB();
    void createAccount();
private:
    std::string firstName, lastName, email, password, sex;
};

class LoginAccount {
public:
    LoginAccount();
    void login();
    void accountMenu();
    void postArticle();
    void sendFriendRequest();
    void likePage();
    void deleteFriend();
    void showFriends();
    void showLikedPages();
    void showDeletedList();
    void showArticles();
    void logout();
private:
    std::string ph, pswd, str1, str2, str3, str4, str5, str6;
    void loadingAnimation();
};

#endif // TINYFB_H
