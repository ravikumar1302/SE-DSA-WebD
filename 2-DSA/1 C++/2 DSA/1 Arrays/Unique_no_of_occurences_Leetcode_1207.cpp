/*
Unique_no_of_occurences_Leetcode_1207

Given an array of integers arr, return true if the number of occurrences of each value in the array is unique, or false otherwise.
*/

bool uniqueOccurrences(vector<int> &arr)
{
    map<int, int> m1; // map for occurences of elements
    map<int, int> m2; // map for uniqueness
    vector<int>::iterator itr;
    for (itr = arr.begin(); itr != arr.end(); itr++)
    {
        auto map_itr = m1.find(*itr);
        if (map_itr == m1.end())
            m1.insert(pair<int, int>(*itr, 1)); // add pair if not present
        else
            map_itr->second = map_itr->second + 1; // increminting value as key already there
    }
    for (auto map_it = m1.begin(); map_it != m1.end(); map_it++)
    {
        auto it = m2.find(map_it->second);
        if (it == m2.end()) // finding that all values are unique or not
            m2.insert(pair<int, int>(map_it->second, 1));
        else
            return false; // returns false if m2 have duplicate value of any key
    }
    return true;
}

// Approach 2
//  Time complexity: O(nlogn)

bool uniqueOccurrences(vector<int> &arr)
{
    sort(arr.begin(), arr.end());
    vector<int> temp;

    for (int i = 0; i < arr.size(); i++)
    {
        int cnt = 1;

        //  to count occurence of current element
        while (i + 1 < arr.size() && arr[i] == arr[i + 1])
        {
            cnt++;
            i++;
        }

        temp.push_back(cnt);
    }
    sort(temp.begin(), temp.end());

    for (int i = 1; i < temp.size(); i++)
    {
        if (temp[i] == temp[i - 1])
            return false;
    }

    return true;
}

// Approach 3
// Time complexity: O(n)

bool uniqueOccurrences(vector<int> &arr)
{
    unordered_map<int, int> freq;
    for (auto val : arr)
        freq[val]++;

    unordered_set<int> temp;
    for (auto val : freq)
        temp.insert(val.second);

    return freq.size() == temp.size();
}