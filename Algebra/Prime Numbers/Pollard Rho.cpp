namespace PollardRho
{
    LL mult(LL a, LL b, LL MOD)
    {
        LL res = 0;
        while(b)
        {
            if(b & 1)
                res = (res + a) % MOD;
            a = (a + a) % MOD;
            b >>= 1;
        }
        return res;
    }

    LL f(LL x, LL c, LL MOD)
    {
        return (mult(x, x, MOD) + c) % MOD;
    }

    LL PollardRho(LL n, LL x0, LL c)
    {
        LL x = x0, y = x0, g = 1;
        while(g == 1)
        {
            x = f(x, c, n);
            y = f(y, c, n);
            y = f(y, c, n);
            g = __gcd(abs(x - y), n);
        }

        return g;
    }
}