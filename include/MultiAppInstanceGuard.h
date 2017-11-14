/**
 * MultiAppInstanceGuard.h
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


#ifndef __MULTI_APP_INSTANCE_GUARD_H__
#define __MULTI_APP_INSTANCE_GUARD_H__


#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QString>


class MultiAppInstanceGuard
{
    public:
        MultiAppInstanceGuard();
        ~MultiAppInstanceGuard();

    public:
        bool run();
        void release();

    private:
        bool isAnotherRunning();

    private:
        const QString MEMORY_KEY = "MultiAppInstanceGuard.memory-key";
        const QString LOCK_KEY = "MultiAppInstanceGuard.lock-key";

        QSharedMemory m_sharedMemory;
        QSystemSemaphore m_memoryLock;
};


#endif  // __MULTI_APP_INSTANCE_GUARD_H__
