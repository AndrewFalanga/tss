
#ifndef _NPM_THREAD_H_
#define _NPM_THREAD_H_

#include <cerrno>
#include <stdint.h>

/**
 * The base class for a thread
 *
 * Implementations should take care to resolve the structures accordingly.
 */
struct _NpmThread {
    int (*Start)(struct _NpmThread*);
    int (*Stop)(struct _NpmThread*);
    uint32_t (*GetId)(struct _NpmThread*);
    int (*IsRunning)(struct _NpmThread*);
    void (*Cleanup)(void);
};

typedef struct _NpmThread NpmThread;

/**
 * Destroy an allocated instance of a thread.
 *
 * This function is a passthrough which will call the (*Cleanup)() method,
 * if any exists, and free the memory. The supplied pointer is then made=
 * NULL.
 *
 * Supplying th == NULL or *th == NULL constitutes success
 */
void DestroyNpmThread(NpmThread **th);

/*
 * Convenience callers
 */
static int StartNpmThread(NpmThread* th)
{
    if (th) return th->Start(th);
    else return EINVAL;
}

static int StopNpmThread(NpmThread* th)
{
    if (th) return th->Stop(th);
    else return EINVAL;
}

static uint32_t GetNpmThreadId(NpmThread* th)
{
    if (th) return th->GetId(th);
    else return EINVAL;
}

static int IsNpmThreadRunning(NpmThread* th)
{
    if (th) return th->IsRunning(th);
    else return EINVAL;
}

/*
 * Purposely no convenience method for the cleanup. That isn't supposed to be
 * called by anything outside of Delete().
 */
#endif
