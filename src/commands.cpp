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
    vector <string> userinput;
    do{
        cout << "function: "; getline(cin, input);
        stringstream check(input);
        while(getline(check, call, ' ')){
            userinput.push_back(call);
        }

        if(userinput.at(0) == "input"){
            if(userinput.at(1) == "matrix"){
                matList = insert(matList);
                print_matrix(matList->m);
            }
            else if(userinput.at(1) == "vector"){

            }
        }



        userinput.clear();
    }while(userinput[0] != "end");
}