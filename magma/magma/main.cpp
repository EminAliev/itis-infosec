#include "magma.h"
using namespace std;

int main()
{
    cout << "Start" << endl;

    char key[] = "ffeeddccbbaa99887766554433221100f0fl f2f3f4f5f6f7f8f9fafbfcfdfeff\0";
    MAGMA magma(key);

    magma.encode();
    magma.decode();
    cout << "Done" << endl;
    return 0;
}
