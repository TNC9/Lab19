#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    string line;
    while(getline(file,line)){
        char name[100];
        int a,b,c;
        sscanf(line.c_str(),"%[^:]: %d %d %d",name,&a,&b,&c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    file.close();
}

void getCommand(string& command, string& key){
    cout << "Please input your command: ";
    string line;
    getline(cin,line);
    int idx = line.find_first_of(" ");
    command = line.substr(0,idx);
    key = line.substr(idx+1);
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i=0; i<names.size(); i++){
        if(toUpperStr(names[i])==key){
            found = true;
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    cout << "---------------------------------\n";
    bool found = false;
    for(unsigned int i=0; i<names.size(); i++){
        if(grades[i]==key[0]){
            found = true;
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    if(!found) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
