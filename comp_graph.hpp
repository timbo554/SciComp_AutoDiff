#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::string;



class Node{

    public:
        string operation;
        double value;
        double grad;
        vector<Node> parent_nodes_reverse_trav; //As in what would be the parent for this node during reverse traversal of the graph
        vector<Node> created_from; // What nodes was this created from


        Node(double); 
            
};




class autodiff{

    public:

        Node node;

        vector<Node> nodes;

        
        

        autodiff(double);

        autodiff add(autodiff A, autodiff B);

        autodiff mult(autodiff A, autodiff B);

        autodiff Log(autodiff A);

        autodiff Sin(autodiff A);

        autodiff Cosine(autodiff A);
};
// Todo : add graph as parameter in the above class asap and also graph attribute 

