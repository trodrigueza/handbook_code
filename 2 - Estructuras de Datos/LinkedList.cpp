// linked list
vector<int> nxt, prv;
vector<int> v;

int del( int idx )
{
    int mn = min( v[ nxt[ idx ] ] , v[ prv[ idx ] ] );
    prv[ nxt[ idx ] ] = prv[ idx ];
    nxt[ prv[ idx ] ] = nxt[ idx ];
    return mn;
}
