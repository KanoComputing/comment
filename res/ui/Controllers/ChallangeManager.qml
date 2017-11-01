/**
 * ChallengeManager.qml
 *
 * Copyright (C) 2017 Kano Computing Ltd.
 * License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * TODO: Description.
 */


pragma singleton


Component {
    id: root

    readonly property int completedChallenges: 0
    readonly property int totalChallenges: 0
    readonly property list challengeNames: []

    challenges = [];

    function load() {
        for each challenge:
            challenges.append (import qml file)

    }
}
