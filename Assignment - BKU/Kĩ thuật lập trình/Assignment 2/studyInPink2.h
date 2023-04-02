/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 10.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

string g(string a, string b) {
    string key = "0000000000";
    int carry = 0;
    for (int i = 0; i < 10; i++) {
        key[i] += (a[i] - '0') + (b[i] - '0') + carry;
        if (key[i] > '9') {
            key[i] -= 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
    }
    return key;
}
bool checkCP(long long n) {
    for (int i = 1; i < n / 2; i++) {
        if (i * i == n) {
            return 1;
        }
    }
    return 0;
}
bool isPrime(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else {
        for (int i = 2; i < n; i++) {
            if (n % i == 0)
                return 0;
        }
    }
    return 1;
}
bool isFibo(int n) {
    if (checkCP(5 * n * n + 4))
        return 1;
    else if (checkCP(5 * n * n - 4))
        return 1;
    else
        return 0;
}
string notebook1(string ntb1) {
    // Complete this function to gain point
    ifstream file;
    file.open(ntb1);
    string s;
    string key = "0000000000";
    int a[50];
    int n;
    int i = 0, count = 0;
    getline(file, s);
    while (!file.eof()) {
        file >> a[i];
        i++;
    }
    int num = (s[11] - '0') * 100 + (s[12] - '0') * 10 + (s[13] - '0');
    if ((s[11] >= '0' && s[11] <= '9') && (s[12] >= '0' && s[12] <= '9') && (s[13] >= '0' && s[13] <= '9'))
    {
        if (s[11] == '0' && s[12] == '0' && s[13] == '0')
        {
            return "0000000000";
        }

        else
        {
            for (int u = 0; u < 10; u++) 
            {
                for (int j = 0; j < num; j++) 
                {
                    if( u == a[j])
                    {
                        count++;
                    }
                }
                n = count % 10;
                key[u] = '0' + n;
                count = 0;
            }
            return key;
        }
    }
    file.close();
    return "0000000000";
}

string notebook2(string ntb2) {
    // Complete this function to gain point
    ifstream file;
    file.open(ntb2);
    string line1;
    getline(file, line1);
    int size_1 = line1.length();
    int count = 0;
    long long cntP = 0;
    if (size_1 != 5)
        return "1111111111";
    else
    {
        for (int i = 0; i < size_1; i++) 
        {
            if (line1[i] < '0' || line1[i] > '9')
                return "1111111111";
        }
        int num = stoi(line1);
        if (num < 5 || num > 100)
            return "1111111111";
        else {
            string a[20];
            for (int i = 0; i < num; i++) 
            {
                getline(file, a[i]);
            }
            for (int i = 0; i < num; i++) 
            {
                for (int j = 0; j < a[i].length(); j++) 
                {
                    if (a[i][j] == 'P' || a[i][j] == 'p') {
                        if (a[i][j + 1] == 'i' && a[i][j + 2] == 'n' && a[i][j + 3] == 'k') {
                            count++;
                        }
                    }
                }
                cntP += count;
                count = 0;
            }
            if (cntP < 10000)
                cntP = cntP * cntP;
            while (cntP < 1000000000) 
            {
                cntP = cntP * 10 + 9;
            }
            return to_string(cntP);
        }
    }
    file.close();
    return "000000000";
}

string notebook3(string ntb3) {
    // Complete this function to gain point
    ifstream file;
    file.open(ntb3);
    int arr[20][20];
    int temp, max, count;
    string key = "0000000000";
    for (int i = 0; i < 10; i++) 
    {
        for (int j = 0; j < 10; j++) {
            file >> temp;
            if (temp < 0)
                temp = -temp;
            arr[i][j] = temp;
            file.ignore(1);
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            while(isPrime(arr[i][j]) == 0) {
                arr[i][j]++;
            }
        }
        for (int j = 0; j < i; j++) {
            while(isFibo(arr[i][j]) == 0)
                arr[i][j]++;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (arr[i][7] > arr[i][8])
            swap(arr[i][7], arr[i][8]);
        if (arr[i][8] > arr[i][9])
            swap(arr[i][8], arr[i][9]);
        if (arr[i][7] > arr[i][8])
            swap(arr[i][7], arr[i][8]);
    }
    for (int i = 0; i < 10; i++) {
        max = 0;
        count = 0;
        for (int j = 0; j < 10; j++) {
            if (arr[i][j] >= max) {
                max = arr[i][j];
                count = j;
            }
        }
        key[i] = count + '0';
    }
    file.close();
    return key;
    return "000000000";
}

string generateListPasswords(string pwd1, string pwd2, string pwd3) {
    // Complete this function to gain point
    string key;
    string p12 = g(pwd1, pwd2);
    string p13 = g(pwd1, pwd3);
    string p23 = g(pwd2, pwd3);
    key = pwd1 + ";" + pwd2 + ";" + pwd3 + ";" + p12 + ";" + p13 + ";" + p23 + ";" + g(p12, pwd3) + ";" + g(pwd1, p23) + ";" + g(p12, p13);
    return key;
    return "000000000";
}

bool chaseTaxi(
    int arr[100][100],
    string points,
    string moves,
    string& outTimes,
    string& outCatchUps
) {
    // Complete this function to gain point
    int x = 0, y = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            arr[i][j] = -9;
        }
    }
    arr[0][0] = 0;
    bool chase = false;
    int time_taxi[50], m = 1;
    int a_x[1005], u = 0, a_y[1005], o = 0;
    time_taxi[0] = 0;
    for (int i = 0; i < moves.length(); i++)
    {
        if (moves[i] == 'U') {
            if (x != 0) {
                x -= 1;
                arr[x][y] = arr[x + 1][y] + 9;
                time_taxi[m] = arr[x][y];
                m++;
            }
        }
        else if (moves[i] == 'D') {
            if (x != 99) {
                x += 1;
                arr[x][y] = arr[x - 1][y] + 9;
                time_taxi[m] = arr[x][y];
                m++;
            }
        }
        else if (moves[i] == 'L') {
            if (y != 0) {
                y -= 1;
                arr[x][y] = arr[x][y + 1] + 9;
                time_taxi[m] = arr[x][y];
                m++;
            }
        }
        else {
            if (y != 99) {
                y += 1;
                arr[x][y] = arr[x][y - 1] + 9;
                time_taxi[m] = arr[x][y];
                m++;
            }
        }
    }
    for (int i = 0; i < points.length(); i++) {
        if (points[i] == ',') {
            if (points[i - 2] == '(') {
                a_x[u] = points[i - 1] - '0';
                u++;
            }
            else {
                a_x[u] = (points[i - 2] - '0') * 10 + (points[i - 1] - '0');
                u++;
            }
            if (points[i + 2] == ')') {
                a_y[o] = points[i + 1] - '0';
                o++;
            }
            else {
                a_y[o] = (points[i + 1] - '0') * 10 + (points[i + 2] - '0');
                o++;
            }
        }
    }
    int time_SW = 0;
    outCatchUps = {};
    for (int i = 0; i < u; i++)
    {
        if (i != 0) time_SW += 14 * (abs(a_x[i] - a_x[i - 1]) + (abs(a_y[i] - a_y[i - 1])));
        else time_SW += 14 * (abs(a_x[i]) + (abs(a_y[i])));
        if (time_SW <= arr[a_x[i]][a_y[i]]) {
            chase = true;
            outCatchUps += ";Y";
            outTimes += ";" + to_string(time_SW);
            for (int j = i; j < u - 1; j++) {
                outTimes += ";-";
                outCatchUps += ";-";
            }
            break;

        } outTimes += ";" + to_string(time_SW);
        outCatchUps += ";N";
    }
    outCatchUps.erase(outCatchUps.begin());
    outTimes.erase(outTimes.begin());
    if (chase)
        return true;
    else
        return false;
}

string enterLaptop(string tag, string message) {
    // Complete this function to gain point
    ifstream file;
    file.open(tag);
    string line1, line2;
    getline(file, line1);
    getline(file, line2);
    int i = line1.find(' ');
    line1=line1.substr(i+1);
    int j = line2.find(' ');
    int k = line2.rfind(' ');
    line2 = line2.substr(j, (k - j - 3));
    int n3 = stoi(line2);
    string name;
    for (int u = 0; u < n3; u++) {
        name += message;
    }
    string key;
    key = line1 + ';' + name;
    return key;
    return "";
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
