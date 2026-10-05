#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string name;     // 图书名称
    string isbn;     // ISBN编号
    string press;    // 出版社
    double price;    // 价格
    int pages;       // 页数
    bool isAvailable;// 在馆状态 true=可借 false=不可借

public:
    // 构造函数：初始化
    Book(string n = "", string i = "", string p = "", double pr = 0, int pg = 0, bool ava = true)
        : name(n), isbn(i), press(p), price(pr), pages(pg), isAvailable(ava) {
    }

    // 修改所有信息
    void setInfo(string n, string i, string p, double pr, int pg, bool ava) {
        name = n;
        isbn = i;
        press = p;
        price = pr;
        pages = pg;
        isAvailable = ava;
    }

    // 单独设置各个成员
    void setName(string n) { name = n; }
    void setIsbn(string i) { isbn = i; }
    void setPress(string p) { press = p; }
    void setPrice(double pr) { price = pr; }
    void setPages(int pg) { pages = pg; }
    void setAvailable(bool ava) { isAvailable = ava; }

    // 获取成员
    string getName() const { return name; }
    string getIsbn() const { return isbn; }
    string getPress() const { return press; }
    double getPrice() const { return price; }
    int getPages() const { return pages; }
    bool getAvailable() const { return isAvailable; }

    // 输出图书全部信息
    void showInfo() const {
        cout << "====图书信息====" << endl;
        cout << "书名：" << name << endl;
        cout << "ISBN：" << isbn << endl;
        cout << "出版社：" << press << endl;
        cout << "价格：" << price << endl;
        cout << "页数：" << pages << endl;
        cout << "在馆状态：" << (isAvailable ? "可借阅" : "已借出") << endl;
    }

    // 校验ISBN-10合法性
    bool checkIsbn() const {
        string s = isbn;
        // 去除横杠
        string pure;
        for (char c : s) {
            if (c != '-') pure += c;
        }
        if (pure.size() != 10) return false;

        int sum = 0;
        for (int i = 0; i < 9; i++) {
            if (!isdigit(pure[i])) return false;
            sum += (pure[i] - '0') * (i + 1);
        }
        // 第10位可以是数字或X（代表10）
        char last = pure[9];
        if (last == 'X' || last == 'x') {
            sum += 10 * 10;
        }
        else if (isdigit(last)) {
            sum += (last - '0') * 10;
        }
        else {
            return false;
        }
        return sum % 11 == 0;
    }
};

// 主函数测试
int main() {
    Book b1("C++程序设计", "7-302-10253-5", "清华大学出版社", 39.5, 320, true);
    b1.showInfo();

    if (b1.checkIsbn()) {
        cout << "ISBN校验：合法" << endl;
    }
    else {
        cout << "ISBN校验：不合法" << endl;
    }

    // 修改图书信息测试
    b1.setAvailable(false);
    cout << "\n修改状态后：" << endl;
    b1.showInfo();

    return 0;
}
