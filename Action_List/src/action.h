#pragma once
#include <iostream>
#include <queue>
#include <memory>
#include <string>
#include <cstdio>

class Action {
    public :
        virtual bool isFinished() = 0;
        virtual bool update(int dt) = 0;
        virtual ~Action() {}
};

class Nothing : public Action {
    public :
        int m_runningTime = 0;
        int m_currentTime = 0;
        bool m_finish = false;

        Nothing(int runTime = 1000) {
            m_runningTime = runTime;
            m_finish = false;
        }
        
        virtual bool isFinished() {
            return m_finish;
        }

        virtual bool update(int dt) {
            m_currentTime += dt;
            std::cout << m_currentTime << "\t" << "\tNothing...\n";

            if( m_currentTime > m_runningTime ) {
                m_finish = true;
            }

            return isFinished();
        }

        virtual ~Nothing() {
            std::cout << "~Nothing() \n";
        }
};

class Turning : public Action {
    public :
        int m_runningTime = 0;
        int m_currentTime = 0;
        bool m_finish = false;

        Turning(int runTime = 1000) {
            m_runningTime = runTime;
            m_finish = false;
        }
        
        virtual bool isFinished() {
            return m_finish;
        }

        virtual bool update(int dt) {
            m_currentTime += dt;
            std::cout << m_currentTime << "\t" << "Turning...\n";

            if( m_currentTime > m_runningTime ) {
                m_finish = true;
            }

            return isFinished();
        }

        virtual ~Turning() {
            std::cout << "~Turning() \n";
        }
};

class GoFront : public Action {
    public :
        int m_runningTime = 0;
        int m_currentTime = 0;
        bool m_finish = false;

        GoFront(int runTime = 1000) {
            m_runningTime = runTime;
            m_finish = false;
        }
        
        virtual bool isFinished() {
            return m_finish;
        }

        virtual bool update(int dt) {
            m_currentTime += dt;
            std::cout << m_currentTime << "\t" << "GoFront...\n";

            if( m_currentTime > m_runningTime ) {
                m_finish = true;
            }
            return isFinished();
        }

        virtual ~GoFront() {
            std::cout << "~GoFront() \n";
        }
};

class CuteTrick {
    public :
        std::queue<std::shared_ptr<Action>> m_actionList;

        CuteTrick(const std::string &str) {
            for(int i=0; i<str.length(); i++) {
                switch( str[i] ) {
                    case '0' :
                        m_actionList.push(std::make_shared<GoFront>(3000));
                        break;
                    case '1' :
                        m_actionList.push(std::make_shared<Nothing>(5000));
                        break;
                    case '2' :
                        m_actionList.push(std::make_shared<Turning>(2000));
                        break;
                    default :
                        std::cout << str[i] << " : wrong input \n";
                        break;
                }
            }

        }

        bool update(int dt = 100) {
            static int testTime = 0;
            if( m_actionList.empty() ) {
                return true;
            }

            testTime += dt;
            if( m_actionList.front()->update(dt) ) {
                m_actionList.pop();
            }

            return false;
        }
};
