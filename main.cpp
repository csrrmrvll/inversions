#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;
using Vector = vector<int>;
using Pair = pair<Vector,unsigned int>;

void output(Vector v)
{
    for (int n : v)
    {
        cout << n << " ";
    }
    cout << endl;
}

Pair mergeAndCountSplitInv(Pair p1,Pair p2)
{
    Vector  v1 = p1.first,
            v2 = p2.first;
    int i = 0,
        j = 0,
        size1 = v1.size(),
        size2 = v2.size(),
        total = size1 + size2;
    Pair out(Vector(total),p1.second + p2.second);
    Vector & v = out.first;
    unsigned int & count = out.second;
    int k = 0;
    while ((i < size1) && (j < size2))
    {
        if (v1[i] < v2[j])
        {
            v[k++] = v1[i++];
        }
        else
        {
            v[k++] = v2[j++];
            count += size1 - i;
        }
    }
    while (i < size1)
    {
        v[k++] = v1[i++];
    }
    while (j < size2)
    {
        v[k++] = v2[j++];
    }
    return out;
}

Vector copy(Vector v,int first,int last)
{
    Vector out;
    for (int i = first; i < last; ++i)
    {
        out.emplace_back(v[i]);
    }
    return out;
}

Pair mergeSortAndCountInv(Vector v)
{
    int size = v.size();
    if (size < 2)
    {
        return Pair(v,0);
    }
    int mid = size / 2;
    Vector  v1 = copy(v,0,mid),
            v2 = copy(v,mid,size);
    Pair    firstInv = mergeSortAndCountInv(v1),
            secondInv = mergeSortAndCountInv(v2);
    return mergeAndCountSplitInv(firstInv,secondInv);
}

int main()
{
    string line;
    ifstream is;
    is.open("E:\\dev\\inversions\\bin\\Release\\IntegerArray.txt",std::ios::in);
    Vector v;
    if (is.is_open())
    {
        while (getline(is,line))
        {
            int n;
            std::istringstream is(line);
            is >> n;
            v.emplace_back(n);
        }
        is.close();
    }
    else
    {
        cout << "file is not open!!" << endl;
        return 1;
    }
    Pair result = mergeSortAndCountInv(v);
    int size = v.size();
    Vector sorted(size);
    iota(sorted.begin(),sorted.end(),1);
    if (result.first != sorted)
    {
        cout << "wrong sorting algorithm" << endl;
        return 1;
    }
    cout << "number of inversions: " << result.second << endl;
    return 0;
}
