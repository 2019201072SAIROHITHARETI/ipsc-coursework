#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int flops = 0;

class BandedMatrix
{
    public:
    int p, q, n;
    vector<vector<double>> mat;
    BandedMatrix(int m, int n, int p, int q)
    {
        this->mat.resize(m, vector<double>(n, 0));
        this->n = n;
        this->p = p;
        this->q = q;
    }
    void loadBandedMatrix(vector<vector<double>> mat)
    {
        this->mat = mat;
    }
    double getActualij(int i , int j)
    {
        if(i-j+this->q < n)
            return this->mat[i-j+this->q][j];
        else
        {
            return 0;
        }
        
    }
};

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

vector<vector<double>> bandedMatMul(BandedMatrix& mat_x, BandedMatrix& mat_y)
{
    int n = mat_x.n;
    vector<vector<double>> res(n, vector<double>(n, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int k_start = max(max(0, i-mat_x.p), max(0, j-mat_y.q));
            int k_stop = min(min(i+mat_x.q + 1, n),min(j+mat_y.p + 1, n));
            // cout << "k_start: " << k_start << " k_Stop: " << k_stop << endl;
            for(int k = k_start; k < k_stop; k++)
            {
                flops += 2;
                // cout << "a: " << mat_x.getActualij(i, k) << " b: " << mat_y.getActualij(k, j) << endl;
                res[i][j] += mat_x.getActualij(i, k)*mat_y.getActualij(k, j);
            }
        }
    }
    return res;
}

int main()
{
    int m1, n1, p1, q1, m2, n2, p2, q2;
    cout << "Enter the banded matrix dimensions m, n and p, q:" << endl;
    cin >> m1 >> n1 >> p1 >> q1;
    BandedMatrix x(m1, n1, p1, q1);
    cout << "Enter the banded matrix values:" << endl;
    auto mat_x = readMatrix(m1, n1);
    x.loadBandedMatrix(mat_x);

    cout << "Enter the banded matrix dimensions m, n and p, q:" << endl;
    cin >> m2 >> n2 >> p2 >> q2;
    BandedMatrix y(m2, n2, p2, q2);
    cout << "Enter the banded matrix values:" << endl;
    auto mat_y = readMatrix(m2, n2);
    y.loadBandedMatrix(mat_y);
    // assert(mat_x[0].size() == mat_y.size());
    auto res = bandedMatMul(x, y);
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
    //Storage complexity is O(n*n) for the result
    return 0;
}