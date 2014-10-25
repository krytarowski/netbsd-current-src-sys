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

#ifdef ADVFS_DEBUG
#define ADVFS_LK_STRINGS /* needed for lock string arrays */
                         /* in ms_generic_locks.h */
#endif

#include <sys/param.h>
#include <sys/types.h>
#include <sys/condvar.h>
#include <sys/syslog.h>
#include <sys/time.h>

#include "../msfs/ms_public.h"
#include "../msfs/ms_privates.h"


static lkHdrT *find_locked_lock(lkHdrT *lk);

#define ADVFS_MODULE MS_GENERIC_LOCKS

/*
 * LockMgrMutex
 *
 * Used to protect global Lock Manager structures (mainly the mutex
 * linked list).
 */
kmutex_t LockMgrMutex;
kmutex_t* MutexList;

decl_simple_lock_info(, msfs_lockmgrmutex_lockinfo )
decl_simple_lock_info(, msfs_mp_mutex_lockinfo )

typedef enum { 
    MUTEX_LOCK, MUTEX_UNLOCK, CV_WAIT, CV_DONEWAIT,
    GEN_LOCK, GEN_UNLOCK, SHARE_LOCK, SHARE_UNLOCK,
    EXCL_LOCK, EXCL_UNLOCK, CV_SIGNAL, CV_BROADCAST ,
    SET_STATE, WAIT_FOR, WAIT_WHILE
} LkTraceActionT ;

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
    log( LOG_MEGASAFE | LOG_INFO,
            "%2d.%3d %d ", hdrTime.tv_sec & 0x7f,
            hdrTime.tv_usec>>10, current_thread() );
#else
    struct timeval time;
    struct timezone tzone;
    pthread_t tid;
    tid = pthread_self( );


    if( gettimeofday( &time, &tzone ) < 0 )  {
        perror( "gettimeofday" );
        exit( 1 );
    }

#ifdef _OSF_SOURCE

    ms_printf( "%2d.%3d %d ", time.tv_sec & 0x7f,
            (time.tv_usec>>10),
            tid );
#else
    ms_printf( "%2d.%3d %d ", time.tv_sec & 0x7f,
            (time.tv_usec>>10),
            ((uint32T)tid.field1 >> 4) & 0xfff );

#endif /* _OSF_SOURCE */

#endif /* _KERNEL */
}
   
