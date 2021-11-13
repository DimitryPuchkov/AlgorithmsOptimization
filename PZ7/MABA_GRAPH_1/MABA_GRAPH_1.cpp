#include <vector>
#include <iostream>
#include <ctime>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

void writeGraph(vector<vector<int>> graph, string fileName)
{
   ofstream out;
   out.open(fileName);

   for (int i = 0; i < graph.size() - 1; i++)
   {
      sort(graph[i].begin(), graph[i].end());

      out << i + 1 << ": ";

      for (int j = 0; j < graph[i].size(); j++)
      {
         out << graph[i][j] << " ";
      }

      out << endl;

   }
}

vector<vector<int>> getVertexList(string fileName, int *m)
{
   ifstream fin;

   fin.open(fileName);

   int n = 0;
   fin >> *m;
   fin >> n;

   vector <vector<int>> a(n, vector<int>(2));

   for (int i = 0; i < n; i++)
   {

      int v1 = 0, v2 = 0;
      fin >> v1;
      fin >> v2;

      a[i][0] = v1;
      a[i][1] = v2;
   }

   return a;
}

vector<vector<int>> getAdditionalList(vector<vector<int>> vertexList, int m)
{
   vector <vector<int>> additionalList(m + 1);

   for (int i = 0; i < vertexList.size(); i++)
   {
      additionalList[vertexList[i][0] - 1].push_back(vertexList[i][1]);
      additionalList[vertexList[i][1] - 1].push_back(vertexList[i][0]);
   }

   return additionalList;
}

vector <vector<int>> getVertexListForFullGraph(string fileName, int *m)
{
   ifstream fin;

   fin.open(fileName);

   fin >> *m;

   vector <vector<int>> a(*m, vector<int>(2));

   for (int i = 0; i < *m; i++)
   {

      int v = 0;
      fin >> v;
      if (i > 0)
         a[i - 1][1] = v;

      a[i][0] = v;

   }

   return a;
}
void Task1()
{

   int m = 0;
   vector<vector<int>> vertexList = getVertexList("input.txt", &m);

   vector<vector<int>> graph = getAdditionalList(vertexList, m);
   writeGraph(graph, "out.txt");

}


void Task2()
{
   ifstream fin;

   fin.open("n.txt");

   int count = 0;

   fin >> count; // files number

   fin.close();

   int m = 0;

   int max_val = -99999;

   /*vector<vector<int>> a = getVertexListForFullGraph("1.txt", &m);

   for (int i = 0; i < a.size(); i++)
   {
      cout << a[i][0] << " " << a[i][1] << endl;
   }*/

   //vector<int> arr1;
   //vector<int> arr2;
   vector<vector<int>> arr(count); // array of arrays of vertexes

   int len = 0;

   for (int i = 0; i < count; i++) // scanning graphs
   {
      fin.open(to_string(i + 1) + ".txt");
      fin >> len;
      for (int j = 0; j < len; j++)
      {
         int elem = 0;
         fin >> elem;

         if (elem > max_val)
            max_val = elem;

         arr[i].push_back(elem);

      }
      fin.close();
   }


   
   /*int arr2_len = 0;

   ifstream fin3;

   fin3.open("2.txt");

   fin3 >> arr2_len;

   for (int i = 0; i < arr2_len; i++)
   {
      int elem = 0;
      fin3 >> elem;

      if (elem > max_val)
         max_val = elem;

      arr2.push_back(elem);

   }*/



   cout << max_val;

   vector<vector<vector<int>>> V(count, vector<vector<int>>(max_val)); // create additional list of gull graphs

      for (int i = 0; i < count; i++)
         for (int j = 0; j < arr[i].size(); j++)
         {
            for (int k = 0; k < arr[i].size(); k++)
               if(k != j)
                  V[i][arr[i][j] - 1].push_back(k);
         }
   return;
  
}

double Sum(int n, double* a)
{
    double s = 0;

    for (int i = 0; i < n; i++)
    {
        s += a[i];
    }

    return s;
}
//-----------------------------------------------------------------------------
double SumVectorVector(vector< vector<double> >& a)
{
    double s = 0;

    int sz1 = a.size();
    for (int i = 0; i < sz1; i++)
    {
        int sz2 = a[i].size();
        for (int j = 0; j < sz2; j++)
        {
            s += a[i][j];
        }
    }

    return s;
}

//-----------------------------------------------------------------------------
void TestSumMatrix(int n, int m)
{
    vector< vector<double> > a;
    a.resize(n, vector<double>(m, 1));

    cout << SumVectorVector(a) << '\t' << Sum(n*m, &a[0][0]) << endl;
}


void Task3()
{
    int n, m;

    cout << "n = ";
    cin >> n;
    cout << "\nm = ";
    cin >> m;
    cout << "\n";

    TestSumMatrix(n, m);

}


int main()
{

   double c =  0.0 / -1.0;



}

