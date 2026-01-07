#include<iostream>
#include<iomanip>
#include<random>
#include<vector>
#include<string>
#include "entropy.hpp"
#include "block.hpp"
#include"Blockchain.hpp"
#include "mining.hpp"
#include<time.h>
#include"utils.hpp"
#include<fstream>

using namespace std;
//g++ -Wall -Wextra -g3 main.cpp -o output/main -lssl -lcrypto && ./output/main


int main(){
    int option = -1;
    do{
        cout << "(1) Create a new public/private key pair"<<endl;
        cout << "(2) Create a new block"<<endl;
        cout << "(3) verify the last block added"<<endl;
        cin >> option;
        switch(option){
            case 0:break;
            case 1:{
                create_private_public_key();
                break;
            }
            case 2:{
                cout<<"Write your address\n";
                //Funcion to process the transaction
                string sender_add;
                cin.ignore();
                getline(cin,sender_add);

                
                create_block(sender_add);
               
                break;
            }
            case 3:{
                ifstream chain("chain.txt");
                string index,date_time,last_hash = string(64,'0'),hash_,data,last,miner_add,amount;
                while(chain >> index >> date_time >> last_hash >> hash_ >> miner_add >> amount >> data >> last){
                    if(last == "1"){
                        cout << "Block Index: "<<index<<endl;
                        cout << "date_time: "<<date_time<<endl;
                        cout << "Last Hash: "<<last_hash<<endl;
                        cout << "Hash: "<<hash_<<endl;
                        cout << "Data: "<<data<<endl;
                    }
                }
                break;
            }
        }
    }while(option);
    
    return 0;
}
