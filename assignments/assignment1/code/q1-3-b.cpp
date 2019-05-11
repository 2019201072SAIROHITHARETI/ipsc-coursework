#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int flops = 0;

vector<int> readIndex(int len)
{
    vector<int> res(len,0);
    for(int j = 0; j < len; j++)
    {
        cin >> res[j];
    }
    return res;
}

vector<double> readVal(int len)
{
    vector<double> res(len,0);
    for(int j = 0; j < len; j++)
    {
        cin >> res[j];
    }
    return res;
}

class CSRMatrix
{
    public:
    int n;
    vector<int> row_lens;
    vector<int> col_indices;
    vector<double> values;
    CSRMatrix(int len)
    {
        this->n = len;
        this->row_lens.resize(len);
        this->col_indices.resize(len);
        this->values.resize(len);
    }
    CSRMatrix()
    {
    }
};

CSRMatrix matMul(CSRMatrix& mat_x, CSRMatrix& mat_y)
{
    map<int,map<int,int>> m;
    CSRMatrix res;
    for(int i = 0; i < mat_x.n; i++)
    {
        for(int k = mat_x.row_lens[i]; k < mat_x.row_lens[i+1]; k++)
        {
            int r = i+1;
            int c = mat_x.col_indices[k-1];
            for(int j = mat_y.row_lens[c-1]; j < mat_y.row_lens[c]; j++)
            {
                {
                    if(m.find(r) == m.end())
                    {
                        m[r] = map<int,int>();
                    }
                    if(m[r].find(mat_y.col_indices[j-1]) == m[r].end())
                    {
                        m[r][mat_y.col_indices[j-1]] = 0;
                    }
                    flops += 2;
                    m[r][mat_y.col_indices[j-1]] += mat_x.values[k-1]*mat_y.values[j-1];
                }
            }
        }
    }
    res.row_lens.resize(mat_x.n+1, 0);
    for(auto i : m)
    {
        if(res.row_lens[i.first-1] == 0)
        {
            res.row_lens[i.first-1] = res.values.size()+1;
        }
        for(auto j : i.second)
        {
            if(j.second != 0)
            {
                res.col_indices.push_back(j.first);
                res.values.push_back(j.second);
            }
        }
    }
    res.n = res.row_lens.size()-1;
    res.row_lens[res.n] = res.row_lens[res.n-1] + 1;
    return res;
}

CSRMatrix readCSR()
{
    int len1;
    CSRMatrix m1;
    cout << "Enter the row pointer array length:" << endl;
    cin >> len1;
    cout << "Enter the row pointer array:" << endl;
    auto row_pointers1 = readIndex(len1);
    cout << "Enter the value/cols array length:" << endl;
    cin >> len1;
    cout << "Enter the col indices array:" << endl;
    auto cols1 = readIndex(len1);
    cout << "Enter the value array:" << endl;
    auto val1 = readVal(len1);
    cout <<"blah blah" << endl;
    cout << row_pointers1.size() << " " << cols1.size() << " " << val1.size() << endl;
    m1.row_lens = row_pointers1;
    m1.col_indices = cols1;
    m1.values = val1;  
    m1.n = m1.row_lens.size()-1;
    return m1;
}

int main()
{
    CSRMatrix m1 = readCSR();
    CSRMatrix m2 = readCSR();

    auto res = matMul(m1, m2);
    cout << "Result of matrix multiplication" << endl;
    cout << "row indices" << endl;
    for(int i = 0; i < res.row_lens.size(); i++)
    {
        cout << res.row_lens[i] << " ";
    }
    cout << endl;
    cout << "col indices" << endl;
    for(int i = 0; i < res.col_indices.size(); i++)
    {
        cout << res.col_indices[i] << " ";
    }
    cout << endl;
    cout << "Values" << endl;
    for(int i = 0; i < res.values.size(); i++)
    {
        cout << res.values[i] << " ";
    }
    cout << endl;
    cout << "Flops: " << flops << endl;
    //Storage complexity is O(m*n) for the result
    return 0;
}