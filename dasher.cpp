#include "raylib.h"

int main(){
    //dimensions window
    const int width{640};
    const int height{480};

    InitWindow(width,height,"Dapper Dasher");
    SetTargetFPS(60);

    //nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0,0.0,nebula.width/8,nebula.height/8};
    Vector2 nebPos{width,height-nebRec.height};
    int nebVel{-300};
    int nebFrame{0};
    float nebUpdatetime{1.0/12.0};
    float nebRunningtime{0.0};

    //scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width=scarfy.width/6;
    scarfyRec.height=scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y=0;
    Vector2 scarfyPos;
    scarfyPos.x=width/2-scarfyRec.width/2;
    scarfyPos.y=height-scarfyRec.height;

    int frame{0};
    float updatetime{1.0/12.0};
    float runningtime{0.0};

    const int gravity{1200};
    const int jumpVel{-600};
    int velocity{0};
    bool IsInAir{false};

    while(WindowShouldClose()!=true){
        BeginDrawing();
        ClearBackground(RED);
       float DT{GetFrameTime()};
        if(scarfyPos.y>=height-scarfyRec.height){
            velocity = 0;
            IsInAir = false;
        }
        else{
            velocity+=gravity*DT;
            IsInAir=true;
        }

        if(IsKeyPressed(KEY_SPACE) && IsInAir==false)
        {
            velocity += jumpVel;
        }
        
        nebPos.x += nebVel*DT;
        scarfyPos.y += velocity*DT;

        runningtime+=DT;
        nebRunningtime+=DT;
        nebRec.x=nebFrame*nebRec.width;
        scarfyRec.x = frame*scarfyRec.width;

        if(runningtime>=updatetime and !IsInAir){
            frame++;
            runningtime=0.0;
            if (frame >5){
                frame=0;
            }
        }
        if(nebRunningtime>=nebUpdatetime ){
            nebFrame++;
            nebRunningtime=0.0;
            if (nebFrame >7){
                nebFrame=0;
            }
        }

        DrawTextureRec(nebula,nebRec,nebPos,WHITE);
        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}