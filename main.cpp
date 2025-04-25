#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

class Book {
public:
    string author;
    string title;
    string publish;
    int year;
    int pages;

    Book(string a, string t, string p, int y, int pg)// конструктор
        : author(a), title(t), publish(p), year(y), pages(pg) {
    }

    bool operator<(const Book& other) const {//сравниваем два объекта(возвращает true если первый объект должен стоять перед объектом 2)
        return title < other.title;
    }
    bool operator==(const Book& other) const {//для unordered_set необходимо точно определять равенство элементов(если a == b, то их хеши должны совпадать)
        return title == other.title && author == other.author;
    }
    void print(ostream& out) const {//выводит книги 
        out << author << ", " << title << ", " << publish
            << ", " << year << " год, " << pages << " стр.";
    }
};

ostream& operator<<(ostream& out, const Book& book) {//перегрузка(ostream& out - ссылка на выходной поток)
    book.print(out);
    return out;
}

namespace std {//хеш-функция для unordered_set
    template<>
    struct hash<Book> {
        size_t operator()(const Book& b) const {
            return hash<string>()(b.title) ^ hash<string>()(b.author);
        }
    };
}
int main() {
    ifstream in("input.txt");//исходный файл
    ofstream out("output.txt");//для результата 

    vector<Book> books;
    string author, title, publish;
    int year, pages;

    while (getline(in, author) && getline(in, title) &&//считываем файл
        getline(in, publish) && in >> year >> pages) {
        in.ignore(); //пропускаем символ перевода строки
        books.push_back(Book(author, title, publish, year, pages));
    }

    out << "Исходный список книг:\n";//выводим список книг без сортировки 
    for (const auto& book : books) {
        out << book << "\n";
    }

    sort(books.begin(), books.end());//сортируем 

    out << "\nСписок после сортировки по названию:\n";
    for (const auto& book : books) {
        out << book << "\n";
    }

    deque<Book> bookdeq;//создаем пустой 
    copy(books.begin(), books.end(), back_inserter(bookdeq));

    set<Book> bookSet(books.begin(), books.end());//добавление в set 
    unordered_set<Book> bookUSet(books.begin(), books.end());//добавление в unordered_set

    out << "\nСкопированный список в deque:\n";
    for (const auto& book : bookdeq) {
        out << book << "\n";
    }

    out << "\nUnordered_set книг :\n";
    for (const auto& b : bookUSet) out << b << "\n";

    in.close();
    out.close();
    return 0;
}
