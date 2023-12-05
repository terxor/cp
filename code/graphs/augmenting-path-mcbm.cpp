/* Augmenting path algorithm for max cardinality bipartite matching */
/* Notes:
In augExists(u):
- u belongs to leftSet
- match[v] = -1 implies vertex v is unmatched
- match[v] as well as visited[v] make sense only for vertices in rightSet 
- we don't need to check if match[v] = u because if that is the case, then visited[v] = 1 (and we came here by call augExists(match[v]))

Also:
- adj must be of size V, vertices are numbered 0...V-1 
- Vertex numbering: 0...(leftSet.size-1), ... (rightSet.size + leftSet.size-1). Construct adjacency list accordingly 
- Adjacency list contains directed edges (from leftSet to rightSet) 
- All vertices in leftSet are unmatched initially. Calling augExists on an
unmatched vertex will not affect any other unmatched vertices in leftSet
*/

#include <bits\stdc++.h>
using namespace std;

vector<int> match, visited, leftSet, rightSet;
vector<vector<int>> adj;
int numVertices;

bool augExists (int u) {
	for (int v : adj[u]) if (!visited[v]) { 
		visited[v] = true;
		if (match[v] == -1 || augExists(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int maxMatching () {
	match.assign(numVertices, -1); 
	int ans = 0;
	for (int i = 0; i < (int)leftSet.size(); i++) {
		visited.assign(numVertices, 0);
		ans += augExists(i);
	}
	return ans;
}

int main() {

	leftSet.push_back(0);
	leftSet.push_back(1);
	rightSet.push_back(2);
	rightSet.push_back(3);
	numVertices = (int)leftSet.size() + (int)rightSet.size();

	adj.assign(numVertices, vector<int>(0));
	adj[0].push_back(2);
	adj[0].push_back(3);
	adj[1].push_back(2);
	adj[1].push_back(3);
	
	printf("%d\n", maxMatching());	
}
