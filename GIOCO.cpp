

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <string.h>

const int Dimcubo = 50, Hcolori = 100, Lcolori = 50;
const int Lfinestra = 700;
const int Hfinestra = 400;
const float Speed = 170.0f;
const float Obbiettivotempoframe = 1000.0f / 80.0f;

struct Pos {
    int x;
    int y;
}Poscubo= { 5, 200 };

//////
SDL_Rect Rcolori[4];
Pos Poscolori[4], Poscolori2[4];
SDL_Color Ccolori[4];
SDL_Color Ccubo;
//////
SDL_Color Coloretesto = {255, 255, 255, 200 };
TTF_Font* font = TTF_OpenFont("fonte.ttf", 20);

//////

float Colspeed = 20.0f;

int Xcolori = 200, Xcolori2 = Xcolori + 350;

bool inizia = 0, running = 1, collisione = 0;

int iCcubo, punteggio = 0;

void scrittaPunti(SDL_Renderer* Render)
{
    std::string Testopunti = "Punti : " + punteggio;
    SDL_Surface* Suppunti= TTF_RenderText_Blended(font,Testopunti.c_str(), Coloretesto); 
    SDL_Texture* Texpunti = SDL_CreateTextureFromSurface(Render, Suppunti);
    SDL_Rect Rtesto = { 120, 120, 200, 40 }; 
    SDL_RenderCopy(Render,Texpunti , NULL, &Rtesto);
    

}

void collisioni(Pos Poscolori[])
{
    for (int i = 0; i < 4; i++)
    {
        if (i != iCcubo)
        {
            if (Poscubo.x + Dimcubo < Poscolori[i].x || Poscubo.x> Poscolori[i].x + Lcolori ||
                Poscubo.y + Dimcubo < Poscolori[i].y || Poscubo.y>Poscolori[i].y + Hcolori)
            {
                if (Poscubo.x == Poscolori[0].x - Dimcubo)
                {
                    punteggio++;
                }
            }
            else
            {
                running = 0;
            }
        }
    }
}

void genColori()
{

    for (int i = 0; i < 4; i++)
    {
        Ccolori[i].r = rand() % 256;
        Ccolori[i].g = rand() % 256;
        Ccolori[i].b = rand() % 256;
    }
    int casuale = rand() % 4 + 1;
    switch (casuale)
    {
    case 1:
    {
        Ccubo = Ccolori[0];
        iCcubo = 0;
        break;
    }
    case 2:
    {
        Ccubo = Ccolori[1];
        iCcubo = 1;
        break;
    }
    case 3:
    {
        Ccubo = Ccolori[2];
        iCcubo = 2;
        break;
    }
    case 4:
    {
        Ccubo = Ccolori[3];
        iCcubo = 3;
        break;
    }
    }
}

