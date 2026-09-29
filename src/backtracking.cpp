#include "backTracking.h"
//record when hit a wall, and then go back to the last position and try another direction
//complete answer at reaching
/* codigo de video
void dfs(int u, int target, vector<int> adj[], bool visited[],vector<int>& path){
    visited[u] = true;
    path.push_back(u);
    if(u == target){
        for(int v:path){
            cout<<v<<" ";
        }
        cout<<endl;
    }else{
        for(int v:adj[u]){
            if(!visited[v]){
                dfs(v,target,adj,visited,path);
            }
        }
    }
    visited[u] = false;
    path.pop_back();
}*/
//entendimiento del codigo por mi parte hasta el momento
BackTracking::BackTracking() {
bool visited[100]=false;
}
void BackTracking::dfs( ,Node v) {
    visit(v);
    marked[v] = true;
    for w in neighbors(v) do
        if(!visited(w)){
            dfs(w)
        }
}