#include <iostream> 
#include <string>
#include <vector>


using namespace std;

template<typename T> struct node;
template<typename T> bool operator==(const node<T> &lhs, const node<T> &rhs);
template<typename T> bool operator!=(const node<T> &lhs, const node<T> &rhs);
template<typename T> class directed_acyclic_graph;

template<typename t> struct node{

	// Friend Functions & Classes
	template<typename T> friend bool operator==(const node<T> &lhs, const node<T> &rhs);
	template<typename T> friend bool operator!=(const node<T> &lhs, const node<T> &rhs);
	template<typename T> friend class directed_acyclic_graph;

	// Default Constructor
	node() = default;

	// Constructors
	node(t v): name(""), val(v) {}
	node(string n, t v): name(n), val(v) {}

	// Variables
	string name;
	t val;
	vector<pair<node<t>*, int>> parents;
	vector<pair<node<t>*, int>> children;

};

template<typename T> class directed_acyclic_graph{

public:
	// Default Constructor
	directed_acyclic_graph() = default;

	// Constuctor
	directed_acyclic_graph(T val): tree("", val) {}
	directed_acyclic_graph(string n, T val): tree(n, val) {}
	
	// Grab Root 	
	node<T> &get_root(){return this->tree;}
	
	// Search Tree
	node<T> search(node<T> mytree, T val, int spot = 0);
	
	// Add Value to Parent
	void add_parent(node<T> &tree, node<T> &sub_tree);

	// Add Value to Child	
	void add_child(node<T> &tree, node<T> &sub_tree);
	
	// Remove Node
	void remove(node<T> &target);

private:
	// Tree
	node<T> tree;

	// Find
	bool found = false;

};

template<typename T> bool operator==(const node<T> &lhs, const node<T> &rhs){return ((lhs.name != rhs.name) || (lhs.val == rhs.val));}
template<typename T> bool operator!=(const node<T> &lhs, const node<T> &rhs){return ((lhs.name != rhs.name) || (lhs.val != rhs.val));}

template<typename T> node<T> directed_acyclic_graph<T>::search(node<T> mytree, T val, int spot){

	if(found == false){

		if(mytree.val == val){

			cout << "Found" << endl;
			found = true;
			return mytree;
		
		} else if((mytree.children.empty()) && (spot == (mytree.parents.size() - 1)) && (mytree != this->tree)){

			cerr << "Value Not Found" << endl;
			return node<T>(-1);

		} else {

			node<T> temp_tree;

			for(auto i = 0; i < mytree.children.size(); ++i){

				temp_tree = this->search(*mytree.children[i].first, val, i);
				if(found == true){
					break;
				}

			}

			if(mytree.name == tree.name){found = false;}

			return temp_tree;

		}

	}


}

// Add Value to Parent
template<typename T> void directed_acyclic_graph<T>::add_parent(node<T> &tree, node<T> &sub_tree){

	tree.parents.push_back({&sub_tree, tree.parents.size() + 1});
	sub_tree.children.push_back({&tree, sub_tree.children.size() + 1});

}

// Add Value to Child	
template<typename T> void directed_acyclic_graph<T>::add_child(node<T> &tree, node<T> &sub_tree){

	tree.children.push_back({&sub_tree, tree.children.size() + 1}); 
	sub_tree.parents.push_back({&tree, sub_tree.parents.size() + 1});

}


template<typename T> void directed_acyclic_graph<T>::remove(node<T> &target){

	for(auto i = 0; i < target.parents.size(); ++i){

		target.parents[i].first->children.erase(target.parents[i].first->children.begin() + target.parents[i].second);
		target.parents.erase(target.parents.begin() + i);

	}


	for(auto i = 0; i < target.children.size(); ++i){

		target.children[i].first->parents.erase(target.children[i].first->parents.begin() + target.children[i].second);
		target.children.erase(target.children.begin() + i);

	}

}

void print_tree(node<int> test_node){

	for(auto i = 0; i < test_node.children.size(); ++i){

		cout << test_node.children[i].first->name << " " << test_node.children[i].first->val << endl;

		if(test_node.children[i].first->children.size() > 0){

			print_tree(*test_node.children[i].first);

		}

	}

}

int main(){

	directed_acyclic_graph<int> dag("Joey", 3);

	node<int> node1("Dave", 2);
	node<int> node2("Sam", 1);
	node<int> node3("Jodie", 5);
	node<int> node4("Bill", 8);
	node<int> node5("Adam", 4);
	node<int> node6("Dane", 17);

	dag.add_child(dag.get_root(), node1);
	dag.add_child(node1, node2);
	dag.add_child(node2, node3);
	dag.add_child(node2, node4);	
	dag.add_child(dag.get_root(), node5);
	dag.add_child(node5, node6);

	dag.remove(node4);

	cout << dag.search(dag.get_root(), node6.val).val << endl;
	
//	cout << dag.search(dag.get_root(), 6).val << endl;

}
