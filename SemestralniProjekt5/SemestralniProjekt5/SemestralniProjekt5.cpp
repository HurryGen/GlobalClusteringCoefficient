

#include <iostream>
#include <iomanip>
#include "Graph.h"
using namespace std;

int main()
{
    Graph* g1 = new Graph("Graph1.txt");
    cout << "Largest Component Size: " << g1->FindLargestComponent().size() << " Nodes" << endl;
    cout << "Global Clustering Coefficient: " << ::setprecision(20) << g1->GlobalClusteringCoefficient();
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    delete g1;
    Graph* g2 = new Graph("Graph2.txt");
    cout << "Largest Component Size: " << g2->FindLargestComponent().size() << " Nodes" << endl;;
    cout << "Global Clustering Coefficient: " << ::setprecision(20) << g2->GlobalClusteringCoefficient();
    delete g2;
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    Graph* g3 = new Graph("Graph3.txt");
    cout << "Largest Component Size: " << g3->FindLargestComponent().size() << " Nodes" << endl;;
    cout << "Global Clustering Coefficient: " << ::setprecision(20) << g3->GlobalClusteringCoefficient();
    delete g3;
}
