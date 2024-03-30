#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Q {
    int id, from, to;
    string question;
};
struct A {
    int Q_id;
    string Answer;
};
struct User {
    int id;
    string name, username;
    string gmail, password;
};
class DataBase {
public:
    DataBase() {};
    void Download_Data(vector<Q>& Que, vector<User>& U, vector<A>& ans) {
        ifstream users("Users.txt");
        if (users.is_open()) {
            User in;
            while (users >> in.id) {
                users.ignore();
                getline(users, in.name);
                getline(users, in.username);
                getline(users, in.gmail);
                getline(users, in.password);
                U.push_back(in);
            }
            users.close();
        }
        else cout << "Can't open users file\n";
        ifstream Questions("Question.txt");
        if (Questions.is_open()) {
            Q in;
            while (Questions >> in.id >> in.from >> in.to) {
                Questions.ignore();
                getline(Questions, in.question);
                Que.push_back(in);
            }
            Questions.close();
        }
        else cout << "Can't open Question file\n";
        ifstream answers("Answers.txt");
        if (answers.is_open()) {
            A in;
            while (answers >> in.Q_id) {
                answers.ignore();
                getline(answers, in.Answer);
                ans.push_back(in);
            }
            answers.close();
        }
        else cout << "Can't open Answers file\n";
    }
    void Update_Data(vector<Q>& Que, vector<User>& U, vector<A>& ans) {
        fstream users;
        users.open("Users.txt", std::ofstream::out | std::ofstream::trunc);
        if (users.is_open()) {
            User out;
            for (auto it : U) {
                users << it.id << '\n';
                users << it.name << '\n';
                users << it.username << '\n';
                users << it.gmail << '\n';
                users << it.password << '\n';
            }
            users.close();
        }
        else cout << "Can't open users file\n";
        fstream Questions;
        Questions.open("Question.txt", std::ofstream::out | std::ofstream::trunc);
        if (Questions.is_open()) {
            for (auto it : Que) {
                Questions << it.id << ' ';
                Questions << it.from << ' ';
                Questions << it.to << '\n';
                Questions << it.question << '\n';
            }
            Questions.close();
        }
        else cout << "Can't open Question file\n";
        fstream answers;
        answers.open("Answers.txt", std::ofstream::out | std::ofstream::trunc);
        if (answers.is_open()) {
            for (auto it : ans) {
                answers << it.Q_id << '\n';
                answers << it.Answer << '\n';
            }
            answers.close();
        }
        else cout << "Can't open Answers file\n";
    }
};
bool is_name_valid(string name) {
    if (name.size() < 5) {
        cout << "name is too short\n";
        return 0;
    }
    if (name.size() > 30) {
        cout << "name is too long\n";
        return 0;
    }
    return 1;
}
bool is_username_valid(string username, vector<User>users) {
    if (username.size() < 5) {
        cout << "name is too short\n";
        return 0;
    }
    if (username.size() > 30) {
        cout << "name is too long\n";
        return 0;
    }
    if (!isalpha(username.front())) {
        cout << "First character must by letter\n";
    }
    for (auto it : username) {
        if (!isalpha(it) && !isdigit(it) && it != '_') {
            cout << "Invalid character : " << it << '\n';
            return 0;
        }
    }
    for (auto it : users) {
        if (it.username == username) {
            cout << "This username is already taken\n";
            return 0;
        }
    }
    return 1;
}
bool is_gmail_valid(string gmail, vector<User>users) {
    string last = "@gmail.com";
    if (gmail.substr(gmail.size() - last.size(), last.size()) != last) {
        cout << "Yout gmail must finish with : " << last << '\n';
        return 0;
    }
    for (auto it : users) {
        if (it.gmail == gmail) {
            cout << "This gmail is already used\n";
            return 0;
        }
    }
    return 1;
}
bool is_password_valid(string password) {
    if (password.size() < 8) {
        cout << "Password must contains at least 8 characters\n";
        return 0;
    }
    bool uppercase = 0, lowercase = 0, digit = 0;
    for (auto it : password) {
        if (islower(it))lowercase = 1;
        if (isupper(it))uppercase = 1;
        if (isdigit(it))digit = 1;
    }
    if (!uppercase) {
        cout << "Password must contains at least 1 uppercase character\n";
        return 0;
    }
    if (!lowercase) {
        cout << "Password must contains at least 1 lowercase character\n";
        return 0;
    }
    if (!digit) {
        cout << "Password must contains at least 1 digit\n";
        return 0;
    }
    return 1;
}
class User_Operation {
public:
    User_Operation() {};
    bool Print_Questions_To_me(vector<Q>& questions, vector<A>& answers, User current_user) {       // 1
        bool ok = 0;
        for (auto it : questions) {
            if (it.to == current_user.id) {
                ok = 1;
                cout << "Question with id " << it.id << ": \n" << "From " << it.from << " to you\n";
                cout << it.question << '\n';
                bool k = 0;
                for (auto itt : answers) {
                    if (itt.Q_id == it.id) {
                        k = 1;
                        cout << "Answer: " << itt.Answer << '\n';
                        break;
                    }
                }
                if (!k)cout << "Questions isn't answered yet\n";
            }
        }
        return ok;
    }
    bool Print_Questions_From_me(vector<Q>& questions, vector<A>& answers, User current_user) {       // 2
        bool ok = 0;
        for (auto it : questions) {
            if (it.from == current_user.id) {
                ok = 1;
                cout << "Question with id " << it.id << ": \n" << "From you to " << it.to << '\n';
                cout << it.question << '\n';
                bool k = 0;
                for (auto itt : answers) {
                    if (itt.Q_id == it.id) {
                        k = 1;
                        cout << "Answer: " << itt.Answer << '\n';
                        break;
                    }
                }
                if (!k)cout << "Questions isn't answered yet\n";
            }
        }
        return ok;
    }
    bool List_Users(vector<User>& users, User current_user) {       // 6
        int cnt = 0;
        for (auto it : users) {
            if (it.id != current_user.id) {
                cout << "User " << ++cnt << ": \n" << "Username: " << it.username << " & his id :" << it.id << '\n';
            }
        }
        return cnt;
    }
    void Ask_Questions(vector<Q>& questions, vector<A>& answers, vector<User>& users, User current_user) {      //  3
        bool ok = List_Users(users, current_user);
        if (ok) {
            cout << "Print id of user you want to ask: ";
            Q new_Q;
            for (int i = 123;; i++) {
                bool ok = 1;
                for (auto it : questions) {
                    if (it.id == i)ok = 0;
                }
                if (ok) {
                    new_Q.id = i;
                    break;
                }
            }
            new_Q.from = current_user.id;
            cout << "Insert id of user you want to ask: ";
            cin >> new_Q.to;
            cout << "Insert your Question: ";
            cin.ignore();
            getline(cin, new_Q.question);
            questions.push_back(new_Q);
            DataBase DB;
            DB.Update_Data(questions, users, answers);
        }
        else cout << "There is no users in system yet\n";
    }
    void Answer_Question(vector<Q>& questions, vector<A>& answers, vector<User>& users, User current_user) {      //  4
        bool ok = Print_Questions_To_me(questions, answers, current_user);
        if (ok) {
            cout << "Choose Question id you want to answer: ";
            int id; cin >> id;
            for (auto it : questions) {
                if (it.id == id) {
                    bool k = 1;
                    for (auto itt : answers) {
                        if (itt.Q_id == it.id) {
                            k = 0;
                            break;
                        }
                    }
                    if (k) {
                        cout << "Question is: " << it.question << '\n';
                        cout << "Insert your answer: ";
                        A new_A;
                        new_A.Q_id = it.id;
                        cin.ignore();
                        getline(cin, new_A.Answer);
                        answers.push_back(new_A);
                        DataBase DB;
                        DB.Update_Data(questions, users, answers);
                    }
                    else cout << "This Question is Already answered\n";
                    break;
                }
            }
        }
        else cout << "You don't have any questions yet\n";
    }
    void Delete_Question(vector<Q>& questions, vector<User>& users, vector<A>& answers, User current_user) {
        bool ok = Print_Questions_From_me(questions, answers, current_user);
        if (ok) {
            cout << "Choose Question id you want to delete: ";
            int id; cin >> id;
            bool k = 0;
            for (int i = 0; i < questions.size(); i++) {
                if (questions[i].id == id) {
                    questions.erase(questions.begin() + i);
                    i--;
                    k = 1;
                }
            }
            for (int i = 0; i < answers.size(); i++) {
                if (answers[i].Q_id == id) {
                    answers.erase(answers.begin() + i);
                    i--;
                }
            }
            if (k) {
                DataBase DB;
                DB.Update_Data(questions, users, answers);
                cout << "Your question has been deleted succesfully...\n";
            }
            else cout << "There is no quesion with id you insert\n";
        }
        else cout << "There is no questions to delete it\n";
    }
};
class AskMe {
    DataBase DB;
    User current_user;
    vector<Q>questions;
    vector<User>users;
    vector<A>answers;
public:
    AskMe() {
        DB.Download_Data(questions, users, answers);
        int choice;
        bool ok = 1;
        while (ok) {
            cout << "1 - Sign in\n";
            cout << "2 - Sign up\n";
            cout << "Insert your choice : ";
            cin >> choice;
            if (choice == 1) {
                bool valid = 0;
                string un, pass;
                cout << "Insert your username : ";
                cin >> un;
                cout << "\nInsert your password : ";
                cin >> pass;
                for (auto it : users) {
                    if (it.username == un && it.password == pass) {
                        valid = 1;
                        current_user = it;
                        break;
                    }
                }
                if (valid) {
                    cout << "You signed in succesfully...\n";
                    ok = 0;
                }
                else cout << "Invalid data\n";
            }
            else if (choice == 2) {
                User new_user;
                string st;
                cout << "Insert your name : ";
                cin.ignore();
                while (getline(cin, st)) {
                    if (is_name_valid(st)) {
                        new_user.name = st;
                        break;
                    }
                }
                cout << "Insert your username : ";
                while (getline(cin, st)) {
                    if (is_username_valid(st, users)) {
                        new_user.username = st;
                        break;
                    }
                }
                cout << "Insert your gmail : ";
                while (getline(cin, st)) {
                    if (is_gmail_valid(st, users)) {
                        new_user.gmail = st;
                        break;
                    }
                }
                cout << "Insert your password : ";
                while (getline(cin, st)) {
                    if (is_password_valid(st)) {
                        new_user.password = st;
                        break;
                    }
                }
                for (int i = 101;; i++) {
                    bool ok = 1;
                    for (auto it : users) {
                        if (it.id == i)ok = 0;
                    }
                    if (ok) {
                        new_user.id = i;
                        break;
                    }
                }
                cout << "Your id is : " << new_user.id << '\n';
                users.push_back(new_user);
                DB.Update_Data(questions, users, answers);
                cout << "Now sign in with you new account\n";
            }
            else cout << "Invalid choice\n";
        }
    }

