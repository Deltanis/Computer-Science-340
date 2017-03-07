/*
Assignment 3, Question 1 "Kruskal's Algorithm"
Austin McPhail
200341412

*/

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
#include <iostream>
#include <climits> //Used for HIGH_VALUE
//hi
using namespace std;

//Priority Queue Data Structures
struct Edge {
	int vertex1;
	int vertext2;
	int distance;
};
//EDGE ARRAYS FOR GRAPH FROM CLASS
Edge q[12];
Edge t[12];

/*//EDGE ARRAYS FOR GRAPH.TXT
Edge q[23];
Edge t[23];
*/
int t_array_pos = 0;

//Kruskal Data Structures
struct SubsetNode;
struct VertexNode {
	int vertex;
	VertexNode* next;
	SubsetNode* subset;
};
struct SubsetNode {
	int size;
	VertexNode* firstVertex;
};
struct SetNode {
	int vertex;
	SetNode* left;
	SubsetNode* subset;
	SetNode* right;
	int height;
};
SetNode* s;

void KruskalsMinimumSpanningTree(Edge q[], Edge t[], SetNode* &s);
void Initialization(Edge q[], int &edgeCount, SetNode* &s, int &vertexCount);
void Search(Edge q[], int &edgeCount, SetNode* &s, int vertexCount, Edge t[]);
void Tree(Edge t[]);
void Insert(int x, int y, int z, Edge q[], int &edgeCount);
bool Insert(int w, SetNode* &s, int &vertexCount);
void MakeSet(SetNode* &v);
Edge DeleteMin(Edge q[], int &edgeCount);
int Max(int height1, int height2);
int Height(SetNode* s);
SetNode* Find(int vertex, SetNode* &s);
void Union(SetNode* &vTo, SetNode* &vFrom, SetNode* &s);
void InsertUnsorted(Edge e, Edge t[]);
void LL(SetNode* &s);
void LR(SetNode* &s);
void RR(SetNode* &s);
void RL(SetNode* &s);

int main() {
	KruskalsMinimumSpanningTree(q, t, s);
}

