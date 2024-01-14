#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
//класс Contact и PhoneBook
class Contact {
private:
    char* fullName;
    char* homePhone;
    char* workPhone;
    char* mobilePhone;
    char* additionalInfo;
    char* copyString(const char* source) {
        if (source == nullptr) return nullptr;
        char* destination = new char[strlen(source) + 1];
        strcpy(destination, source);
        return destination;
    }
public:
    Contact() : Contact(nullptr, nullptr, nullptr, nullptr, nullptr) {}
    Contact(const char* name, const char* home, const char* work, const char* mobile, const char* info)
        : fullName(copyString(name)), homePhone(copyString(home)), workPhone(copyString(work)),
        mobilePhone(copyString(mobile)), additionalInfo(copyString(info)) {}
    Contact(const Contact& other)
        : fullName(copyString(other.fullName)), homePhone(copyString(other.homePhone)),
        workPhone(copyString(other.workPhone)), mobilePhone(copyString(other.mobilePhone)),
        additionalInfo(copyString(other.additionalInfo)) {}
    ~Contact() {
        delete[] fullName;
        delete[] homePhone;
        delete[] workPhone;
        delete[] mobilePhone;
        delete[] additionalInfo;
    }
    Contact& operator=(const Contact& other) {
        if (this != &other) {
            delete[] fullName;
            delete[] homePhone;
            delete[] workPhone;
            delete[] mobilePhone;
            delete[] additionalInfo;
            fullName = copyString(other.fullName);
            homePhone = copyString(other.homePhone);
            workPhone = copyString(other.workPhone);
            mobilePhone = copyString(other.mobilePhone);
            additionalInfo = copyString(other.additionalInfo);
        }
        return *this;
    }
    void setFullName(const char* name) {
        delete[] fullName;
        fullName = copyString(name);
    }
    void setHomePhone(const char* home) {
        delete[] homePhone;
        homePhone = copyString(home);
    }
    void setWorkPhone(const char* work) {
        delete[] workPhone;
        workPhone = copyString(work);
    }
    void setMobilePhone(const char* mobile) {
        delete[] mobilePhone;
        mobilePhone = copyString(mobile);
    }
    void setAdditionalInfo(const char* info) {
        delete[] additionalInfo;
        additionalInfo = copyString(info);
    }
    const char* getFullName() const { return fullName; }
    const char* getHomePhone() const { return homePhone; }
    const char* getWorkPhone() const { return workPhone; }
    const char* getMobilePhone() const { return mobilePhone; }
    const char* getAdditionalInfo() const { return additionalInfo; }
};
class PhoneBook {
private:
    Contact* contacts;
    size_t size;
    size_t capacity;

public:
    PhoneBook() : contacts(nullptr), size(0), capacity(0) {}
    ~PhoneBook() {
        clear();
    }
    void displayContacts() const {
        for (size_t i = 0; i < size; ++i) {
            cout << "Контакт " << i + 1 << ":" << "\n";
            cout << "Имя: " << contacts[i].getFullName() << "\n";
            cout << "Домашний телефон: " << contacts[i].getHomePhone() << "\n";
            cout << "Рабочий телефон: " << contacts[i].getWorkPhone() << "\n";
            cout << "Мобильный телефон: " << contacts[i].getMobilePhone() << "\n";
            cout << "Дополнительная информация: " << contacts[i].getAdditionalInfo() << "\n";
            cout << "---------------------" << "\n";
        }
    }
    void addContact(const Contact& newContact) {
        if (size == capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            Contact* newContacts = new Contact[newCapacity];
            for (size_t i = 0; i < size; ++i) {
                newContacts[i] = contacts[i];
            }
            delete[] contacts;
            contacts = newContacts;
            capacity = newCapacity;
        }
        contacts[size++] = newContact;
    }
    void removeContact(size_t index) {
        if (index < size) {
            for (size_t i = index; i < size - 1; ++i) {
                contacts[i] = contacts[i + 1];
            }
            --size;
        }
        else {
            cout << "Некорректный индекс контакта." << "\n";
        }
    }
    void clear() {
        delete[] contacts;
        contacts = nullptr;
        size = capacity = 0;
    }
};
int main() {
    //к заданию "Телефонная книга"
    setlocale(LC_ALL, "RUS");
    PhoneBook phoneBook;
    Contact contact1("Иван Иванов", "123-456-7890", "987-654-3210", "555-123-4567", "Друг");
    phoneBook.addContact(contact1);
    Contact contact2("Петр Петров", "111-222-3333", "444-555-6666", "777-888-9999", "Коллега");
    phoneBook.addContact(contact2);
    cout << "Все контакты:" << "\n";
    phoneBook.displayContacts();
    phoneBook.removeContact(0);
    cout << "Контакты после удаления:" << "\n";
    phoneBook.displayContacts();
    cout << "\n";
    cout << "\n";
}