
import java.io.*;
import java.util.*;

public class CreateData {
	void run(){
		try{
			Random rand=new Random();
			PrintWriter out=new PrintWriter(new File("in.txt"));
			int cas=10000;
			for(int i=1;i<=cas;i++){
				int n=7,m=9;
				out.println(n+" "+m);
				for(int j=1;j<=m;j++){
					int a=rand.nextInt(n)+1;
					int b=rand.nextInt(n)+1;
					out.println(a+" "+b+" "+rand.nextInt(1000));
				}
			}
			out.close();
		}catch (IOException e){
			throw new RuntimeException();
		}
	}
	public static void main(String[] args){
		CreateData a=new CreateData();
		a.run();
	}
}
