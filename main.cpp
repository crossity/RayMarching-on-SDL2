#include "functions.h"

#include <iostream>
#include <SDL.h>

#define Width  400//1440
#define Height 400//800

using namespace std;

void User_Update(bool &run, SDL_Renderer *renderer, float &camera_angle, vec3 &camera) {
    SDL_SetRenderDrawColor(renderer, 179, 224, 242, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    sphere s(vec3(0.f, 0.f, 3.f), 1.f, vec3(255, 0, 0));
    plane pl(-1.f, vec3(220, 97, 49));
    vec3 light(2.f, 2.f, 0, 224, 224, 242);
    float aspect = (float)Width / (float)Height;
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            vec2 uv = vec2((float)j / Width * 2.f - 1.f, (float)i / Height * 2.f - 1.f);
            uv.x *= aspect;
            uv.y *= -1;
            // if (uv.x*uv.x + uv.y*uv.y <= 1)
            //     SDL_RenderDrawPoint(renderer, j, i); 
            vec3 p(uv.x, uv.y, 1, 179, 224, 242);
            p = RotateY(vec3(), camera_angle, p);
            p = norm(p);
            float dist;
            float step = 0.01;
            while (step <= 8.f) {
                dist = fmin(s.dist(p * step + camera), pl.dist(p * step + camera));
                if (s.dist(p * step + camera) <= 0.00001f) {
                    p.r = s.color.x;
                    p.g = s.color.y;
                    p.b = s.color.z;
                    vec3 shadow = dir(p * step + camera, light);
                    for (float move = 0.1f; move < 10.f ; ) {
                        dist = fmin(s.dist(shadow * move + p * step + camera), length(shadow * move + p * step + camera, light));
                        if (length(shadow * move + p * step + camera, light) <= 1.f) {
                            p.r += light.r;
                            p.g += light.g;
                            p.b += light.b;
                            p.r /= 2.f;
                            p.g /= 2.f;
                            p.b /= 2.f;
                            break;
                        }
                        if (s.dist(shadow * move + p * step + camera) < 0.0000001f) {
                            p.r /= 2.f;
                            p.g /= 2.f;
                            p.b /= 2.f;
                            break;
                        }
                        move += dist;
                    }
                    break;
                }
                if (pl.dist(p * step + camera) <= 0.00001f) {
                    p.r = pl.color.x;
                    p.g = pl.color.y;
                    p.b = pl.color.z;
                    vec3 shadow = dir(p * step + camera, light);
                    for (float move = 0.1f; move < 10.f; ) {
                        dist = fmin(s.dist(shadow * move + p * step + camera), length(shadow * move + p * step + camera, light));
                        if (length(shadow * move + p * step + camera, light) <= 1.f) {
                            p.r += light.r;
                            p.g += light.g;
                            p.b += light.b;
                            p.r /= 2.f;
                            p.g /= 2.f;
                            p.b /= 2.f;
                            break;
                        }
                        if (s.dist(shadow * move + p * step + camera) <= 0.00001f) {
                            p.r /= 2.f;
                            p.g /= 2.f;
                            p.b /= 2.f;
                            break;
                        }
                        move += dist;
                    }
                    break;
                }
                step += dist;
            }
            SDL_SetRenderDrawColor(renderer, p.r, p.g, p.b, 255);
            SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_RenderPresent(renderer);
    // run = false;
    // camera_angle += 0.1;
}   

int main() {
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        cout << "SDL could not be initiaiized: " << SDL_GetError();
    else
        cout << "SDL system is ready to go" << endl;

    window = SDL_CreateWindow("3D Eingine", 20, 20, Width, Height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool run = true;

    float camera_angle = 0;
    vec3 camera = vec3(0, 0, 0);

    User_Update(run, renderer, camera_angle, camera);
    
    while (run) {
        SDL_Event event;
    
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT:
                    run = false;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}