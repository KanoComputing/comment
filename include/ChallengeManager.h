/**
 * ChallengeManager.h
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * Header for the ChallengeManager class.
 */


#ifndef __CHALLENGE_MANAGER_H__
#define __CHALLENGE_MANAGER_H__


#include <QObject>
#include <QList>
#include <QStringList>
#include <QQmlApplicationEngine>


class ChallengeManager: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int completedChallenges READ getCompletedChallenges NOTIFY completedChallengesChanged)
    Q_PROPERTY(int totalChallenges READ getTotalChallenges NOTIFY totalChallengesChanged)

    public:
        ChallengeManager(QObject* parent = 0);
        ~ChallengeManager();

    signals:
        void completedChallengesChanged();
        void totalChallengesChanged();

    public:
        void load(QQmlApplicationEngine *p_engine);

        Q_INVOKABLE int getCompletedChallenges() const;
        Q_INVOKABLE int getTotalChallenges() const;

    private:
        int m_completedChallenges = 0;
        int m_totalChallenges = 0;

        QList<QObject*> m_challenges;
        QStringList m_challengePaths;

    private:
        bool setCompletedChallenges(const int completedChallenges);
        bool setTotalChallenges(const int totalChallenges);

        bool findChallengePaths();
};


#endif
