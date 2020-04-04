int lastRemaining(int n, int m) {
        int res = 0;
        for (int i = 2; i != n + 1; i++)
            res = (m + res) % i;
        return res;
    }
