#include <iostream>
#include <bits/stdc++.h>
#include "all-headers.h"

using namespace std;

/*void parse_user_input(vector <string> *userinput){
    string input, call;
    cout << "function: "; cin >> input;
    vector <string> tokens;
    stringstream check1(input);

    while(getline(check1, call, ' ')){
        tokens.push_back(call);
    }
    
}*/

void function_call(Nodeptr matList){
    string input, call;
    cout << "function: "; cin >> input;
    vector <string> userinput;
    stringstream check1(input);

    while(getline(check1, call, ' ')){
        userinput.push_back(call);
    }

    if(userinput[0] == "input_matrix"){
        insert(matList);
        print_matrix(matList->m);
    }
    



}