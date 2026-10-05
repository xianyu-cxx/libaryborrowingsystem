#include <iostream>
#include <string>
#include <vector>   // STL vector，报告要求的STL容器
using namespace std;

class Book {
private:
    string name;
    string isbn;
    string press;
    double price;
    int pages;
    bool isAvailable;
public:
    Book(string n = "", string i = "", string p = "", double pr = 0, int pg = 0, bool ava = true)
        : name(n), isbn(i), press(p), price(pr), pages(pg), isAvailable(ava) {
    }

    void setInfo(string n, string i, string p, double pr, int pg, bool ava) {
        name = n; isbn = i; press = p; price = pr; pages = pg; isAvailable = ava;
    }
    void setName(string n) { name = n; }
    void setIsbn(string i) { isbn = i; }
    void setPress(string p) { press = p; }
    void setPrice(double pr) { price = pr; }
    void setPages(int pg) { pages = pg; }
    void setAvailable(bool ava) { isAvailable = ava; }

    string getName() const { return name; }
    string getIsbn() const { return isbn; }
    string getPress() const { return press; }
    double getPrice() const { return price; }
    int getPages() const { return pages; }
    bool getAvailable() const { return isAvailable; }

    void showInfo() const {
        cout << "====图书信息====" << endl;
        cout << "书名：" << name << endl;
        cout << "ISBN：" << isbn << endl;
        cout << "出版社：" << press << endl;
        cout << "价格：" << price << endl;
        cout << "页数：" << pages << endl;
        cout << "在馆状态：" << (isAvailable ? "可借阅" : "已借出") << endl;
    }

    // ISBN?10校验
    bool checkIsbn() const {
        string s = isbn;
        string pure;
        for (char c : s) if (c != '-') pure += c;
        if (pure.size() != 10) return false;
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (!isdigit(pure[i])) return false;
            sum += (pure[i] - '0') * (i + 1);
        }
        char last = pure[9];
        if (last == 'X' || last == 'x') sum += 10 * 10;
        else if (isdigit(last)) sum += (last - '0') * 10;
        else return false;
        return sum % 11 == 0;
    }
};

// 学生类：Student，借书函数参数传入Book对象 →【依赖关系】学生依赖Book完成借书
class Student {
private:
    string stuName;
    int stuId;
public:
    Student(string name = "", int id = 0) :stuName(name), stuId(id) {}
    // 借书：参数传Book对象，依赖Book类
    bool borrowBook(Book& b) {
        if (b.getAvailable()) {
            b.setAvailable(false);
            cout << stuName << " 借书成功！" << endl;
            return true;
        }
        else {
            cout << "借书失败，图书已被借出！" << endl;
            return false;
        }
    }
    void returnBook(Book& b) {
        b.setAvailable(true);
        cout << stuName << " 还书完成" << endl;
    }
};

// Library图书馆类：内部持有vector<Book> books 【组合关系】图书馆包含一批图书对象
class Library {
private:
    vector<Book> books;  // STL容器vector，报告要求的特色功能
public:
    void addBook(const Book& b) {
        books.push_back(b);
    }
    void showAllBooks() {
        for (auto& bk : books) {
            bk.showInfo();
        }
    }
};

int main()
{
    Book b1("C++程序设计", "7-302-10253-5", "清华大学出版社", 39.5, 320, true);
    Book b2("数据结构", "7-302-20213-3", "清华大学出版社", 45, 410, true);

    Library lib;
    lib.addBook(b1);
    lib.addBook(b2);
    cout << "图书馆全部图书：" << endl;
    lib.showAllBooks();

    Student s1("张三", 2025001);
    cout << "\n-----学生借书测试-----" << endl;
    s1.borrowBook(b1);
    b1.showInfo();

    cout << "\n-----学生还书测试-----" << endl;
    s1.returnBook(b1);
    b1.showInfo();

    if (b1.checkIsbn()) cout << "ISBN校验：合法\n";
    else cout << "ISBN校验：不合法\n";
    return 0;
}
