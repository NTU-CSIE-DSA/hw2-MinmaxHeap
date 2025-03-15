#include <iostream>
#include <assert.h>
#include "jngen.h"
using namespace std;
/*
 * Testcase format:
 * <N>
 * <type_1> (<job_id_1> <priority_1>)
 * <type_2> (<job_id_2> <priority_2>)
 * ...
 * <type_N> (<job_id_N> <priority_N>)
 */
#define MAXSZ 1000000
#define MAXP 1000000000
#define MAXID 1000000000
int main(int argc, char* argv[]){
	registerGen(argc, argv);
	int minN = (atoi(argv[1]) < 0) ? 5 : atoi(argv[1]);
	int maxN = (atoi(argv[2]) < 0) ? 1000000 : atoi(argv[2]);
	int addRatio = (atoi(argv[3]) < 0) ? 50 : atoi(argv[3]);
	int rmMaxRatio = (atoi(argv[4]) < 0) ? 25 : atoi(argv[4]);
	int rmMinRatio = (atoi(argv[5]) < 0) ? 25 : atoi(argv[5]);
	int flag = (atoi(argv[6]));
	int N = rnd.next(minN, maxN);
	cout << N << endl;
	assert(addRatio + rmMaxRatio + rmMinRatio == 100);
	set<int> jobIds;
	set<int> priorities;

	if (flag){
		int initialJobs = rnd.next(1, N / 5);
		for (int i=0; i<initialJobs; i++){
			int job_id = rnd.next(1, MAXID);
			while (jobIds.find(job_id) != jobIds.end()){
				job_id = rnd.next(1, MAXID);
			}
			jobIds.insert(job_id);
			int priority = rnd.next(1, MAXP);
			while (priorities.find(priority) != priorities.end()){
				priority = rnd.next(1, MAXP);
			}
			priorities.insert(priority);
			cout << "1 " << job_id << " " << priority << endl;
		}
		N -= initialJobs;
	}

	for (int i=0; i<N; i++){
		int type = rnd.next(1, 100);
		if (type <= addRatio){
			int job_id = rnd.next(1, MAXID);
			while (jobIds.find(job_id) != jobIds.end()){
				job_id = rnd.next(1, MAXID);
			}
			jobIds.insert(job_id);
			int priority = rnd.next(1, MAXP);
			while (priorities.find(priority) != priorities.end()){
				priority = rnd.next(1, MAXP);
			}
			priorities.insert(priority);
			cout << "1 " << job_id << " " << priority << endl;
		}
		else if (type <= addRatio + rmMaxRatio){
			cout << "2" << endl;
		}
		else {
			cout << "3" << endl;
		}
	}
	
	
	return 0;
}
