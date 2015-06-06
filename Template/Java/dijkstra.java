import java.io.*;
import java.util.*;
import java.math.*;

//dijkstra
public class Main {
    final int maxn=1005;
    class Node implements Comparable{ //dij节点类,同时也是Edge类
    	public int v,val;
    	public Node(){}
    	public Node(int _v,int _val){
    		v=_v; val=_val;
    	}
    	public int compareTo(Object obj){
    		Node b=(Node)obj;
    		if( val<b.val ) return -1;
    		else if( val==b.val ) return 0;
    		return 1;
    	}
    }
    List<Node> adj[]; //lin jie biao
    public void dijkstra(int src,int[] dis){
    	PriorityQueue<Node> pq=new PriorityQueue<Node>(); //
    	final int inf=0x1fffffff;
    	Arrays.fill(dis, inf);
    	pq.add(new Node(src,0)); dis[src]=0;
    	while( !pq.isEmpty() ){
    		Node cur=pq.remove(),e;//edge
    		if( cur.val > dis[cur.v] ) continue;
    		for(int i=0;i<adj[cur.v].size();i++){
    			e=adj[cur.v].get(i);
    			if( dis[e.v]>dis[cur.v]+e.val ){
    				dis[e.v]=dis[cur.v]+e.val;
    				pq.add(new Node(e.v,dis[e.v]));
    			}
    		}
    	}
    }
    public void run(){
        Scanner cin=new Scanner(new BufferedInputStream(System.in));
        adj=new List[maxn];
        for(int i=0;i<adj.length;i++) adj[i]=new Vector<Node>();
        int[] dis=new int[maxn];
        //以上必须*****
        int n,m;
        while( cin.hasNext() ){
        	n=cin.nextInt(); m=cin.nextInt();
        	if( n==0 && m==0 ) break;
        	for(int i=1;i<=n;i++) adj[i].clear();
        	for(int i=1;i<=m;i++){
        		int u=cin.nextInt();
        		int v=cin.nextInt();
        		int val=cin.nextInt();
        		adj[u].add(new Node(v,val));
        		adj[v].add(new Node(u,val));
        	}
        	dijkstra(1,dis);
        	System.out.println(dis[n]);
        }
    }
    public static void main(String[] args){
    	try{
			//System.setIn(new FileInputStream("in.txt"));
			//System.setOut(new PrintStream(new FileOutputStream("out.txt")) );
		}catch(Exception e ){
			throw new RuntimeException();
		}
		Main a=new Main();
		a.run();
		System.out.flush();
		System.out.close();
    }
}
