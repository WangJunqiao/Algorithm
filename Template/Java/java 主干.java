import java.io.*;
import java.math.BigInteger;
import java.util.*;
import java.util.Map.Entry;


public class Main {

	void run() {
		 
	}

	public static void main(String[] args) throws Exception {
		try {
			reader = new BufferedReader(new InputStreamReader(System.in));
			out = new PrintWriter(System.out);

			Main instance = new Main();
			instance.run();

			out.close();
		} catch (Exception e) {
			throw new RuntimeException();
		}
	}
	public static <T> void print(T s){
		out.print(s.toString() );
	}
	public static <T> void println(T s){
		out.println(s.toString() );
	}

	static int nextInt() {
		return Integer.parseInt(nextToken());
	}

	static char nextChar() {
		return nextToken().charAt(0);
	}

	static long nextLong() {
		return Long.parseLong(nextToken());
	}

	static String next() {
		return nextToken();
	}

	static BigInteger nextBigInteger() {
		return new BigInteger(nextToken());
	}

	static BufferedReader reader;
	static StringTokenizer toker;
	static PrintWriter out;

	static String nextToken() {
		try {
			while (toker == null || !toker.hasMoreTokens()) {
				String line = reader.readLine();
				if (line == null)
					return null;
				toker = new StringTokenizer(line);
			}
			return toker.nextToken();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return "";
	}

}

class Tool {
	/**
	 * 倒置数组中的元素
	 * @param array
	 */
	public static <T> void reverse(T[] array){
		T tmp;
		for(int i=0, j=array.length-1; i<j ;i++, j--){
			tmp=array[i];
			array[i]=array[j];
			array[j]=tmp;
		}
	}
}

class MapTest{
	public static void run(){
		System.out.println("MapTest run:");
		
		Map<String, Integer> mp=new TreeMap<String, Integer>();
		mp.put("zjut_DD", 44);
		mp.put("dd", 55);
		mp.put("jdk", 3425);

		Iterator<Entry<String, Integer>> iterator=mp.entrySet().iterator();
		while( iterator.hasNext() ){
			Entry<String, Integer> entry=iterator.next();
			System.out.println( entry.getKey() + "  ->  "+entry.getValue() );
		}
	}
}

class SetTest{
	public static void run(){
		System.out.println("SetTest run:");
		
		Set<String> st=new HashSet<String>();
		st.add("zjut_DD");
		st.add("dd");
		st.add("std");
		Iterator<String> iterator=st.iterator();
		while( iterator.hasNext() ){
			String string=iterator.next();
			System.out.println(string);
		}
	}
}
