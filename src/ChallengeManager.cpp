/**
 * ChallengeManager.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description
 */


#include <algorithm>
#include <chrono>
#include <thread>

#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlProperty>

#include "ChallengeManager.h"
#include "Utils.h"


ChallengeManager::ChallengeManager(QObject* parent): QObject(parent) {

}


ChallengeManager::~ChallengeManager() {

}


// --- Public QML Invokable Methods -----------------------------------------------------


Q_INVOKABLE void ChallengeManager::load(QQmlApplicationEngine *p_engine) {
    int completedChallenges = 0;

    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: load: Called";
    #endif

    if (!findChallengePaths()) {
        #ifdef QT_DEBUG
            qDebug() << "ERROR: ChallengeManager: load: Could not find challenges!";
        #endif
        return;
    }

    m_challenges.insert(0, NULL);

    for (auto path : m_challengePaths) {
        QQmlComponent component(p_engine, path, QQmlComponent::PreferSynchronous);

        if (component.isError()) {
            #ifdef QT_DEBUG
                qDebug() << "ChallengeManager: load: ERROR loading component"
                         << path << '\n' << component.errors();
            #endif
            continue;
        }

        QObject *challenge = component.create();
        QQmlEngine::setObjectOwnership(challenge, QQmlEngine::CppOwnership);

        QQmlProperty::write(challenge, "objectName", QFileInfo(path).baseName());
        m_challenges.insert(QQmlProperty::read(challenge, "index").toInt(), challenge);

        #ifdef QT_DEBUG
            qDebug() << "ChallengeManager: load: Loaded challenge"
                     << "\n\t at path" << path
                     << "\n\t with objectName" << QQmlProperty::read(challenge, "objectName").toString()
                     << "\n\t with name" << QQmlProperty::read(challenge, "name").toString()
                     << "\n\t at index" << QQmlProperty::read(challenge, "index").toInt()
                     << "\n\t with" << QQmlProperty::read(challenge, "totalSteps").toInt() << "steps";
        #endif
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    setCompletedChallenges(completedChallenges);
    setTotalChallenges(m_challenges.size() - 1);
    setCurrentChallenge(1);
}


Q_INVOKABLE bool ChallengeManager::nextChallenge() {
    int fromIndex = QQmlProperty::read(m_pCurrentChallenge, "index").toInt();

    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: nextChallenge: fromIndex is" << fromIndex;
    #endif

    // TODO: Find the next uncompleted challenge.
    int toIndex = std::max(1, (fromIndex + 1) % m_challenges.size());

    setCurrentChallenge(toIndex);
    return true;
}


// --- Properties: Getters and Setters --------------------------------------------------


Q_INVOKABLE int ChallengeManager::getCompletedChallenges() const {
    return m_completedChallenges;
}


Q_INVOKABLE int ChallengeManager::getTotalChallenges() const {
    return m_totalChallenges;
}


Q_INVOKABLE QObject* ChallengeManager::getCurrentChallenge() const {
    return m_pCurrentChallenge;
}


bool ChallengeManager::setCompletedChallenges(const int completedChallenges) {
    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: setCompletedChallenges:" << completedChallenges;
    #endif
    if (completedChallenges > m_completedChallenges && completedChallenges >= 0) {
        m_completedChallenges = completedChallenges;
        emit completedChallengesChanged();
        return true;
    }
    return false;
}


bool ChallengeManager::setTotalChallenges(const int totalChallenges) {
    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: setTotalChallenges:" << totalChallenges;
    #endif
    if (totalChallenges > m_totalChallenges && totalChallenges >= 0) {
        m_totalChallenges = totalChallenges;
        emit totalChallengesChanged();
        return true;
    }
    return false;
}


bool ChallengeManager::setCurrentChallenge(const int challengeIndex) {
    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: setCurrentChallenge:" << challengeIndex;
    #endif
    if (challengeIndex < 0 || m_challenges.size() < challengeIndex) {
        #ifdef QT_DEBUG
            qDebug() << "ChallengeManager: setCurrentChallenge: ERROR index will be"
                     << "out of bounds";
        #endif
        return false;
    }

    QObject* p_challenge = m_challenges[challengeIndex];

    if (p_challenge == m_pCurrentChallenge || p_challenge == NULL) {
        #ifdef QT_DEBUG
            qDebug() << "ChallengeManager: setCurrentChallenge: ERROR next challenge"
                     << "is either the same or NULL";
        #endif
        return false;
    }

    m_pCurrentChallenge = p_challenge;
    emit currentChallengeChanged();
    return true;
}


bool ChallengeManager::setCurrentChallenge(const QObject* p_challenge) {
    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: setCurrentChallenge:" << p_challenge;
    #endif
    // TODO: Implement this (if needed).
}


// --- Private Methods ------------------------------------------------------------------


void onChallengeCompleted(QString challengeId, int challengeIndex) {
    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: onChallengeCompleted:" << challengeId << challengeIndex;
    #endif
    // TODO: notify the savefile here
}


bool ChallengeManager::findChallengePaths() {
    QDir challengeDir;
    challengeDir.setNameFilters(QStringList() << "*.qml");

    QStringList challengeDirPaths = {
        // Kano OS install path.
        "/usr/share/comment/challenges",

        #ifdef QT_DEBUG
            // Mac OS local path from executable.
            Utils::getAppRelativePath("../../../../res/challenges"),
            // Raspberry Pi local path from executable.
            Utils::getAppRelativePath("../res/challenges")
        #endif
    };

    for (auto path : challengeDirPaths) {
        challengeDir.setPath(path);
        m_challengePaths = challengeDir.entryList();

        if (!m_challengePaths.isEmpty()) {
            for (auto &path : m_challengePaths) {
                path = challengeDir.absoluteFilePath(path);
                #ifdef QT_DEBUG
                    qDebug() << "ChallengeManager: findChallengePaths: Found challenge at" << path;
                #endif
            }
            return true;
        }
    }

    return false;
}
