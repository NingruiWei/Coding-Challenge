#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <math.h>
#include <stdio.h>

using namespace std;
string descramble(vector<int> seq, vector<char> fragment_data, int n){
    // first we calculate the maximum number of fragments each 
    int n_limit = ceil(n / 2);
    unordered_map<int, unordered_map<char, int>> fragment_map;
    unordered_map<int, char> answer_map;
    string answer = "";
    for(size_t i = 0; i < seq.size(); ++i){
        if (fragment_map.find(seq[i]) != fragment_map.end()){
            // if we have already stored sequence number
            if (fragment_map[seq[i]].find(fragment_data[i]) != fragment_map[seq[i]].end()){
                // if this sequence number has seen the shard before
                // we increment the number stored 
                ++fragment_map[seq[i]][fragment_data[i]]; 
            }
            else{
                // if we haven't seen this specific char before then we add it to the map, and give it the starting value of 1
                // as we just saw it for the first time
                fragment_map[seq[i]][fragment_data[i]] = 1;

            }

        }

        else{
            // if we haven't already stored the sequence number
            // we create a new key for that sequence
            fragment_map[seq[i]] = unordered_map<char, int>();

            // since this is the first time we see the sequence this is also the first time this sequence sees this shard so we can directly initialize it
            fragment_map[seq[i]][fragment_data[i]] = 1;

        }
        
         if (fragment_map[seq[i]][fragment_data[i]] > n_limit){
                    // if we have reached over half of the number of messages sent
                    // then we can confirm this is the fragment for this sequence number
                    //and place it in the answer map
                    answer_map[seq[i]] = fragment_data[i];
        }
    }

    if (answer_map.size() == fragment_map.size()){
        if(answer_map[answer_map.size() - 1] != '#'){
            return "";
        }
        // if the two maps are the same size, that must mean that we "found" all the values and are safe to recreate the string
        // which we do by looping through the answer hash table
        for(size_t i = 0; i < answer_map.size() - 1; ++i){
            if (answer_map[i] == '#'){
                return "";
            }
            answer += answer_map[i];
        }
        // have to add the ending #
        answer += '#';
        
    }
     return answer;
}
// testing case where we don't have > 50% of shards found for first or second sequence
void Test1(){
    cout << "running Test 1: ";
    vector<int> seq{1, 1, 0, 0, 0, 2, 2, 2};
    vector<char>data{'+',  '+',  'A',  'A',  'B',  '#',  '#',  '#'};
    int n = 4;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is Empty" << endl;
}

// testing case where everything goes right
void Test2(){
    cout << "running Test 2: ";
    vector<int> seq{1, 1, 0, 0, 0, 2, 2, 2};
    vector<char>data{'-', '-', 'Z', 'Z', 'X', '#', '#', '#'};
    int n = 3;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is Z-#" << endl;
}

// testing case where we have the # character before the end, so output should be empty
void Test3(){
    cout << "running Test 3: ";
    vector<int> seq{1, 1, 0, 0, 0, 2, 2, 2};
    vector<char>data{'#', '#', 'Z', 'Z', 'X', '#', '#', '#'};
    int n = 3;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is Empty" << endl;
}

// testing case where last character isnt #, so output should be empty
void Test4(){
    cout << "running Test 4: ";
    vector<int> seq{1, 1, 0, 0, 0, 2, 2, 2};
    vector<char>data{'-', '-', 'Z', 'Z', 'X', '-', '-', '-'};
    int n = 3;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is Empty" << endl;
}
// testing edge case where there's only one shard 
void Test5(){
    cout << "running Test 5: ";
    vector<int> seq{0};
    vector<char>data{'#'};
    int n = 1;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is #" << endl;
}

void Test6(){
    cout << "running Test 6: ";
    vector<int> seq{0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
    vector<char>data{'#',  '?',  '?',  '?',  '?',  '?',  '?',  '?',  '#',  '?',  '#',  '#'};
    int n = 3;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is ???#" << endl;
}


// testing if we're missing a sequence number
void Test7(){
    cout << "running Test 7: ";
    vector<int> seq{0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 3, 3};
    vector<char>data{'#',  '?',  '?',  '?',  '?',  '?',  '?',  '?',  '#',  '?',  '#',  '#'};
    int n = 3;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is Empty" << endl;
}

// theres only one sequence number but it doesn't resolve to #
void Test8(){
    cout << "running Test 8: ";
    vector<int> seq{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<char>data{'#',  '?',  '?',  '?',  '?',  '?',  '?',  '?',  '#',  '?',  '#',  '#'};
    int n = 12;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is Empty" << endl;
}

// theres only one sequence number, a ton of shards, but it does resolve to #
void Test9(){
    cout << "running Test 8: ";
    vector<int> seq{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<char>data{'#',  '#',  '#',  '#',  '#',  '?',  '?',  '?',  '#',  '?',  '#',  '#'};
    int n = 12;
    cout << "returned value is:  '" << descramble(seq, data, n) << "'  expected output is #" << endl;
}

int main(){
   Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();

}

