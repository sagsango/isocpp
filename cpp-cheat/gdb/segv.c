/*
Let's take a look at what happens on a segmentation fault.
*/

int main(void) {
    (*((char*)0))++;
    return 0;
}
