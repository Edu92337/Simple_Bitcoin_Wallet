#pragma once
#include"entropy.hpp"
#include<iostream>
#include "block.hpp"
#include<cstring>
#include<string>
#include <openssl/sha.h>
#include<openssl/ripemd.h>
#include <cstring>
#include <iomanip>
#include <sstream>
#include<fstream>
using namespace std;

string sha256(const string& input){
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << hex << setw(2) << setfill('0') << static_cast<unsigned int>(hash[i]);
    }

    return ss.str();
}
string ripemd160(const string& input){
    unsigned char hash[RIPEMD160_DIGEST_LENGTH];

    RIPEMD160(reinterpret_cast<const unsigned char*>(input.c_str()),input.length(),hash);    
    stringstream ss;
    for(int i = 0;i<RIPEMD160_DIGEST_LENGTH;i++){
        ss << hex << setw(2) << setfill('0') << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}
string public_key_2_address(vector<unsigned char>public_key){
    string pk="";
    for(char c : public_key)pk+=c;
    return ripemd160(sha256(pk));
}
void create_private_public_key(){
    auto [entropy,public_key] = generate_entropy();
                cout<<"Generated Entropy(Private Key): ";
                for(auto byte: entropy){
                    cout<<hex<<setw(2)<<setfill('0')<<(int)byte;
                }
                cout<<endl;
                cout<<"\nPublic Key: ";
                for(auto byte: public_key){
                    cout<<hex<<setw(2)<<setfill('0')<<(int)byte;
                }cout <<endl;
                cout<<dec<<endl;
                cout<<"Address:"<< public_key_2_address(public_key)<<endl;
}

int verify_transaction(string sender_add,string receiver_add,long long value){
    ifstream chain("chain.txt");
    int quantity  = 0;
    string index,date_time,last_hash = string(64,'0'),hash_,data,last,miner_add,amount;

    while(chain >> index >> date_time >> last_hash >> hash_ >> miner_add >> amount >> data >> last){
        if(miner_add == sender_add)quantity+=stoi(amount);
    }
    return quantity-value;
    
}

int create_transaction(string sender_add,string receiver_add,long long amount){
    //Creates the Data of a transaction
    int change = verify_transaction(sender_add,receiver_add,amount);
    if(change>=0){
        return change;
    }else return 0;


}



