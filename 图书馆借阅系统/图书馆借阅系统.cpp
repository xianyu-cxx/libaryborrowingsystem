#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ========== 基类：资源 Resource ==========
class Resource
{
protected:
    string name;    //资源名称
    string id;      //资源编号
    int totalNum;   //总数量
    int availNum;   //可借数量
public:
    //基类构造函数
    Resource(string n, string i, int t, int a) :name(n), id(i), totalNum(t), availNum(a) {}

    //基类公共方法
    void addCount(int num)  //增加资源数量
    {
        totalNum += num;
        availNum += num;
    }
    bool reduceCount(int num) //减少资源数量
    {
        if (totalNum >= num)
        {
            totalNum -= num;
            if (availNum > totalNum) availNum = totalNum;
            return true;
        }
        return false;
    }
    bool borrow() //借阅
    {
        if (availNum > 0)
        {
            availNum--;
            return true;
        }
        cout << "资源不足，借阅失败！" << endl;
        return false;
    }
    void giveBack() //归还
    {
        if (availNum < totalNum)
        {
            availNum++;
        }
    }
    //基类普通显示函数，子类可以扩展自己的信息
    void showBaseInfo()
    {
        cout << "名称：" << name << " 编号：" << id << " 总数：" << totalNum << " 可借：" << availNum << endl;
    }
    //基类析构
    ~Resource() {}
};

// ========== 派生类1：图书Book，公有继承Resource ==========
class Book : public Resource
{
private:
    string isbn;
    string press;   //出版社
    int pages;      //页数
public:
    //派生类构造：必须先调用基类构造函数
    Book(string n, string i, int t, int a, string is, string p, int pg)
        : Resource(n, i, t, a), isbn(is), press(p), pages(pg) {
    }

    //子类扩展：显示图书全部信息（基类公共信息+自己独有信息）
    void showInfo()
    {
        showBaseInfo(); //调用继承来的基类函数
        cout << "【图书】ISBN:" << isbn << " 出版社:" << press << " 页数:" << pages << endl;
    }
};

// ========== 派生类2：杂志Magazine，公有继承Resource ==========
class Magazine : public Resource
{
private:
    string issn;
    string pubDate; //出版年月
public:
    Magazine(string n, string i, int t, int a, string is, string date)
        : Resource(n, i, t, a), issn(is), pubDate(date) {
    }

    void showInfo()
    {
        showBaseInfo();
        cout << "【杂志】ISSN:" << issn << " 出版年月:" << pubDate << endl;
    }
};

// ========== 派生类3：电子资源EResource，公有继承Resource ==========
class EResource : public Resource
{
private:
    string link;
    string validTime; //有效期
public:
    EResource(string n, string i, int t, int a, string l, string v)
        : Resource(n, i, t, a), link(l), validTime(v) {
    }

    void showInfo()
    {
        showBaseInfo();
        cout << "【电子资源】链接:" << link << " 有效期:" << validTime << endl;
    }
};

//主函数，菜单测试
int main()
{
    //创建子类对象，会自动执行：先基类构造，再子类构造
    Book b("C++程序设计", "B001", 5, 5, "9781234", "人民邮电出版社", 320);
    Magazine m("计算机学报", "M001", 3, 3, "CN11-2196", "2026-10");
    EResource e("在线C++教程", "E001", 10, 10, "https://xxx.com", "2028-12");

    cout << "=======初始资源信息=======" << endl;
    b.showInfo();
    m.showInfo();
    e.showInfo();

    cout << "\n=======测试借阅图书=======" << endl;
    b.borrow();
    b.showInfo();

    cout << "\n=======测试归还图书=======" << endl;
    b.giveBack();
    b.showInfo();

    cout << "\n=======给杂志增加2本=======" << endl;
    m.addCount(2);
    m.showInfo();

    return 0;
}
