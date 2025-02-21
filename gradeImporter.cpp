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


add logic to have column headers of unique user id and assignment name. prompt user for assignment name / class period? 

cpp gui? research gui writing  - fltk - begin building


fix issue where Unique User ID and assignment name are not appearing in final map












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
        for (char& c : key) if (c == ',') c = ' ';
        value = line.substr(0, comma);
        userIds[key] = value;

        
    }
    file.close();

    return userIds;

}

auto GetKiraGradebook() {
    ifstream file("Introduction to CS in Python (High School)_1st Period_7th Period_3rd Period_4th Period_5th period_6th Period_2025-02-20 (1).csv");
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
   for (const auto& [key2, value2]: m1) { 
    for (const auto& [key1, value1] : m2){ 
        if (value1 == "Unique User ID" && end.find(value1) != end.end()) {
            end[value1] = aN;
        } if (key1 == key2) {
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