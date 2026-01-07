#pragma once
#include<iostream>
#include <iomanip>
#include<vector>
#include<string>
#include "block.hpp"
#include<fstream>
#include<time.h>
#include"utils.hpp"
#include"mining.hpp"
using namespace std;
/*
BLOCK:
        long long index;
        string date_time;
        string last_hash;
        string hash_;
        string data;
        
->in txt:
    1 index date_time last_hash hash data last
*/
void create_block(string ndata){
    //first reads the hole file to find the last
    ifstream chain("chain.txt");
    string index,date_time,last_hash = string(64,'0'),hash_,data,last;
    string last_idx="-1";
    string last_block_hash = string(64,'0');
    vector<string>lines;

    //Implementation of earn by mining funcion
    cout <<"Write your address: ";
    string miner_add;
    cin >> miner_add;
    int amount = 20; //needs to be variable

    string old_miner_add; // Variable to read old miner addresses from file
    int old_amount;
    while(chain >> index >> date_time >> last_hash >> hash_ >> old_miner_add >> old_amount >> data >> last){
        string line = index+" "+date_time+" "+last_hash+" "+hash_+" "+old_miner_add+" "+to_string(old_amount)+" "+data+" ";
        if(last == "1"){ 
            line += "0";
            last_block_hash = hash_;
            last_idx = index;
        } else {
            line += "0";
        }

        lines.push_back(line);
    }
    chain.close();

    // Create and mine the new block
    long long new_index = stoi(last_idx) + 1;
    date_time = to_string(time(0));
    Block temp_block(new_index, date_time, last_block_hash, "", ndata,0);
    pair<long long, string> mining_result = mine_block(temp_block);
    
    string new_hash = mining_result.second;

    string new_block = to_string(new_index)+" "+date_time+" "+last_block_hash+" "+new_hash+" "+miner_add+" "+to_string(amount)+" "+ndata+" "+"1";
    lines.push_back(new_block);

    //Writes the lines in the file
    ofstream chain1("chain.txt");
    for(string line : lines){
        chain1 << line<<'\n';
    }chain1.close();
}
