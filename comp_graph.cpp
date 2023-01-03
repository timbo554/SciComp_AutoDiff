#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::string;

class Node{

    public:
        string operation;
        double value;
        int index;
        double grad;
        comp_graph graph;
        vector<Node> parent_nodes_reverse_trav; //As in what would be the parent for this node during reverse traversal of the graph
        vector<Node> created_from; // What nodes was this created from


        Node(comp_graph graph,double value){
            this->index = graph.node_index;
            this->value = value;
        } 
            
};

class comp_graph{
    
    
    public:
        int node_index = 0;
        vector<Node> nodes;
        void read_node(Node node){

            nodes.push_back(node);
            node_index++;
    }
};


class autodiff{

    public:

        Node node;
        

        autodiff(comp_graph graph,double value){

            this->node.index = graph.node_index;
            this->node.graph = graph;
            this->node.value = value;
            graph.read_node(this->node);

        }

        autodiff add(autodiff A, autodiff B,comp_graph graph){

            autodiff C(graph,A.node.value + B.node.value); 
            C.node.operation= "add";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            B.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            C.node.created_from.push_back(B.node);
            A.node.grad = 1.0;
            B.node.grad = 1.0;
            graph.read_node(C.node);
            return C;

        }

        autodiff mult(autodiff A, autodiff B, comp_graph graph){

            autodiff C(graph,A.node.value + B.node.value); 
            C.node.operation= "mult";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            B.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            C.node.created_from.push_back(B.node);
            A.node.grad = B.node.value;
            B.node.grad = A.node.value;
            graph.read_node(C.node);
            return C;

        }

        autodiff Log(comp_graph graph, autodiff A)){

            autodiff C(graph,log(A.node.value)); 
            C.node.operation= "log";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            A.node.grad = 1.0 / A.node.value;
            graph.read_node(C.node);
            return C;
        }

        autodiff Sin(autodiff A, comp_graph graph){

            autodiff C(graph,sin(A.node.value)); 
            C.node.operation= "sin";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            A.node.grad = cos(A.node.value);            
            graph.read_node(C.node);
            return C;

        }

        autodiff Cosine(autodiff A, comp_graph graph){

            autodiff C(graph,sin(A.node.value)); 
            C.node.operation= "cos";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            A.node.grad = -sin(A.node.value);            
            graph.read_node(C.node);
            return C;

        }
};
// Todo : add graph as parameter in the above class asap and also graph attribute 




int main(){
    comp_graph G;
    autodiff A = autodiff(G,10);
}
