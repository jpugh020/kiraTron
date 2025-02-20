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

        string lastName;



        int comma = line.find(',');

        lastName = line.substr(0, comma);
        
        line = line.substr(comma + 1);
        //cout<<quote<<endl;
        lastName = lastName.substr(lastName.find(' ') + 1);
        int quote = lastName.length() - 1;
        lastName = lastName.substr(0, quote);
        

        key = lastName;

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

    while (it1 != m1.end()) {
        map<string, string>::iterator it2 = m2.begin();
        while(it1->first != it2->first && it2 != m2.end()) {
            it2++;
        }
        
            end[it2->second] = it1->second;
    
        
        ++it1;
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