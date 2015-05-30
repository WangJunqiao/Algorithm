//哈希表，quick and dirty solution
const int mod=99997;   //映射范围
const int maxn=200000; //节点总数

template<typename TK, typename TV, int (*h)(const TK &tk)> //h函数返回下标%mod
struct HashMap{
	struct Entry{ TK k; TV v; int x;  } dd[maxn];
	int l[mod], e;
	//
	HashMap() { clear(); }
	void clear(){ e = 0; memset(l,-1,sizeof(l)); }
	int find(TK k){   //查找下标,没有返回-1
		int i = h(k);
		for(int p = l[i];p >= 0;p = dd[p].x)
			if(dd[p].k == k) return p;
		return -1;
	}
	void insert(TK k, TV v){ //插入
		int i = h(k);
		dd[e].k=k; dd[e].v=v; dd[e].x=l[i]; l[i]=e++;
	}
	TV& operator[] (TK k){
		int t=find(k);
		if( t==-1 ) { insert(k,TV()); return dd[e-1].v;}
		else return dd[t].v;
	}
	int size() { return e; }
};//
int h(const int &a){ //需要修改
	return (a%mod+mod)%mod;
}
HashMap<int, int, h> mp;