// Código handbook -------------------------------------------------------------------
// 0 indexed Segment, remember to set the default value to return in case
// of not range needed when query
struct Node {
};

int n;
Node sgt[800000];
vector<Node> val;

Node merge(const Node x, const Node y) {
}

void build(int node = 1, int l = 0, int r = n - 1) {
    if (l == r) sgt[ node ] = val[ l ];
    else {
        int mid = l + ( r-l ) / 2;
        build( node*2 , l , mid );
        build( node*2+1 , mid+1 , r );
        sgt[ node ] = merge( sgt[ node*2 ] , sgt[ node*2+1 ] );
    }
}

Node update(int idx, Node val, int node = 1, int start = 0, int end = n-1) {
    if (start == end) {
        sgt[ node ] = val;
        return sgt[ node ];
    }
    int mid =  start + ( end - start ) / 2;
    if ( start <= idx && idx <= mid ) update( idx , val , 2*node , start , mid );
    else update( idx , val , 2*node+1 , mid+1 , end );
    sgt[ node ] = merge( sgt[ 2*node ] , sgt[ 2*node+1 ] );
    return sgt[ node ];
}

Node query(int a, int b, int node = 1, int l = 0, int r = n - 1) {
    if (l > b || r < a) return Node{};
    if (l >= a && r <= b) return sgt[ node ];
    int mid = (l + r) / 2;
    return merge( query( a , b , node * 2 , l , mid ) , 
            query( a , b , node * 2 + 1 , mid+1 , r ) );
}

// Encuentra el k-ésimo elemento para segment binario vivo/muerto
int kth(int k, int node = 1, int l = 0, int r = m - 1) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (sgt[node*2].number > k) {
        return kth(k, node*2, l, mid);
    } else {
        return kth(k - sgt[node*2].number, node*2+1, mid+1, r);
    }
}
// -----------------------------------------------------------------------------------
