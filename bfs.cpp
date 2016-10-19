#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int n,e;
int start;
int len=0;
int parent(int index){
    return (index-1)/2;
}
int right_child(int index){
    return (2*index+2);
}
int left_child(int index){
    return (2*index+1);
}
void exchange(int dist[][2],int first,int second,int pos[]){
    int temp1=dist[first][0];
    int temp2=dist[first][1];
    pos[dist[first][1]]=second;
    pos[dist[second][1]]=first;
    dist[first][0]=dist[second][0];
    dist[first][1]=dist[second][1];
    dist[second][0]=temp1;
    dist[second][1]=temp2;

}
void heap_insert(int dist[][2],int index,int pos[]){
    while (index>0 && dist[parent(index)][0]>dist[index][0]){
        int parente=parent(index);
        exchange(dist,index,parente,pos);
        index=parente;
    }
}
int extract_min(int dist[][2],int pos[]){
    len--;
    int mini=dist[0][1];
    dist[0][0]=dist[len][0];
    dist[0][1]=dist[len][1];
    pos[dist[len][1]]=0;          // changing position of vertex in heap...
    int index=0;
    while (index<len){
        int smallest=index;
        int left=left_child(index);
        int right=right_child(index);
        if (left<len && dist[left][0]<dist[smallest][0]){
            smallest=left;
        }
        if (right<len && dist[right][0]<dist[smallest][0]){
            smallest=right;
        }
        if (smallest!=index){
            exchange(dist,index,smallest,pos);
            index=smallest;
        }
        else {
            break;
        }
    }
    return mini;
}
void djistkra(vector<vector<int>> &indice,int dist[][2],bool visited[]){
    int pos[n+1];
    visited [start]=true;
    for (int i=1;i<=n;i++){
        pos[i]=-1;
        if (indice[start][i]>0){
            dist[len][0]=indice[start][i];
            dist[len][1]=i;
            pos[i]=len;
            heap_insert(dist,len,pos);
            len++;
        }
    }
    start=0;
    while (len!=0){
        start+=dist[0][0];
        int u=extract_min(dist,pos);

        visited[u]=true;
        for (int it=1;it<=n;it++){
            if (indice[u][it]>0 && !visited[it]){   // to see if edge u is connected with it && it is already not visited
                if (pos[it]>=0){           // if it was accounted for edge b/w source..

                    dist[pos[it]][0]=min(dist[pos[it]][0],indice[u][it]);
                    heap_insert(dist,pos[it],pos);
                }
                else {

                    dist[len][0]=indice[u][it];
                    dist[len][1]=it;
                    pos[it]=len;
                    heap_insert(dist,len,pos);
                    len++;
                }
            }
        }
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        fstream myfile;
        myfile.open("my.txt");
        myfile>>n>>e;
        bool visited[n+1]={false};  // for storing the visited node
        vector<vector<int>>indice(
            n+1,
            vector<int>(n+1,-1));
        for (int i=0;i<e;i++){
            int var1,var2,d;
            myfile>>var1>>var2>>d;
            if (indice[var1][var2]>0){
                indice[var1][var2]=min(d,indice[var1][var2]);
                indice[var2][var1]=indice[var1][var2];
            }
            else{
                indice[var1][var2]=d;
                indice[var2][var1]=d;
            }
        }

        myfile>>start;

        int dist[n+1][2];
        djistkra(indice,dist,visited);
        cout<<start;
    return 0;
}
