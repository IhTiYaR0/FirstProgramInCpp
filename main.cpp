#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;


void clear() {
    system("clear");
}


class User {
    private:
        int id = 0;
        string username;
        string password;
    public:
        User(int id, const string &username, const string &password) {
            this -> id = id;
            this -> username = username;
            this -> password = password;
        }

        bool checkUserForLogin(const string &username, const string &password) {
            return this -> username == username && this -> password == password; 
        }

        string getUsername() {
            return username;
        }

        int getUserId() {
            return id;
        }

        void getUser() {
            cout << "Имя: " << username << endl << "Пароль: " << password  << endl;
        }

        bool currentUser() {
            return username == "";
        }

        void logout() {
            id = 0;
            username = "";
            password = "";
        }

    };
class UserManager {
    private:
        vector<User> users;
        int nextId = 1;

    public:
        bool createUser(const string &username, const string &password) {
            for (auto &user : users) {
                if (username == user.getUsername()) return false;
            }
            users.emplace_back(nextId++, username, password);
            return true;
        }

        bool loginUser(const string &username, const string &password, User &currentUser) {
            for (auto &user : users) {
                if (user.checkUserForLogin(username, password)) {
                    currentUser = user;
                    return true;
                }
            }
            return false;
        }

        void logoutUser(User &currentUser) {
            currentUser.logout();
        }

        void proflieUser(User &currentUser) {
            if (currentUser.currentUser()) {
                cout << "Вы не залогинелись" << endl;
                return;
            } 
            else currentUser.getUser();
        }

};


class Note {
    private:
        int id;
        int userId;
        // string title;
        string content;
    
    public:
        Note(int id, int userId, const string &content) {
            this -> id = id;
            this -> userId = userId;
            // this -> title = title;
            this -> content = content;
        }

        void viewNote() {
            cout << id  << ". " << content << endl;
        }
        
        int getUserIdInNote() {
            return userId;
        }

        int getIdNote() {
            return id;
        }

        // string getTite() {
        //     return title;
        // }

        string& getCotent() {
            return content;
        }
};


class NoteManager {
    private:
        vector<Note> notes;
        int nextId = 1;
    
    public:
        void createNote(const string &content, User &currentUser) {
            Note note(nextId++, currentUser.getUserId(), content);
            notes.push_back(note);
        }

        void showNotes() {
            for (auto &note : notes) {
                note.viewNote();
            }
        }

        void viewMyNotes(User &currentuser) {
            bool hasNote = false; 
            for (auto &note : notes) {
                if (note.getUserIdInNote() == currentuser.getUserId() && !notes.empty()) {
                    note.viewNote();
                    hasNote = true;
                }
            }
            if (!hasNote) cout << "У вас нету заметок!" << endl;
            // return hasNote;
        }

        void delateNote(const string &noteIdForDelate, User &userId) {
            bool checkUserIdForNoteId = false;

            try {
                int userIdInInt = stoi(noteIdForDelate);
                for (int i = 0; i < notes.size(); i++) {
                    if (notes[i].getIdNote() == userIdInInt && notes[i].getUserIdInNote() == userId.getUserId()) {
                        notes.erase(notes.begin() +i);
                        clear();
                        cout << "Удален заметка номер: " << noteIdForDelate << endl;
                        checkUserIdForNoteId = true;
                        break;
                    }
                }
            } catch (...) {
                clear();
                checkUserIdForNoteId = true;
                cout << "Не корректный ввод!" << endl;
            }

            if (!checkUserIdForNoteId) {
                clear();
                cout << "Это заметка не принодлежит вам!" << endl;
            } 
        }

        bool checkIdNoteForUserId(const string &noteIdForEdit, User &userId) {
            bool correctInput = false;
            try {
                int checkUserIdForNoteId = stoi(noteIdForEdit);
                for (int i = 0; i < notes.size(); i++) {
                    if (notes[i].getIdNote() == checkUserIdForNoteId && notes[i].getUserIdInNote() == userId.getUserId()) {
                        return correctInput = true;
                    }
                }
            } catch (...) {
                clear();
                cout << "Не корректный ввод!" << endl;
                return correctInput = false;
            }
            if (!correctInput) cout << "Лох!" << endl;
            return correctInput;
        }

        void editNote(const string &noteIdForEdit, const string &content, User &userId) {
            int checkUserIdForNoteId = stoi(noteIdForEdit);
            for (int i = 0; i < notes.size(); i++) {
                if (notes[i].getIdNote() == checkUserIdForNoteId && notes[i].getUserIdInNote() == userId.getUserId()) {
                    notes[i].getCotent() = content;
                    checkUserIdForNoteId = true;
                }
            }
            if (!checkUserIdForNoteId) {
                clear();
                cout << "Это заметка не принодлежит вам!";
            }
        }
};


