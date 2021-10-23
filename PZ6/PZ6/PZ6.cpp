#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>


using namespace std;

void taskOne()
{
   cout << "Enter number of elements" << endl;

   int n = 0;

   cin >> n;

   stack<int> s;
   cout << "enter elements" << endl;

   int elem;

   for (int i = 0; i < n; i++)
   {
      cin >> elem;
      s.push(elem);
   }


   int stack_size = s.size();

   for (int i = 0; i < stack_size; i++)
   {
      cout << s.top();
      s.pop();

   }
}

void TaskTwo()
{
   cout << "Enter number of elements" << endl;

   int n = 0;

   cin >> n;
   cout << "enter elements" << endl;

   int elem;

   vector<int> v;

   for (int i = 0; i < n; i++)
   {
      cin >> elem;
      v.push_back(elem);
   }

   sort(v.begin(), v.end());

   v.resize(unique(v.begin(), v.end()) - v.begin());

   int s = v.size();

   for (int i = 0; i < s; i++)
      cout << v[i];

}

void taskThree()
{

   int index = 1, elem = 1;

   vector<vector<int>> v;

   while (index != 0 || elem != 0)
   {
      cout << "enter index" << endl;
      cin >> index;

      if (index +1> v.size())
         v.resize(index + 1);

      cout << "enter element" << endl;
      cin >> elem;

      if(index != 0 || elem != 0)
          v[index].push_back(elem);
   }


   int s = v.size();

   for (int i = 0; i < s; i++)
      sort(v[i].begin(), v[i].end());


   ofstream file;
   file.open("1.txt");

   for (int i = 0; i < s; i++)
   {
      for (int j = 0; j < v[i].size(); j++)
         file << v[i][j] << " ";
      file << endl;
   }

}
int main()
{
   taskThree();

}
