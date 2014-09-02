#define maxn 2005
#define maxm 4000005

//����ͼǿ��ͨ����Tarjan�㷨,���һ���ڵ��Ǹ�,��ôDFN(����������)==Low(�ܴﵽ����ͱ��)
struct Tarjan{
	bool in[maxn];
	int DFN[maxn], Low[maxn], compo, deep; //��ȱ�����һ��ȫ����!!!! 
	//����0~N-1,�������label������,label[i]��ʾi����ڵ�����˭,�����������м�����base0
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
				Low[u] = min(Low[u], DFN[v]); //DFN[v]������****����Low[v]
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
}dir_tarjan;//**************ģ�����************************
/*
2-sat ���Ӷ�O(E)
��N����,ȡN/2��,����һ����������
����ѡa+n:
adj.insert(a+n,a); ����һ�¾�����
*/
struct TwoSAT{
	int N, label[maxn], _N, another[maxn]; //_N��ʾ�������м�����base0
	AdjList adj,_adj; //�������ͼ���ڽӱ� �������
	int *list, st[maxn],ind ; Edge *E;
	bool vst[maxn], temp[maxn];
	int _h(int t){ //�ɶԵ�����һ��
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
	void construct(bool *sel){ //����һ���,sel[i]=true��ʾ��i����ѡ����
		adj.init(); _adj.init();
		for(int i=0;i<N;i++){ //�ع�ͼ
			for(int p=list[i];p!=-1;p=E[p].next){
				int v=E[p].v;
				if( label[i] == label[v] ) continue;
				adj.insert(label[i], label[v]);
				_adj.insert(label[v], label[i]);
			}
		}
		ind=0; fill(vst,vst+_N+1,false);
		for(int i=0;i<_N;i++){ //��������
			if( vst[i]==false ) dfs_topo(i);
		}
		for(int i=0;i<N;i++){ //�������ͼ�����
			another[ label[i] ]=label[ _h(i) ];
			another[ label[_h(i)] ]=label[ i ];
		}
		fill(vst,vst+_N+1,false);
		fill(temp,temp+_N+1,false);
		for(int i=0;i<ind;i++){ //�Ե�����ѡ��
			if( vst[ st[i] ] ) continue;
			temp[ st[i] ]=true;
			if( !vst[another[ st[i] ]] )_delete( another[ st[i] ] );
		}
		for(int i=0;i<N;i++)  sel[i] = temp[ label[i] ]; //Ⱦɫ
	}
	void dfs_topo(int u){ //��������
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
}_2sat; //****************ģ�����*********************
