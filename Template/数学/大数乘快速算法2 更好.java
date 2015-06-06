
import java.io.*;
import java.util.*;
import java.lang.reflect.Array;
import java.math.*;
//hdu 1402    http://acm.hdu.edu.cn/showproblem.php?pid=1402
/*
大数乘快速算法, Karatsuba algorithm:
计算a*b: 
a=x1*B^m + x0
b=y1*B^m + y0

z2=x1y1,  z0=x0y0
z1=(x0+x1)*(y0+y1) -z0-z2   //优化的关键所在!!

a*b=z2*B^(2m) + z1*B^m + z0
复杂度f(n)=3*f(n/2)+O(n)....f(n)=n^(log2(3))...
另外为了提高效率,计算过程中不进行进位处理,最后才进位...这个导致BASE的选取收到影响(不能太大,否则溢出)
*/
class FastMul2{ //使用long long
	final int SIZE=6;
	final int BASE=1000000; //10^SIZE
	long[] transform(String a, int s){
		long[] x=new long[s];
		for(int e=0, i=a.length()-SIZE;i>-SIZE;i-=SIZE){
			long val=0;
			for(int j=i;j<i+SIZE;j++) if( j>=0 ) val=10*val+a.charAt(j)-'0';
			x[e++]=val;
		}
		return x;
	}
	public long[] mul(String a,String b){// a="32" b="32" 返回 "1024"
		int s=1;
		while( s<Math.max(a.length()/SIZE + 1, b.length()/SIZE + 1)) s<<=1;
		long[] x=transform(a, s);
		long[] y=transform(b, s);
		long[] z=fastmul(x,y);
		long c=0;
		for(int i=0;i<z.length;i++){
			c+=z[i]; z[i]=c%BASE; c/=BASE;
		}
		print(z);
		return z;
	}
	//534253245 54325
	public void print(long[] z){
		int i=z.length-1;
		while( i>0 && z[i]==0 ) i--;
		System.out.printf("%d", (int)z[i--]);
		while( i>=0 ) System.out.printf("%06d", (int)z[i--]);
		System.out.println();
	}
	public long[] fastmul(long[] a, long[] b) { 
		if (a.length <=16) { //再分下去得不偿失
			long[] res=new long[a.length * 2];
			for(int i=0;i<a.length;i++) if( a[i]!=0 ){
				for(int j=0;j<b.length;j++) if( b[j]!=0 ){
					res[i+j]+=a[i]*b[j];
				}
			}
			return res;
		} else { 
			int k = a.length >> 1; 

			long[] x0=Arrays.copyOfRange(a, 0, k);
			long[] x1=Arrays.copyOfRange(a, k, k<<1);
			long[] y0=Arrays.copyOfRange(b, 0, k);
			long[] y1=Arrays.copyOfRange(b, k, k<<1);

			long[] z0 = fastmul(x0, y0); 
			long[] z2 = fastmul(x1, y1); 
			
			for (int i = 0; i < k; ++i) x0[i] += x1[i]; 
			for (int i = 0; i < k; ++i) y0[i] += y1[i]; 
			
			long[] z1 = fastmul(x0, y0); 
			for (int i = 0; i < 2 * k; ++i) z1[i] -= (z0[i] + z2[i]); 
			
			long[] res = new long[4 * k]; 
			for (int i = 0; i < 2 * k; ++i) res[i] += z0[i]; 
			for (int i = 0; i < 2 * k; ++i) res[i + k] += z1[i];
			for (int i = 0; i < 2 * k; ++i) res[i + 2 * k] += z2[i];
			return res; 
		} 
	} 
}


public class Main {
	public static void main(String[] args){
		FastMul2 f=new FastMul2();
		Scanner cin=new Scanner(new BufferedReader( new InputStreamReader(System.in) ));
		while( cin.hasNext() ){
			String a,b;
			a=cin.next();
			b=cin.next();
			f.mul(a, b);
		}
	}
}

