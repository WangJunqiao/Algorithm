#define maxn 2005
#define maxm 4000005

//有向图强连通分量Tarjan算法,如果一个节点是根,那么DFN(深度优先序号)==Low(能达到的最低标号)
struct Tarjan{
	bool in[maxn];
	int DFN[maxn], Low[maxn], compo, deep; //深度必须是一个全局量!!!! 
	//处理0~N-1,结果存在label数组里,label[i]表示i这个节点属于谁,返回收缩后还有几个点base0
	int DirGraphShrink(int N, vector<int> *adj, vector<int> &label){
		memset(in, false, sizeof(in)); 
		memset(DFN, 0, sizeof(DFN));
		compo = deep = 0;
		label = vector<int>(N, 0);
		stack<int> st;
		for (int i = 0; i < N; i ++) {
			if (DFN[i] == 0) {
				_tarjan(i, st, adj, label);
			}
		}
		return compo;
	}
	void _tarjan(int u, stack<int> &st, vector<int> *adj, vector<int> &label){
		DFN[u] = Low[u] = ++ deep;
		st.push_back(u); 
		in[u] = true;
		for (int i = 0; i < adj[u].size(); i ++) {
			int v = adj[u][i];
			if (DFN[v] == 0) {
				_tarjan(v, st, adj, label);
				Low[u] = min(Low[u], Low[v]);
			} else if (in[v]) {
				Low[u] = min(Low[u], DFN[v]); //DFN[v]必须是****不是Low[v]
			}
		}
		if (Low[u] == DFN[u]) {
			while (true) {
				int v = st.top();
				st.pop();
				label[v] = compo;  
				in[v]=false;
				if (v == u) {
					break;
				}
			}
			compo++;
		}
	}
}dir_tarjan;//**************模板结束************************
/*
2-sat 复杂度O(E)
共N个人,取N/2个,满足一定限制条件
不能选a+n:
adj.insert(a+n,a); 这样一下就行了
*/
struct TwoSAT{
	int N, label[maxn], _N, another[maxn]; //_N表示收缩后还有几个点base0
	AdjList adj,_adj; //收缩后的图的邻接表 和逆向表
	int *list, st[maxn],ind ; Edge *E;
	bool vst[maxn], temp[maxn];
	int _h(int t){ //成对的另外一个
		if( t>=(N>>1) ) return t-(N>>1);
		else return t+(N>>1);
	}
	bool twoSAT(int N,int *list, Edge *E){
		this->N=N; this->list=list; this->E=E;
		_N=dir_tarjan.DirGraphShrink(N,list,E,label);
		for(int i=0;i<N;i++)
			if( label[i] == label[ _h(i) ] ) return false;
		return true;
	}
	void construct(bool *sel){ //构造一组解,sel[i]=true表示第i个被选上了
		adj.init(); _adj.init();
		for(int i=0;i<N;i++){ //重构图
			for(int p=list[i];p!=-1;p=E[p].next){
				int v=E[p].v;
				if( label[i] == label[v] ) continue;
				adj.insert(label[i], label[v]);
				_adj.insert(label[v], label[i]);
			}
		}
		ind=0; fill(vst,vst+_N+1,false);
		for(int i=0;i<_N;i++){ //拓扑排序
			if( vst[i]==false ) dfs_topo(i);
		}
		for(int i=0;i<N;i++){ //收缩后的图结对子
			another[ label[i] ]=label[ _h(i) ];
			another[ label[_h(i)] ]=label[ i ];
		}
		fill(vst,vst+_N+1,false);
		fill(temp,temp+_N+1,false);
		for(int i=0;i<ind;i++){ //自底向上选择
			if( vst[ st[i] ] ) continue;
			temp[ st[i] ]=true;
			if( !vst[another[ st[i] ]] )_delete( another[ st[i] ] );
		}
		for(int i=0;i<N;i++)  sel[i] = temp[ label[i] ]; //染色
	}
	void dfs_topo(int u){ //拓扑排序
		vst[u]=true;
		for(int p=adj.list[u];p!=-1;p=E[p].next)
			if( vst[ E[p].v ]==false ) dfs_topo( E[p].v );
		st[ind++]=u;
	}
	void _delete(int u){
		vst[u]=true;
		for(int p=_adj.list[u];p!=-1;p=E[p].next)
			if( vst[ E[p].v ]==false ) _delete( E[p].v );
	}
}_2sat; //****************模板结束*********************
