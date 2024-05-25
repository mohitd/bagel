
extern "C" {
int answerToLife() {
    return 42;
}

int* answerToLifeHeap() {
    return new int(42);
}

double* g() {
    static double g = 9.8;
    return &g;
}

}