void KruskalsMinimumSpanningTree(Edge q[], Edge t[], SetNode* &s) {
	int edgeCount = 0;
	int vertexCount = 0;
	Initialization(q, edgeCount, s, vertexCount);
	/*
	for (int i = 0; i < 23; i++) {
		cout << "q[" << i << "]:" << endl;
		cout << "     vertex1 = " << q[i].vertex1 << endl;
		cout << "     vertex2 = " << q[i].vertext2 << endl;
		cout << "     distance = " << q[i].distance << endl;
		cout << endl;
	}
	*/
	Search(q, edgeCount, s, vertexCount, t);
	Tree(t);
	return;
}
void Initialization(Edge q[], int &edgeCount, SetNode* &s, int &vertexCount) {
	bool result;

	//DATA FROM IN CLASS GRAPH
	int X[12] = {3, 3, 3, 1, 1, 6, 6, 4, 4, 4, 2,  7};
	int Y[12] = {1, 4, 6, 2, 4, 4, 7, 2, 5, 7, 5,  5};
	int Z[12] = {4, 2, 5, 2, 1, 8, 1, 3, 7, 4, 10, 6};

	for (int i = 1; i < 12; i++) {
		int x = X[i];
		int y = Y[i];
		int z = Z[i];
		Insert(x, y, z, q, edgeCount);
		result = Insert(x, s, vertexCount);
		if (result == true) {
			SetNode* v = Find(x, s);
			MakeSet(v);
		}
		result = Insert(y, s, vertexCount);
		if (result == true) {
			SetNode* v = Find(y, s);
			MakeSet(v);
		}
	}
	return;
	

	/* //DATA FROM GRAPH.TXT
	int X[23] = { 0, 1,  1,  2,   2,  3,  6,  6,  5,  5,  8,  8,   6,  10,  14, 8,  11, 7,   11, 13, 13,  13, 9 };
	int Y[23] = { 0, 2,  3,  4,   5,  10, 3,  4,  7,  8,  4,  6,   10, 14,  12, 10, 8,  11,  12, 12, 7,   9,  7 };
	int Z[23] = { 0, 70, 61, 31, 110, 59, 88, 70, 30, 67, 65, 100, 65, 140, 85, 26, 12, 126, 19, 39, 105, 30, 74 };

	for (int i = 1; i < 23; i++) {
		int x = X[i];
		int y = Y[i];
		int z = Z[i];
		Insert(x, y, z, q, edgeCount);
		result = Insert(x, s, vertexCount);
		if (result == true) {
			SetNode* v = Find(x, s);
			MakeSet(v);
		}
		result = Insert(y, s, vertexCount);
		if (result == true) {
			SetNode* v = Find(y, s);
			MakeSet(v);
		}
	}
	return;
	*/
}
void Search(Edge q[], int &edgeCount, SetNode* &s, int vertexCount, Edge t[]) {
	while (t_array_pos < vertexCount - 1) {
		int t_size = t_array_pos;
		//e is the shortest edge in the priority queue
		Edge e = DeleteMin(q, edgeCount);
		SetNode* v1 = Find(e.vertex1, s);
		SetNode* v2 = Find(e.vertext2, s);
		if (v1->subset != v2->subset) {
			//e is added to the edges in the minimum spanning tree
			InsertUnsorted(e, t);
			//merge the two subsets in the AVL tree
			//move the smaller subset to the larger subset
			if (v1->subset->size >= v2->subset->size)
				Union(v1, v2, s);
			else
				Union(v2, v1, s);

		}
	}
}
void Tree(Edge t[]) {
	for (int i = 0; i < t_array_pos; i++) {
		cout << t[i].vertex1;
		cout << "--";
		cout << t[i].vertext2;
		cout << " (Length = ";
		cout << t[i].distance;
		cout << ")";
		cout << endl;
	}
}
//Binary Heap Insert
void Insert(int x, int y, int z, Edge q[], int &edgeCount) {
	//create new edge
	Edge e;
	e.vertex1 = x;
	e.vertext2 = y;
	e.distance = z;
	//increment edges in tree
	edgeCount++;
	//determine positioning of e in priority queue
	int i = edgeCount;
	//percolate upwards
	while ((i > 1) && (e.distance < (q[i / 2].distance))) {
		q[i] = q[i / 2];
		i = i / 2;
	}
	q[i] = e;
	return;
}
//AVL Tree Insert
bool Insert(int w, SetNode* &s, int &vertexCount) {
	bool result = false;
	if (s == NULL) {
		//insert new leafnode
		s = new SetNode;
		s->vertex = w;
		s->left = NULL;
		s->subset = NULL;
		s->right = NULL;
		vertexCount++;
		result = true;
	}
	else if (w < s->vertex) {
		//traverse to left subtree
		result = Insert(w, s->left, vertexCount);
		if (result == true) {
			if (Height(s->left) - Height(s->right) == 2) {
				if (w < s->left->vertex) {
					LL(s);
				}
				else {
					LR(s);
				}
			}
		}
	}
	else if (w > s->vertex) {
		//traverse to right subtree
		result = Insert(w, s->right, vertexCount);
		if (result == true) {
			if (Height(s->right) - Height(s->left) == 2) {
				if (w > s->right->vertex) {
					RR(s);
				}
				else {
					RL(s);
				}
			}
		}
	}
	else
		result = false;
	if (result == true) {
		s->height = (Max(Height(s->left), Height(s->right)) + 1);
	}
	return result;
}
void MakeSet(SetNode* &v) {
	v->subset = new SubsetNode;
	v->subset->size = 1;
	v->subset->firstVertex = new VertexNode;
	v->subset->firstVertex->vertex = v->vertex;
	v->subset->firstVertex->next = NULL;
}
Edge DeleteMin(Edge q[], int &edgeCount) {
	Edge e = q[1];
	//move last edge in tree to the root of q
	q[1] = q[edgeCount];
	edgeCount--;
	//percolate downwards
	Edge temp = q[1];
	int i = 1;
	while (i * 2 <= edgeCount) {
		int child = i * 2;
		if ((child != edgeCount) && (q[child + 1].distance < q[child].distance))
			child++;
		if (q[child].distance < temp.distance)
   			q[i] = q[child];
		else
			break;
		i = child;
	}
	q[i] = temp;
	return e;
}
void Union(SetNode* &vTo, SetNode* &vFrom, SetNode* &s) {
	vTo->subset->size = vTo->subset->size + vFrom->subset->size;
	VertexNode* v = vTo->subset->firstVertex;
	while (v->next != NULL) {
		v = v->next;
	}
	v->next = vFrom->subset->firstVertex;
	delete vFrom->subset;
	v = v->next;
	while (v != NULL) {
		vFrom = Find(v->vertex, s);
		vFrom->subset = vTo->subset;
		v = v->next;
	}
	return;
}
void InsertUnsorted(Edge e, Edge t[]) {
	t[t_array_pos] = e;
	t_array_pos++;
	return;
}
SetNode* Find(int vertex, SetNode* &s){
	if (s == NULL || vertex == s->vertex)
		return s;
	else if (vertex < s->vertex)
		return Find(vertex, s->left);
	else
		return Find(vertex, s->right);
}

//AVL Tree Balancing
void LL(SetNode* &s) {
	SetNode* q = s->left;
	s->left = q->right;
	q->right = s;
	s->height = Max((Height(s->left)), (Height(s->right) + 1));
	q->height = Max((Height(q->left)), (Height(q->right) + 1));
	s = q;
	return;
}
void LR(SetNode* &s) {
	RR(s->left);
	LL(s);
	return;
}
void RR(SetNode* &s) {
	SetNode* q = s->right;
	s->right = q->left;
	q->left = s;
	s->height = Max((Height(s->left)), (Height(s->right) + 1));
	q->height = Max((Height(q->left)), (Height(q->right) + 1));
	s = q;
	return;
}
void RL(SetNode* &s) {
	LL(s->right);
	RR(s);
}
int Height(SetNode* s) {
	if (s == NULL)
		return -1;
	else
		return s->height;
}
int Max(int height1, int height2) {
	if (height1 >= height2)
		return height1;
	else
		return height2;
}