class SystemManager {
    public:
        void barDisplay(const string &text) {
            cout << "----------------------" << endl;
            cout << text << endl;
            cout << "----------------------" << endl;
        }
        
        void authDisplay() {
            barDisplay("|     Авторизация    |");
            cout << "| 1.Регистрация      |" << endl << "| 2.Войти            |" << endl << "| 3.Выйти из системы |" << endl << "----------------------" << endl << "Вариант: ";
        }
        
        void registerDisplay(const string &username = "Пуста", const string &password = "Пуста") {
            clear();
            barDisplay("|     Регистрация    |");
            cout << "Имя: " << username << endl << "Пароль: " << password << endl << "--------------------" << endl;
        }

        void loginDisplay(const string &username = "Пуста", const string &password = "Пуста") {
            clear();
            barDisplay("|        Войти       |");
            cout << "Имя: " << username << endl << "Пароль: " << password << endl << "--------------------" << endl;
        }

        void mainPage() {
            barDisplay("|  Главная страница  |");
            cout << "| 1.Профиль          |" << endl << "| 2.Заметки          |" << endl << "| 3.Выйти            |" << endl << "| 4.Выйти из системы |" << endl << "----------------------" << endl << "Вариант: ";
        }

        void notePage() {
            barDisplay("|       Заметки      |");
            cout << "| 1.Мои заметки      |" << endl << "| 2.Создать заметку  |" << endl << "| 3.Удалить заметку  |" << endl << "| 4.Изменить заменку |"<< endl << "| 5.Назад            |" << endl << "| 6.Выти из системы  |" << endl << "----------------------" << endl << "Вариант: ";
        }
        
        void createPageDisplay() {
            clear();
            barDisplay("|      Создание      |");
        }

        void myNotesPage() {
            clear();
            barDisplay("|     Мои Заметки    |");
        }

        void delateNotePage() {
            clear();
            barDisplay("|      Удаление      |");
        }

        void editNotePage() {
            clear();
            barDisplay("|  Изменить заметку  |");
        }
        
        void checkEmptyUsernameAndPassword(string &username, string &password) {
            do {
                cout << "Имя: ";
                getline(cin, username);
                // registerDisplay(username);
                if (username.empty()) cout << "Имя не может быть пустым!" << endl;
            } while (username.empty());
        
            do {
                cout << "Пароль: ";
                getline(cin, password);
                if (password.empty()) cout << "Пароль не может быть пустым!" << endl;
            } while (password.empty());
                    
        }

        void checkEmptyTitle(string &title) {
            do {
                cout << "Заметка: ";
                getline(cin, title);
                // registerDisplay(username);
                if (title.empty()) cout << "Имя не может быть пустым!" << endl;
            } while (title.empty());     
        }
        
        
        void mainPage(bool &loggined, User &currentuser, bool &inTheSystem, NoteManager &noteManager) {
            UserManager userManager;
            string userInput;
            bool inPage = false;
            while(loggined) {
                    mainPage();
                    getline(cin, userInput);
        
                    if(userInput == "1") {
                        clear();
                        barDisplay("|  Ваш пользователь  |");
                        userManager.proflieUser(currentuser);
                        getline(cin, userInput);
                        clear();
                    }

                    else if (userInput == "2") {
                        inPage = true;
                        clear();
                        notesPage(inPage, loggined, currentuser,noteManager, inTheSystem);
                    }

                    else if (userInput == "3") {
                        userManager.logoutUser(currentuser);
                        loggined = false;
                        clear();
                        break;
                    }
                    else if (userInput == "4") {
                        inTheSystem = false;
                        break;
                    }
                    else {
                        clear();
                    }
                }
        }

