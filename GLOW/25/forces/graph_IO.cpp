/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "graph_IO.h"

const char* GRAPH_KEYWORD = "GRAPH";

void load(My_graph& G, const char* filename)
{
    G.clear();

    std::ifstream infile(filename);
    if(!infile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    int number_of_nodes, number_of_edges;
    std::string graphkeyword;
    infile >> graphkeyword;
    if(graphkeyword != GRAPH_KEYWORD) {
        std::cerr << "File does not appear to contain a saved graph\n";
        return;
    }
    infile >> number_of_nodes >> number_of_edges;
    std::map<int, My_node*> M;
    int i = 0;
    while(i != number_of_nodes) {
        double x, y;
        bool b;
        infile >> x >> y >> b;
        My_node* N = G.insert_node( Node_parameter( Point_E2d(x,y), b ) );
        M[i] = N;
        i++;
    };
    while(number_of_edges--) {
        int s, t;
        infile >> s >> t;
        G.insert_edge( M[s], M[t] );
    }
}

void save(My_graph& G, const char* filename)
{
    std::ofstream outfile(filename);
    if(!outfile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    outfile << GRAPH_KEYWORD << "\n" << G.nodes.size() << " " << G.edges.size() << std::endl;
    std::map<My_node*, int> M;
    int counter = 0;
    for(std::list<My_node*>::const_iterator My_node_It = G.nodes.begin();
        My_node_It != G.nodes.end(); ++My_node_It) {
        outfile << (*My_node_It)->info() << std::endl;
        M[*My_node_It] = counter++;
    }
    for(std::list<My_edge*>::const_iterator My_edge_It = G.edges.begin();
        My_edge_It != G.edges.end(); ++My_edge_It) {
        outfile << M[(*My_edge_It)->source()] << " " << M[(*My_edge_It)->target()] << std::endl;
    }
    outfile.close();
}
