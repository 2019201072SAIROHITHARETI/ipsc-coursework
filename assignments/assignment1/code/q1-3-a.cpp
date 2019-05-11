#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int flops = 0;

vector<int> readVector(int len)
{
    vector<int> res(len,0);
    for(int j = 0; j < len; j++)
    {
        cin >> res[j];
    }
    return res;
}

class COOMatrix
{
    public:
    int n;
    vector<int> row_indices;
    vector<int> col_indices;
    vector<int> values;
    COOMatrix(int len)
    {
        this->n = len;
        this->row_indices.resize(len);
        this->col_indices.resize(len);
        this->values.resize(len);
    }
    COOMatrix()
    {
    }
    void readInput()
    {
        cout << "Enter the row indices array:" << endl;
        this->row_indices = readVector(this->n);
        cout << "Enter the col indices array:" << endl;
        this->col_indices = readVector(this->n);
        cout << "Enter the value array:" << endl;
        this->values = readVector(this->n);
    }
};

COOMatrix matMul(COOMatrix& mat_x, COOMatrix& mat_y)
{
    unordered_map<int,unordered_map<int,int>> m;
    COOMatrix res;
    for(int i = 0; i < mat_x.n; i++)
    {
        for(int j = 0; j < mat_y.n; j++)
        {
            if(mat_x.col_indices[i] == mat_y.row_indices[j])
            {
                if(m.find(mat_x.row_indices[i]) == m.end())
                {
                    m[mat_x.row_indices[i]] = unordered_map<int,int>();
                }
                if(m[mat_x.row_indices[i]].find(mat_y.col_indices[j]) == m[mat_x.row_indices[i]].end())
                {
                    m[mat_x.row_indices[i]][mat_y.col_indices[j]] = 0;
                }
                flops += 2;
                m[mat_x.row_indices[i]][mat_y.col_indices[j]] += mat_x.values[i]*mat_y.values[j];
            }
        }
    }
    for(auto i : m)
    {
        for(auto j : i.second)
        {
            if(j.second != 0)
            {
                res.row_indices.push_back(i.first);
                res.col_indices.push_back(j.first);
                res.values.push_back(j.second);
            }
        }
    }
    res.n = res.col_indices.size();
    return res;
}

int main()
{
    int len1, len2;
    cout << "Enter the length:" << endl;
    cin >> len1;
    COOMatrix m1(len1);
    m1.readInput();

    cout << "Enter the length:" << endl;
    cin >> len1;
    COOMatrix m2(len1);
    m2.readInput();

    auto res = matMul(m1, m2);
    cout << "Result of matrix multiplication" << endl;
    cout << "row indices" << endl;
    for(int i = 0; i < res.n; i++)
    {
        cout << res.row_indices[i] << " ";
    }
    cout << endl;
    cout << "col indices" << endl;
    for(int i = 0; i < res.n; i++)
    {
        cout << res.col_indices[i] << " ";
    }
    cout << endl;
    cout << "Values" << endl;
    for(int i = 0; i < res.n; i++)
    {
        cout << res.values[i] << " ";
    }
    cout << endl;
    cout << "Flops: " << flops << endl;
    //Storage complexity is O(m*n) for the result
    return 0;
}