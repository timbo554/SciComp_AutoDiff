#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Node{

    public:
        string operation;
        double value;
        double grad;
        bool is_leaf;
        vector<Node> parent_nodes;
        int num_parent_nodes;


        Node(string operation,double value,double grad,bool is_leaf,vector<Node> parent_nodes){
            this->operation = operation;
            this->value = value;
            this->is_leaf = is_leaf;
            this->grad = grad;
            
            if (this->operation == "plus"){

                this->num_parent_nodes = 2;
                // this part is incomplete



        } 
        }
};

class comp_graph{
    
    public:
        Node node;

    comp_graph(string operation,double value,double grad,bool is_leaf,vector<Node> parent_nodes){

        this->node = Node(operation,value,grad,is_leaf,parent_nodes);

        

    }
    

};

