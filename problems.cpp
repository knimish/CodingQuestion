#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

//vertical order traversal of binary tree
typedef struct TreeNode{

	int val;
	int dist;
	struct TreeNode *left;	
	struct TreeNode *right;	
} TreeNode;

void verticalordertraversal(TreeNode* root, vector<int> &traversal) {

	if(root == NULL)
		return;

	unordered_map<int, vector<int> > map;
	unordered_map<int, vector<int> > :: iterator it;

	stack<TreeNode*> stk;

	//set distance of root as 0
	root->dist = 0;

	//Do inorder traversal and fill in the map;
	stk.push(root);
	while( !stk.empty() ) {

		//pick the top item
		TreeNode* temp = stk.top();
		stk.pop();

		//try to find the nodes with similar horizontal distance
		it = map.find(root->dist);
		if( it == map.end() ){ 
			//if first element with the horizontal distance create new vector and push the element
			vector<int> curr;
			curr.push_back(root->val);
			map.insert( make_pair(root->dist, curr) );
		}
		else {
			//if found push the node to the vector
			it->second.push_back(root->val);
		}

		//for inorder traversal picking right node first
		if(temp->right){
			temp->right->dist = temp->dist+1;
			stk.push(temp->right);
		}
		if(temp->left){
			temp->left->dist = temp->dist-1;
			stk.push(temp->left);
		}

	}

	for(it = map.begin(); it != map.end(); it++ ){
		for(int i=0; i<it->second.size(); i++){
			traversal.push_back(it->second[i]);
		}
	}

	return;
}

int main() {

	vector<int> output;

	TreeNode* root; // create tree
	verticalordertraversal(root, output);
}