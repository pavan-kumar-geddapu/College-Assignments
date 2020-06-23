#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

int Nb=4, Nr=10, Nk=4;

vector<vector<string> > sBox{   
    {"63","7c","77","7b","f2","6b","6f","c5","30","01","67","2b","fe","d7","ab","76"},
    {"ca","82","c9","7d","fa","59","47","f0","ad","d4","a2","af","9c","a4","72","c0"},
    {"b7","fd","93","26","36","3f","f7","cc","34","a5","e5","f1","71","d8","31","15"},
    {"04","c7","23","c3","18","96","05","9a","07","12","80","e2","eb","27","b2","75"},
    {"09","83","2c","1a","1b","6e","5a","a0","52","3b","d6","b3","29","e3","2f","84"},
    {"53","d1","00","ed","20","fc","b1","5b","6a","cb","be","39","4a","4c","58","cf"},
    {"d0","ef","aa","fb","43","4d","33","85","45","f9","02","7f","50","3c","9f","a8"},
    {"51","a3","40","8f","92","9d","38","f5","bc","b6","da","21","10","ff","f3","d2"},
    {"cd","0c","13","ec","5f","97","44","17","c4","a7","7e","3d","64","5d","19","73"},
    {"60","81","4f","dc","22","2a","90","88","46","ee","b8","14","de","5e","0b","db"},
    {"e0","32","3a","0a","49","06","24","5c","c2","d3","ac","62","91","95","e4","79"},
    {"e7","c8","37","6d","8d","d5","4e","a9","6c","56","f4","ea","65","7a","ae","08"},
    {"ba","78","25","2e","1c","a6","b4","c6","e8","dd","74","1f","4b","bd","8b","8a"},
    {"70","3e","b5","66","48","03","f6","0e","61","35","57","b9","86","c1","1d","9e"},
    {"e1","f8","98","11","69","d9","8e","94","9b","1e","87","e9","ce","55","28","df"},
    {"8c","a1","89","0d","bf","e6","42","68","41","99","2d","0f","b0","54","bb","16"}   };

vector<vector<string> > invSBox{   
    {"52","09","6a","d5","30","36","a5","38","bf","40","a3","9e","81","f3","d7","fb"},
    {"7c","e3","39","82","9b","2f","ff","87","34","8e","43","44","c4","de","e9","cb"},
    {"54","7b","94","32","a6","c2","23","3d","ee","4c","95","0b","42","fa","c3","4e"},
    {"08","2e","a1","66","28","d9","24","b2","76","5b","a2","49","6d","8b","d1","25"},
    {"72","f8","f6","64","86","68","98","16","d4","a4","5c","cc","5d","65","b6","92"},
    {"6c","70","48","50","fd","ed","b9","da","5e","15","46","57","a7","8d","9d","84"},
    {"90","d8","ab","00","8c","bc","d3","0a","f7","e4","58","05","b8","b3","45","06"},
    {"d0","2c","1e","8f","ca","3f","0f","02","c1","af","bd","03","01","13","8a","6b"},
    {"3a","91","11","41","4f","67","dc","ea","97","f2","cf","ce","f0","b4","e6","73"},
    {"96","ac","74","22","e7","ad","35","85","e2","f9","37","e8","1c","75","df","6e"},
    {"47","f1","1a","71","1d","29","c5","89","6f","b7","62","0e","aa","18","be","1b"},
    {"fc","56","3e","4b","c6","d2","79","20","9a","db","c0","fe","78","cd","5a","f4"},
    {"1f","dd","a8","33","88","07","c7","31","b1","12","10","59","27","80","ec","5f"},
    {"60","51","7f","a9","19","b5","4a","0d","2d","e5","7a","9f","93","c9","9c","ef"},
    {"a0","e0","3b","4d","ae","2a","f5","b0","c8","eb","bb","3c","83","53","99","61"},
    {"17","2b","04","7e","ba","77","d6","26","e1","69","14","63","55","21","0c","7d"}   };

map<string,string> hexToBinary = {  {"0","0000"},{"1","0001"},{"2","0010"},{"3","0011"},
                                    {"4","0100"},{"5","0101"},{"6","0110"},{"7","0111"},
                                    {"8","1000"},{"9","1001"},{"a","1010"},{"b","1011"},
                                    {"c","1100"},{"d","1101"},{"e","1110"},{"f","1111"}    };

map<string,string> binaryToHex = {  {"0000","0"},{"0001","1"},{"0010","2"},{"0011","3"},
                                    {"0100","4"},{"0101","5"},{"0110","6"},{"0111","7"},
                                    {"1000","8"},{"1001","9"},{"1010","a"},{"1011","b"},
                                    {"1100","c"},{"1101","d"},{"1110","e"},{"1111","f"}    };

