#include <iostream> 
#include <string>
#include <vector>

using namespace std;

template<typename T> struct node;
template<typename T> bool operator==(const node<T> &lhs, const node<T> &rhs);
template<typename T> class binary_search_tree;

template<typename t> struct node{

	// Friend Functions & Classes
	template<typename T> friend bool operator==(const node<T> &lhs, const node<T> &rhs);
	template<typename T> friend class binary_search_tree;

	// Default Constructor
	node() = default;

	// Constructors
	node(t v): val(v) {}

	// Copy Assignment Operator
	node<t>& operator=(node<t> ex){

		this->val = ex.val;
		this->left_subtree = ex.left_subtree;	
		this->right_subtree = ex.right_subtree;

	}

	t val;
	node<t> *left_subtree = nullptr;
	node<t> *right_subtree = nullptr;

};

template<typename T> class binary_search_tree{

public:
	// Default Constructor
	binary_search_tree() = default;

	// Constuctor
	binary_search_tree(T val): tree(val) {}
	
	// Grab Root 	
	node<T> &get_root(){return this->tree;}
	
	// Search Tree
	node<T> search(node<T> tree, T val);
	
	// Add Value	
	void add(node<T> &tree, node<T> &sub_tree);

	// Remove Value
	bool remove(node<T> &parent, node<T> child, T val, string tree_side = "left");

private:
	// Tree
	node<T> tree;

};

template<typename T> bool operator==(const node<T> &lhs, const node<T> &rhs){return ((lhs.val == rhs.val) && (lhs.left_subtree == rhs.left_subtree) && (lhs.right_subtree == rhs.right_subtree));}

template<typename T> node<T> binary_search_tree<T>::search(node<T> tree, T val){

	if(tree.val == val){

		cout << "Found" << endl;
		return tree;

	} else if((val < tree.val) && (tree.left_subtree != nullptr)){			

		return search(*tree.left_subtree, val);

	} else if((val >= tree.val) && (tree.right_subtree != nullptr)){

		return search(*tree.right_subtree, val); 

	} else {

		cerr << "Value Not Found" << endl;
		return node<T>(-1);
	}

}


template<typename T> void binary_search_tree<T>::add(node<T> &tree, node<T> &sub_tree){

	if((tree.left_subtree == nullptr) && (tree.right_subtree == nullptr)){

		if(sub_tree.val < tree.val){

			tree.left_subtree = &sub_tree;

		} else {

			tree.right_subtree = &sub_tree;

		}

	} else if((tree.left_subtree == nullptr) && (sub_tree.val < tree.val)){

		tree.left_subtree = &sub_tree;

	} else if((tree.right_subtree == nullptr) && (sub_tree.val >= tree.val)){

		tree.right_subtree = &sub_tree;
		
	} else if((tree.right_subtree != nullptr) && (tree.left_subtree != nullptr)){ 

		if(sub_tree.val < tree.val){

			add(*tree.left_subtree, sub_tree);

		} else {

			add(*tree.right_subtree, sub_tree);

		}

	} else {

		cerr << "Can't Insert This Node" << endl;		

	}
}

template<typename T> bool binary_search_tree<T>::remove(node<T> &parent, node<T> child, T val, string tree_side){

	if((child.val == val) && (parent == child)){
		
		if(child.left_subtree != nullptr){

			this->tree = *child.left_subtree;
			if(child.right_subtree != nullptr){

				this->add(this->tree, *child.right_subtree);

			}

		} else if(child.right_subtree != nullptr){

			this->tree = *child.right_subtree;
		}

	} else if((child.val == val) && (child.left_subtree == nullptr) && (child.right_subtree == nullptr)){

		if(tree_side == "left"){

			parent.left_subtree = nullptr;

		} else {

			parent.right_subtree = nullptr;

		}	

	} else if((child.val == val) && ((child.left_subtree == nullptr) || (child.right_subtree == nullptr))){

		auto p = (child.left_subtree == nullptr) ? child.right_subtree : child.left_subtree;

		if(tree_side == "left"){

			parent.left_subtree = nullptr;

		} else {

			parent.right_subtree = nullptr;	


		}

		if((p->val < parent.val) && (parent.left_subtree == nullptr)){

			parent.left_subtree = p;

		} else if((p->val >= parent.val) && (parent.right_subtree == nullptr)){

			parent.right_subtree = p;

		} else {

			this->add(this->tree, *p);

		}
	
	} else if((child.val == val) && (child.left_subtree != nullptr) && (child.right_subtree != nullptr)){


		auto p = (child.left_subtree->val < parent.val) ? child.left_subtree : child.right_subtree;
		auto p_not = (child.left_subtree->val < parent.val) ? child.right_subtree : child.left_subtree;

		if((p == child.left_subtree) && (p->right_subtree == nullptr)){

			p->right_subtree = child.right_subtree;		

		} else if((p == child.right_subtree) && (p->left_subtree == nullptr)){

			p->left_subtree = child.left_subtree;		

		} else {

			this->add(this->tree, *p_not);

		}

		if(tree_side == "left"){

			parent.left_subtree = p;

		} else {

			parent.right_subtree = p;
		
		}		


	} else if(child.val != val){

		if((val < child.val) && (child.left_subtree != nullptr)){

			remove(child, *child.left_subtree, val, "left");		

		} else if((val >= child.val) && (child.right_subtree != nullptr)){

			remove(child, *child.right_subtree, val, "right");

		} else {

			cerr << "Value Not Found" << endl;

		}

	}

}

int main(){

	binary_search_tree<int> bst(3);

	node<int> tree1(2);
	node<int> tree2(1);
	node<int> tree3(5);
	node<int> tree4(8);
	node<int> tree5(4);

	bst.add(bst.get_root(), tree1);
	bst.add(bst.get_root(), tree2);
	bst.add(bst.get_root(), tree3);	
	bst.add(bst.get_root(), tree4);
	bst.add(bst.get_root(), tree5);

//	bst.remove(bst.get_root(), bst.get_root(), 6, "left");
//	bst.remove(bst.get_root(), bst.get_root(), 4, "left");

	
	cout << bst.search(bst.get_root(), 8).val << endl;
//	cout << bst.search(bst.get_root(), 6).val << endl;

}
