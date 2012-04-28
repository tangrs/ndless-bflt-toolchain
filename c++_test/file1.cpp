/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

extern "C" {
#include <os.h>
}


class test_class3 {
    public:
    test_class3() {
        printf("test_class3 constructor called\n");
    }
};

test_class3 globobj2;