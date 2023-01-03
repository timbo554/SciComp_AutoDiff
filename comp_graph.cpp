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
    this->node.grad = 0.0;
    this->node.local_grad = 0.0;
    
    
}

void comp_graph::read_node(autodiff A){
    this->Nodes.push_back(A.node);
}

void comp_graph::reverse_grad(autodiff A){
    comp_grads(A,1.0);

}

void comp_graph::comp_grads(autodiff A, double seed){
    for (auto Auto : A.node.created_from){
        seed = seed * Auto.node.local_grad;
        Auto.node.grad += seed;
        comp_grads(Auto,seed);

    }
} 



autodiff add(autodiff A, autodiff B,comp_graph graph){

            autodiff C(A.node.value + B.node.value); 
            C.node.operation= "add";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            B.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A);
            C.node.created_from.push_back(B);
            graph.Nodes.push_back(C.node);
            return C;

        }

autodiff mult(autodiff A, autodiff B,comp_graph graph){
            autodiff C(A.node.value * B.node.value); 
            C.node.operation= "mult";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            B.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A);
            C.node.created_from.push_back(B);
            graph.Nodes.push_back(C.node);
            return C;

}

autodiff Log(autodiff A,comp_graph graph){

            autodiff C(log(A.node.value)); 
            C.node.operation= "log";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A);
            graph.Nodes.push_back(C.node);
            return C;
}

autodiff Sin(autodiff A,comp_graph graph){

            autodiff C(sin(A.node.value)); 
            C.node.operation= "sin";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A);     
            graph.Nodes.push_back(C.node);       
            return C;

        }

autodiff Cosine(autodiff A,comp_graph graph){

            autodiff C(cos(A.node.value)); 
            C.node.operation= "cos";
            A.node.parent_nodes_reverse_trav.push_back(C.node);
            C.node.created_from.push_back(A);  
            graph.Nodes.push_back(C.node);
            return C;

        }

void diff_sum(autodiff A){
    A.node.created_from.at(0).node.local_grad = 1.0;
    A.node.created_from.at(1).node.local_grad = 1.0;
}

void diff_mult(autodiff A){
    A.node.created_from.at(0).node.local_grad = A.node.created_from.at(1).node.value;
    A.node.created_from.at(1).node.local_grad = A.node.created_from.at(0).node.value;
}

void diff_sin(autodiff A){
    A.node.created_from.at(0).node.local_grad = cos(A.node.created_from.at(0).node.value);
}

void diff_log(autodiff A){
        A.node.created_from.at(0).node.local_grad = 1.0 / A.node.created_from.at(0).node.value;
}

void diff_cos(autodiff A){
    A.node.created_from.at(0).node.local_grad = -sin(A.node.created_from.at(0).node.value);
}


int main(){
    comp_graph graph; 
    autodiff A = autodiff(10.0);
    autodiff B = autodiff(12.0);
    autodiff C = autodiff(25.0);
    autodiff D = mult(add(A,B,graph),C,graph);
}
