/* simple ticket spinlock implementation as outlined by
 * John M. Mellor-Crummey and Michael L. Scott. 1991. 
 * Algorithms for scalable synchronization on shared-memory multiprocessors. 
 * ACM Trans. Comput. Syst. 9, 1 (Feb. 1991), 21–65. https://doi.org/10.1145/103727.103729 
 */
#include <asm.h>
#include <spinlock.h>
#include <printf.h>
#include <sbi.h>

void 
initlock(spinlock_t *l)
{
	l->ticket = 0;
	l->turn = 0;
}

void 
acquire(spinlock_t *l)
{
	sie_disable(); 


	int myturn = __sync_fetch_and_add(&l->ticket, 1);
	while (l->turn != myturn)
		;
	__sync_synchronize();
}

void 
release(spinlock_t *l) 
{
	sie_disable(); 

	__sync_add_and_fetch(&l->turn, 1);

	sie_enable();
}
