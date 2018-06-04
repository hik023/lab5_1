#include "iostream"
#include <math.h>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

const int L = 7;

string MyConvertToBin(int number)
{
    int num = number;
    string snum;

    for (int i = 0; i < L - 1; i++)
    {
        if (num / 2 != 0)
        {
            if (num % 2 == 0)
                snum = "0" + snum;
            else snum = "1" + snum;
            num = num / 2;
            if (num == 1) snum = "1" + snum;
        }
        else snum = "0" + snum;
    }
    return snum;
}

int MyConvertToDec(string snumber)
{
    string snum = snumber;
    int num = 0;

    for (int i = 0; i < snum.length(); i++)
    {
        num += ((int)snum[i] - 48) * pow((double)2, (double)(snum.length() - 1 - i));
    }
    return num;
}

vector<string> SearchNeigh(string s)
{
    char p[L];
    string temp;
    vector<string> a;
    a.reserve(L);
    for (int i = 0; i < s.length(); i++)
    {
        p[i] = s[i];
    }
    for (int i = 0; i < s.length(); i++)
    {
        temp = "";
        if (p[i] == '1')
        {
            p[i] = '0';
            for (int j = 0; j < s.length(); j++)
                temp += p[j];
            a.push_back(temp);
            p[i] = '1';
        }
        else
        {
            p[i] = '1';
            for (int j = 0; j < s.length(); j++)
                temp += p[j];
            a.push_back(temp);
            p[i] = '0';
        }
    }
    return a;
}

double FitNeigh(string neighbour)
{
    return (sin((double)(MyConvertToDec(neighbour)+1))*sin((double)(MyConvertToDec(neighbour)+1)) + log((double)(MyConvertToDec(neighbour)+1)));
}

string MK()
{
    return MyConvertToBin(rand() % 128);
}

string depth(vector<string> neigh)
{
    return neigh[rand()%7];
}

string width(double* fit, vector<string> neighbour)
{
    double CurrMax = 0;
    int p = 0;
    for (int i = 0; i < L; i++)
        if (CurrMax < fit[i])
        {
            CurrMax = fit[i];
            p = i;
        }
    return neighbour[p];
}

int main()
{
    srand(time(0));
    int i = 1, n = 10, k;
    int z = rand() % 128;
    double max;
    string S = MyConvertToBin(z);
    string maxS;
    vector<string> neighbour;
    double fit[L];
    double x;
    max = FitNeigh(S);
    maxS = S;
    string status = "status: changed";
    cout << "----------------" << endl << "Step: " << 1 << endl;
    cout << "maxS = " << maxS << endl << "max = " << max << endl;
    cout << "S = " << S << endl << "fit = " << FitNeigh(S) << endl;
    cout << status << endl;
    while (i < n)
    {

        status = "status: not changed";
        neighbour = SearchNeigh(maxS);
        for (int j = 0; j < L; j++)
        {
            fit[j] = FitNeigh(neighbour[j]);
        }
        k = rand() % 3;
        switch (k)
        {
            case 0:
            {
                S = MK();
                x = FitNeigh(S);
                cout << "Monte carlo choosed" << '\n';
                break;
            }
            case 1:
            {
                S = depth(neighbour);
                x = FitNeigh(S);
                cout << "In depth choosed" << '\n';
                break;
            }
            case 2:
            {
                S = width(fit, neighbour);
                x = FitNeigh(S);
                cout << "In width choosed" << '\n';
                break;
            }
        }

        i++;
        cout << "----------------" << endl << "Step: " << i << endl;
        cout << "maxS = " << maxS << endl << "max = " << max << endl;
        cout << "S = " << S << endl << "fit = " << x << endl;
        if (x > max)
        {
            status = "status: changed";
            max = x;
            maxS = S;
        }
        cout << status << endl;
        switch (k)
        {
            case 0:
            {
                cout << "Monte carlo choosed" << '\n';
                break;
            }
            case 1:
            {
                cout << "In depth choosed" << '\n';
                break;
            }
            case 2:
            {
                cout << "In width choosed" << '\n';
                break;
            }
        }
    }
    cout << endl << "maxS = " << maxS << endl << "max = " << max << endl;
    return 0;
}