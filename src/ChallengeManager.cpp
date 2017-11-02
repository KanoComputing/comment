/**
 * ChallengeManager.cpp
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description
 */


#include <chrono>
#include <thread>

#include <QDir>
#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QUrl>
#include <QQmlApplicationEngine>
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
    int totalChallenges = 0;

    #ifdef QT_DEBUG
        qDebug() << "ChallengeManager: load: Called";
    #endif

    if (!findChallengePaths()) {
        #ifdef QT_DEBUG
            qDebug() << "ERROR: ChallengeManager: load: Could not find challenges!";
        #endif
        return;
    }

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

        int challengeIndex = QQmlProperty::read(challenge, "index").toInt();
        m_challenges.insert(challengeIndex, challenge);
        totalChallenges++;

        #ifdef QT_DEBUG
            qDebug() << "ChallengeManager: load: Loaded challenge"
                     << "\n\t at path" << path
                     << "\n\t with name" << QQmlProperty::read(challenge, "name").toString()
                     << "\n\t at index" << challengeIndex
                     << "\n\t with" << QQmlProperty::read(challenge, "totalSteps").toInt() << "steps";
        #endif
    }

    setCompletedChallenges(completedChallenges);
    setTotalChallenges(totalChallenges);
}


// --- Properties: Getters and Setters --------------------------------------------------


Q_INVOKABLE int ChallengeManager::getCompletedChallenges() const {
    return m_completedChallenges;
}


Q_INVOKABLE int ChallengeManager::getTotalChallenges() const {
    return m_totalChallenges;
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


// --- Private Methods ------------------------------------------------------------------


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
