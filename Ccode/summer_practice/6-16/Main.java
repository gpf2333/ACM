import java.util.*;
import java.io.*;
import java.math.*;

public class Main{

    static Scanner cin = new Scanner(new BufferedInputStream(System.in));
    public static void main(String []arg){
        int n;
        n = cin.nextInt();
        String str = new String();
        str = cin.next();
        int mid = n / 2;
        BigInteger ans = new BigInteger(str);
        for(int i = 0; i < mid; ++i){
            if(mid - i < 0) continue;
            if(str.charAt(mid - i) == '0') continue ;
            String b = str.substring(mid - i, n);
            String a = str.substring(0, mid - i);
            BigInteger aa = new BigInteger(a);
            BigInteger c = aa.add(new BigInteger(b));
            if (ans.compareTo(c) > 0){
                ans = c;
            }
            break ;
        }
        for(int i = 1; i <= mid; ++i){
            if(mid + i >= n) continue ;
            if(str.charAt(mid + i) == '0') continue ;
            String b = str.substring(mid + i, n);
            String a = str.substring(0, mid + i);
            BigInteger aa = new BigInteger(a);
            BigInteger c = aa.add(new BigInteger(b));
            if (ans.compareTo(c) > 0){
                ans = c;
            }
            break ;
        }
        System.out.println(ans);
    }
}