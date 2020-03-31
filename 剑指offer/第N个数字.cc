int findNthDigit(int n) {
        long long digitNum = 1,base = 9;
        while(n > base*digitNum){
            n -= base*digitNum;
            digitNum++;
            base *= 10;
        }
        base = pow(10,digitNum-1);
        int pos = n % digitNum;
        if(pos == 0) pos = digitNum;
        if(pos == digitNum) base += n / digitNum -1;
        else base += n/digitNum;
        for(int i=pos;i<digitNum;i++) base/=10;
        return base%10;
    }
