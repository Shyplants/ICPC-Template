#define SIZE 10000001
bool notprime[SIZE];
void precompute() {
    notprime[0] = true, notprime[1] = true;
    for (int i = 2; i <= (int)sqrt(SIZE + 0.5); i++) {
        if (!notprime[i]) {
            for (int j = i + i; j <= SIZE; j += i) notprime[j] = true;
        }
    }
}