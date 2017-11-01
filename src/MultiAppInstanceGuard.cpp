/**
 * MultiAppInstanceGuard.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * This object allows an app to restrict the number of instances of itself to 1.
 *
 * It works by creating a multiprocess "flag" in memory, as opposed to a PID file
 * on the disk. The shared memory block is visible by all instaces of the app and
 * can tell whether they're the first to run or not. To protect against some race
 * conditions implicit with reading data in a multiprocess context, a system
 * semaphore lock is used.
 *
 * Inspired from:
 *   http://stackoverflow.com/questions/5006547/qt-best-practice-for-a-single-instance-app-protection/28172162
 *   http://habrahabr.ru/post/173281/
 */


#include <QSharedMemory>
#include <QDebug>

#include "MultiAppInstanceGuard.h"


MultiAppInstanceGuard::MultiAppInstanceGuard()
    : m_memoryLock(LOCK_KEY, 1) {

    m_sharedMemory.setKey(MEMORY_KEY);

    // Hack for cleaning up after a previous instance of the app that crashed
    // unexpectedly with a core dump or otherwise.
    m_memoryLock.acquire();
    {
        QSharedMemory fix(MEMORY_KEY);
        fix.attach();
    }
    m_memoryLock.release();
}

MultiAppInstanceGuard::~MultiAppInstanceGuard() {
    release();
}

// --- Public Methods -------------------------------------------------------------------

bool MultiAppInstanceGuard::run() {
    if (isAnotherRunning()) {
        #ifdef QT_DEBUG
            qDebug() << "Cannot open multiple instances of this app!";
        #endif
        return false;
    }

    // Synchronise processes when creating the shared memory block.
    m_memoryLock.acquire();
    const bool successful = m_sharedMemory.create(1, QSharedMemory::AccessMode::ReadOnly);
    m_memoryLock.release();

    if (!successful) {
        #ifdef QT_DEBUG
            QSharedMemory::SharedMemoryError errorId = m_sharedMemory.error();
            qDebug() << "ERROR: MultiAppInstanceGuard: run: Creating shared memory block"
                     << "failed:" << errorId << m_sharedMemory.errorString();
        #endif
        return false;
    }
    return true;
}

void MultiAppInstanceGuard::release() {
    // Synchronise processes when freeing the shared memory block.
    m_memoryLock.acquire();
    if (m_sharedMemory.isAttached())
        m_sharedMemory.detach();
    m_memoryLock.release();
}

// --- Private Methods ------------------------------------------------------------------

bool MultiAppInstanceGuard::isAnotherRunning() {
    if (m_sharedMemory.isAttached()) {
        return false;
    }

    // Synchronise processes when testing the shared memory block.
    m_memoryLock.acquire();
    const bool isRunning = m_sharedMemory.attach();
    if (isRunning) {
        m_sharedMemory.detach();
    } else {
        #ifdef QT_DEBUG
            qDebug() << "MultiAppInstanceGuard: isAnotherRunning: Attaching to shared"
                     << "memory block failed. This must be the first app instance.";
        #endif
    }
    m_memoryLock.release();

    return isRunning;
}
