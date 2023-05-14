#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

/**
 * Trida Graph pro cteni grafu ze souboru a nasledne vypocitani shlukovaciho koeficientu nejvetsi komponenty v grafu
 */
class Graph
{
private:
	/**
	* Struktura node reprezentuje vrcholy grafu:
	* Obsahuje seznam sousedu, hodnotu a stav vrcholu, jestlize byl prochazen nebo ne (misto int state by se v mem pripade dalo pouzit bool state)
	*/
	struct Node
	{
		vector<Node*> neighbours;
		int value;
		int state;
	};
	/**
	* nodes - seznam vrcholu v grafu
	*/
	vector <Node*> nodes;
	/**
	* Funkce pro inicializace vrchlu, ktera je potrebna pro pruchod do sirky/hloubky
	*/
	void Init();
public:
	/**
	* Konstruktor se vztupnim parametrem cesty k souboru grafu, ktery se stara o zapis vsech vrcholu a jejich sousedu z txt souboru do seznamu nodes
	*/
	Graph(string path);
	/**
	* Destrukror pro dealokaci seznamu vrcholu
	*/
	~Graph();
	/**
	* Funkce pro pruchod grafu do sirky
	*/
	vector<Node*> BreadthFirst(Node* start);
	/**
	* Funkce pro nalezeni nejvetsi komponenty v grafu. Vyuziva jiz zminenou funkci "BreadthFirst"
	*/
	vector<Node*> FindLargestComponent();
	/**
	* Funkce pro vypocet shlukovaciho koeficientu nejvetsi komponenty v grafu
	*/
	double GlobalClusteringCoefficient();
	/**
	* Testovaci funkce pro vypis nejvetsi komponenty v grafu a jejich vrcholu
	*/
	void printNodes();
};

