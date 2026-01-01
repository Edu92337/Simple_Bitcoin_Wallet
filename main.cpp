#include<iostream>
#include<iomanip>
#include<random>
#include<vector>
#include<string>
#include "entropy.hpp"
#include "block.hpp"
#include "mining.hpp"
#include<time.h>
using namespace std;
//g++ -Wall -Wextra -g3 main.cpp -o output/main -lssl -lcrypto && ./output/main

int main(){
    auto [entropy,publick_key] = generate_entropy();
    Block block(1,to_string(time(0)),"0000000000000000","", "Some transaction data",0,5);
    auto [nonce,hash] = mine_block(block, block.getDifficulty());
    cout<<"Generated Entropy(Private Key): ";
    for(auto byte: entropy){
        cout<<hex<<setw(2)<<setfill('0')<<(int)byte;
    }
    cout<<endl;
    cout<<"\nPublic Key: ";
    for(auto byte: publick_key){
        cout<<hex<<setw(2)<<setfill('0')<<(int)byte;
    }
    cout<<dec<<endl;
    cout<<"\nBlock Hash: "<<hash<<endl;
    for(auto byte: hash){
        cout<<hex<<setw(2)<<setfill('0')<<(int)byte;
    }
    cout<<dec<<endl;
    cout<<"\nMined Nonce: "<<nonce<<endl;
    
    
    return 0;
}