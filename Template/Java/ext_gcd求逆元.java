//java ext_gcd����Ԫ
	int[] ext_gcd(int a,int b){ //int[] -> (x,y,gcd(a,b) )
		if( b==0 ){
			int[] r=new int[3];
			r[0]=1; r[1]=0; r[2]=a;
			return r;
		}else{
			int[] r=ext_gcd(b,a%b);
			int tmp=r[0]; r[0]=r[1]; r[1]=tmp-a/b*r[1];
			return r;
		}
	}
	int get_ni(int a,int p){ //p is prime
		int[] r=ext_gcd(a,p); return r[0];
	}