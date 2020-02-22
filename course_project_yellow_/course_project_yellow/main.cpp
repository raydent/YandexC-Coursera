
#include <iostream>
#include <stdexcept>

#include "database.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

using namespace std;

string ParseEvent(istream& is) {
    string temp;
    string res;
    bool first = false;
    while (is.peek() == ' ') {
        is.ignore(1);
    }
    getline(is, res);
    return res;
}

void TestAll();
void TestCommandLast();

int main() {
    TestAll();
    TestCommandLast();
    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else if (command == "Print") {
            db.Print(cout);
        }
        else if (command == "Del") {
            auto condition = ParseCondition(is);//condition is tree (is Node)
            auto predicate = [condition](const Date& date, const string& event) {//predicate is tree (is Node)
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        }
        else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        }
        else if (command.empty()) {
            continue;
        }
        else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
}

void TestCommandLast() {
    {
        Database db;
        istringstream is, iss;
        is.str("Add 2017-01-01 New Year");

        string command;
        is >> command;
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        db.Add(date, event);

        ostringstream os;
        db.Print(os);

        vector<string> events;
        events.push_back(os.str());
        AssertEqual(events, vector<string>{"2017-01-01 New Year\n"}, "Parse Add 01");
    }
    /*{                                       // Add
        Database db;
        istringstream is, iss;
        is.str("\
        Add 2017-01-01 Holiday\n\
        Add 2017-03-08 Holiday\n\
        Add 2017-1-1 New Year\n\
        Add 2017-1-1 New Year\n");

        for (int i = 0; i < 4; i++)
        {
            string command;
            is >> command;

            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }

        ostringstream os;
        db.Print(os);

        vector<string> events;
        events.push_back(os.str());
        AssertEqual(events, vector<string>{"\
        2017-01-01 Holiday\n\
        2017-01-01 New Year\n\
        2017-03-08 Holiday\n"}, "Parse multi-Add 02");
    }*/

}