#include <vector>
#include <iostream>
#include <ctime>
#include <stack>
#include <queue>
#include <fstream>

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

void Task1()
{

   int m = 0;
   vector<vector<int>> vertexList = getVertexList("input.txt", &m);

   vector<vector<int>> graph = getAdditionalList(vertexList, m);
   writeGraph(graph, "out.txt");

}


void Task2()
{
   int m = 0, m2 = 0;
   vector<vector<int>> vertexList1 = getVertexList("1.txt", &m);

   vector<vector<int>> vertexList2 = getVertexList("2.txt", &m2);

   vector<vector<int>> associatedList;

   for (int i = 0; i < vertexList1.size(); i++)
   {
      associatedList.push_back(vertexList1[i]);
   }

   for (int j = 0; j < vertexList2.size(); j++)
   {
      if (vertexList1[j][0] != vertexList2[j][0] || vertexList1[j][1] != vertexList2[j][1])
         associatedList.push_back(vertexList2[j]);
   }

   vector<vector<int>> graph = getAdditionalList(associatedList, m);

   writeGraph(graph, "out.txt");

}


int main()
{

   Task2();


}

