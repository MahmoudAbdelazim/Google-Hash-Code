#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
#define PB push_back
#define LOOP(i, a, b) for(int (i) = a; (i) < (b); i++)
#define ALL(x) (x).begin(), (x).end()


struct Skill {
    string name;
    ll level;
};

struct Contr {
    string name;
    ll N;
    vector<Skill> skills;
    ll dayAvailable = 0;

    bool hasRequiredSkill(Skill &skill) {
        for (Skill &s: skills) {
            if (s.name == skill.name && s.level >= skill.level) return true;
        }
        return false;
    }
};

struct Project {
    string name;
    ll D;
    ll S;
    ll B;
    ll R;
    bool finished = false;
    vector<pair<Skill, ll>> roles;
};

vector<Contr> contributors;
vector<Project> projects;
vector<Project> output;
map<string, vector<vll>> skills;

ll C, P;

int main() {
    freopen("E:\\Projects\\Google-Hash-Code\\Hash Code 2022\\in_b.txt", "r", stdin);
    ofstream out;
    out.open("E:\\Projects\\Google-Hash-Code\\Hash Code 2022\\b.txt");

    cin >> C >> P;
    LOOP(i, 0, C) {
        Contr contr;
        cin >> contr.name;
        cin >> contr.N;
        LOOP(j, 0, contr.N) {
            Skill skill;
            cin >> skill.name;
            cin >> skill.level;
            contr.skills.PB(skill);
            if (skills.count(skill.name)) {
                skills[skill.name][skill.level].PB(i);
            } else {
                skills[skill.name] = vector<vll>(105);
                skills[skill.name][skill.level].PB(i);
            }
        }
        contributors.PB(contr);
    }
    LOOP(i, 0, P) {
        Project p;
        cin >> p.name >> p.D >> p.S >> p.B >> p.R;
        LOOP(j, 0, p.R) {
            Skill role;
            cin >> role.name >> role.level;
            p.roles.PB({role, -1});
        }
        projects.PB(p);
    }
    sort(ALL(projects), [](const Project &p1, const Project &p2) {
        return (p1.S / (double)p1.D) > (p2.S / (double) p2.D);
    });
    int projectIdx = 0;
    ll t = 0;
    while (t <= 1e4) {
        for (Project &project: projects) {
            if (project.finished) continue;
            for (auto &role: project.roles) {
                if (!skills.count(role.first.name)) break;
                for (ll j = role.first.level; j <= 100; j++) {
                    for (int i = 0; i < skills[role.first.name][j].size(); i++) {
                        auto &contr = contributors[skills[role.first.name][j][i]];
                        if (contr.dayAvailable <= t) {
                            role.second = skills[role.first.name][j][i];
                            contr.dayAvailable = t + project.D;
                            break;
                        }
                    }
                    if (role.second != -1) break;
                }
            }
            for (auto &role: project.roles) {
                if (!skills.count(role.first.name)) break;
                if (role.second != -1) continue;
                ll j = role.first.level - 1;
                for (int i = 0; i < skills[role.first.name][j].size(); i++) {
                    auto &contr = contributors[skills[role.first.name][j][i]];
                    if (contr.dayAvailable <= t) {
                        for (auto &r: project.roles) {
                            if (r.second != -1 && contributors[r.second].hasRequiredSkill(role.first)) {
                                role.second = skills[role.first.name][j][i];
                                contr.dayAvailable = t + project.D;
                                break;
                            }
                        }
                        if (role.second != -1) break;
                    }
                }
            }
            bool work = true;
            for (auto &role: project.roles) {
                if (role.second == -1) {
                    work = false;
                    for (auto &r: project.roles) {
                        if (r.second != -1) {
                            contributors[r.second].dayAvailable = t;
                            r.second = -1;
                        }
                    }
                    break;
                }
            }

            if (work) {
                project.finished = true;
                output.PB(project);
                for (auto &role: project.roles) {
                    for (Skill &skill: contributors[role.second].skills) {
                        if (skill.level <= role.first.level) skill.level++;
                    }
                }
            }
            projectIdx++;
        }
        t++;
    }
    out << output.size() << "\n";
    for (Project &project: output) {
        out << project.name << "\n";
        for (auto &role: project.roles) {
            out << contributors[role.second].name << " ";
        }
        out << "\n";
    }
    out.close();
}