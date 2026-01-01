#ifndef MINING_HPP
#define MINING_HPP

#include<iostream>
#include "block.hpp"
#include<string>
#include <openssl/sha.h>
#include <cstring>
#include <iomanip>
#include <sstream>
using namespace std;

// Function to compute SHA-256 hash
string sha256(const string& input){
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << hex << setw(2) << setfill('0') << static_cast<unsigned int>(hash[i]);
    }

    return ss.str();
}

pair<long long,string> mine_block(const Block& block,int difficulty){
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