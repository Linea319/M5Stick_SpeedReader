#include "FSM.h"

FSM::FSM(State& initState)
{
    m_pCurrentState = &initState;
    m_pCurrentState->OnEnter();
    m_pNewState = 0;
}

void FSM::Update(const float dt)
{
    if(m_pNewState)
    {
        m_pCurrentState->OnExit();
        m_pCurrentState = m_pNewState;
        m_pNewState = nullptr;
        m_pCurrentState->OnEnter();
    }
    m_pCurrentState->OnUpdate(dt);
}

bool FSM::IsState(const State& state) const
{
    return m_pCurrentState == &state;
}
bool FSM::GoToState(State& newState)
{
    if(IsState(newState))
        return false;
    m_pNewState = &newState;
    return true;
}