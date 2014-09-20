/*
 * =======================================================================
 *   (c) Copyright Hewlett-Packard Development Company, L.P., 2008
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of version 2 the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * =======================================================================
 *
 *
 * Facility:
 *
 *      MSFS
 *
 * Abstract:
 *
 *      Defines generic locks and routines to manipulate the locks.
 *
 * Date:
 *
 *      Wed Sep  5 15:53:40 1990
 */
/*
 * HISTORY
 */
#if 0
#pragma ident "@(#)$RCSfile: ms_generic_locks.c,v $ $Revision: 1.1.37.1 $ (DEC) $Date: 2001/01/24 21:05:26 $"
#endif

#include <fs/msfs/ms_public.h>
#include <fs/msfs/ms_privates.h>
#ifdef _KERNEL
#include <sys/syslog.h>
#include <sys/kernel.h>
#include <sys/time.h>
#endif				/* _KERNEL */

static lkHdrT *find_locked_lock(lkHdrT * lk);

#define ADVFS_MODULE MS_GENERIC_LOCKS

/*
 * LockMgrMutex
 *
 * Used to protect global Lock Manager structures (mainly the mutex
 * linked list).
 */
mutexT LockMgrMutex;
mutexT *MutexList;

	typedef enum {
		MUTEX_LOCK, MUTEX_UNLOCK, CV_WAIT, CV_DONEWAIT,
		GEN_LOCK, GEN_UNLOCK, SHARE_LOCK, SHARE_UNLOCK,
		EXCL_LOCK, EXCL_UNLOCK, CV_SIGNAL, CV_BROADCAST,
		SET_STATE, WAIT_FOR, WAIT_WHILE
	}    LkTraceActionT;
#define TIME_MASK 0x3ff

	extern unsigned TrFlags;

/*
 * Lock statistics
 */

	advfsLockStatsT *AdvfsLockStats = NULL;



/*
 * trace_hdr
 *
 * Print the header out for tracing
 */
	void
	     trace_hdr(void)
{
#ifdef _KERNEL
	struct timeval hdrTime;
	int s;
	TIME_READ(hdrTime);
	log(LOG_MEGASAFE | LOG_INFO,
	    "%2d.%3d %d ", hdrTime.tv_sec & 0x7f,
	    hdrTime.tv_usec >> 10, current_thread());
#else
	struct timeval time;
	struct timezone tzone;
	pthread_t tid;
	tid = pthread_self();


	if (gettimeofday(&time, &tzone) < 0) {
		perror("gettimeofday");
		exit(1);
	}

	ms_printf("%2d.%3d %u ", time.tv_sec & 0x7f,
	    (time.tv_usec >> 10),
	    tid.pta_magic);

#endif				/* _KERNEL */
}
#ifdef _KERNEL
char *
strrchr(char *s, char c)
{
	int l = strlen(s);

	if (l == 0) {
		return 0;
	}
	for (l--; l >= 0; l--) {
		if (s[l] == c) {
			return &s[l];
		}
	}

	return 0;
}
#endif

void
bs_lock_mgr_init(void)
{

	/*
         * Initialize the Lock Mgr's mutex.
         */
	simple_lock_setup(&LockMgrMutex.mutex, msfs_lockmgrmutex_enterinfo);

	AdvfsLockStats = (advfsLockStatsT *) ms_malloc(sizeof(advfsLockStatsT));
	if (AdvfsLockStats != NULL) {
		bzero(AdvfsLockStats, sizeof(advfsLockStatsT));
	}
}

/*
 * cond_wait
 */
void
cond_wait(
    cvT * cvp,			/* in - condition variable */
    mutexT * mp		/* in - mutex */
)
{
	if (AdvfsLockStats) {
		AdvfsLockStats->wait++;
	}
	/*
         * Thread_sleep will give up the simple lock as it
         * sleeps so we reacquire the lock when we awaken.
         * Note that a simple_lock_t is a pointer.
         * The cast should be to a long for alpha but
         * the routine takes an int.
         */
	thread_sleep((vm_offset_t) cvp, &mp->mutex, FALSE);
	simple_lock(&mp->mutex);
}
/*
 * cond_signel
 */
void
cond_signal(
    cvT * cvp			/* in - condition variable */
)
{
	if (AdvfsLockStats) {
		AdvfsLockStats->signal++;
	}
	/*
         * The cast should be to a long for alpha but
         * the routine takes an int.
         */
	thread_wakeup_one((vm_offset_t) cvp);
}
/*
 * cond_broadcast
 */
