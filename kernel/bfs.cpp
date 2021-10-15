#include <cassert>
#include <queue>
#include <iostream>
#include "csr.h"

using std::cout;
using std::endl;

void run_bfs(graph_t& g, vid_t root)
{
    csr_t* csr = &g.csr;

    //TODO
    cout << "root = " << root << endl;
    int frontier[1024]={0};
    int next[1024]={0};
    int parents[1024];
    frontier[root]=1;
    int flag=0;
    int cnt=csr->get_vcount();

    for(int i=0; i<cnt; i++){
    	parents[i]=-1;
    }

    while (1){
    	for (int n=0; n<cnt; n++){

	    	if (frontier[n]==1){
	    		flag=1;

		        for (int i=0; i<cnt; i++){
		            if (parents[i]==-1){
		                for(int j=csr->offset[i]; j<csr->offset[i+1];j++){
		                	if (frontier[csr->nebrs[j]]==1){
		                        parents[i]=csr->nebrs[j];
		                        next[i]=1;
		                        break;
		                    }
		                }
		            }
		        }

			    for(int i=0; i<cnt;i++){
			    	if (frontier[i]==1)
			    		frontier[i]=0;
			    	if (next[i]==1){
			    		frontier[i]=1;
			    		next[i]=0;
			    	}			    		
			    }
			    break;

		    }
		}
		if(flag==0)
			break;
		flag=0;
	}

	queue<int> q;
	queue<int> nq;
	q.push(root);
	int level=0;
	int visited[1024]={0};
	visited[root]=1;

	while (!q.empty()){
		cout<<"----------------------------------------------------------"<<endl;
		cout<<"level "<<level<<":"<<q.size()<<" nodes"<<endl;
		while (!q.empty()){
			int x=q.front();
			printf("%d ", x);
			for (int i=0;i<cnt;i++){
				if (parents[i]==x && visited[i]==0){
					nq.push(i);
					visited[i]=1;
				}
			}
			q.pop();
		}

		while (!nq.empty()){
			q.push(nq.front());	
			nq.pop();		
		}
		level++;
		cout<<endl;
	}   
}

