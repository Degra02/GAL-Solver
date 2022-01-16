#include <iostream>
#include <bits/stdc++.h>
#include "all-headers.h"

using namespace std;

void parse_user_input(vector <string> *userinput){
    if(userinput->size() != 0){
        for(int i = userinput->size() - 1; i >= 0; i--){
            userinput->pop_back();
        }
    }
    string input, call;
    cout << "function: "; fflush(stdin); getline(cin, input);
    stringstream check(input);

    while(getline(check, call, ' ')){
        (*userinput).push_back(call);
    }
    
}

void function_call(Nodeptr matList){
    string end;
    vector <string> userinput;
    do{ 
        parse_user_input(&userinput);

        if(userinput[0] == "new"){
            if(userinput[1] == "matrix"){
                matList = insert(matList);
            }
            else if(userinput[1] == "vector"){
                continue;
            }
            else{
                continue;
            }
        } else if(userinput[0] == "calculate"){
            if(userinput[1] == "matrix"){
                if(userinput[2] == "product"){

                } else if(userinput[2] == "sum"){

                } else if(userinput[2] == ""){

                }
            }
            else if(userinput[1] == "vector"){

            }
            else {
                continue;
            }
        }

        end = userinput[0];
    }while(end != "end");
}