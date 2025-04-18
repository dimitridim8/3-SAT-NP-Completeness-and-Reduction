#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
using namespace std;

//Create Clarifier for 3-SAT

bool C(vector<vector<int>> cnf, vector<bool> T){
    for(int i = 0; i < cnf.size(); i++){
        //return false;
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
        index--;
        T_helper(T, index);
        return;
    }
}

//Create Algorithm for 3-SAT
vector<bool> SAT_algorithm(vector<vector<int>> cnf, int n){
    
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
    
    while(!output && !T[0]){
        //Use Clarifier to Determine whether current T is a solution
        if(C(cnf, T)){
            output = true;
            //cout << "T Found" << endl;
        }
        else{
            //Update Truth Alignment
            T_helper(T, n);
            
            /*for(int i = 0; i < T.size(); i++){
                cout << T[i] << " ";
            }
            cout << endl;*/
        }
    }
    

    //Store Whether CNF has solution in T[0], then return T
    T[0] = output;
    return T;
}

void generate_worst_case(string file_name, int c, int n){
    ofstream file(file_name);
    //Write to File Whether Certifier Test, and # of Variables
    file << "0" << endl;
    file << n << endl;

    //Generate Impossible Clauses to Show Worst Case Time Complexity
    file << 1 << " " << 2 << " " << 3 << " ";
    file << 1 << " " << -2 << " " << -3 << " ";
    file << -1 << " " << -2 << " " << 3 << " ";
    file << -1 << " " << 2 << " " << -3 << " ";
    file << -1 << " " << 2 << " " << 3 << " ";
    file << -1 << " " << -2 << " " << -3 << " ";
    file << 1 << " " << 2 << " " << -3 << " ";
    file << 1 << " " << -2 << " " << 3 << " ";

    //Generate Clauses for CNF and Write to File
    for(int i = 0; i < c; i++){
        int r1 = rand() % n+1;
        if(r1 == 0){r1++;}
        int r2 = rand() % n+1;
        if(r2 == 0){r2++;}
        while(r1 == r2){
            r2 = rand() % n+1;
            if(r2 == 0){r2++;}
        }
        int r3 = rand() % n+1;
        if(r3 == 0){r3++;}
        while(r1 == r3 || r2 == r3){
            r3 = rand() % n+1;
            if(r3 == 0){r3++;}
        }
        file << r1 << " " << r2 << " " << r3 << " ";
    }
    file << endl;
    file.close();
    return;
}

void generate_input(string file_name, bool cert, int c, int n){
    ofstream file(file_name);
    //Write to File Whether Certifier Test, and # of Variables
    if(cert){
        file << "1" << endl;
    }
    else{
        file << "0" << endl;
    }
    file << n << endl;

    //Generate Clauses for CNF and Write to File
    for(int i = 0; i < c; i++){
        int r1 = rand() % n+1;
        if(r1 == 0){r1++;}
        int r2 = rand() % n+1;
        if(r2 == 0){r2++;}
        while(r1 == r2){
            r2 = rand() % n+1;
            if(r2 == 0){r2++;}
        }
        int r3 = rand() % n+1;
        if(r3 == 0){r3++;}
        while(r1 == r3 || r2 == r3){
            r3 = rand() % n+1;
            if(r3 == 0){r3++;}
        }
        r1 = r1 - 2 * (r1 * (rand() % 2));
        r2 = r2 - 2 * (r2 * (rand() % 2));
        r3 = r3 - 2 * (r3 * (rand() % 2));
        
        file << r1 << " " << r2 << " " << r3 << " ";
    }
        file << endl;
    if(cert == 1){
        for(int i = 0; i < n; i++){
            int r = rand() % 2;
            file << r << " ";
        }
        file << endl;
    }
    file.close();
    return;
}

