#pragma once
#ifndef MINING_HPP
#define MINING_HPP

#include<iostream>
#include "block.hpp"
#include<string>
#include <openssl/sha.h>
#include <cstring>
#include <iomanip>
#include <sstream>
#include"utils.hpp"
using namespace std;



pair<long long,string> mine_block(const Block& block,int difficulty=4){
    long long nonce = 0;
    string prefix(difficulty, '0');
    string hash;
    string calculated_hash;
    while(true){
        // Hash calculation 
        hash = to_string(block.getIndex()) + block.getDateTime() + block.getLastHash() + block.getData() + to_string(nonce);
        calculated_hash = sha256(hash);
        // Simple hash simulation: take the first 'difficulty' characters
        string simulated_hash = calculated_hash.substr(0, difficulty);
        if(simulated_hash == prefix){
            break;
        }
        nonce++;
    }
    return pair<long long,string>(nonce, calculated_hash);
}

#endif // MINING_HPP