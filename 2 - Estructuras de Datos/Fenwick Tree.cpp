int ft[ MAXN ];

void update( int i , int val )
{
    for (; i <= n; i += i & (-i) ) ft[ i ] += val;
}

int query( int i )
{
    int s = 0;
    for (; i > 0; i -= i & (-i) ) s += ft[ i ];
    return s;
}
