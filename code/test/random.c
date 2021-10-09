/* random.c
 *	Test RandomNum()
 */

#include "syscall.h"

int main() {
    int result;
    result = RandomNum();
    PrintNum(result);
}
