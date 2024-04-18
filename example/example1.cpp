int sumAB(int a, int b) {
    return a+b;
}

int mulAB(int a, int b) {
    
    return sumAB(a,b)*b;
}

int main() {
    int v1 = 10;
    int v2 = 15;
    int v3 = sumAB(v1, v2);
    int v6 = sumAB(v1, v2);
    int v5 = mulAB(v1, v2);
    int v4 = mulAB(v1, v2);
    return 0;
}