void
cond_broadcast(
    cvT * cvp			/* in - condition variable */
)
{
	if (AdvfsLockStats) {
		AdvfsLockStats->broadcast++;
	}
	/*
         * The cast should be to a long for alpha but
         * the routine takes an int.
         */
	thread_wakeup((vm_offset_t) cvp);
}
void
advfs_cv_init(
    cvT * cvp
)
{
	*cvp = 0;
}


/*
 * lk_init
 *
 * Initializes a lock and adds it to its mutex's linked list of locks.
 *
 * NOTE: The caller must hold the mutex locked.
 */

void
lk_init(
    void *lk,			/* in - pointer to the lock */
    mutexT * mutex,		/* in - pointer to the lock's mutex */
    lkTypeT lkType,		/* in - lock's type (generic, state, etc.) */
    int resources,		/* in - number of resources for a generic lock */
    lkUsageT usage		/* in - lock's usage */
)
{
	lkHdrT *lkHdr = lk, *curLk, *newLk;

	switch (lkType) {
	case LKT_STATE:
		{
			stateLkT *lk = (void *) lkHdr;
			stateLkT nilStateLk = {LKT_STATE, 0};
			*lk = nilStateLk;
#ifndef _KERNEL
			advfs_cv_init(&lk->cv);
#endif
		}
		break;

	case LKT_BUF:
		{
			bufLkT *lk = (void *) lkHdr;
			bufLkT NilBufLk = {LKT_BUF, 0};
			*lk = NilBufLk;
#ifndef _KERNEL
			advfs_cv_init(&lk->bufCond);
#endif
		}
		break;

	default:
		ADVFS_SAD1("lk_init: unknown lock type", lkType);
	}

	lkHdr->lkUsage = usage;
	lkHdr->mutex = mutex;
}


/*
 * lk_destroy
 *
 * Removes a lock from its mutex's linked list of locks.
 *
 * NOTE: The caller must hold the lock's mutex locked.
 */

void
lk_destroy(
    void *lk			/* in - pointer to the lock */
)
{
}


/*
 * lk_signal
 *
 * Wakes up threads waiting on the semaphore.  The routine
 * either does nothing, wakes up a single thread, or wakes up all waiting
 * threads depending on the value of the 'action' parameter.
 *
 * ASSUMPTIONS: The mutex protecting the semaphore must be locked by the
 * caller.
 */
void
lk_signal(
    unLkActionT action,		/* in */
    void *lk			/* in */
)
{
	lkHdrT *lkHdr = (lkHdrT *) lk;
	stateLkT *slk = (stateLkT *) lk;

	if (lkHdr->lkType == LKT_STATE) {
		if (action == UNLK_SIGNAL) {
			if (AdvfsLockStats) {
				AdvfsLockStats->usageStats[lkHdr->lkUsage].signal++;
				AdvfsLockStats->stateSignal++;
			}
			cond_signal(&slk->cv);
		} else if (action == UNLK_BROADCAST) {
			if (AdvfsLockStats) {
				AdvfsLockStats->usageStats[lkHdr->lkUsage].broadcast++;
				AdvfsLockStats->stateBroadcast++;
			}
			cond_broadcast(&slk->cv);
		}
	}
}


/*
 * lk_set_state
 *
 * Changes the state of the state lock to the desired state.  Returns
 * the apporiate unlock action (signal or broadcast).  The caller should
 * call lk_signal() after releasing the associated mutex (see lk_unlock()
 * and lk_signal()).
 *
 * ASSUMPTIONS: The mutex protecting the state lock must be locked by the
 * caller.
 */

unLkActionT
lk_set_state(
    stateLkT * lk,
    lkStatesT newState
)
{
	unLkActionT unlock_action = UNLK_NEITHER;

	lk->state = newState;

	if (lk->waiters > 0) {
		if (lk->waiters == 1) {
			if (AdvfsLockStats) {
				AdvfsLockStats->usageStats[lk->hdr.lkUsage].signal++;
				AdvfsLockStats->stateSignal++;
			}
			unlock_action = UNLK_SIGNAL;
		} else {
			if (AdvfsLockStats) {
				AdvfsLockStats->usageStats[lk->hdr.lkUsage].broadcast++;
				AdvfsLockStats->stateBroadcast++;
			}
			unlock_action = UNLK_BROADCAST;
		}
	}
	return unlock_action;
}


