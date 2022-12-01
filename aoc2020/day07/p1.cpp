#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <deque>

using namespace std;

#define LOG1(x) cout << x << endl;
#define LOG2(x, y) cout << x << y << endl;

class Bag {
public:
    Bag(string name): name(name){}
    ~Bag(){}
    string name;
    void SetName(string n) { name = n; }
    string GetName() { return name; }
    bool compare(shared_ptr<Bag> b) {
        return this->name == b->name;
    }

};

class Rule {
public:
    Rule(shared_ptr<Bag> b): mainBag(b){}
    ~Rule(){}
    void AddBag(shared_ptr<Bag> b, int qty) {
        subBags.insert({b, qty});
    }
    bool containsBag(shared_ptr<Bag> b) {
        for(pair<shared_ptr<Bag>, int> s: subBags) {
            if( b.get()->compare( s.first ) ) {
                return true;
            }
        }
        return false;
    }
    string AsString() {
        string res;
        res += mainBag->GetName();
        for(pair<shared_ptr<Bag>, int> b: subBags) {
            res += " <";
            res += b.first->GetName();
            res += ", ";
            res += to_string(b.second);
            res += ">";
        }
        return res;
    }
    shared_ptr<Bag> mainBag;
    map<shared_ptr<Bag>, int> subBags;
};


void tokenize(const string& s, const char& delim, vector<string>& out) {
    stringstream ss(s);
    string line;
    while(getline(ss, line, delim)) {
        out.push_back(line);
    }
}

void ParseInput(vector<Bag>& bags, vector<Rule>& rules) {
    ifstream input("input_data.txt");
    size_t  pos;
    for(string line; getline(input, line);) {
        pos = line.find("contain");
        string lower = line.substr(0, pos-1); // rm trailing space
        string upper = line.substr(pos+8); // 8 is len of contain + space

        pos = lower.find("bag");
        lower = lower.substr(0, pos-1);
        Bag bag(lower);
        bags.push_back(bag);
        Rule rule(make_shared<Bag>(bag));

        if (upper[0] == 'n') { // no bags
            rules.push_back(rule);
            continue;
        }
        else {
            vector<string> innerBagStr;
            tokenize(upper, ',', innerBagStr);
            for(string& s: innerBagStr) {
                if(s[0] == ' ') {
                    s = s.substr(1);
                }
                if(s[s.length()-1] == ' ') {
                    s = s.substr(0, s.length()-2);
                }
                if(s[s.length()-1] == '.') {
                    s = s.substr(0, s.length()-1);
                }
                pos = s.find("bag");
                s = s.substr(0, pos-1);

                Bag b(s.substr(2, s.length()-1));
                rule.AddBag(make_shared<Bag>(b), stoi(s.substr(0,1)));
            }
        }
        rules.push_back(rule);
    }
}

int main() {
    vector<Bag> Bags;
    vector<Rule> Rules;
    ParseInput(Bags, Rules);

    Bag targetBag("shiny gold");

    set<shared_ptr<Bag>> confirmedBags;
    deque<shared_ptr<Bag>> bagsToCheck;

	for(Bag& b: Bags) {
		if(b.name == "shiny gold") {
			bagsToCheck.push_back(make_shared<Bag>(b));
			break;
		}
	}

    while(bagsToCheck.size() > 0) {
        for(Rule& r: Rules) {
            if( r.containsBag(bagsToCheck.at(0))) {
                bagsToCheck.push_back(r.mainBag);
            }
        }
        confirmedBags.insert(bagsToCheck.at(0));
        bagsToCheck.pop_front();
    }
	confirmedBags.erase(confirmedBags.begin());

	LOG2("Number of bags: ", confirmedBags.size())
    return 0;
}
