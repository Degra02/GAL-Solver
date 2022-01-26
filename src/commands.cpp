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
    string name;
    vector <string> userinput;
    do{ 
        parse_user_input(&userinput);

        if(userinput[0] == "new"){
            if(userinput[1] == "matrix"){
                list->Mlist = command_new_matrix(list->Mlist);
            } else if(userinput[1] == "vector"){
                list->Vlist = command_new_vector(list->Vlist);
            } else if(userinput[1] == "system"){
                list->Eqlist = command_new_system(list->Eqlist);
            } else if(userinput[1] == "set"){
                list->Slist = command_new_vectors_set(list->Slist);
            } else if(userinput[1] == "function"){
                list = command_new_function(list);
                list = command_save_function(list);
            } else {
                cout << "Invalid function call" << endl << endl;
            }
        } else if(userinput[0] == "calculate"){
            if(userinput[1] == "matrix"){
                if(userinput[2] == "product"){
                    list->Mlist = command_matrix_product(list->Mlist);
                } else if(userinput[2] == "sum"){
                    list->Mlist = command_matrix_sum(list->Mlist);
                } else if(userinput[2] == "difference"){
                    list->Mlist = command_matrix_difference(list->Mlist);
                } else if(userinput[2] == "transpose"){
                    list->Mlist = command_matrix_traspose(list->Mlist);
                } else if(userinput[2] == "scalar"){
                    list->Mlist = command_matrix_scalar_mult(list->Mlist);
                } else if(userinput[2] == "stairs"){
                    list->Mlist = command_matrix_stairs(list->Mlist);
                } else if (userinput[2] == "rref"){
                    list->Mlist = command_matrix_rref(list->Mlist);
                } else if(userinput[2] == "rank"){
                    command_matrix_rank(list->Mlist);
                } else if(userinput[2] == "base"){
                    command_matrix_is_base(list->Mlist);
                } else if(userinput[2] == "det"){
                    command_matrix_det(list->Mlist);
                } else if(userinput[2] == "reverse"){
                    list->Mlist = command_matrix_reverse(list->Mlist);
                } else {
                    cout << "Invalid function call" << endl << endl;
                }
            } else if(userinput[1] == "vector"){
                if(userinput[2] == "scalar"){
                    command_fvector_scalar_product(list->Vlist);
                } else if(userinput[2] == "sum"){
                    list->Vlist = command_fvector_sum(list->Vlist);
                } else if(userinput[2] == "difference"){
                    list->Vlist = command_fvector_difference(list->Vlist);
                } else if(userinput[2] == "norm"){
                    command_fvector_norm(list->Vlist);
                } else if(userinput[2] == "angle"){
                    command_fvector_angle(list->Vlist);
                } else if(userinput[2] == "cross"){
                    list->Vlist = command_fvector_cross_product(list->Vlist);
                } else {
                    cout << "Invalid function call" << endl << endl;
                }
            } else if(userinput[1] == "system"){
                if(userinput[2] == "solution"){
                    list->Eqlist = command_system_solution(list->Eqlist);
                } else if(userinput[2] == "build"){
                    list = command_system_build(list);
                }
            } else if(userinput[1] == "set"){
                if(userinput[2] == "base"){
                    command_set_is_base(list->Slist);
                } else if(userinput[2] == "li"){
                    command_set_is_independent(list->Slist);
                } else if(userinput[2] == "gen"){
                    command_set_is_generator(list->Slist);
                } else if(userinput[2] == "gs"){
                    list->Slist = command_gram_schmidt(list->Slist);
                } else if(userinput[2] == "ort"){
                    list->Slist = command_orthogonal_complement(list->Slist);
                } else if(userinput[2] == "complete"){
                    list->Slist = command_base_completion(list->Slist);
                } else {
                    cout << "Invalid function call" << endl << endl;
                }
            } else if(userinput[1] == "function"){
                if(userinput[2] == "matrix"){
                    
                } else if(userinput[2] == "apply"){
                    list = command_apply_function(list);
                } else if(userinput[2] == "ker"){
                    list = command_function_ker(list);
                } else if(userinput[2] == "im"){
                    list = command_function_im(list);
                } else {
                    cout << "Invalid function call" << endl << endl;
                }
            } else {
                cout << "Invalid function call" << endl << endl;
            }
        } else if(userinput[0] == "print"){
            if(userinput[1] == "matrix"){
                command_print_matrix(list->Mlist);
            } else if(userinput[1] == "vector"){
                command_print_vector(list->Vlist);
            } else if(userinput[1] == "system"){
                command_print_system(list->Eqlist);
            } else if(userinput[1] == "set"){
                command_print_vectors_set(list->Slist);
            } else if(userinput[1] == "function"){
                command_print_function(list->Flist);
            } else {
                cout << "Invalid function call" << endl << endl;
            }
        } else if(userinput[0] == "remove"){
            if(userinput[1] == "matrix"){
                list->Mlist = remove_search(list->Mlist);
            } else if(userinput[1] == "vector"){
                list->Vlist = remove_vsearch(list->Vlist);
            } else if(userinput[1] == "system"){
                list->Eqlist = remove_esearch(list->Eqlist);
            } else if(userinput[1] == "set"){
                list->Slist = remove_ssearch(list->Slist);
            } else {
                cout << "Invalid function call" << endl << endl;
            }
        } else if(userinput[0] == "view"){
            if(userinput[1] == "matrices"){
                command_print_all_matrices(list->Mlist);
            } else if(userinput[1] == "vectors"){
                command_print_all_vectors(list->Vlist);
            } else if(userinput[1] == "systems"){
                command_print_all_systems(list->Eqlist);
            } else if(userinput[1] == "sets"){
                command_print_all_sets(list->Slist);
            } else {
                cout <<"Invalid function call" << endl << endl;
            }
        } else if(userinput[0] == "cls"){
            system("cls");
        } else {
            if(userinput[0] != "END")
                cout << "No such function" << endl << endl;
        }

    }while(userinput[0] != "END");
}