void genPosizioni(bool flag,Pos Poscolori[],int Xcolori)
{
    if (flag == 0)
    {
        std::vector<int> vettore = { 0, 100, 200, 300 };
        int random = std::rand() % vettore.size();
        for (int i = 0; i < 4; i++)
        {
            if (!vettore.empty()) {
                int random = std::rand() % vettore.size();
                Poscolori[i].y = vettore[random];
                vettore.erase(vettore.begin() + random);
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        Poscolori[i].x = Xcolori;
    }
}

void setup(SDL_Window* finestra, SDL_Renderer* Render) 
{
    SDL_Surface* icona = IMG_Load("icona.png");

    SDL_SetWindowIcon(finestra, icona);

    SDL_Texture* Texinizio = IMG_LoadTexture(Render, "Inizio.png");

    SDL_SetRenderDrawColor(Render, 0, 0, 0, 100);

    SDL_RenderClear(Render);

    SDL_RenderCopy(Render, Texinizio, NULL, NULL);

    SDL_RenderPresent(Render);

    genPosizioni(0, Poscolori, Xcolori);

    genPosizioni(0, Poscolori2, Xcolori2);

    genColori();
}

void Input()
{
    SDL_Event evento;
    while (SDL_PollEvent(&evento)) 
    {
        switch (evento.type)
        {
        case SDL_QUIT:
        {
            running = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            switch (evento.key.keysym.sym)
            {
            case SDLK_RETURN:
            {
                inizia = 1;
                break;
            }
            default:break;
            }
            break;
        }
        default:break;
        }
    }
}

void Update(float deltaTime)
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    float distanza = Speed * deltaTime;

    float velocitacolori = Colspeed * deltaTime;

    if (keystate[SDL_SCANCODE_UP])
    {
        if (Poscubo.y > 0)
        {
            Poscubo.y -= distanza;
        }
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        if (Poscubo.y < Hfinestra - Dimcubo)
        {
            Poscubo.y += distanza;
        }
    }
    if (keystate[SDL_SCANCODE_LEFT])
    {
            if (Poscubo.x > 0)
            {
                Poscubo.x -= distanza;
            }
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        if (Poscubo.x < Lfinestra - Dimcubo)
        {
            Poscubo.x += distanza;
        }
    }

    if (Xcolori > 1)
    {
        Xcolori -= (Colspeed * deltaTime);
    }
    else
    {
        Xcolori -= Colspeed - 5;
    }

    if (Xcolori2 > 1)
    {
        Xcolori2 -= (Colspeed * deltaTime);
    }
    else
    {
        Xcolori2 -= Colspeed - 5;
    }

    if (Xcolori < -50)
    {
        Xcolori = 700;
        genPosizioni(0, Poscolori, Xcolori);
    }

    if (Xcolori2 < -50)
    {
        Xcolori2 = Xcolori + 350;
        genPosizioni(0, Poscolori2, Xcolori2);
    }

    genPosizioni(1, Poscolori, Xcolori);

    genPosizioni(1, Poscolori2, Xcolori2);

    collisioni(Poscolori);
    ///// scopri se c e stata collisione con ogni rettangolo di colore diverso della 1 fila
    collisioni(Poscolori2);
    ///// scopri se c e stata collisione con ogni rettangolo di colore diverso della 2 fila 
    


}

void Renderizza(SDL_Renderer* Render, const Pos& Poscubo) 
{
    SDL_SetRenderDrawColor(Render, 0, 0, 0, 255);
    
    SDL_RenderClear(Render);

    SDL_Rect Rcubo = { int(Poscubo.x), int(Poscubo.y), Dimcubo, Dimcubo };

    SDL_SetRenderDrawColor(Render, Ccubo.r, Ccubo.g, Ccubo.b, 255);
    
    SDL_RenderFillRect(Render, &Rcubo);

    for (int i = 0; i < 4; i++)
    {
        Rcolori[i] = { Poscolori[i].x,Poscolori[i].y,50,100 };

        SDL_SetRenderDrawColor(Render, Ccolori[i].r, Ccolori[i].g, Ccolori[i].b, 255);

        SDL_RenderFillRect(Render, &Rcolori[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        Rcolori[i] = { Poscolori2[i].x,Poscolori2[i].y,Lcolori,Hcolori };

        SDL_SetRenderDrawColor(Render, Ccolori[i].r, Ccolori[i].g, Ccolori[i].b, 255);

        SDL_RenderFillRect(Render, &Rcolori[i]);
    }

    scrittaPunti(Render);

    SDL_RenderPresent(Render);
}

int main(int argc, char* argv[]) 
{
    SDL_SetMainReady();

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Errore " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* Finestra = SDL_CreateWindow("Colors Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Lfinestra, Hfinestra, SDL_WINDOW_SHOWN);
    if (Finestra == nullptr) 
    {
        std::cerr << "Errore  " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* Render = SDL_CreateRenderer(Finestra, -1, SDL_RENDERER_ACCELERATED);
    if (Render == nullptr)
    {
        std::cerr << "Errore " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    Uint32 tempoUltimoFrame = SDL_GetTicks();

    std::srand((std::time(NULL)));

    setup(Finestra,Render);

    while (running) 
    {
        Uint32 tempoCorrente = SDL_GetTicks();
        float deltaTime = (tempoCorrente - tempoUltimoFrame) / 1000.0f;
        tempoUltimoFrame = tempoCorrente;

        Input();

        if (inizia == 1)
        {
            Update(deltaTime);
            Renderizza(Render, Poscubo);

            Uint32 tempoFrame = SDL_GetTicks() - tempoCorrente;

            if (tempoFrame < Obbiettivotempoframe) 
            {
                SDL_Delay(Uint32(Obbiettivotempoframe - tempoFrame));
            }
        }
    }

    SDL_DestroyRenderer(Render);
    SDL_DestroyWindow(Finestra);
    SDL_Quit();

    return 0;
}