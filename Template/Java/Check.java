import java.io.BufferedInputStream;
import java.util.Scanner;

import java.io.*;

public class Check {
	void run(){
		try{
			Scanner cin1=new Scanner(new FileInputStream("out.txt"));
			Scanner cin2=new Scanner(new FileInputStream("out2.txt"));
			String line1,line2;
			int num=0,fail=0;
			while( cin1.hasNextLine() ){
				line1=cin1.nextLine();
				line2=cin2.nextLine();
				num++;
				if( line1.compareTo(line2)!=0){
					System.out.println(num+" ÐÐ²»Í¬!!\n"+line1+"\n"+line2);
					fail=1;
					break;
				}
			}
			if( fail==0 ) System.out.println("same!");
		}catch(Exception e){
			throw new RuntimeException() ;
		}
	}
	public static void main(String[] args){
		Check a=new Check();
		a.run();
	}
}
