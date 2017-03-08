/*
Assignment 3, Question 1 "Edmonds-Carp Max Flow Algorithm"
Austin McPhail
200341412
*/

#include <iostream>
#include <climits>

using namespace std;

//Data Structures
int r[8][8]; //residual capacity network
int p[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; //current path returned from the breadth first search
bool v[8]; //indicates whether a vertex has been visited on the current path
int q[8]; //used to enforce breadth first order
int n = 8; //verticies

void EdmondsCarpMaxFlow(int r[][8], int n, int source, int sink);
void Initialization(int r[][8], int n);
int Search(int r[][8], int n, int source, int sink);
int Min(int x, int y);
bool BreadthFirstSearch(int r[][8], int p[], int n, int source, int sink);
void Paths(int r[][8], int n, int source, int sink, int maxFlow);

int main() {
	EdmondsCarpMaxFlow(r, n, 1, 8);
	cout << endl << endl;
	//Print out r array
	cout << "  |  1  2  3  4  5  6  7  8" << endl;
	cout << "__|________________________" << endl;
	for (int i = 0; i < 8; i++) {
		cout << (i + 1) << " |";
		for (int j = 0; j < 8; j++) {
			if (r[i][j] == -1 || r[i][j] > 9)
				cout << " " << r[i][j];
			else
				cout << "  " << r[i][j];
		}
		cout << endl;
	}
}

void EdmondsCarpMaxFlow(int r[][8], int n, int source, int sink) {
	Initialization(r, n);
	int maxFlow = Search(r, n, source-1, sink-1);
	Paths(r, n, source-1, sink-1, maxFlow);
	return;
}

void Initialization(int r[][8], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			r[i][j] = -1;
		}
	}

	//Print out r array
	cout << "r before adding values: " << endl;
	cout << "  |  1  2  3  4  5  6  7  8" << endl;
	cout << "__|________________________" << endl;
	for (int i = 0; i < 8; i++) {
		cout << (i + 1) << " |";
		for (int j = 0; j < 8; j++) {
			if (r[i][j] == -1 || r[i][j] > 9)
				cout << " " << r[i][j];
			else
				cout << "  " << r[i][j];
		}
		cout << endl;
	}

	int I[13] = {1, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6, 7, 7};
	int J[13] = {2, 3, 4, 5, 5, 6, 5, 7, 6, 8, 8, 6, 8};
	int C[13] = {1, 2, 4, 1, 1, 1, 2, 2, 2, 2, 4, 4, 1};
	for (int x = 0; x < 13; x++) {
		int i = I[x];
		int j = J[x];
		int c = C[x];

		r[i-1][j-1] = c;
		r[j-1][i-1] = 0;
	}
	//Print out r array
	cout << "r after adding values: " << endl;
	cout << "  |  1  2  3  4  5  6  7  8" << endl;
	cout << "__|________________________" << endl;
	for (int i = 0; i < 8; i++) {
		cout << (i + 1) << " |";
		for (int j = 0; j < 8; j++) {
			if (r[i][j] == -1 || r[i][j] > 9)
				cout << " " << r[i][j];
			else
				cout << "  " << r[i][j];
		}
		cout << endl;
	}
}

int Search(int r[][8], int n, int source, int sink) {
	int maxFlow = 0;
	bool pathFound = BreadthFirstSearch(r, p, n, source, sink);

	//Check pathFound
	if (pathFound)
		cout << "true" << endl;
	else
		cout << "false" << endl;
	//-----------------

	while (pathFound) {
		int pathFlow = INT_MAX;
		int j = sink;
		while (j != source) {
			int i = p[j];
			pathFlow = Min(pathFlow, r[i][j]);
			j = i;
		}
		j = sink;
		while (j != source) {
			int i = p[j];
			r[i][j] = r[i][j] - pathFlow;
			r[j][i] = r[j][i] + pathFlow;
			j = i;
		}
		maxFlow = maxFlow + pathFlow;
		pathFound = BreadthFirstSearch(r, p, n, source, sink);

		//Print out r array
		cout << "  |  1  2  3  4  5  6  7  8" << endl;
		cout << "__|________________________" << endl;
		for (int i = 0; i < 8; i++) {
			cout << (i + 1) << " |";
			for (int j = 0; j < 8; j++) {
				if (r[i][j] == -1 || r[i][j] > 9)
					cout << " " << r[i][j];
				else
					cout << "  " << r[i][j];
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	return maxFlow;
}

int Min(int x, int y) {
	if (x < y)
		return x;
	else
		return y;
}

bool BreadthFirstSearch(int r[][8], int p[], int n, int source, int sink) {
	for (int i = 0; i < n; i++) {
		v[i] = false;
	}
	int head = 0;
	int tail = 0;
	q[tail] = source;
	tail++;
	v[source] = true;
	while (head != tail) {
		int i = q[head];
		head++;
		for (int j = 0; j < n; j++) {
			if ((v[j] == false) && (r[i][j] > 0)) {
				q[tail] = j;
				tail++;
				p[j] = i;
				v[j] = true;
			}
		}
	}
	return v[sink];
}

void Paths(int r[][8], int n, int source, int sink, int maxFlow) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (r[i][j] != -1) {
				cout << i+1;
				cout << "-(";
				cout << r[i][j];
				cout << ")-";
				cout << j+1;
				cout << endl;
			}
		}
	}
	cout << "MAXFLOW = " << maxFlow << endl;
	return;
}