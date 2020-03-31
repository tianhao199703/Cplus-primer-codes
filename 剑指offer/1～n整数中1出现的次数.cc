int countDigitOne(int n) {
        int ones = 0;
        for (long long m = 1; m <= n; m *= 10) {
            int a = n/m, b = n%m;
            //a%10是代表当前处理的位，需要计算当前位有多少1
            if(a%10 == 0){//当前位为0，
                ones += (a / 10) * m;//0-a/10-1的当前位有1
            }
            else if(a%10 == 1){//0-a/10的当前位有1，且a/10不全，为b+1
                ones += a / 10 * m + b + 1;
            }
            else ones += (a / 10) * m + m;//0-a/10的当前位有1
        }
        return ones;
    }
