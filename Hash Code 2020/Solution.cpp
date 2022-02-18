#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct details {
    ll score;
    ll book_idx;

    bool operator<(details d) const {
        return score < d.score;
    }

    bool operator>(details d) const {
        return score > d.score;
    }
};

struct library {
    ll ID;
    ll numBooks;
    ll signup;
    ll booksPerDay;
    vector<details> books;
    bool valid = true;
    ll average;
    ll booksScore;
    vector<ll> booksScanned;

    bool operator<(const library& l) const {
        return average < l.average;
    }

    bool operator>(const library& l) const {
        return average > l.average;
    }
};

ll B, L, D;
vector<pair<ll, ll>> arr;
vector<int> librariesUsed;

bool vis[(int) (1e5 + 5)];
int freq[(int) (1e5 + 5)];

void scan(library &l, int curDay) {
    int count = 0;
    for (int i = curDay; i <= D; count++) {
        if (l.books.empty())
            break;
        if (vis[l.books[l.books.size() - 1].book_idx]) {
            count--;
            l.books.pop_back();
            continue;
        }
        vis[l.books[l.books.size() - 1].book_idx] = true;
        l.books.pop_back();
        if (count == l.booksPerDay) {
            count = 0;
            i++;
        }
    }
    if (!l.booksScanned.empty())
        librariesUsed.push_back(l.ID);
}

int main() {
    fstream input_file;
    input_file.open("C:\\Users\\M.Abdelazim\\Desktop\\e_so_many_books.txt");

    input_file >> B >> L >> D;
    vector<ll> book_score(B);
    for (int i = 0; i < B; i++)
        input_file >> book_score[i];
    vector<library> libraries(L);
    for (int i = 0; i < L; ++i) {
        input_file >> libraries[i].numBooks >> libraries[i].signup >> libraries[i].booksPerDay;
        if (libraries[i].signup >= D) {
            libraries[i].valid = false;
            continue;
        }
        ll books_score = 0;
        details detail{};
        for (int j = 0; j < libraries[i].numBooks; j++) {
            input_file >> detail.book_idx;
            freq[detail.book_idx]++;
            detail.score = book_score[detail.book_idx];
            if (freq[detail.book_idx] == 1)
                books_score += detail.score;
            libraries[i].books.push_back(detail);
        }
        sort(libraries[i].books.begin(), libraries[i].books.end());
        libraries[i].booksScore = books_score;
        libraries[i].ID = i;
        libraries[i].average = libraries[i].booksScore / (libraries[i].signup);
    }
    sort(libraries.rbegin(), libraries.rend());
    for (int i = 0; i < L; i++) {
        if (libraries[i].valid) {
            arr.emplace_back(libraries[i].signup, i);
        }
    }
    for (int i = 1; i < L; i++) {
        arr[i].first += arr[i - 1].first;
    }
    int j = 0;
    for (int i = 1; i <= D; i++) {
        if (arr[j].first == i) {
            scan(libraries[arr[j].second], i);
            j++;
        }
    }
    input_file.close();
    fstream output;
    output.open("D:\\e_output.txt", ios::out);

    output << librariesUsed.size() << "\n";
    for (int i = 0; i < L; i++) {
        if (libraries[i].valid && !libraries[i].booksScanned.empty()) {
            output << libraries[i].ID << " " << libraries[i].booksScanned.size() << "\n";
            for (long long o : libraries[i].booksScanned) {
                output << o << " ";
            }
            output << "\n";
        }
    }
}