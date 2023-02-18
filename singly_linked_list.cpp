#include <iostream>

using namespace std;

struct node{

	// Default Constructor
	node() = default;

	// Constructor with Data
	node(int val): num(val) {next = NULL; last = false;}

	// Constructor With Stoppage Var
	node(int val, bool lst): num(val), last(lst) {next = NULL;}

	// Add Node
	void add(node &tgt);

	// Remove Node
	void cut(node tgt);

	// Iterate through linked-list
	void iter();

	// Used to Halt Iter Function
	bool last;

	// Data
	int num;

	// Pointer to Next Node
	node *next;

};

void node::add(node &tgt){

	tgt.next = this->next;
	this->next = &tgt;

}

void node::cut(node tgt){

	this->next = tgt.next;

}

void node::iter(){

	cout << this->num << endl;	
	if(last == false){next->iter();}
}

int main(){

	node one(0);
	node two(1);
	one.next = &two;
	node three(2);
	two.next = &three;
	node four(3, true);
	three.next = &four;
	one.cut(two);
	one.iter();

}
