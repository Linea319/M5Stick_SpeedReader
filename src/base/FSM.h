#pragma once

class State
{
    public:
        virtual ~State(){}
        virtual void OnEnter() = 0;
        virtual void OnUpdate(const float dt) = 0;
        virtual void OnExit() = 0;
};

template <class T>
class StateTemplate:public State
{
protected:
    /* data */
    typedef void(T::*PFNSTATE)(void);
    typedef void(T::*PFNSTATE_FLT)(const float);
    T* m_pInstance;
    PFNSTATE m_pfnEnter;
    PFNSTATE_FLT m_pfnUpdate;
    PFNSTATE m_pfnExit;
public:
    StateTemplate(/* args */):
    m_pfnEnter(0),
    m_pfnUpdate(0),
    m_pfnExit(0)
    {}
    
    void Set(T* pInstance, PFNSTATE pfnEnter, PFNSTATE_FLT pfnUpdate, PFNSTATE pfnExit)
    {
        m_pInstance = pInstance;
        m_pfnEnter = pfnEnter;
        m_pfnUpdate = pfnUpdate;
        m_pfnExit = pfnExit;
    }

    virtual void OnEnter()
    {
        if(m_pfnEnter)
            (m_pInstance->*m_pfnEnter)();
    }
    virtual void OnUpdate(const float dt)
    {
        if(m_pfnUpdate)
            (m_pInstance->*m_pfnUpdate)(dt);
    }
    virtual void OnExit()
    {
        if(m_pfnExit)
            (m_pInstance->*m_pfnExit)();
    }
};

class FSM
{
protected:
    /* data */
    State* m_pCurrentState;
    State* m_pNewState;
public:
    FSM(State& initState);
    virtual ~FSM() {}
    virtual void Update(const float dt);
    bool IsState(const State& state)const;
    bool GoToState(State& newState);
};
