extern "C" {
// here are the magic parts, will be explained in the following sections
#include "fff.h"
DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(int, get_hw_status);
FAKE_VOID_FUNC_VARARG(add_log, const unsigned char *, ...);
}

void some_hw_mux() {}; // dummy

int very_important_func()
{
    int hw_status;

    some_hw_mux();

    hw_status = get_hw_status();
    add_log("HW_STS %d", hw_status);

    return (hw_status == 2) ? TRUE: FALSE;
}

TEST(TestFunc, Case1) {
    int rtn;
    get_hw_status_fake.return_val = 2; // stub
    rtn = very_important_func();
    ASSERT_EQ(rtn, TRUE);
    ASSERT_EQ(add_log_fake.call_count, 1); // mock
}
