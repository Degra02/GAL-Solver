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
    printf("\x01b[1;38;5;3mFunction >>\x1b[0m "); fflush(stdin); getline(cin, input);
    stringstream check(input);

    while(getline(check, call, ' ')){
        (*userinput).push_back(call);
    }
    userinput->push_back("");
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
                list = command_new_system(list);
            } else if(userinput[1] == "set"){
                list->Slist = command_new_vectors_set(list->Slist);
            } else if(userinput[1] == "function"){
                list = command_new_function(list);
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
                } else if(userinput[2] == "cim"){ // stands for counter image
                    list = command_counter_image(list); // set of generators for all the counter images
                } else if(userinput[2] == "apply"){
                    list = command_apply_function(list);
                } else {
                    cout << "Invalid function call" << endl << endl;
                }
            } else if(userinput[1] == "system"){
                if(userinput[2] == "solution"){
                    list = command_system_solution(list);
                } else {
                    cout << "Invalid function call" << endl << endl;
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
                } else if(userinput[2] == "bc"){ // stands for base change
                    list = command_base_change(list);
                } else {
                    cout << "Invalid function call" << endl << endl;
                }
            } else if(userinput[1] == "function"){
                if(userinput[2] == "rm"){ // stands for representative matrix
                    list = command_representative_matrix_formula(list);
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
            } else if(userinput[1] == "function"){
                list->Flist = remove_fsearch(list->Flist);
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
            } else if(userinput[1] == "functions"){
                command_print_all_functions(list->Flist);
            } else {
                cout <<"Invalid function call" << endl << endl;
            }
        } else if(userinput[0] == "cls" || userinput[0] == "clear"){
            #if defined(_WIN32)
            system("cls");
            #endif
            #if defined(__linux__)
            system("clear");
            #endif 
            #if defined(__unix__)
            system("clear");
            #endif

        } else if(userinput[0] == "/help"){
            command_help();
        } else {
            if(userinput[0] != "END")
                cout << "No such function >> " << userinput[0] << endl << endl;
        }

    }while(userinput[0] != "END");
}

void command_help(){
    cout << "\x01b[38;5;241m";
    cout << "new\n   " << "matrix: create a new matrix\n   " << "vector: create a new vector\n   " << "set: create a new set of vectors\n   " << "function: create a new linear function\n";
    cout << endl << "calculate\n   " << "matrix:\n      ";
    cout << "product: product between two matrices\n      " << "sum: sum between two matrices\n      " << "difference: difference between two matrices\n      " << "transpose: calculate transpose matrix from a given one\n      ";
    cout << "scalar: scalar product of a matrix\n      " << "stairs: stairs form of a matrix\n      " << "rref: rref form of a matrix\n      " << "rank: rank of a matrix\n      " << "base: tells if the columns are a base\n      ";
    cout << "det: determinant of a matrix\n      " << "reverse: calculates the reverse of a given matrix\n\n   ";
    cout << "vector:\n      " << "scalar: scalar product of a vector\n      " << "sum: sum between two vectors\n      " << "difference between two vector\n      " << "norm: vector norm\n      " << "angle: angle between two vectors\n      ";
    cout << "cross: cross product between two vectors (R3)\n      " << "cim: counter image of a vector (involves linear function)\n      " << "apply: applies the chosen lineat function to a vector(new or existing)\n\n   ";
    cout << "system:\n      " << "solution: solutions of a linear system\n\n   ";
    cout << "set:\n      " << "base: tells if the set is a base\n      " << "li: tells if the set is linearly independent\n      " << "gen: tells if the set is a generator\n      " << "gs: calculates an orthonormal base from the set (Gram Schmidt)\n      "; 
    cout << "ort: calculates the orthogonal complement of the set\n      " << "complete: completes the set to a base of Rn\n\n   ";
    cout << "function:\n      " << "rm: finds the representative matrix of a function (from Base to same Base)\n      " << "apply: applies the function to a vector\n      " << "ker: calculates function kernel\n       " << "im: calculates function image\n      " << "bc: calculates base change matrix\n\n";
    cout << "remove:\n      " << "matrix: remove the chosen matrix\n      " << "vector: remove the chosen vector\n      " << "set: remove the chosen set\n      " << "system: remove the chosen system\n      " << "function: remove the chosen function\n\n";
    cout << "print:\n      " << "matrix: prints the chosen matrix\n      " << "vector: prints the chosen vector\n      " << "set: prints the chosen set\n      " << "system: prints the chosen system\n      " << "function: prints the chosen function \n\n";
    cout << "view:\n      " << "matrices: prints all saved matrices\n      " << "vectors: prints all saved vectors\n      " << "sets: prints all saved sets\n      " << "systems: prints all saved systems\n      " << "functions: prints all saved functions\n\n";
    cout << endl << "\x01b[0m";
}