#ifndef ENTROPY_HPP
#define ENTROPY_HPP

#include<iostream>
#include<random>
#include<vector>
#include<string>
#include<openssl/ec.h>
#include<openssl/bn.h>
#include <openssl/evp.h>

using namespace std;
const unsigned char N[32] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
    0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B,
    0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41
};

bool is_valid_entropy(const vector<unsigned char>& entropy){
    //verify if the size is valid
    bool at_least_one_non_zero = false;
    bool less_than_N = true;
    if(entropy.size()!=32){
        return false;
    }
    //verify if at least one byte is non-zero
    for(auto byte: entropy){
        if(byte!=0){
            at_least_one_non_zero = true;
            break;
        }
    }
    //varify if entropy < N
    for(size_t i=0;i<32;i++){
        if(entropy[i]>N[i]){
            less_than_N = false;
            break;
        }
    }
    if(at_least_one_non_zero && less_than_N){
        return true;
    }
    
    return false;
}
pair<vector<unsigned char>,vector<unsigned char>>generate_entropy(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);
    size_t size_key = 32;
    vector<unsigned char>entropy(size_key),public_key(size_key+1);
    do{
        for(size_t i = 0;i<size_key;i++){
            entropy[i] = (unsigned char)dis(gen);
        }
    }while(!is_valid_entropy(entropy));

    EC_GROUP* group = EC_GROUP_new_by_curve_name(NID_secp256k1); 
    const EC_POINT* G = EC_GROUP_get0_generator(group);
    BIGNUM* priv_bn = BN_bin2bn(entropy.data(), 32, NULL);
    EC_POINT* pub_point = EC_POINT_new(group);
    EC_POINT_mul(group, pub_point, priv_bn, NULL, NULL, NULL);
    EC_POINT_point2oct(group, pub_point, POINT_CONVERSION_COMPRESSED,public_key.data(), 33, NULL);
    EC_POINT_free(pub_point);
    BN_free(priv_bn);
    EC_GROUP_free(group);

    return {entropy, public_key};
}

#endif // ENTROPY_HPP

