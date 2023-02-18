#include <iostream>

using namespace std;

struct node{

	// Default Constructor
	node() = default;

	// Constructor with Data
	node(int val): num(val) {prev = NULL, next = NULL; last = false;}

	// Constructor With Stoppage Var
	node(int val, bool lst): num(val), last(lst) {prev = NULL, next = NULL;}

	// Add Node
	void add(node &tgt, node &next_tgt);

	// Remove Node
	void cut(node tgt, node &next_tgt);

	// Iterate through linked-list
	void iter();

	// Used to Halt Iter Function
	bool last;

	// Data
	int num;

	// Pointer to Previous Node
	node *prev;

	// Pointer to Next Node
	node *next;

};

void node::add(node &tgt, node &next_tgt){

	tgt.prev = this;
	tgt.next = this->next;
	this->next = &tgt;
	next_tgt.prev = &tgt; 
}

void node::cut(node tgt, node &next_tgt){

	this->next = tgt.next;
	next_tgt.prev = this;

}

void node::iter(){

	cout << this->num << endl;	
	if(last == false){next->iter();}
}

int main(){

	// Create Doubly Linked List
	node one(0);
	node two(1);
	two.prev = &one;
	one.next = &two;
	node three(2);
	three.prev = &two;
	two.next = &three;
	node four(3, true);
	four.prev = &three;
	three.next = &four;

	// Remove Two
	one.cut(two, three);	
	one.iter();
	cout << endl;

	// Add Two
	one.add(two, three);
	one.iter();

}
