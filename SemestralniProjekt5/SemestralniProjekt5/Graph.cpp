#include "Graph.h"

/**
* Funkce pro inicializaci, pomoci foreach projede všechny vrcholy v seznamu a nastavi jim hodnotu stavu 0
*/

void Graph::Init()
{
	for (Node* nod : nodes)
	{
		nod->state = 0;
	}
}

/**
* Konstruktor
* nejdrive se projede cely soubor a najde nejvetsi hodnotu
* vytvori se nody od 0 do nejvetsiho cisla, znovu se projede txt soubor a zapisou se sousedi
*/
Graph::Graph(string path)
{
	ifstream file(path);

	int nodescount = 0;
	int val1, val2;
	while (!file.eof())
	{
		file >> val1 >> val2;
		if(val1 >= val2)
		{ 
			if (val1 > nodescount)
				nodescount = val1;
		}
		else
		{
			if (val2 > nodescount)
				nodescount = val2;
		}
		
	}

	Node* newNode;
	for (int i = 0; i <= nodescount; i++)
	{
		newNode = new Node;
		newNode->value = i;
		nodes.push_back(newNode); 
	}
	file.clear();
	file.seekg(0);
	while (!file.eof())
	{
		file >> val1 >> val2;
		nodes[val1]->neighbours.push_back(nodes[val2]);
		nodes[val2]->neighbours.push_back(nodes[val1]);
	}

	file.close();
}
/**
* Destruktor
* foreachem vymaze jednotlive nody z nodes
*/
Graph::~Graph()
{
	for (Node* nod : nodes)
		delete nod;
}
/**
* Do parametru vlozim zacatecni node a ulozim ho do queue
* Z queue se jednotlive projizdi sousedi, vrcholu ktery byl navstiven se nastavi state na 1
* Po projeti vsemi sousedy se seznam vrcholu se returne
*/
vector<Graph::Node*> Graph::BreadthFirst(Graph::Node* start) {
	vector<Node*> component;
	queue<Node*> q;
	q.push(start);
	start->state = 1;

	while (!q.empty()) {
		Node* current = q.front();
		q.pop();
		component.push_back(current);

		for (Node* neighbour : current->neighbours) {
			if (neighbour->state == 0) {
				q.push(neighbour);
				neighbour->state = 1;
			}
		}
	}

	return component;
}
/**
* Funkce pro nalezeni nejvetsi komponenty zpusti funkci "Init" a pote porovnava velikost komponent ktere vratila funkce "BreadthFirst"
* Nejvetsi komponenta se returne
*/
vector<Graph::Node*> Graph::FindLargestComponent() {
	Init();
	vector<Node*> largestComponent;

	for (Node* node : nodes) {
		if (node->state == 0) {
			vector<Node*> component = BreadthFirst(node);
			if (component.size() > largestComponent.size()) {
				largestComponent = component;
			}
		}
	}

	return largestComponent;
}
/**
* Vypocet shlukovaciho koeficientu nejvetsi komponenty v grafu
* Nejvetsi komponenta se vezme z funkce "FindLargestComponent", ktera se ulozi do seznamu largestComponent
* Z tohoto seznamu se pote berou jednotlive vrcholy u kterych se hleda jestli maji 2 nebo vice sousedu
* Pokud ano pomoci vzorecku se vypocita hodnota pro nodeTriplets a ulozi se to totalTriplets
* Pote se zkontroluje jestli jsou sousede spojeni nebo ne, pokud ano pricte se 1 k connectedNodeTriplets, tato promenna se nasledne ulozi do connectedTriplets
* Pro konecny vypocet pouzije vzorec (double)connectedTriplets / (double)totalTriplets a vrati hodnotu
*/
double Graph::GlobalClusteringCoefficient()
{
	vector<Node*> largestComponent = FindLargestComponent();

	int numNodes = largestComponent.size();
	int totalTriplets = 0;
	int connectedTriplets = 0;
	for (int i = 0; i < numNodes; i++) {
		Node* node = largestComponent[i];
		int numNeighbors = node->neighbours.size();
		if (numNeighbors >= 2) {
			int nodeTriplets = (numNeighbors * (numNeighbors - 1)) / 2;
			totalTriplets += nodeTriplets;

			int connectedNodeTriplets = 0;
			for (int j = 0; j < numNeighbors; j++) {
				for (int k = j + 1; k < numNeighbors; k++) {
					Node* neighbour1 = node->neighbours[j];
					Node* neighbour2 = node->neighbours[k];
					for (Node* commonNeighbour : neighbour1->neighbours) {
						if (commonNeighbour == neighbour2) {
							connectedNodeTriplets++;
							break;
						}
					}
				}
			}
			connectedTriplets += connectedNodeTriplets;
		}
	}

	double globalCC = (double)connectedTriplets / (double)totalTriplets;
	return globalCC;
}
/**
* Testovaci funkce pro zobrazeni velikosti nejvetsi komponenty a jednotlivych vrcholu
*/
void Graph::printNodes()
{
	vector<Node*> largestComponent = FindLargestComponent();
	cout << "Largest Component Size: " << largestComponent.size() << endl;
	cout << "Nodes in the Largest Component: ";
	for (Node* node : largestComponent) {
		cout << node->value << " ";
	}
	cout << endl;
}