map<string,int> hexToDec = {    {"0",0},{"1",1},{"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},
                                {"8",8},{"9",9},{"a",10},{"b",11},{"c",12},{"d",13},{"e",14},{"f",15}    };


void printVector(vector<string> v){
    for(int i=0;i<v.size();i++){
        cout<<i<<" "<<v[i]<<endl;
    }
}
void printVector(vector<int> v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void printVector(vector<vector<string> > v){
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
}

string xorBinary(string a, string b){
    a = hexToBinary[a];
    b = hexToBinary[b];
    string resultBits = "";
    for(int i=0;i<a.length();i++){
        resultBits += to_string(( (a[i]-'0')+(b[i]-'0') ) % 2);
    }
    return binaryToHex[resultBits];
}

string xorHex(string a, string b){
    string resultWord = "";
    for(int i=0;i<a.length();i++){
        resultWord += xorBinary(a.substr(i,1), b.substr(i,1));
    }
    return resultWord;
}

string rotWord(string tempWord){
    return tempWord.substr(2,6) + tempWord.substr(0,2);
}

string subWord(string tempWord){
    string resultWord = "";
    for(int i=0;i<4;i++){
        resultWord += sBox[hexToDec[tempWord.substr(i*2,1)]][hexToDec[tempWord.substr(i*2+1,1)]];
    }
    return resultWord;
}

vector<string> keyExpansion(string cipherKey){
    vector<string> Rcon{"01000000","02000000","04000000","08000000","10000000","20000000","40000000","80000000","1b000000","36000000"};
    vector<string> words(Nb*(Nr+1));

    int index=0;
    while(index < Nk){
        words[index] = cipherKey.substr(index*8,8);
        index++;        
    }
    while(index < Nb*(Nr+1)){
        string tempWord = words[index-1];
        if(index % Nk == 0){
                tempWord = xorHex( subWord( rotWord(tempWord)), Rcon[index/Nk - 1]);
        }
        words[index] = xorHex(words[index-Nk], tempWord);
        index++;
    }

    return words;
}

vector<int> xorBits(vector<int> a,vector<int> b){
    for(int i=0;i<8;i++){
        a[i] = (a[i]+b[i])%2;
    }
    return a;
}
vector<int> leftShift(vector<int> row, int noOfTimes){
    for(int i=0;i<noOfTimes;i++){
        row.erase(row.begin());
        row.push_back(0);
    }
    return row;
}
string bitsMultiplication(string x, string y){
    vector<int> a, b;
    vector<int> modulus{0,0,0,1,1,0,1,1};
    for(int i=0;i<x.length();i++){
        string bitA = hexToBinary[x.substr(i,1)];
        string bitB = hexToBinary[y.substr(i,1)];
        for(int j=0;j<bitA.length();j++){
            a.push_back(bitA[j]-'0');
            b.push_back(bitB[j]-'0');
        }
    }
    vector<vector<int> > shiftReg;
    shiftReg.push_back(b);
    for(int i=1;i<8;i++){
        shiftReg.push_back(leftShift(shiftReg[i-1],1));        
        if(shiftReg[i-1][0]==1){
            shiftReg[i]=xorBits(shiftReg[i],modulus);
        }        
    }
    vector<int> result{0,0,0,0,0,0,0,0};
    for(int i=0;i<8;i++){
        if(a[i]==1){
            for(int j=0;j<8;j++){
                result[j] = (result[j]+shiftReg[8-i-1][j])%2;
            }
        }
    }
    string resultString = "";
    for(int i=0;i<2;i++){
        string temp = "";
        for(int j=0;j<4;j++){
            temp += to_string(result[i*4+j]);
        }
        resultString += binaryToHex[temp];
    }
    return resultString;
}

void leftShift(vector<string>& row, int noOfTimes){
    for(int i=0;i<noOfTimes;i++){
        string temp = row[0];
        row.erase(row.begin());
        row.push_back(temp);
    }
}

void subBytes(vector<vector<string> >& state){
    for(int i=0;i<Nb;i++){
        for(int j=0;j<Nb;j++){
            state[i][j]=sBox[hexToDec[state[i][j].substr(0,1)]][hexToDec[state[i][j].substr(1,1)]];
        }
    }
}

void shiftRows(vector<vector<string> >& state){
    for(int i=1;i<Nb;i++){
        leftShift(state[i], i);
    }
}

void mixColumns(vector<vector<string> >& state){
    vector<vector<string> > tempState = state;
    for(int j=0;j<Nb;j++){
        tempState[0][j] = xorHex( xorHex(bitsMultiplication("02",state[0][j]),bitsMultiplication("03",state[1][j])) , xorHex(state[2][j],state[3][j]) );
        tempState[1][j] = xorHex( xorHex(bitsMultiplication("02",state[1][j]),bitsMultiplication("03",state[2][j])) , xorHex(state[0][j],state[3][j]) );
        tempState[2][j] = xorHex( xorHex(bitsMultiplication("02",state[2][j]),bitsMultiplication("03",state[3][j])) , xorHex(state[0][j],state[1][j]) );
        tempState[3][j] = xorHex( xorHex(bitsMultiplication("03",state[0][j]),bitsMultiplication("02",state[3][j])) , xorHex(state[1][j],state[2][j]) );
    }
    state = tempState;
}

void addRoundKey(vector<vector<string> >& state, vector<string> words, int round){
    for(int i=0;i<Nb;i++){
        for(int j=0;j<Nb;j++){
            state[i][j] = xorHex(state[i][j], words[round*Nb+j].substr(i*2,2));
        }
    }
}

string encryption(string input, vector<string> words){
    vector<vector<string> > state;
    for(int i=0;i<Nb;i++){
        vector<string> stateColumn;
        for(int j=0;j<Nb;j++){
            stateColumn.push_back(input.substr(i*2+j*8,2));
        }
        state.push_back(stateColumn);
    }

    addRoundKey(state, words, 0);
    int round=1;
    while(round < Nr){
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, words, round);
        round++;
    }
    subBytes(state);
    shiftRows(state);
    addRoundKey(state,words,round);

    string output = "";
    for(int j=0;j<Nb;j++){
        for(int i=0;i<Nb;i++){
            output += state[i][j];
        }
    }
    
    return output;
}

void invSubBytes(vector<vector<string> >& state){
    for(int i=0;i<Nb;i++){
        for(int j=0;j<Nb;j++){
            state[i][j]=invSBox[hexToDec[state[i][j].substr(0,1)]][hexToDec[state[i][j].substr(1,1)]];
        }
    }
}

void invShiftRows(vector<vector<string> >& state){
    for(int i=1;i<Nb;i++){
        leftShift(state[i], Nb-i);
    }
}

void invMixColumns(vector<vector<string> >& state){
    vector<vector<string> > tempState = state;
    for(int j=0;j<Nb;j++){
        tempState[0][j] = xorHex( xorHex(bitsMultiplication("0e",state[0][j]),bitsMultiplication("0b",state[1][j])) , xorHex(bitsMultiplication("0d",state[2][j]),bitsMultiplication("09",state[3][j])) );
        tempState[1][j] = xorHex( xorHex(bitsMultiplication("09",state[0][j]),bitsMultiplication("0e",state[1][j])) , xorHex(bitsMultiplication("0b",state[2][j]),bitsMultiplication("0d",state[3][j])) );
        tempState[2][j] = xorHex( xorHex(bitsMultiplication("0d",state[0][j]),bitsMultiplication("09",state[1][j])) , xorHex(bitsMultiplication("0e",state[2][j]),bitsMultiplication("0b",state[3][j])) );
        tempState[3][j] = xorHex( xorHex(bitsMultiplication("0b",state[0][j]),bitsMultiplication("0d",state[1][j])) , xorHex(bitsMultiplication("09",state[2][j]),bitsMultiplication("0e",state[3][j])) );
    }
    state = tempState;
}

string decryption(string input, vector<string> words){
    vector<vector<string> > state;
    for(int i=0;i<Nb;i++){
        vector<string> stateColumn;
        for(int j=0;j<Nb;j++){
            stateColumn.push_back(input.substr(i*2+j*8,2));
        }
        state.push_back(stateColumn);
    }

    addRoundKey(state, words, Nr);
    int round = Nr-1;
    while(round > 0){
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, words, round);
        invMixColumns(state);
        round--;
    }
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state,words,round);

    string output = "";
    for(int j=0;j<Nb;j++){
        for(int i=0;i<Nb;i++){
            output += state[i][j];
        }
    }
    
    return output;
}

int main(){

    //string cipherKey = "000102030405060708090a0b0c0d0e0f";
    //string plainText = "00112233445566778899aabbccddeeff";
    string plainText, cipherKey;
    cin>>plainText;
    cin>>cipherKey;
    vector<string> words = keyExpansion(cipherKey);
    string cipherText ="";
    for(int i=0;i<plainText.length()/32;i++){
        cipherText += encryption(plainText.substr(i*32,32), words);
    }    
    string plainFromCipherText = "";
    for(int i=0;i<cipherText.length()/32;i++){
        plainFromCipherText += decryption(cipherText.substr(i*32,32), words);
    }
    cout<<cipherText<<endl;
    cout<<plainFromCipherText;

return 0;
}
