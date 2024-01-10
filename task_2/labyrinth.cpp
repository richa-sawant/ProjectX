#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<string>> ans;
int cmp = 0;

void dfs(int i, int j, int cnt, vector<vector<string>> &arr)
{
    int rows = arr.size();
    int cols = arr[0].size();
    arr[i][j] = to_string(cnt);
    for (int k = -1; k <= 1; k++)
    {
        for (int l = -1; l <= 1; l++)
        {
            if (k == 0 && l == 0)
                continue;
            int row = i + k, col = j + l;
            if (row >= 0 && row < rows && col >= 0 && col < cols && arr[row][col] == ".")
            {
                dfs(row, col, cnt + 1, arr);
            }
        }
    }
    if (cnt > cmp)
    {
        cmp = cnt;
        ans = arr;
    }
}

void replace_shortest(vector<vector<string>> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            if (arr[i][j] != "#")
            {
                arr[i][j] = ".";
            }
        }
    }
}

int main()
{
    ifstream inFile("labyrinth.txt");
    ofstream outFile("output.txt");

    vector<vector<string>> arr(5);
    for (auto &i : arr)
    {
        string temp;
        inFile >> temp;
        for (int j = 0; j < temp.size(); j++)
        {
            string cmp = "";
            cmp += temp[j];
            i.push_back(cmp);
        }
    }

    int rows = arr.size();
    int cols = arr[0].size();
    bool blocked_row_found = false;
    for (int i = 0; i < rows; i++)
    {
        bool all_hashes = true;
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] != "#")
            {
                all_hashes = false;
                break;
            }
        }
        if (all_hashes)
        {
            blocked_row_found = true;
            break;
        }
    }

    if (blocked_row_found)
    {
        outFile << -1 << endl;
        for (int i = 0; i < rows; i++)
        {
            for (auto j : arr[i])
            {
                outFile << j << " ";
            }
            outFile << endl;
        }
    }
    else
    {
        for (int i = 0; i < cols; i++)
        {
            if (arr[0][i] == ".")
            {
                replace_shortest(arr);
                dfs(0, i, 0, arr);
            }
        }

        if (cmp == 0)
        {
            outFile << -1 << endl;
        }
        else
        {
            outFile << cmp + 1 << endl;
            for (int i = 0; i < rows; i++)
            {
                for (auto j : ans[i])
                {
                    outFile << j << " ";
                }
                outFile << endl;
            }
        }
    }

    inFile.close();
    outFile.close();
    return 0;
}
