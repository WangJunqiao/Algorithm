
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

递归优化的方法很好
*/
class FastMul{  //略慢...使用int
	final int SIZE=2;
	final int BASE=100; //10^SIZE
	int[] transform(String a, int s){
		int[] x=new int[s];
		for(int e=0, i=a.length()-SIZE;i>-SIZE;i-=SIZE){
			int val=0;
			for(int j=i;j<i+SIZE;j++) if( j>=0 ) val=10*val+a.charAt(j)-'0';
			x[e++]=val;
		}
		return x;
	}
	public int[] mul(String a,String b){// a="32" b="32" 返回 "1024"
		int s=1;
		while( s<Math.max(a.length()/SIZE + 1, b.length()/SIZE + 1)) s<<=1;
		int[] x=transform(a, s);
		int[] y=transform(b, s);
		int[] z=fastmul(x,y);
		for(int i=0,c=0;i<z.length;i++){
			c+=z[i]; z[i]=c%BASE; c/=BASE;
		}
		print(z);
		return z;
	}
	public void print(int[] z){
		int i=z.length-1;
		while( i>0 && z[i]==0 ) i--;
		System.out.printf("%d", z[i--]);
		while( i>=0 ) System.out.printf("%02d", z[i--]);
		System.out.println();
	}
	public int[] fastmul(int[] a, int[] b) { 
		if (allZero(a) || allZero(b)) { 
			return new int[a.length + b.length]; 
		} 
		if (a.length < 30){  //调节算法常数, 到地下很短的再分治就效率不高了...
			return slowmul(a, b); 
		} else { 
			
			int k = a.length / 2; 

			int[] x0=Arrays.copyOfRange(a, 0, k);
			int[] x1=Arrays.copyOfRange(a, k, k<<1);

			int[] y0=Arrays.copyOfRange(b, 0, k);
			int[] y1=Arrays.copyOfRange(b, k, k<<1);

			int[] z0 = fastmul(x0, y0); 
			int[] z2 = fastmul(x1, y1); 
			
			int[] x0_1 = new int[k]; 
			for (int i = 0; i < k; ++i) x0_1[i] = x0[i] + x1[i]; 
			
			int[] y0_1 = new int[k]; 
			for (int i = 0; i < k; ++i) y0_1[i] = y0[i] + y1[i]; 
			
			int[] tmp = fastmul(x0_1, y0_1); 
			for (int i = 0; i < 2 * k; ++i) tmp[i] -= (z0[i] + z2[i]); 
			
			int[] res = new int[4 * k]; 
			for (int i = 0; i < 2 * k; ++i) res[i] += z0[i]; 
			for (int i = 0; i < 2 * k; ++i) res[i + k] += tmp[i]; 
			for (int i = 0; i < 2 * k; ++i) res[i + 2 * k] += z2[i]; 
			return res; 
		} 
	} 

	boolean allZero(int[] a) { 
		for (int i = 0; i < a.length; ++i) 
			if (a[i] != 0) 
				return false; 
		return true; 
	} 

	int[] slowmul(int[] a, int[] b) { 
		int[] c = new int[a.length + b.length]; 
		for (int i = 0; i < a.length; ++i) 
			if (a[i] != 0) 
				for (int j = 0; j < b.length; j += 1) 
					if (b[j] != 0) 
						c[i + j] += a[i] * b[j]; 
		return c; 
	} 
}


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
	public void print(long[] z){
		int i=z.length-1;
		while( i>0 && z[i]==0 ) i--;
		System.out.printf("%d", (int)z[i--]);
		while( i>=0 ) System.out.printf("%06d", (int)z[i--]);
		System.out.println();
	}
	public long[] fastmul(long[] a, long[] b) { 
		if (allZero(a) || allZero(b)) { 
			return new long[a.length + b.length]; 
		} 
		
		if (a.length < 30) { //这个系数....非常重要!!!!
			return slowmul(a, b); 
		} else { 
			int k = a.length / 2; 

			long[] x0=Arrays.copyOfRange(a, 0, k);
			long[] x1=Arrays.copyOfRange(a, k, k<<1);

			long[] y0=Arrays.copyOfRange(b, 0, k);
			long[] y1=Arrays.copyOfRange(b, k, k<<1);

			long[] z0 = fastmul(x0, y0); 
			long[] z2 = fastmul(x1, y1); 
			
			long[] x0_1 = new long[k]; 
			for (int i = 0; i < k; ++i) x0_1[i] = x0[i] + x1[i]; 
			
			long[] y0_1 = new long[k]; 
			for (int i = 0; i < k; ++i) y0_1[i] = y0[i] + y1[i]; 
			
			long[] tmp = fastmul(x0_1, y0_1); 
			for (int i = 0; i < 2 * k; ++i) tmp[i] -= (z0[i] + z2[i]); 
			
			long[] res = new long[4 * k]; 
			for (int i = 0; i < 2 * k; ++i) res[i] += z0[i]; 
			for (int i = 0; i < 2 * k; ++i) res[i + k] += tmp[i]; 
			for (int i = 0; i < 2 * k; ++i) res[i + 2 * k] += z2[i]; 
			return res; 
		} 
	} 
	boolean allZero(long[] a) { 
		for (int i = 0; i < a.length; ++i) 
			if (a[i] != 0) 
				return false; 
		return true; 
	} 

	long[] slowmul(long[] a, long[] b) { 
		long[] c = new long[a.length + b.length]; 
		for (int i = 0; i < a.length; ++i) 
			if (a[i] != 0) 
				for (int j = 0; j < b.length; j += 1) 
					if (b[j] != 0) 
						c[i + j] += a[i] * b[j]; 
		return c; 
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

