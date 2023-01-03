#include <iostream>
#include <vector>
#include <cmath>
#include "comp_graph.hpp"

using std::vector;
using std::string;
using std::cout;
        
autodiff::autodiff(double value){

    Node node;
    this->node = node;
    this->node.value = value;
    this->node.operation = "None";
    this->node.grad = 1.0;
    
}

autodiff add(autodiff A, autodiff B){

            autodiff C(A.node.value + B.node.value); 
            C.node.operation= "add";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            B.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            C.node.created_from.push_back(B.node);
            A.node.grad = 1.0;
            B.node.grad = 1.0;
            return C;

        }

autodiff mult(autodiff A, autodiff B){
            autodiff C(A.node.value + B.node.value); 
            C.node.operation= "mult";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            B.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            C.node.created_from.push_back(B.node);
            A.node.grad = B.node.value;
            B.node.grad = A.node.value;
            return C;

}

autodiff Log(autodiff A){

            autodiff C(log(A.node.value)); 
            C.node.operation= "log";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            A.node.grad = 1.0 / A.node.value; 
            return C;
}

autodiff Sin(autodiff A){

            autodiff C(sin(A.node.value)); 
            C.node.operation= "sin";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            A.node.grad = cos(A.node.value);            
            return C;

        }

autodiff Cosine(autodiff A){

            autodiff C(sin(A.node.value)); 
            C.node.operation= "cos";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A.node);
            A.node.grad = -sin(A.node.value);            
            return C;

        }

// Todo : add graph as parameter in the above class asap and also graph attribute 




int main(){
    
    autodiff A = autodiff(10.0);
    autodiff C = autodiff(12.0);
    autodiff B = mult(A,C);
    autodiff D = Log(B);
    for (auto node : A.node.parent_nodes_reverse_trav){
        cout << node.value;
    }
}
