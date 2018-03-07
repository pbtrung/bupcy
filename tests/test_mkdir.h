#include "greatest.h"

#include "utils/utils.h"
#include "utils/common.h"
#include "CException/CException.h"

TEST test_mkdir_recursive() {
	CEXCEPTION_T e;
	Try {
		bstring home_dir = bupcy_get_home_dir();
		char path[] = "ワンピース\\Tankōbon\\雑誌\\コミックス";
		int rc = bcatcstr(home_dir, path);
		ASSERT(rc == BSTR_OK);
    	bool b = bupcy_mkdir_recursive((char *)home_dir->data);
    	ASSERT(b == true);
    	bdestroy(home_dir);
	}
	Catch(e) {
		log_rc_msg(e);
	}
    PASS();
}

SUITE(test_mkdir) { 
    RUN_TEST(test_mkdir_recursive);
}
