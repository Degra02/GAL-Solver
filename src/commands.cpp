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
    printf("\x01b[1;38;5;3mFunction: \x1b[0m"); fflush(stdin); getline(cin, input);
    stringstream check(input);

    while(getline(check, call, ' ')){
        (*userinput).push_back(call);
    }
    
}

void function_call(Lists list){
    Matrix m;
    string end;
    vector <string> userinput;
    do{ 
        parse_user_input(&userinput);

        if(userinput[0] == "new"){
            if(userinput[1] == "matrix"){
                string name;
                cout << "name= "; cin >> name;
                list->Mlist = insert(list->Mlist, name);
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
        } else if(userinput[0] == "print"){
            if(userinput[1] == "matrix"){
                if((m = get_search(list->Mlist, userinput[2])) != NULL){
                    print_matrix(m);
                } else {
                    cout << endl << "Matrix not found" << endl << endl;
                }
            } else if(userinput[1] == "vector"){

            }
        }

        end = userinput[0];
    }while(end != "end");
}