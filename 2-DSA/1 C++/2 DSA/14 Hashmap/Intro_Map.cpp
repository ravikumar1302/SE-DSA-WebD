#include<iostream>
#include<map>
#include<unordered_map>
using namespace std;

int main() {

    // Creation
    unordered_map<string, int> m;

    // Insertion methods

    // 1st
    pair<string, int> p = make_pair("This", 2);
    m.insert(p);

    // 2nd
    pair<string, int> p2 ("is", 3);
    m.insert(p2);

    // 3rd
    m["Coding"] = 4;
    m["Coding"] = 1;    // Updates value of "Coding"

    // Searching
    cout<<m["Coding"]<<endl;
    cout<<m.at("is")<<endl;
    // cout<<m.at("DSA")<<endl; // It will print error, as we haven't entered such key
    cout<<m["DSA"]<<endl;       // But this prints 0, Because this make a entry corresponding to this new key "DSA" and assign it 0 value
    cout<<m.at("DSA")<<endl;    // This will output 0, as in above line entry is created

    // Size
    cout<<m.size()<<endl;

    // To check presence
    cout<<m.count("Algorithms")<<endl;

    // Erase
    m.erase("is");
    cout<<m.size()<<endl;

    // Access
    // Method -1
    for(auto i : m)
        cout<<i.first<<" "<<i.second<<endl;
    
    // Method -2 : Iterator
    cout<<endl<<"Using iterator"<<endl;
    unordered_map<string, int> :: iterator it = m.begin();
    while(it != m.end())
    {
        cout<<it->first<<" "<<it->second<<endl;
        it++;
    }
        

    return 0;
}