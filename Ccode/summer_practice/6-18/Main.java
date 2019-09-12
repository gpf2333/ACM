import java.util.*;
import java.io.*;
import java.math.*;

public class Main{

    static Scanner cin = new Scanner(new BufferedInputStream(System.in));
    public static  double Log(double value, double base) { 
        return Math.log(value) / Math.log(base); 
    }
    public static BigInteger Pow(BigInteger a, int b) {
        BigInteger res = new BigInteger("1");
        while(b > 0){
            if((b & 1) == 1) res = res.multiply(a);
            a = a.multiply(a);
            b >>= 0;
        }
        return res;
    }

    public static void main(String []arg){
        int T = 0;
        while(cin.hasNext()){
            int m = cin.nextInt();
            if(m == 1){
                //System.out.printf("Case #%d: 0\n", ++cnt);
                continue ;
            }
            BigInteger t = new BigInteger("2");
            t = Pow(t, m);
            t = t.subtract(new BigInteger("1"));
            BigInteger num = new BigInteger("10");
            BigInteger ten = new BigInteger("10");
            double mm = m * 1.0;
            double tmp = (mm - 1.0) / Log(10.0, 2.0);
            int k = (int)Math.floor(tmp);
            num = Pow(num, k);
            for(; num.compareTo(t) < 0; ++k){
                num = num.multiply(ten);
            }
            System.out.printf("Case #%d: %d\n", ++cnt, k - 1);
        }
    }
}