#ifdef _KERNEL
char *
strrchr( char *s, char c )
{
    int l = strlen( s );

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

/*
 * trace_lkcall
 *
 * Print out info about the lock action
 */ 
void
trace_lkcall( 
             LkTraceActionT action,  /* in */
             kcondvar_t *resp,               /* in */ 
             mutexT *mp,             /* in */
             int ln,                 /* in */
             char *fn,               /* in */
             void *lk                /* in */
             )
{
#ifdef ADVFS_DEBUG
    stateLkT *slk = (stateLkT *) lk;

    char *LkPrintAction[] = { 
        "Mutex Lk  ", 
        "Mutex Unlk", 
        "CV Block  ", 
        "CV Resume ",
        "CV Signal ",
        "CV Bcast  ",
        "Set State ",
        "Wait For  ",
        "Wait While",
    };

    trace_hdr();

    log( LOG_MEGASAFE | LOG_INFO, "%11s ",  LkPrintAction[ action ] );

    switch (action) {
        case MUTEX_LOCK:
        case MUTEX_UNLOCK:
            log( LOG_MEGASAFE | LOG_INFO,
                "%08x  %2d mtx --------  --     ", mp, mp->lock_cnt );
            break;

        case CV_WAIT:
        case CV_DONEWAIT:
            log( LOG_MEGASAFE | LOG_INFO, "%08x  %2d mtx %08x     cnd ", 
                mp, mp->lock_cnt, resp );
            break;

        case CV_SIGNAL:
        case CV_BROADCAST:
            log( LOG_MEGASAFE | LOG_INFO, "--------  --     %08x     cnd ", resp );
            break;

        case WAIT_FOR: 
        case WAIT_WHILE: 
            log( LOG_MEGASAFE | LOG_INFO, "%08x  %2d mtx %08x  %2d slk ", 
                mp, mp->lock_cnt, slk, slk->state );
            break;

        case SET_STATE: 
            log( LOG_MEGASAFE | LOG_INFO, "--------  --     %08x  %2d slk ", slk, slk->state );
            break;

        default:
            log( LOG_MEGASAFE | LOG_INFO, "--------  --     --------  --     " );
            break;
    }
    log( LOG_MEGASAFE | LOG_INFO, "  %4d:%s\n", ln, strrchr( fn, '/' )+1 );

#endif /* ADVFS_DEBUG */
}

void
bs_lock_mgr_init( void )
{

    /*
     * Initialize the Lock Mgr's mutex.
     */
    simple_lock_setup( &LockMgrMutex.mutex, msfs_lockmgrmutex_lockinfo );

    AdvfsLockStats = (advfsLockStatsT *)ms_malloc( sizeof( advfsLockStatsT ) );
    if (AdvfsLockStats != NULL) {
        bzero( AdvfsLockStats, sizeof( advfsLockStatsT ) );
    }
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
    void *lk,           /* in - pointer to the lock */
    kmutex_t *mutex,      /* in - pointer to the lock's mutex */
    lkTypeT lkType,     /* in - lock's type (generic, state, etc.) */
    int resources,      /* in - number of resources for a generic lock */
    lkUsageT usage      /* in - lock's usage */
    )
{
    lkHdrT *lkHdr = lk, *curLk, *newLk;

#ifdef ADVFS_DEBUG
    if (lkHdr->mutex != NULL) {
        /* Assume it is already linked properly */
        return;
    }
#endif /* ADVFS_DEBUG */

    switch (lkType) {
        case LKT_STATE:
            {
            stateLkT *lk = (void *)lkHdr;
            stateLkT nilStateLk = { LKT_STATE, 0 }; 
            *lk = nilStateLk;
#ifndef _KERNEL
            cv_init( &lk->res );
#ifdef ADVFS_DEBUG
            lk->hdr.try_line_num = -1;
#endif /* ADVFS_DEBUG */
#endif
            }
            break;

        case LKT_BUF:
            {
            bufLkT *lk = (void *)lkHdr;
            bufLkT NilBufLk = { LKT_BUF, 0 };
            *lk = NilBufLk;
#ifndef _KERNEL
            cv_init( &lk->bufCond );
#ifdef ADVFS_DEBUG
            lk->hdr.try_line_num = -1;
#endif /* ADVFS_DEBUG */
#endif
            }
            break;

        default:
            ADVFS_SAD1( "lk_init: unknown lock type", lkType );
    }

    lkHdr->lkUsage = usage;

#ifdef ADVFS_DEBUG
    /* add to head of linked list */
    lkHdr->nxtLk = mutex->locks;
    mutex->locks = lkHdr;
#endif /* ADVFS_DEBUG */

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
    void *lk    /* in - pointer to the lock */
    )
{
#ifdef ADVFS_DEBUG
    lkHdrT *prevLk, *curLk, *lkHdr = lk;
    int found = FALSE;

    /*
     * Find the lock in the mutex's linked list of locks.
     */

    if (lkHdr->mutex == NULL) {
        ADVFS_SAD0( "lk_destroy: lk has no mutex" );
    }

    prevLk = curLk = lkHdr->mutex->locks;

    while (!found && (curLk != NULL)) {
        if (curLk == lk) {
            found = TRUE;
        } else {
            prevLk = curLk;
            curLk = curLk->nxtLk;
        }
    }

    if (!found) {
        ADVFS_SAD0( "lk_destroy: lk is not in mutex's linked list" );
    }

    /*
     * Remove the lock from the mutex's linked list.
     */

    if (lkHdr == lkHdr->mutex->locks) {
        lkHdr->mutex->locks = lkHdr->nxtLk;
    } else {
        prevLk->nxtLk = lkHdr->nxtLk;
    }

    lkHdr->mutex = NULL;
    lkHdr->nxtLk = NULL;
#endif /* ADVFS_DEBUG */
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
_lk_signal( 
           unLkActionT action,       /* in */ 
           void *lk,                 /* in */
           int ln,                   /* in */
           char *fn                  /* in */
           )
{
    lkHdrT *lkHdr = (lkHdrT *) lk;
    stateLkT *slk = (stateLkT *) lk;

    if (lkHdr->lkType == LKT_STATE) {
        if (action == UNLK_SIGNAL) {
            if (AdvfsLockStats) {
                AdvfsLockStats->usageStats[ lkHdr->lkUsage ].signal++;
                AdvfsLockStats->stateSignal++;
            }
            cv_signal( &slk->res, ln, fn );
        } else if (action == UNLK_BROADCAST) {
            if (AdvfsLockStats) {
                AdvfsLockStats->usageStats[ lkHdr->lkUsage ].broadcast++;
                AdvfsLockStats->stateBroadcast++;
            }
            cv_broadcast( &slk->res, ln, fn );
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
_lk_set_state(
    stateLkT *lk,
    lkStatesT newState,
    int ln,
    char *fn
    )
{
    unLkActionT unlock_action = UNLK_NEITHER;

#ifdef ADVFS_DEBUG
    if (TrFlags&trLock) {
        trace_lkcall( SET_STATE, &lk->res, NULL, ln, fn, lk );
    }
#endif /* ADVFS_DEBUG */

    lk->state = newState;

    if (lk->waiters > 0) {
        if (lk->waiters == 1) {
            if (AdvfsLockStats) {
                AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].signal++;
                AdvfsLockStats->stateSignal++;
            }
            unlock_action = UNLK_SIGNAL;
        } else {
            if (AdvfsLockStats) {
                AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].broadcast++;
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
_lk_wait_for(
    stateLkT *lk,
    kmutex_t *lk_mutex,
    lkStatesT waitState,
    int ln,
    char *fn
    )
{
    int wait = 0;

#ifdef ADVFS_DEBUG
    if (!lk_mutex->locked) {
        printf( "_lk_wait_for: ln = %d, fn = %s\n", ln, fn );
        ADVFS_SAD0( "_lk_wait_for: mutex not locked" );
    }

    if (TrFlags&trLock) {
        trace_lkcall( WAIT_FOR, &lk->res, lk_mutex,ln,fn, lk );
    }

    lk->hdr.try_line_num = ln;
    lk->hdr.try_file_name = fn;
#endif /* ADVFS_DEBUG */

    if (AdvfsLockStats) {
        AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].lock++;
        AdvfsLockStats->stateLock++;
    }

    if (lk->state != waitState) {
        if (AdvfsLockStats) {
            if (wait) {
                AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].reWait++;
                AdvfsLockStats->stateReWait++;
            } else {
                wait = 1;
            }

            AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].wait++;
            AdvfsLockStats->stateWait++;
        }

        lk->waiters++;

        while (lk->state != waitState) {
            cv_wait( &lk->res, lk_mutex, ln, fn );
        }

        lk->waiters--;
    }

#ifdef ADVFS_DEBUG
    lk->hdr.line_num = ln;
    lk->hdr.file_name = fn;
    lk->hdr.use_cnt++;
#endif /* ADVFS_DEBUG */
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
_lk_wait_for2(
    stateLkT *lk,
    kmutex_t *lk_mutex,
    lkStatesT waitState1,
    lkStatesT waitState2,
    int ln,
    char *fn
    )
{
    int wait = 0;

#ifdef ADVFS_DEBUG
    if (!lk_mutex->locked) {
        printf( "_lk_wait_for2: ln = %d, fn = %s\n", ln, fn );
        ADVFS_SAD0( "_lk_wait_for2: mutex not locked" );
    }

    if (TrFlags&trLock) {
        trace_lkcall( WAIT_FOR, &lk->res, lk_mutex,ln,fn, lk );
    }

    lk->hdr.try_line_num = ln;
    lk->hdr.try_file_name = fn;
#endif /* ADVFS_DEBUG */

    if (AdvfsLockStats) {
        AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].lock++;
        AdvfsLockStats->stateLock++;
    }

    while ((lk->state != waitState1) && (lk->state != waitState2)) {
        if (AdvfsLockStats) {
            if (wait) {
                AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].reWait++;
                AdvfsLockStats->stateReWait++;
            } else {
                wait = 1;
            }

            AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].wait++;
            AdvfsLockStats->stateWait++;
        }

        lk->waiters++;

        cv_wait( &lk->res, lk_mutex, ln, fn );

        lk->waiters--;
    }

#ifdef ADVFS_DEBUG
    lk->hdr.line_num = ln;
    lk->hdr.file_name = fn;
    lk->hdr.use_cnt++;
#endif /* ADVFS_DEBUG */
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
_lk_wait_while(
    stateLkT *lk,
    kmutex_t *lk_mutex,
    lkStatesT waitState,
    int ln,
    char *fn
    )
{
    int wait = 0;

#ifdef ADVFS_DEBUG
    if (!lk_mutex->locked) {
        printf( "_lk_wait_while ln = %d, fn = %s\n", ln, fn );
        ADVFS_SAD0( "_lk_wait_while: mutex not locked" );
    }

    if (TrFlags&trLock) {
        trace_lkcall( WAIT_WHILE, &lk->res, lk_mutex,ln,fn, lk );
    }

    lk->hdr.try_line_num = ln;
    lk->hdr.try_file_name = fn;
#endif /* ADVFS_DEBUG */

    if (AdvfsLockStats) {
        AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].lock++;
        AdvfsLockStats->stateLock++;
    }

    if (lk->state == waitState) {
        if (AdvfsLockStats) {
            if (wait) {
                AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].reWait++;
                AdvfsLockStats->stateReWait++;
            } else {
                wait = 1;
            }

            AdvfsLockStats->usageStats[ lk->hdr.lkUsage ].wait++;
            AdvfsLockStats->stateWait++;
        }

        lk->waiters++;

        while (lk->state == waitState) {
            cv_wait( &lk->res, lk_mutex, ln, fn );
        }

        lk->waiters--;
    }

#ifdef ADVFS_DEBUG
    lk->hdr.line_num = ln;
    lk->hdr.file_name = fn;
    lk->hdr.use_cnt++;
#endif /* ADVFS_DEBUG */
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
    lkHdrT   *lkHdr = lock;
    stateLkT *slk = (void *)lkHdr;
    bufLkT   *blk = (void *)lkHdr;

    switch (lkHdr->lkType) {
        case LKT_STATE:
            return( slk->waiters > 0 );
            
        case LKT_BUF:
            return( blk->waiting > 0 );
            
        default:
            return ( FALSE );
    }
}

#ifdef ADVFS_DEBUG
static lkHdrT *
find_locked_lock(
    lkHdrT *lk
    )
{
    while (lk != NULL) {
        if (lk_is_locked( lk )) {
            return lk;
        }

        lk = lk->nxtLk;
    }

    return NULL;
}
#endif /* ADVFS_DEBUG */

void
bs_dump_locks( int locked )
{
#ifdef ADVFS_DEBUG
    kmutex_t *mp = NULL;
    lkHdrT *lkHdr = NULL;

    mp = MutexList;

    while (mp != NULL) {
        if (!locked || 
            (locked && 
             ((mp->lock_cnt > 0) || find_locked_lock( mp->locks )))) {
            printf( "\n" );
            printf( " mutex : 0x%08x  (%s)\n", mp, mp->name );
            printf( "\tlocked        : %d\n", mp->locked );
            printf( "\ttry line num  : %d\n", mp->try_line_num );
            if (mp->try_file_name == NULL) {
                printf( "\ttry file name : \n" );
            } else {
                printf( "\ttry file name : %s\n", mp->try_file_name );
            }
            printf( "\tlock cnt      : %d\n", mp->lock_cnt );
            printf( "\tline num      : %d\n", mp->line_num );
            if (mp->file_name == NULL) {
                printf( "\tfile name     : \n" );
            } else {
                printf( "\tfile name     : %s\n", mp->file_name );
            }

            lkHdr = mp->locks;

            while (lkHdr != NULL) {
                if (locked && !lk_is_locked( lkHdr )){
                    lkHdr = lkHdr->nxtLk;
                    continue;
                }
                
                printf( "\n" );
                printf( "\tlock type     : %s\n", lkTypeNames[lkHdr->lkType]);
                printf( "\tlock usage    : %s\n", lkUsageNames[lkHdr->lkUsage]);
                printf( "\tuse cnt       : %d\n", lkHdr->use_cnt );
                printf( "\tmutex         : 0x%08x\n", lkHdr->mutex );
                printf( "\tnxtFtxLk      : 0x%08x\n", lkHdr->nxtFtxLk );
                printf( "\ttry_line_num  : %d\n", lkHdr->try_line_num );
                if (lkHdr->try_file_name == NULL) {
                    printf( "\ttry_file_name : \n" );
                } else {
                    printf( "\ttry_file_name : %s\n", lkHdr->try_file_name );
                }
                printf( "\tline_num      : %d\n", lkHdr->line_num );
                if (lkHdr->file_name == NULL) {
                    printf( "\tfile_name     : \n" );
                } else {
                    printf( "\tfile_name     : %s\n", lkHdr->file_name );
                }

                switch (lkHdr->lkType) {

                case LKT_BUF:
                    {
                    bufLkT *lk = (void *)lkHdr;
                    printf("\tstate         : 0x%08x\n", lk->state );
                    printf("\twaiting       : %d\n", lk->waiting );
                    }
                    break;

                case LKT_STATE:
                    {
                    stateLkT *lk = (void *)lkHdr;
                    char *stateNames[] = { 
                        "LKW_NONE",
                    
                        /* bfAccessT client states */
                        "ACC_VALID",
                        "ACC_INVALID",
                        "ACC_INIT_TRANS",
                        "ACC_FTX_TRANS", 
                    
                        /* struct vd */
                        "ACTIVE_DISK",   
                        "INACTIVE_DISK",
                        "BLOCKED_Q",     
                        "UNBLOCKED_Q",
                    
                        /* struct bsBuf */
                        "BUF_DIRTY",
                        "BUF_BUSY",
                        "BUF_UNPIN_BLOCK",
                        "BUF_PIN_BLOCK",
                    
                        /* block for a free buffer header */
                        "BUF_AVAIL",
                        "NO_BUF_AVAIL",

                        /* bitfile set states in bfSetT */
                        "BFS_INVALID",
                        "BFS_READY",
                        "BFS_CLONING",
                        "BFS_BUSY",
                        "BFS_DELETING",
                        "BFS_DELETING_CLONE"
                        };
                    printf("\twaiters       : %d\n", lk->waiters );
                    printf("\tstate         : %s\n", stateNames[lk->state] );
                    printf("\tpending state : %s\n", stateNames[lk->state] );
                    }
                    break;

                default:
                    break;
                }

                lkHdr = lkHdr->nxtLk;
            }
        }

        mp = mp->next_mutex;
    }
#else
    printf( "no lock dumps when ADVFS_DEBUG is not defined\n" );
#endif /* ADVFS_DEBUG */
}
