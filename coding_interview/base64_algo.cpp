/**
    Simple implementation of base64 encoding-decoding algorithm.
    Interview question for SDE @Microsoft Japan, 2013
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cassert>

using namespace std;
#define INVALID -1

class Base64{
    static char encode(unsigned char uc);
    static unsigned char decode(char c);
    static bool is_base_64(char c);
public:
    static string encode(const vector<unsigned char> &vby);
    static vector<unsigned char> decode(const string &str);
};

// translate a 6-bit pattern into a base64 character
inline char Base64::encode(unsigned char uc){
    if(uc < 26) return 'A' + uc;
    if(uc < 52) return 'a' + (uc-26);
    if(uc < 62) return '0' + (uc-52);
    if(uc == 62) return '+';
    if(uc == 63) return '/';
    return INVALID;
}

// decode a base64 character into a 6-bit pattern
inline unsigned char Base64::decode(char c){
    if('A' <= c && c <= 'Z') return c-'A';
    if('a' <= c && c <= 'z') return c-'a'+26;
    if('0' <= c && c <= '9') return c-'0'+52;
    if(c == '+') return 62;
    if(c == '/') return 63;
    return INVALID;
}

// check if a character is a base64 character
inline bool Base64::is_base_64(char c){
    if('A' <= c && c <= 'Z') return true;
    if('a' <= c && c <= 'z') return true;
    if('0' <= c && c <= '9') return true;
    if(c == '+' || c == '/' || c == '=') return true;
    return false;
}

/**
    Encode a vector of (8-bit) bytes (vby) into a string of Base64 character
    Note: 3 (8-bit) bytes = 24 bits = 4 (6-bit) base64 characters
    Encode strategy: convert each 3-byte block into 4 base64 chars
    If one byte left, 2 more 0 bytes are padded, and '000000' -> '=' in base64
    If two bytes left, 1 more 0 byte is padded, and '000000' -> '=' in base64
    Hence, the encoded string will end with "==" if one byte left, and "=" if
    two bytes left
*/

inline string Base64::encode(const vector<unsigned char> & vby){
    string ret;
    if((int)vby.size() == 0) return ret;

    for(int i = 0; i < (int)vby.size(); i+=3){
        unsigned char by1 = 0, by2 = 0, by3 = 0;
        by1 = vby[i];
        if(i+1 < vby.size()) by2 = vby[i+1];
        if(i+2 < vby.size()) by3 = vby[i+2];

        unsigned char by4 = 0, by5 = 0, by6 = 0, by7 = 0;
        by4 = by1 >> 2; // first 6 bits
        by5 = ((by1 & 0x3) << 4) | (by2 >> 4); // last 2 bits + next 4 bits
        by6 = ((by2 & 0xf) << 2) | (by3 >> 6); // last 4 bits + next 2 bits
        by7 = (by3 & 0x3f); // last 6 bits

        ret += encode(by4);
        ret += encode(by5);
        if(i+1 < vby.size()) ret += encode(by6);
        else ret += "=";
        if(i+2 < vby.size()) ret += encode(by7);
        else ret += "=";

        // To improve human-readbility, for a string of base64 characters
        // after 76 characters, we include carriage return character
        if(i % (76/4*3) == 0) ret += "\r\n";
    }
    return ret;
}

/**
    Decode a string of base64 chars into 8-bit bytes stream (vector)
    Basic strategy: Convert 4 base64 char block --> 3 8-bit byte block
*/
inline vector<unsigned char> Base64::decode(const string & str){
    string a_str;
    // sanity check, removing invalid chars
    for(int i = 0; i < (int)str.length(); i++){
        if(is_base_64(str[i])) a_str += str[i];
    }
    int len = (int) a_str.length();
    vector<unsigned char> ret;
    if(len == 0) return ret;

    for(int i = 0; i < len; i+=4){
        char c1 = 'A', c2 = 'A', c3 = 'A', c4 = 'A';
        c1 = a_str[i];
        if(i+1 < len) c2 = a_str[i+1];
        if(i+2 < len) c3 = a_str[i+2];
        if(i+3 < len) c4 = a_str[i+3];

        unsigned char by1 = 0, by2 = 0, by3 = 0, by4 = 0;
        by1 = decode(c1);
        by2 = decode(c2);
        by3 = decode(c3);
        by4 = decode(c4);

        ret.push_back( (by1 << 2) | (by2 >> 4) );
        if(c3 != '='){
            ret.push_back( ((by2 & 0xf) << 4) | (by3 >> 2) );
        }
        if(c4 != '='){
            ret.push_back( ((by3 & 0x3) << 6) | by4 );
        }
    }
    return ret;
}

int main(){
    Base64 test;
    string in = "my name is duong!";
    vector<unsigned char> vby;
    for(int i = 0; i < in.length(); i++) vby.push_back((unsigned char)in[i]);
    string encoded = test.encode(vby);
    cout << "Base64 encoded string: " << encoded << endl;
    vector<unsigned char> decoded = test.decode(encoded);
    string out = "";
    for(int i = 0; i < (int)decoded.size(); i++) out += decoded[i];
    cout << "Base64 decoded string: " << out << endl;
    assert(in == out);
    return 0;
}
