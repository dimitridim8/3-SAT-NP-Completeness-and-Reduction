#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

//Create Clarifier for 3-SAT

bool C(vector<int*> cnf, vector<bool> T){
    for(int i = 0; i < cnf.size(); i++){
        //Find Literals
        int l1 = cnf[i][0];
        int l2 = cnf[i][1];
        int l3 = cnf[i][2];
        
        //Verify Input
        if(l1 == 0 || l2 == 0 || l3 == 0){
            return false;
        }
        else if(abs(l1) > T.size() || abs(l2) > T.size() || abs(l3) > T.size()){
            return false;
        }

        //Determine if Clause is True Based off Current Truth Assignment
        bool l1_true = (T[abs(l1)] && l1 > 0) || (!T[abs(l1)] && l1 < 0);
        bool l2_true = (T[abs(l2)] && l2 > 0) || (!T[abs(l2)] && l2 < 0);
        bool l3_true = (T[abs(l3)] && l3 > 0) || (!T[abs(l3)] && l3 < 0);

        //If Clause is not True, Return False
        if(!l1_true && !l2_true && !l3_true){
            return false;
        }
    }
    return true;
}


void T_helper(vector<bool>& T, int index){
    if(!T[index]){
        T[index] = true;
        return;
    }
    else{
        T[index] = false;
        return T_helper(T, index--);
    }
}

//Create Algorithm for 3-SAT
vector<bool> SAT_algorithm(vector<int*> cnf, int n){
    
    //Check if Valid Input
    if(cnf.size() <= 0 || n < 3){
        return vector<bool>({false});
    }
    
    //Create Initial Truth Alignment
    vector<bool> T;
    for(int i = 0; i <= n; i++){
        T.push_back(false);
    }

    //Check Each Truth Alignment
    bool output = false;
    int step = 0;
    
    while(!output && !T[0] && step < 100){
        //Use Clarifier to Determine whether current T is a solution
        if(C(cnf, T)){
            output = true;
        }
        //Update Truth Alignment
        T_helper(T, n);
        step++;
    }
    

    //Store Whether CNF has solution in T[0], then return T
    T[0] = output;
    return T;
}

void run(string input_name, string output_name){
    //Read in Input File
    ifstream input_file(input_name);
    if(!input_file.is_open()){
        input_file.close();
        if(input_name=="./input.txt"){
            cout << "input.txt not detected. Running testcases" << endl;
            run("./test_units/input-files/input-1.txt", "./test_units/output-files/output-1.txt");
            run("./test_units/input-files/input-2.txt", "./test_units/output-files/output-2.txt");
            run("./test_units/input-files/input-3.txt", "./test_units/output-files/output-3.txt");
            run("./test_units/input-files/input-4.txt", "./test_units/output-files/output-4.txt");
            run("./test_units/input-files/input-5.txt", "./test_units/output-files/output-5.txt");
            cout << "Finished Running Test Cases, check ./test_units for output" << endl;
        }
        return;
    }

    //Determine Whether Using Certifier or Algorithm
    string str, s;
    int cert;
    if(!getline(input_file, str)){
        cout << "Invalid input" << endl;
        return;
    }
    cert = stoi(str);

    //Read in Clauses
    vector<int*> cnf;
    if(!getline(input_file, str)){
        cout << "Invalid input" << endl;
        return;
    }

    stringstream ss(str);
    int clause[3] = {1, 2, 3};
    while(getline(ss, s, ' ')){
        clause[0] = stoi(s);
        if(!getline(ss, s, ' ')){
            cout << "Invalid input" << endl;
            return;
        }
        clause[1] = stoi(s);
        if(!getline(ss, s, ' ')){
            cout << "Invalid input" << endl;
            return;
        }
        clause[2] = stoi(s);
        cnf.push_back(clause);
    }

    //Read in # of Variables

    
}

int main(){
    //Create Test CNF with 3 clauses and 3 different variables
    vector<int*> cnf;
    int temp[3] = {1, -2, 3};
    cnf.push_back(temp);
    temp[0] = -1;
    temp[1] = 2;
    temp[2] = 3;
    cnf.push_back(temp);
    temp[0] = 1;
    temp[1] = 2;
    cnf.push_back(temp);
    
    vector<bool> output = SAT_algorithm(cnf, 3);
    if(!output[0]){
        cout << "No Solution" << endl;
    }
    else{
        cout << "Solution:" << endl;
        for(int i = 1; i < output.size()-1; i++){
            cout << "X" << i << " = " << output[i] << ", ";
        }
        cout << "X" << output.size()-1 << " = " << output[output.size()-1] << endl;
    }
    
    return 1;
}