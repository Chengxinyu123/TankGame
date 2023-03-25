#include <SDL.h>
#include <stdbool.h>

// 定义游戏窗口大小
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// 定义坦克大小和移动速度
#define TANK_SIZE 32
#define TANK_SPEED 4

// 定义子弹大小和速度
#define BULLET_SIZE 8
#define BULLET_SPEED 8

// 定义敌人数量和生成间隔
#define ENEMY_NUM 10
#define ENEMY_INTERVAL 100

int main(int argc, char* argv[])
{
    // 初始化SDL库
    SDL_Init(SDL_INIT_VIDEO);

    // 创建游戏窗口
    SDL_Window* window = SDL_CreateWindow("Tank Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 加载游戏素材
    SDL_Surface* tank_surface = SDL_LoadBMP("tank.bmp");
    SDL_Texture* tank_texture = SDL_CreateTextureFromSurface(renderer, tank_surface);
    SDL_FreeSurface(tank_surface);

    SDL_Surface* bullet_surface = SDL_LoadBMP("bullet.bmp");
    SDL_Texture* bullet_texture = SDL_CreateTextureFromSurface(renderer, bullet_surface);
    SDL_FreeSurface(bullet_surface);

    SDL_Surface* enemy_surface = SDL_LoadBMP("enemy.bmp");
    SDL_Texture* enemy_texture = SDL_CreateTextureFromSurface(renderer, enemy_surface);
    SDL_FreeSurface(enemy_surface);

    // 定义游戏元素
    int player_x = WINDOW_WIDTH / 2 - TANK_SIZE / 2;
    int player_y = WINDOW_HEIGHT - TANK_SIZE;
    int player_speed_x = 0;
    int player_speed_y = 0;

    int bullet_x = 0;
    int bullet_y = 0;
    bool bullet_fired = false;

    int enemy_x[ENEMY_NUM];
    int enemy_y[ENEMY_NUM];
    bool enemy_alive[ENEMY_NUM];
    int enemy_interval = 0;

    // 游戏循环
    bool running = true;
    while (running)
    {
        // 处理用户输入
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    player_speed_x = -TANK_SPEED;
                    break;
                case SDLK_RIGHT:
                    player_speed_x = TANK_SPEED;
                    break;
                case SDLK_UP:
                    player_speed_y = -TANK_SPEED;
                    break;
                case SDLK_DOWN:
                    player_speed_y = TANK_SPEED;
                    break;
                case SDLK_SPACE:
                    if (!bullet_fired)
                    {
                        bullet_x = player_x + TANK_SIZE / 2 - BULLET_SIZE / 2;
                        bullet_y = player_y - BULLET_SIZE;
                        bullet_fired = true;
                    }
                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keys
                {
                case SDLK_LEFT:
                    player_speed_x = 0;
                    break;
                case SDLK_RIGHT:
                    player_speed_x = 0;
                    break;
                case SDLK_UP:
                    player_speed_y = 0;
                    break;
                case SDLK_DOWN:
                    player_speed_y = 0;
                    break;
                default:
                    break;
                }
            }
        }
    }

    // 移动玩家坦克
    player_x += player_speed_x;
    player_y += player_speed_y;

    // 边界检测
    if (player_x < 0)
    {
        player_x = 0;
    }
    if (player_x > WINDOW_WIDTH - TANK_SIZE)
    {
        player_x = WINDOW_WIDTH - TANK_SIZE;
    }
    if (player_y < 0)
    {
        player_y = 0;
    }
    if (player_y > WINDOW_HEIGHT - TANK_SIZE)
    {
        player_y = WINDOW_HEIGHT - TANK_SIZE;
    }

    // 移动子弹
    if (bullet_fired)
    {
        bullet_y -= BULLET_SPEED;
        if (bullet_y < 0)
        {
            bullet_fired = false;
        }
    }

    // 检测子弹和敌人碰撞
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy_alive[i] && bullet_fired && bullet_x + BULLET_SIZE > enemy_x[i] && bullet_x < enemy_x[i] + TANK_SIZE && bullet_y + BULLET_SIZE > enemy_y[i] && bullet_y < enemy_y[i] + TANK_SIZE)
        {
            enemy_alive[i] = false;
            bullet_fired = false;
        }
    }

    // 生成敌人
    enemy_interval++;
    if (enemy_interval >= ENEMY_INTERVAL)
    {
        enemy_interval = 0;
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (!enemy_alive[i])
            {
                enemy_x[i] = rand() % (WINDOW_WIDTH - TANK_SIZE);
                enemy_y[i] = 0;
                enemy_alive[i] = true;
                break;
            }
        }
    }

    // 移动敌人
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy_alive[i])
        {
            enemy_y[i] += TANK_SPEED;
            if (enemy_y[i] > WINDOW_HEIGHT)
            {
                enemy_alive[i] = false;
            }
        }
    }

    // 绘制游戏场景
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect player_rect = { player_x, player_y, TANK_SIZE, TANK_SIZE };
    SDL_RenderCopy(renderer, tank_texture, NULL, &player_rect);

    if (bullet_fired)
    {
        SDL_Rect bullet_rect = { bullet_x, bullet_y, BULLET_SIZE, BULLET_SIZE };
        SDL_RenderCopy(renderer, bullet_texture, NULL, &bullet_rect);
    }

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy_alive[i])
        {
            SDL_Rect enemy_rect = { enemy_x[i], enemy_y[i], TANK_SIZE, TANK_SIZE };
            SDL_RenderCopy(renderer, enemy_texture, NULL, &enemy_rect);
        }
    }

    SDL_RenderPresent(renderer);
}

// 释放资源
SDL_DestroyTexture(t
SDL_DestroyTexture(bullet_texture);
SDL_DestroyTexture(enemy_texture);
SDL_DestroyTexture(tank_texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();

return 0;