        void notesPage(bool &inPage, bool &loggined, User &currentuser, NoteManager &noteManager, bool &inTheSystem) {
            string userInput;
            while(inPage) {
                notePage();
                getline(cin, userInput);

                if (userInput == "1") {
                    clear();
                    myNotesPage();
                    noteManager.viewMyNotes(currentuser);
                    getline(cin, userInput);
                    clear();
                }
                else if (userInput == "2") {
                    string title;
                    clear();
                    createPageDisplay();
                    checkEmptyTitle(title);
                    noteManager.createNote(title, currentuser);
                    clear();
                }
                else if (userInput == "3") {
                    string userInputForDelateNote;
                    clear();
                    delateNotePage();
                    noteManager.viewMyNotes(currentuser);
                    cout << "Выберите номер: ";
                    getline(cin, userInputForDelateNote);
                    if (userInputForDelateNote.empty()) {clear(); cout << "Вы нечего не написали !" << endl;}
                    else {
                        noteManager.delateNote(userInputForDelateNote,currentuser);
                    }
                }
                else if (userInput == "4") {
                    string userChoiceIdForEditNote;
                    string contentTextForEditNote;
                    editNotePage();
                    noteManager.viewMyNotes(currentuser);
                    cout << "Выберите новер: ";
                    getline(cin, userChoiceIdForEditNote);
                    if(noteManager.checkIdNoteForUserId(userChoiceIdForEditNote, currentuser)) {
                        cout << "Текст: ";
                        getline(cin, contentTextForEditNote);
                        if (contentTextForEditNote.empty()) cout << "Текст не должен быть пустым!" << endl;
                        else noteManager.editNote(userChoiceIdForEditNote, contentTextForEditNote, currentuser);
                        clear();
                        cout << "Заметкак изменен!" << endl;
                    }
                    // else cout << "Нет" << endl;

                }
                else if (userInput == "5") {
                    clear();
                    break;
                }
                else if (userInput == "6") {
                    currentuser.logout();
                    inTheSystem = false;
                    loggined = false;
                    break;
                    
                }
                else clear();
            }
        }
};

int main() {
    User currentuser(0, "", "");
    SystemManager systemManager;
    UserManager userManager;
    NoteManager noteManager;

    clear();
    bool loggined = false;
    bool inTheSystem = true;
    while (inTheSystem) {
        systemManager.authDisplay();

        string userInput;
        getline(cin, userInput);

        if (userInput == "1") {
            clear();

            string username = "Пуста", password = "Пуста";

            systemManager.registerDisplay(username, password);
            systemManager.checkEmptyUsernameAndPassword(username, password);
            if (userManager.createUser(username, password) && userManager.loginUser(username, password, currentuser)) {
                clear();
                loggined = true;
            } else {
                clear();
                cout << "Такой пользователь уже есть !" << endl;  
            } 
        }
        else if (userInput == "2") {
            clear();

            string username = "Пуста", password = "Пуста";

            systemManager.loginDisplay();
            systemManager.checkEmptyUsernameAndPassword(username, password);
            if (userManager.loginUser(username, password, currentuser)) {
                clear();
                loggined = true;
            } else {
                clear();
                cout << "Токого пользователя нет!" << endl;  
            } 
        }
        else if (userInput == "3") {
            clear();
            cout << "Довстречи!" << endl;
            break;
        }
        else {
            clear();
            cout << "Вы нечего не написали!" << endl;
        }
        systemManager.mainPage(loggined, currentuser, inTheSystem, noteManager);
    }
    
       
    // user.createUser("hello", "1234");
    // user.createUser("hello1", "1234");
    // user.createUser("hello2", "1234");


    // note.createNote("test112", "hello", currentuser);
    // note.showNotes();
    // if(user.loginUser("hello2", "1234",currentuser)) cout << "Вы залогинились!" << endl;
    // user.proflieUser(currentuser);
    // note.createNote("test1", "hello", currentuser);
    // note.createNote("test2", "hello", currentuser);

    
    // if(user.loginUser("hello1", "1234",currentuser)) cout << "Вы залогинились!" << endl;
    // else cout << "Не правильный логин или пароль" << endl;
    // // user.proflieUser(currentuser);
    // note.createNote("test1", "hello", currentuser);
    // note.createNote("test2", "hello", currentuser);
    // note.viewMyNotes(currentuser);
    // cout << "----------------------------------" << endl;
    // note.delateNote(1, currentuser);
    // cout << "----------------------------------" << endl;
    // note.viewMyNotes(currentuser);
    // cout << "----------------------------------" << endl;
    // note.editNote(1, "tester", "hello2", currentuser);
    // cout << "----------------------------------" << endl;
    // note.viewMyNotes(currentuser);
    // note.createNote("test2", "hello", currentuser);
    // note.createNote("test2", "hello", currentuser);
    // note.createNote("test2", "hello", currentuser);
    // note.createNote("test2", "hello", currentuser);
    // cout << "----------------------------------" << endl;
    // // note.delateNote(2, currentuser);
    // note.viewMyNotes(currentuser);
    // if(user.loginUser("hello2", "1234",currentuser)) cout << "Вы залогинились!" << endl;
    // else cout << "Не правильный логин или пароль" << endl;
    // note.viewMyNotes(currentuser);

    // note.viewMyNotes(currentuser);
}