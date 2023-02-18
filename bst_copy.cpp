#include <iostream> 
#include <string>
#include <vector>

using namespace std;

template<typename T> struct node;
template<typename T> bool operator==(const node<T> &lhs, const node<T> &rhs);
template<typename T> class binary_search_tree;

template<typename t> struct node{

template<typename T> friend bool operator==(const node<T> &lhs, const node<T> &rhs);
template<typename T> friend class binary_search_tree;

	// Default Constructor
	node() = default;

	// Constructors
	node(t v): val(v) {}
	node(t v, initializer_list<t> ex): val(v), sub_node(ex) {}

	t val;
	vector<node<t>> sub_node;

};

template<typename T> class binary_search_tree{

public:
	// Default Constructor
	binary_search_tree() = default;
	
	// Create Tree
	node<T> find_val(node<T> tree, T val, node<T> temp_tree = node<T>(-1));
	
	// Add Value	
	bool add(node<T> &tree, node<T> tree2, int depth, int curr_layer = 0);

	// Remove Value
	bool cut(node<T> &parent, node<T> &child, T val, int index = 0);

private:
	node<T> tree;

};

template<typename T> bool operator==(const node<T> &lhs, const node<T> &rhs){return ((lhs.val == rhs.val) && (lhs.sub_node == rhs.sub_node));}

template<typename T> node<T> binary_search_tree<T>::find_val(node<T> tree, T val, node<T> temp_tree){

	if(tree.val == val){

		cout << "Found" << endl;
		return tree;

	} else if(tree.sub_node.size() == 0){			

		cerr << "Value Not Found" << endl;
		temp_tree.val = -1;
		return temp_tree;

	} else {

		temp_tree = find_val(tree.sub_node[0], val);

		if((tree.sub_node.size() == 2) && (temp_tree.val == -1)){

			temp_tree = find_val(tree.sub_node[1], val);

		}

		return temp_tree;

	}

	return temp_tree;

}


template<typename T> bool binary_search_tree<T>::add(node<T> &tree, node<T> tree2, int depth, int curr_layer){

	if((tree.sub_node.empty()) && ((curr_layer + 1) == depth)){

		tree.sub_node.push_back(tree2);
		return true;

	} else if((tree.sub_node.size() == 1) && (tree2.val < tree.sub_node[0].val) && ((curr_layer + 1) == depth)){

		tree.sub_node.insert(tree.sub_node.begin(), tree2);
		return true;

	} else if((tree.sub_node.size() == 1) && (tree2.val >= tree.sub_node[0].val) && ((curr_layer + 1) == depth)){

		tree.sub_node.push_back(tree2);
		return true;

	} else if((tree.sub_node.size() == 2) && ((curr_layer + 1) == depth)){

		cerr << "Node Already Has Two Subnodes" << endl;
		return false;	

	} else if((curr_layer + 1) != depth){

		bool found = add(tree.sub_node[0], tree2, depth, ++curr_layer);
			
		if((tree.sub_node.size() == 2) && (found == false)){

			found = add(tree.sub_node[1], tree2, depth, ++curr_layer);

		}

		return found;
	}

}

template<typename T> bool binary_search_tree<T>::cut(node<T> &parent, node<T> &child, T val, int index){

	if(child.val == val){

		if(parent == child){

			parent.val = 0;
			parent.sub_node.erase(parent.sub_node.begin(), parent.sub_node.end());
			cout << "Deleted Root" << endl;

		} else if(child.sub_node.size() == 0){

			parent.sub_node.erase(parent.sub_node.begin() + index);
			cout << "Deleted Node" << endl;

		} else if(child.sub_node.size() == 1){

			parent.sub_node.push_back(child.sub_node[0]);
			parent.sub_node.erase(parent.sub_node.begin());
			cout << "Deleted Node" << endl;		
		
		} else if(child.sub_node.size() == 2){

			auto pick = ((child.sub_node[0].val < child.sub_node[1].val) ? 0 : 1);
			auto no_pick = 1 - pick;

			parent.sub_node.push_back(child.sub_node[pick]);
			if(child.sub_node.size() == 1){
				if(child.sub_node[no_pick].val < child.sub_node[pick].val){
					child.sub_node.insert(child.sub_node.begin(), child.sub_node[no_pick]);
				} else {
					child.sub_node.push_back(child.sub_node[no_pick]);
				}
			}

		
		}

		return true;

	} else if(child.sub_node.size() == 0){			

		cerr << "Value Not Found" << endl;
		return false;

	} else {

		bool found = cut(child, child.sub_node[0], val, 0);

		if((child.sub_node.size() == 2) && (found == false)){

			found = cut(child, child.sub_node[1], val, 1);

		}

		return found;

	}

	return true;

}

int main(){

	binary_search_tree<int> bst;
	node<int> tree(3);
	node<int> tree1(2);
	node<int> tree2(1);
	node<int> tree3(4);
	node<int> tree4(5);
	node<int> tree5(6);

	bst.add(tree, tree1, 1);
	bst.add(tree, tree2, 1);
	bst.add(tree, tree3, 2);	
	bst.add(tree, tree4, 3);
	bst.add(tree, tree5, 3);

	bst.cut(tree, tree, 5);
	bst.cut(tree, tree, 4);

	cout << bst.find_val(tree, 2).val << endl;
	cout << bst.find_val(tree, 4).val << endl;
	cout << bst.find_val(tree, 5).val << endl;	

}
