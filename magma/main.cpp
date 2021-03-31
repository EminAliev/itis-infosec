#include "magma.h"
using namespace std;

int main()
{
    cout << "Start" << endl;

    char key[] = "58943658563456738695486799257846\0";
    MAGMA magma(key);

    magma.encode();
    magma.decode();
    cout << "Done" << endl;
    return 0;
}
