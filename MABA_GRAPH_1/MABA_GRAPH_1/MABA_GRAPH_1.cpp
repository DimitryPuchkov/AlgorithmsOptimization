#include <vector>
#include <iostream>
#include <ctime>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;


void adjacencyMatrix()
{
   ifstream fin;

   int m = 0, n = 0;

   fin.open("C:/Users/lemon/source/repos/MABA_GRAPH_1/Debug/input.txt");

   fin >> m;
   fin >> n;

   vector <vector<bool>> a(m, vector<bool>(m));

   for (int i = 0; i < n; i++)
   {
      int u = 0, v = 0;

      fin >> u;

      fin >> v;

      u--;
      v--;

      //a[u][v] = a[v][u] = true;   // если граф неориентированный

      a[u][v] = true;

   }

   for (int i = 0; i < m; i++)
   {
      for (int j = 0; j < m; j++)
      {
         cout << a[i][j] << " ";
      }

      cout << endl;

   }


}

void Task2()
{
   ifstream fin;

   fin.open("C:/Users/lemon/source/repos/MABA_GRAPH_1/Debug/input.txt");

   int m=0, n = 0;
   fin >> m;
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

   vector <vector<int>> graph(m+1);


   for (int i = 0; i < a.size(); i++)
   {
      graph[a[i][0]].push_back(a[i][1]);

   }

   for (int i = 1; i < graph.size(); i++)
   {
      sort(graph[i].begin(), graph[i].end());

      cout << i;
      for (int j = 0; j < graph[i].size(); j++)
      {
        cout <<" -> " << graph[i][j];
      }

      cout << endl;
   }
   
}



int main()
{

   Task2();

}

