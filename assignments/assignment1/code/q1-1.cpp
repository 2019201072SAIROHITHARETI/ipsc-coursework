#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int flops = 0;

vector<vector<double>> readMatrix(int rows, int cols)
{
    vector<vector<double>> mat_x(rows, vector<double>(cols,0));
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cin >> mat_x[i][j];
        }
    }
    return mat_x;
}

vector<vector<double>> matMul(vector<vector<double>>& mat_x, vector<vector<double>>& mat_y)
{
    int m = mat_x.size();
    int n = mat_x[0].size();
    int k = mat_y[0].size();
    vector<vector<double>> res(m, vector<double>(k, 0));
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < k; j++)
        {
            for(int k = 0; k < n; k++)
            {
                // cout << "a: " << mat_x[i][k] << " b: " << mat_y[k][j] << endl;
                flops += 2;
                res[i][j] += mat_x[i][k]*mat_y[k][j];
            }
        }
    }
    return res;
}

int main()
{
    int m1, n1, m2, n2;
    cout << "Enter the matrix dimensions m, n:" << endl;
    cin >> m1 >> n1;
    cout << "Enter the matrix values:" << endl;
    auto mat_x = readMatrix(m1, n1);
    cout << "Enter the matrix dimensions m, n:" << endl;
    cin >> m2 >> n2;
    cout << "Enter the matrix values:" << endl;
    auto mat_y = readMatrix(m2, n2);
    assert(mat_x[0].size() == mat_y.size());
    auto res = matMul(mat_x, mat_y);
    cout << "Result of matrix multiplication" << endl;
    for(int i = 0; i < m1; i++)
    {
        for(int j = 0; j < n2; j++)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Flops: " << flops << endl;
    //Storage complexity is O(m*n) for the result
    return 0;
}