#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include<iostream>
#include<random>
#include<vector>
#include<string>
using namespace std;

class Block{
    private:
        long long index;
        string date_time;
        string last_hash;
        string hash_;
        string data;
        long long Nonce;
        int difficulty;
    public:
        Block(long long idx, string dt, string last_h, string hsh, string dat, long long nonce, int diff=4)
            : index(idx), date_time(dt), last_hash(last_h), hash_(hsh), data(dat), Nonce(nonce), difficulty(diff) {}

        long long getIndex() const { return index; }
        string getDateTime() const { return date_time; }
        string getLastHash() const { return last_hash; }
        string getHash() const { return hash_; }
        string getData() const { return data; }
        long long getNonce() const { return Nonce; }
        int getDifficulty() const { return difficulty; }

        void setIndex(long long idx) { index = idx; }
        void setDateTime(const string& dt) { date_time = dt; }
        void setLastHash(const string& last_h) { last_hash = last_h; }
        void setHash(const string& hsh) { hash_ = hsh; }
        void setData(const string& dat) { data = dat; }
        void setNonce(long long nonce) { Nonce = nonce; }
        void setDifficulty(int diff) { difficulty = diff; }
};

#endif // BLOCK_HPP