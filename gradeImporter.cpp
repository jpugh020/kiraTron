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

add logic for reading kira grades into map, need to consider how to remove unnecessary info

add logic to compare maps & replace name w/ user id (could be same step as reading grades into map, just compare as you read?)

cpp gui? research gui writing 

.gitignore ignoring proper things?









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

        key = line.substr(comma);
        value = line.substr(0, comma);
        userIds[key] = value;

        
    }
    file.close();

    return userIds;

}

int main() {

    
map<string, string> idList = GetUserIDs();



   

    

    return 0;
}