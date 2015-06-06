import java
.io.*;
import java
.math.
BigInteger;
import java
.util.*;

// hdu 1402

class FFT {
    final double PI = Math.acos(-1.0);

    class Complex {
    public
        double r, i;
    public

        Complex(double r, double i) {
            this.r = r;
            this.i = i;
        }

    public

        Complex add(Complex c) {
            return new Complex(r + c.r, i + c.i);
        }

    public

        Complex sub(Complex c) {
            return new Complex(r - c.r, i - c.i);
        }

    public

        Complex mul(Complex c) {
            return new Complex(r * c.r - i * c.i, r * c.i + i * c.r);
        }
    }
            Complex[]

    fft(Complex[]
    a,
    double alpha
    ){ //折半的是系数a的长度
        int n = a.length;
        if (n == 1) return a;
        Complex[]
        a0 = new Complex[n / 2];
        for (int i = 0; i < n; i += 2) a0[i / 2] = new Complex(a[i].r, a[i].i);
        Complex[]
        a1 = new Complex[n / 2];
        for (int i = 1; i < n; i += 2) a1[i / 2] = new Complex(a[i].r, a[i].i);
        Complex[]
        y0 = fft(a0, alpha);
        Complex[]
        y1 = fft(a1, alpha);
        Complex wn = new Complex(Math.cos(alpha * 2 * PI / n), Math.sin(alpha * 2 * PI / n));
        Complex w = new Complex(1.0, 0), tmp;
        Complex[]
        y = new Complex[n];
        for (int i = 0; i < n / 2; i++) {
            tmp = w.mul(y1[i]);
            y[i] = y0[i].add(tmp);
            y[i + n / 2] = y0[i].sub(tmp);
            w = w.mul(wn);
        }
        return y;
    }
    Complex[]

    toComplex(int[] a, int s) {
        Complex[]
        ret = new Complex[s];
        for (int i = 0; i < ret.length; i++) {
            if (i < a.length) ret[i] = new Complex((double) a[i], 0.0);
            else ret[i] = new Complex(0.0, 0.0);
        }
        return ret;
    }

    long[]

    polyMultiply(int[] c0, int[] c1) {
        int s = 1;
        while (s < c0.length + c1.length) s <<= 1;
        Complex[]
        a0 = toComplex(c0, s);
        Complex[]
        a1 = toComplex(c1, s);
        Complex[]
        y0 = fft(a0, 1.0);
        Complex[]
        y1 = fft(a1, 1.0);
        for (int i = 0; i < y0.length; i++) y0[i] = y0[i].mul(y1[i]);

        //System.out.println("debug: y0*y1");
        //for(int i=0;i<y0.length;i++)
        //	System.out.printf("(%.5f, %.5f), ",y0[i].r, y0[i].i); System.out.println();

        Complex[]
        a = fft(y0, -1.0);
        for (int i = 0; i < a.length; i++) {
            a[i].r /= s;
            a[i].i /= s;
        }
        //System.out.println("debug: a");for(int i=0;i<s;i++) System.out.printf("%.7f ",a[i].r); System.out.println();
        long
        [] c = new long[s];
            for (int i = 0; i < c.length; i++) c[i] = (long) (a[i].r + 0.5);
            return c;
        }
}

class FastMul {
    final int SIZE = 4;  //fft使用了三角函数,是有精度误差的, 这个SIZE <=4 为好...5就wa了
    final int BASE = 10000;
    int[]
    toIntArray(String
    a){
        int
        [] ret = new int[a.length() / SIZE + 1];
            for (int e = 0, i = a.length() - SIZE; i > -SIZE; i -= SIZE) {
                int val = 0;
                for (int j = i; j < i + SIZE; j++) if (j >= 0) val = 10 * val + a.charAt(j) - '0';
                ret[e++] = val;
            }
            return ret;
        }
        public long
        [] mul(String
            a, String
            b){
            int
            [] c0 = toIntArray(a);
                int
                [] c1 = toIntArray(b);
                    FFT f = new FFT();
                    long
                    [] res = f.polyMultiply(c0, c1);
                        long c = 0;
                        for (int i = 0; i < res.length; i++) {
                            c += res[i];
                            res[i] = (int) (c % BASE);
                            c /= BASE;
                        }
                        int i = res.length - 1;
                        while (i > 0 && res[i] == 0) i--;
                        System.out.printf("%d", (int) res[i--]);
                        while (i >= 0) System.out.printf("%04d", (int) res[i--]);
                        System.out.println();
                        return res;
                    }
                }

                public class Main {

                void run() {
                    Scanner cin = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
                }

                void test() {
                    FastMul f = new FastMul();
                    Scanner cin = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
                    while (cin.hasNext()) {
                        String a, b;
                        a = cin.next();
                        b = cin.next();
                        f.mul(a, b);
                    }
                }

            public

                static void main(String[] args) {
                    Main a = new Main();
                    a.test();
                }
            }