#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;

struct street {
    string name;
    ll start{};
    ll end{};
    ll L{};
    int traffic = 0;
    int score = 0;
};

unordered_map<string, street *> streets;
vector<vector<street *>> intersections;

bool cmp(street *a, street *b) {
    if (a->score == b->score) return a->traffic > b->traffic;
    return a->score > b->score;
}

int main() {
    freopen("C:\\Users\\M.Abdelazim\\Desktop\\Hash code\\input\\f.txt", "r", stdin);
    ofstream out;
    out.open("C:\\Users\\M.Abdelazim\\Desktop\\Hash code\\f.txt");

    ll D, I, S, V, F;
    cin >> D >> I >> S >> V >> F;
    intersections.resize(I);
    for (int i = 0; i < S; i++) {
        auto *s = new street;
        string name;
        cin >> s->start >> s->end;
        cin >> name;
        s->name = name;
        cin >> s->L;
        streets[name] = s;
        intersections[s->end].emplace_back(s);
    }
    for (int i = 0; i < V; i++) {
        ll P;
        cin >> P;
        string name;
        for (int j = 0; j < P; j++) {
            cin >> name;
            street *s = streets[name];
            ++s->traffic;
        }
    }

    stringstream output;

    int cnt = 0;
    int i = 0;
    for (auto &in: intersections) {
        int numCars = 0;
        vector<pair<string, int>> streetsUsed;
        for (auto &incoming: in) {
            numCars += incoming->traffic;
        }

        for (auto &incoming: in) {
            ll streetTime = ceil(((double) incoming->traffic / (double) numCars) * (D * 10 / I));
            if (numCars == 0 || streetTime == 0) continue;
            else if (streetTime > D) streetTime = D;
            else {
                streetsUsed.emplace_back(incoming->name, streetTime);
            }
        }
        if (streetsUsed.empty()) {
            ++i;
            continue;
        }
        output << i << "\n";
        output << streetsUsed.size() << "\n";
        for (auto & k : streetsUsed) {
            output << k.first << " " << k.second << "\n";
        }
        ++i;
        ++cnt;
    }
    out << cnt << "\n" << output.str();
    out.close();
}