#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
    public:
        virtual void Init() = 0;
        virtual void Exit() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

        //void ChangeState(GameState* state){ Engine::GetInstance()->ChangeState(state); }

    protected:
        GameState() {}
        virtual ~GameState() {}

        bool m_Pause;

        SDL_Renderer* m_Ctxt;

};

#endif // GAMESTATE_H
