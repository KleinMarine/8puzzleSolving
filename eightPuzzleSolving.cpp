#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <queue>
#include <string.h> 
using namespace std;

struct dataNode {
	int state[9];
	int g, h, f;
	int action;
	dataNode* parent;

	dataNode(int data[9]) {
		for (int i = 0; i < 9; i++) {
			state[i] = data[i];
		}
	}

	dataNode() {
		for (int i = 0; i < 9; i++) {
			state[i] = NULL;
		}
		g = NULL;
		h = NULL;
		f = NULL;
		action = NULL;
		parent = NULL;

	}
	void save(int data[9]) {
		for (int i = 0; i < 9; i++) {
			state[i] = data[i];
		}
	}

	void save(int data[4][9], int num) {
		for (int i = 0; i < 9; i++) {
			state[i] = data[num][i];
		}
	}

};

struct cmp {
	bool operator()(dataNode* a, dataNode* b) {
		if (a->f == b->f)
			return a->g > b->g;
		return a->f > b->f;
	}
};

bool unsolvable(int state[9]) {
	int count = 0;

	for (int j = 0; j < 8; j++) {
		for (int i = j + 1; i < 9; i++) {
			if (state[i] != 0 && state[j] != 0) {
				if (state[j] > state[i]) {
					count++;
				}
			}
		}
	}
	if (count % 2 == 0)
		return true;
	else if (count % 2 == 1)
		return false;
}
int heuristic(int state[9]) {
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[3 * i + j] != 0) {
				if (((state[3 * i + j] / 3) ^ i) != 0) {
					if (((state[3 * i + j] / 3) ^ i) == 3)
						count += 1;
					else
						count += (state[3 * i + j] / 3) ^ i;
				}

				if (((state[3 * i + j] % 3) ^ j) != 0) {
					if (((state[3 * i + j] % 3) ^ j) == 3) {
						count += 1;
					}
					else
						count += ((state[3 * i + j] % 3) ^ j);
				}
			}
		}
	}
	return count;
}
int heuristic(int state[4][9], int num) {
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (state[num][3 * i + j] != 0) {
				if (((state[num][3 * i + j] / 3) ^ i) != 0) {
					if (((state[num][3 * i + j] / 3) ^ i) == 3)
						count += 1;
					else
						count += (state[num][3 * i + j] / 3) ^ i;
				}

				if (((state[num][3 * i + j] % 3) ^ j) != 0) {
					if (((state[num][3 * i + j] % 3) ^ j) == 3) {
						count += 1;
					}
					else
						count += ((state[num][3 * i + j] % 3) ^ j);
				}
			}
		}
	}
	return count;
}
void findSuccessor(int state[9], int nextActoin[4], int nextState[4][9]) {

	int blank;

	for (int i = 0; i < 9; i++) {
		if (state[i] == 0)
			blank = i;
	}

	if ((blank - 3) >= 0)
		nextActoin[0] = 1;
	else
		nextActoin[0] = 0;

	//down
	if (blank + 3 <= 8)
		nextActoin[1] = 1;
	else
		nextActoin[1] = 0;

	//left
	if (blank % 3 != 0)
		nextActoin[2] = 1;
	else
		nextActoin[2] = 0;

	//right
	if (blank % 3 != 2)
		nextActoin[3] = 1;
	else
		nextActoin[3] = 0;

	for (int i = 0; i < 4; i++) {
		int newPosition;
		if (nextActoin[i] == 1) {

			if (i == 0) newPosition = blank - 3;
			else if (i == 1) newPosition = blank + 3;
			else if (i == 2) newPosition = blank - 1;
			else if (i == 3) newPosition = blank + 1;

			if (newPosition == 0)
				nextState[i][0] = 0;
			else if (blank == 0)
				nextState[i][0] = state[newPosition];
			else
				nextState[i][0] = state[0];
			for (int j = 1; j < 9; j++)
			{
				if (newPosition == j)
					nextState[i][j] = 0;
				else if (blank == j)
					nextState[i][j] = state[newPosition];
				else
					nextState[i][j] = state[j];
			}
		}
	}
}
bool goalState(int state[9], int goal[9])
{
	for (int i = 0; i < 9; i++) {
		if (state[i] != goal[i])
			return false;
	}
	return true;
}

void printPath(dataNode* root) {
	if (root->action == 0)
		cout << "move blank to up\n";
	else if (root->action == 1)
		cout << "move blank to down\n";
	else if (root->action == 2)
		cout << "move blank to left\n";
	else if (root->action == 3)
		cout << "move blank to right\n";

}
void findRoot(dataNode* root)
{
	if (root == NULL)
		return;
	findRoot(root->parent);
	if (root->parent != NULL) {
		printPath(root);
	}

}


int main() {
	priority_queue <dataNode*, vector<dataNode*>, cmp > pq;

	dataNode* mynode = NULL, * newnode = NULL, * final = NULL;
	int goal[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int nextAction[4]; //0:up; 1:down; 2:left; 3:right
	int nextState[4][9];

	int data[9];
	char str;
	cin >> str;
	for (int i = 0; i < 9; i++)  cin >> data[i];
	cin >> str;

	mynode = new dataNode;
	mynode->save(data);

	if (!unsolvable(mynode->state)) {
		cout << "No solution!!";
	}
	else if (goalState(mynode->state, goal)) {
		cout << "It is the goal state.";
	}
	else {
		mynode->g = 0;
		mynode->h = heuristic(mynode->state);
		mynode->f = mynode->g + mynode->h;
		mynode->parent = NULL;
		pq.push(mynode);

		while (!pq.empty()) {
			mynode = pq.top();
			pq.pop();

			if (goalState(mynode->state, goal)) {
				final = new dataNode;
				final = mynode;
				break;
			}
			findSuccessor(mynode->state, nextAction, nextState);
			for (int i = 0; i < 4; i++)
			{
				if (nextAction[i] == 1) {
					newnode = new dataNode;
					newnode->save(nextState, i);
					newnode->action = i;
					newnode->g = mynode->g + 1;
					newnode->h = heuristic(nextState, i);
					newnode->f = newnode->g + newnode->h;
					newnode->parent = mynode;
					pq.push(newnode);
				}
			}

		}
		findRoot(final);

	}
}