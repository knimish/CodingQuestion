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

//copy bits from num2 in between m<=n positions to num1
int replacemn(int num1, int num2, int m, int n){

	//m should be less than n
	if(m > n)
		return num1;

	//if upper bound is crossing the size of int
	if(n > 8*sizeof(int))
		return num1;

	int ones = 0xFFFFFFFF;

	//left end Eg: 11000000..
	int uppermask = ones << n;
	//right end Eg: 00001111..
	int lowermask = ( 1 << (m) )-1;
	//mask with 0 between m and n
	int mask = uppermask | lowermask;

	//clear bits between m and n
	num1 = num1 & mask;

	//OR with the bits in num2
	num1 = num1 | ( ~mask & num2) ;

	return num1;
}

bool isValidBST_helper2(TreeNode* root, TreeNode* minnode, TreeNode* maxnode){

	if(root == NULL)
		return true;

	bool lval=false, rval=false;

	if(minnode == NULL || ( minnode && (minnode->val < root->val) ) )
		lval = true;

	if(maxnode == NULL || (maxnode && (maxnode->val > root->val) ) )
		rval = true;

	if(lval && rval)
		return isValidBST_helper2(root->left, minnode, root) && isValidBST_helper2(root->right, root, maxnode);

	return false;
}

bool isValidBST_helper(TreeNode* root, int minval, int maxval){

	if(root == NULL)
		return true;

	if(root->val > minval && root->val < maxval){
		return isValidBST_helper(root->left, minval, root->val) && isValidBST_helper(root->right, root->val, maxval);
	}

	return false;
}

bool isValidBST(TreeNode* root) {

	if(root == NULL)
		return true;

	//return isValidBST_helper(root, INT_MIN, INT_MAX);
	return isValidBST_helper2(root, NULL, NULL);
}

int main() {

	vector<int> output;

	//vertical order traversal
	//TreeNode* root; // create tree
	//verticalordertraversal(root, output);
	
	//replace m n
	replacemn(107, 21, 2, 4);

}