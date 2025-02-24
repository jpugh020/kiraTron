#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <regex>


using namespace std;

/* 

TO-DO LIST:

Way to use cpp to control chrome? Could try to automate download




cpp gui? research gui writing  - fltk - begin building

Change Unique User ID to USER ID - should work with sorting and will still be readable by schoology.

Fix out of range bug - need more edu on iterating with maps, maybe different data type to be more efficient?? 













*/


auto GetUserIDs() {
    ifstream file("userids.csv");
    map<string, string> userIds;

    if (!file.is_open()) {
        cout<<"Error, userIds file not found"<<endl;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string key;
        string value;

        int comma = line.find(',');

        key = line.substr(comma + 1);
        for (char& c : key) {
            if (c == ',') {
                c = ' ';
            }
        }
        value = line.substr(0, comma);
        userIds[key] = value;

        
    }
    file.close();

    return userIds;

}

auto GetKiraGradebook() {
    ifstream file("Introduction to CS in Python (High School)_1st Period_7th Period_3rd Period_4th Period_5th period_6th Period_2025-02-21.csv");
    map<string, string> points;

    if (!file.is_open()) {
        cout<<"Error, Kira file not found"<<endl;
    }

    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string key;
        string value;
        string grade;
        int quote;
        string name;



        int comma = line.find(',');

        name = line.substr(0, comma);
        quote = name.find('\"');
        name.erase(quote, 1);
        quote = name.find('\"');
        name.erase(quote, 1);
        
        line = line.substr(comma + 1);
        
        
        

        key = name;

        comma = line.find(',');
        line = line.substr(comma + 1);
        comma = line.find(',');
        line = line.substr(comma+1);
        if (line == "\"\"") {
            line = "0";
        }

        value = line;

        points[key] = value;

        



        
    }
    file.close();

    return points;



}

auto getFinalCSV(map<string, string> m1, map<string, string>m2) {
    map<string, string>::iterator it1 = m1.begin();
    map<string, string>::iterator it2 = m2.begin();
    map<string, string> end;
    string aN;
    cout<<"What would you like to name the assignment?"<<endl;
    getline(cin, aN);
   for ( auto& [key2, value2]: m1) { 
    for ( auto& [key1, value1] : m2){ 
        if (value1 == "Unique User ID" && end.find(value1) == end.end()) {
            value1 = "UNique User ID";
            end[value1] = aN;
        } if (key1 == key2) {
            end[value1] = value2;
        } else if (key1.substr(key1.find(' ') + 1) == "ALTGILBERS" && key2.substr(key2.find(' ' + 1)) == "ALTGILBERS") {
            end[value1] = value2;
        }

    }
}

    return end;
}

int main() {

map<string, string> finalCSV = getFinalCSV(GetKiraGradebook(), GetUserIDs());


ofstream outputFile;

string period;

for (const auto& [key, value] : finalCSV) {
    if (key == "USRstudent1864") {
        period = "1st Period";
    } else if (key == "USRstudent10232") {
        period = "7th Period";
    } else if (key == "USRstudent1794") {
        period = "6th Period";
    } else if (key == "USRstudent25451") {
        period = "5th Period";
    } else if (key == "USRstudent1094") {
        period = "4th Period";
    } else if (key == "USRstudent27851") {
        period = "3rd Period";
    }

}


outputFile.open(period+".csv", ios::out);
for (const auto& [key, value] : finalCSV) {
    
    outputFile << key << ","<<value<<endl;
        
}
    outputFile.close();
    return 0;
}