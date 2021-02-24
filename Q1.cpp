#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;


bool validate_sequence(vector<string> procedure_names,vector<int> step_numbers){
    // instantiate hash table with the key being the procedure name string, and the value being the sequence number
    unordered_map<string, int> step_map; 

    // This for loop loops over the procedure vector and checks if the hashed value is strictly smaller, 
    // if it is then we continue
    // otherwise, we return false out of the function as a failure
    // if the function makes it through the for loop we know all the sequences are ok and we return true
    // marking a success
    
    for (size_t i = 0; i < procedure_names.size(); ++i){
        // first we have to check if the string is already in the hash table
        if(step_map.find(procedure_names[i]) == step_map.end()){ 

            // if the string is not it will enter in this if statement and we will have to add it to the hash table
            // in this case we dont need to check the previous value because there isnt one
            step_map[procedure_names[i]] = step_numbers[i];
        }
        else{
            // if it enters this else statement, this means that the procedure name is not already stored in the 
            // hash table and this is not the first time we have seen it, that means 
            // there should already be an integer value marking the step number stored
            // so we check if the step number corresponding to the string is less than or equal to the one stored in the
            // hash table
            
            if (step_numbers[i] <= step_map[procedure_names[i]]){
                // if it is less than or equal to, we fail the parameters given by the spec and have to return this
                // run as false aka failure
                return false;
            }
            else{
                // in this case, the new value we have is actually strictly greater than the number that was stored.
                // so we add the new number into the hash table and move on through the loop
                step_map[procedure_names[i]] = step_numbers[i];
            }
            
            
        }
    }
    return true;
}

// testing what happens when sequence num goes down
void Test1(){
    cout << "Test 1 running: " ;
    vector<string> procedure_names{"OD",  "OD",  "ProdGen", "Prop"};
    vector<int> step_numbers{2, 1, 12, 111};
    cout << "returned value is: " << validate_sequence(procedure_names, step_numbers) << "   should be 0" << endl;

}

// sequence number stays the same for one step (neither up or down)
void Test2(){
    cout << "Test 2 running: " ;
    vector<string> procedure_names{"Prop",  "Prop",  "Prop",  "Prop",  "Prop",  "Prop"};
    vector<int> step_numbers{1, 3, 5, 7, 7, 9};
    cout << "returned value is: " << validate_sequence(procedure_names, step_numbers) << "   should be 0" << endl;

}
// only one sequence number
void Test3(){
    cout << "Test 3 running: " ;
    vector<string> procedure_names{"OD"};
    vector<int> step_numbers{10001010};
    cout << "returned value is: " << validate_sequence(procedure_names, step_numbers) << "   should be 1" << endl;

}

// everything goes right
void Test4(){
    cout << "Test 4 running: " ;
    vector<string> procedure_names{"orbit_determination", "product_gen", "propagation", "orbit_determination", "product_gen", "propagation"};
    vector<int> step_numbers{1, 11, 12, 3, 13, 112};
    cout << "returned value is: " << validate_sequence(procedure_names, step_numbers) << "   should be 1" << endl;
}

// once again goes down"
void Test5(){
    cout << "Test 5 running: " ;
    vector<string> procedure_names{"orbit_determination", "orbit_determination", "product_gen", "propagation"} ;
    vector<int> step_numbers{3, 2, 13, 112};
    cout << "returned value is: " << validate_sequence(procedure_names, step_numbers) << "   should be 0" << endl;
}
int main(){
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

}