double run(string input_name, string output_name){
    //Read in Input File
    ifstream input_file(input_name);
    if(!input_file.is_open()){
        input_file.close();
        if(input_name=="./input.txt"){
            cout << "input.txt not detected. Running testcases" << endl;
            string input_path = "./test_units/input-files/input-";
            string output_path = "./test_units/output-files/output-";
            string ext = ".txt";
            generate_input(input_path + "1" + ext, true, 5, 3);
            generate_input(input_path + "2" + ext, true, 50, 10);
            generate_input(input_path + "3" + ext, true, 500, 100);
            generate_input(input_path + "4" + ext, true, 5000, 1000);
            generate_input(input_path + "5" + ext, true, 50000, 10000);
            generate_input(input_path + "6" + ext, false, 5, 3);
            generate_input(input_path + "7" + ext, false, 50, 5);
            generate_input(input_path + "8" + ext, false, 500, 6);
            generate_input(input_path + "9" + ext, false, 5000, 7);
            generate_input(input_path + "10" + ext, false, 50000, 8);
            generate_worst_case(input_path + "11" + ext, 5, 3);
            generate_worst_case(input_path + "12" + ext, 50, 5);
            generate_worst_case(input_path + "13" + ext, 100, 8);
            generate_worst_case(input_path + "14" + ext, 200, 11);
            generate_worst_case(input_path + "15" + ext, 300, 15);
            vector<double> times;
            for(int i = 1; i <= 15; i++){
                times.push_back(run(input_path + to_string(i) + ext, output_path + to_string(i) + ext));
            }
            /*
            run("./test_units/input-files/input-1.txt", "./test_units/output-files/output-1.txt");
            run("./test_units/input-files/input-2.txt", "./test_units/output-files/output-2.txt");
            run("./test_units/input-files/input-3.txt", "./test_units/output-files/output-3.txt");
            run("./test_units/input-files/input-4.txt", "./test_units/output-files/output-4.txt");
            run("./test_units/input-files/input-5.txt", "./test_units/output-files/output-5.txt");
            */
            ofstream time_file("./test_units/CPU_TIMES.txt");
            time_file << "Certifier Tests" << endl;
            for(int i = 1; i <= 5; i++){
                time_file << "Test " << i << " CPU Time: " << times[i-1] << endl;
            }
            time_file << endl << "Algorithm Tests" << endl;
            for(int i = 6; i <= 15; i++){
                time_file << "Test " << i << " CPU Time: " << times[i-1] << endl;
            }
            time_file.close();
            cout << "Finished Running Test Cases, check ./test_units for output" << endl;
        }
        return 0;
    }

    //Determine Whether Using Certifier or Algorithm
    string str, s;
    int cert;
    if(!getline(input_file, str)){
        cout << "Invalid input" << endl;
        return -1;
    }
    cert = stoi(str);

    //Read in # of Variables
    int n;
    if(!getline(input_file, str) || stoi(str) < 3){
        cout << "Invalid input" << endl;
        return -1;
    }
    n = stoi(str);

    //Read in Clauses
    vector<vector<int>> cnf;
    if(!getline(input_file, str)){
        cout << "Invalid input" << endl;
        return -1;
    }

    stringstream ss(str);
    vector<int> clause;
    clause.push_back(1);
    clause.push_back(2);
    clause.push_back(3);
    while(getline(ss, s, ' ')){
        clause[0] = stoi(s);
        if(!getline(ss, s, ' ') || abs(clause[0]) > n){
            cout << "Invalid input" << endl;
            return -1;
        }
        clause[1] = stoi(s);
        if(!getline(ss, s, ' ') || abs(clause[1]) > n){
            cout << "Invalid input" << endl;
            return -1;
        }
        clause[2] = stoi(s);
        if(abs(clause[2] > n)){
            cout << "Invalid input" << endl;
            return -1;
        }
        cnf.push_back(clause);
    }

    if(cnf.size() < 1){
        cout << "Invalid input" << endl;
        return -1;
    }

    //If Using Certifier, Read in Truth Alignment
    vector<bool> T;
    double time;
    if(cert == 1){
        T.push_back(false);
        bool l;
        ss = stringstream(str);
        if(!getline(input_file, str)){
            cout << "Invalid input" << endl;
            return -1;
        }
        for(int i = 1; i <= n; i++){
            if(getline(ss, s, ' ')){
                l = stoi(s);
                if(l == 1){T.push_back(true);}
                else{T.push_back(false);}
            }
        }
        const auto start{std::chrono::steady_clock::now()};
        T[0] = C(cnf, T);
        const auto finish{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{finish - start};
        time = elapsed_seconds.count();
    }
    else{
        const auto start{std::chrono::steady_clock::now()};
        T = SAT_algorithm(cnf, n);
        const auto finish{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{finish - start};
        time = elapsed_seconds.count();
        for(int i = 0; i < 25; i++){
            //cout << cnf[i][0] << " " << cnf[i][1] << " " << cnf[i][2] << endl;
        }
    }

    //Write to Output File
    ofstream output_file(output_name);
    if(cert == 1){
        output_file << "Certifier Test:" << endl;
        output_file << "n = " << n << " T = [";
        for(int i = 1; i < min((int)(T.size()), 25); i++){
            output_file << "X" << i << " = " << T[i] << ", ";
        }
        if(T.size() > 50){
            output_file << "... ";
            for(int i = T.size()-25; i < T.size()-1; i++){
                output_file << "X" << i << " = " << T[i] << ", ";
            }
        }
        else{
            for(int i = 25; i<T.size()-1; i++){
                output_file << "X" << i << " = " << T[i] << ", ";
            }
        }
        output_file << "X" << T.size()-1 << " = " << T[T.size()-1] << "]" << endl;
        if(!T[0]){
            output_file << "Input Truth Alignments are not a Valid Solution to the Given CNF" << endl;
            output_file.close();
            return time;
        }
        output_file << "Input Truth Alignments are a Valid Solution to the Given CNF" << endl;
        output_file.close();
        return time;
    }
    output_file << "Algorithm Test:" << endl;
    output_file << "n = " << n << endl;
    if(!T[0]){
        output_file << "No Solution is possible for the Given CNF" << endl;
        output_file.close();
        return time;
    }
    output_file << "Solution Found!" << endl;
    output_file << "T = [";
    for(int i = 1; i < min((int)(T.size()), 25); i++){
        output_file << "X" << i << " = " << T[i] << ", ";
    }
    if(T.size() > 50){
        output_file << "... ";
        for(int i = T.size()-25; i < T.size()-1; i++){
            output_file << "X" << i << " = " << T[i] << ", ";
        }
    }
    else{
        for(int i = 25; i<T.size()-1; i++){
            output_file << "X" << i << " = " << T[i] << ", ";
        }
    }
    output_file << "X" << T.size()-1 << " = " << T[T.size()-1] << "]" << endl;
    output_file.close();
    return time;
}

int main(){
    /*
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
    */
    //Default Run Using input.txt & output.txt
    run("./input.txt", "./output.txt");
    return 1;
}