    void Menu() {
        cout << "Menu \n";
        cout << "1. Print Questions To me\n";
        cout << "2. Print Questions From me\n";
        cout << "3. Ask Question\n";
        cout << "4. Answer Question\n";
        cout << "5. Delete Question\n";
        cout << "6. List Users\n";
        cout << "7. Logout\n\n";
    }
    void DoWork() {
        int choice;
        bool ok = 1;
        User_Operation up;
        while (ok) {
            Menu();
            cout << "Insert your choice : ";
            cin >> choice;
            cout << '\n';
            if (choice == 1) {
                bool ok = up.Print_Questions_To_me(questions, answers, current_user);
                if (!ok)cout << "You don't have any questions yet\n";
            }
            else if (choice == 2) {
                bool ok = up.Print_Questions_From_me(questions, answers, current_user);
                if (!ok)cout << "You don't have any questions yet\n";
            }
            else if (choice == 3) {
                up.Ask_Questions(questions, answers, users, current_user);
            }
            else if (choice == 4) {
                up.Answer_Question(questions, answers, users, current_user);
            }
            else if (choice == 5) {
                up.Delete_Question(questions, users, answers, current_user);
            }
            else if (choice == 6) {
                up.List_Users(users, current_user);
            }
            else ok = 0;
        }
    }
};
int main() {
    while (1) {
        AskMe ask;
        ask.DoWork();
    }
}