/*
 * lk_wait_for
 *
 * This routine will wait until the state of a state variable changes
 * to the desired state.
 *
 * ASSUMPTIONS: The mutex protecting the state lock must be locked by the
 * caller.
 */

void
lk_wait_for(
    stateLkT * lk,
    mutexT * lk_mutex,
    lkStatesT waitState
)
{
	int wait = 0;

	if (AdvfsLockStats) {
		AdvfsLockStats->usageStats[lk->hdr.lkUsage].lock++;
		AdvfsLockStats->stateLock++;
	}
	if (lk->state != waitState) {
		if (AdvfsLockStats) {
			if (wait) {
				AdvfsLockStats->usageStats[lk->hdr.lkUsage].reWait++;
				AdvfsLockStats->stateReWait++;
			} else {
				wait = 1;
			}

			AdvfsLockStats->usageStats[lk->hdr.lkUsage].wait++;
			AdvfsLockStats->stateWait++;
		}
		lk->waiters++;

		while (lk->state != waitState) {
			cond_wait(&lk->cv, lk_mutex);
		}

		lk->waiters--;
	}
}


/*
 * lk_wait_for2
 *
 * This routine will wait until the state of a state variable changes
 * to one of the two desired states.
 *
 * ASSUMPTIONS: The mutex protecting the state lock must be locked by the
 * caller.
 */

void
lk_wait_for2(
    stateLkT * lk,
    mutexT * lk_mutex,
    lkStatesT waitState1,
    lkStatesT waitState2
)
{
	int wait = 0;

	if (AdvfsLockStats) {
		AdvfsLockStats->usageStats[lk->hdr.lkUsage].lock++;
		AdvfsLockStats->stateLock++;
	}
	while ((lk->state != waitState1) && (lk->state != waitState2)) {
		if (AdvfsLockStats) {
			if (wait) {
				AdvfsLockStats->usageStats[lk->hdr.lkUsage].reWait++;
				AdvfsLockStats->stateReWait++;
			} else {
				wait = 1;
			}

			AdvfsLockStats->usageStats[lk->hdr.lkUsage].wait++;
			AdvfsLockStats->stateWait++;
		}
		lk->waiters++;

		cond_wait(&lk->cv, lk_mutex, ln, fn);

		lk->waiters--;
	}
}


/*
 * lk_wait_while
 *
 * This routine will wait while the state of a state variable remains
 * set to the specified state.
 *
 * ASSUMPTIONS: The mutex protecting the state lock must be locked by the
 * caller.
 */

void
lk_wait_while(
    stateLkT * lk,
    mutexT * lk_mutex,
    lkStatesT waitState
)
{
	int wait = 0;

	if (AdvfsLockStats) {
		AdvfsLockStats->usageStats[lk->hdr.lkUsage].lock++;
		AdvfsLockStats->stateLock++;
	}
	if (lk->state == waitState) {
		if (AdvfsLockStats) {
			if (wait) {
				AdvfsLockStats->usageStats[lk->hdr.lkUsage].reWait++;
				AdvfsLockStats->stateReWait++;
			} else {
				wait = 1;
			}

			AdvfsLockStats->usageStats[lk->hdr.lkUsage].wait++;
			AdvfsLockStats->stateWait++;
		}
		lk->waiters++;

		while (lk->state == waitState) {
			cond_wait(&lk->cv, lk_mutex, ln, fn);
		}

		lk->waiters--;
	}
}


/*
 * lk_is_locked
 *
 * Returns true if the lock is locked.  We consider a state lock
 * to be locked only if there are waiters (it really makes more
 * sense to call lk_get_state() for state locks).
 */

int
lk_is_locked(
    void *lock
)
{
	lkHdrT *lkHdr = lock;
	stateLkT *slk = (void *) lkHdr;
	bufLkT *blk = (void *) lkHdr;

	switch (lkHdr->lkType) {
	case LKT_STATE:
		return (slk->waiters > 0);

	case LKT_BUF:
		return (blk->waiting > 0);

	default:
		return (FALSE);
	}
}

void
bs_dump_locks(int locked)
{
	     printf("no lock dumps (XXX: ADVFS_DEBUG is removed)\n");
}
