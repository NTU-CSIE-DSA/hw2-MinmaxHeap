// To be modified
#include "testlib.h"
using namespace std;

#define MAXN 1000000
#define MAXID 1000000000
#define MAXP 1000000000
/*
 * Testcase format:
 * <N>
 * <type_1> (<job_id_1> <priority_1>)
 * <type_2> (<job_id_2> <priority_2>)
 * ...
 * <type_N> (<job_id_N> <priority_N>)
 */
int main() {
	registerValidation();
	int n = inf.readInt(1, MAXN, "n");
	inf.readEoln();
	for (int i=0; i<n; i++){
		int type = inf.readInt(1, 3, "type");
		if (type == 1){
			inf.readSpace();
			inf.readInt(1, MAXID, "job_id");
			inf.readSpace();
			inf.readInt(1, MAXP, "priority");
			inf.readEoln();
		}
		else inf.readEoln();
	}

	inf.readEof();
	return 0;
}
