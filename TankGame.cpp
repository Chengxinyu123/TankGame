#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

// 游戏地图大小
const int MapWidth = 20;
const int MapHeight = 20;

// 坦克类型
enum class TankType {
    Player, Enemy
};

// 方向类型
enum class Direction {
    Up, Down, Left, Right
};

// 子弹类型
struct Bullet {
    int x;
    int y;
    Direction dir;
};

// 坦克类型
struct Tank {
    int x;
    int y;
    Direction dir;
    TankType type;
    vector<Bullet> bullets;
};

// 敌人类型
struct Enemy {
    int x;
    int y;
    int step;
};

// 游戏地图
char map[MapWidth][MapHeight];

// 初始化游戏地图
void InitMap() {
    for (int i = 0; i < MapWidth; i++) {
        for (int j = 0; j < MapHeight; j++) {
            map[i][j] = ' ';
        }
    }
}

// 在游戏地图上绘制坦克
void DrawTank(const Tank& tank) {
    if (tank.type == TankType::Player) {
        map[tank.x][tank.y] = 'P';
    }
    else {
        map[tank.x][tank.y] = 'E';
    }
}

// 在游戏地图上绘制子弹
void DrawBullet(const Bullet& bullet) {
    switch (bullet.dir) {
    case Direction::Up:
        map[bullet.x][bullet.y] = '^';
        break;
    case Direction::Down:
        map[bullet.x][bullet.y] = 'v';
        break;
    case Direction::Left:
        map[bullet.x][bullet.y] = '<';
        break;
    case Direction::Right:
        map[bullet.x][bullet.y] = '>';
        break;
    }
}

// 在游戏地图上绘制敌人
void DrawEnemy(const Enemy& enemy) {
    map[enemy.x][enemy.y] = 'E';
}

// 在游戏地图上清除坦克
void ClearTank(const Tank& tank) {
    map[tank.x][tank.y] = ' ';
}

// 在游戏地图上清除子弹
void ClearBullet(const Bullet& bullet) {
    map[bullet.x][bullet.y] = ' ';
}

// 在游戏地图上清除敌人
void ClearEnemy(const Enemy& enemy) {
    map[enemy.x][enemy.y] = ' ';
}

// 移动坦克
void MoveTank(Tank& tank) {
    ClearTank(tank);
    switch (tank.dir) {
    case Direction::Up:
        if (tank.x > 0) {
            tank.x--;
        }
        break;
    case Direction::Down:
        if (tank.x < MapWidth - 1) {
            tank.x++;
        }
        break;
    case Direction::Left:
        if (tank.y > 0) {
            tank.y--;
        }
        break;
    case Direction::Right:
        if (tank.y < MapHeight - 1) {
            tank.y++;
        }
        break;
   // 发射子弹
void FireBullet(Tank& tank) {
    Bullet bullet = { tank.x, tank.y, tank.dir };
    tank.bullets.push_back(bullet);
}

// 移动子弹
void MoveBullet(Bullet& bullet) {
    ClearBullet(bullet);
    switch (bullet.dir) {
    case Direction::Up:
        if (bullet.x > 0) {
            bullet.x--;
        }
        break;
    case Direction::Down:
        if (bullet.x < MapWidth - 1) {
            bullet.x++;
        }
        break;
    case Direction::Left:
        if (bullet.y > 0) {
            bullet.y--;
        }
        break;
    case Direction::Right:
        if (bullet.y < MapHeight - 1) {
            bullet.y++;
        }
        break;
    }
    DrawBullet(bullet);
}

// 发射敌人子弹
void EnemyFireBullet(Enemy& enemy) {
    Bullet bullet = { enemy.x, enemy.y, Direction::Down };
    enemy.step = 0;
    enemy.y++;
    DrawEnemy(enemy);
}

// 移动敌人
void MoveEnemy(Enemy& enemy) {
    ClearEnemy(enemy);
    if (enemy.step == 0) {
        EnemyFireBullet(enemy);
    }
    else if (enemy.step < 3) {
        enemy.y++;
    }
    else if (enemy.step == 3) {
        enemy.y--;
    }
    else if (enemy.step < 7) {
        enemy.x++;
    }
    else if (enemy.step == 7) {
        enemy.x--;
    }
    enemy.step++;
    if (enemy.step == 8) {
        enemy.step = 0;
    }
    DrawEnemy(enemy);
}

// 碰撞检测
bool IsCollide(const Bullet& bullet, const Tank& tank) {
    if (bullet.x == tank.x && bullet.y == tank.y) {
        return true;
    }
    return false;
}

// 碰撞检测
bool IsCollide(const Bullet& bullet, const Enemy& enemy) {
    if (bullet.x == enemy.x && bullet.y == enemy.y) {
        return true;
    }
    return false;
}

// 游戏主循环
void GameLoop() {
    // 初始化游戏地图
    InitMap();

    // 创建玩家坦克
    Tank playerTank = { 0, 0, Direction::Right, TankType::Player };
    DrawTank(playerTank);

    // 创建敌人坦克
    vector<Enemy> enemies;
    Enemy enemy1 = { 10, 5, 0 };
    Enemy enemy2 = { 15, 10, 0 };
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    for (auto& enemy : enemies) {
        DrawEnemy(enemy);
    }

    // 游戏主循环
    while (true) {
        // 处理用户输入
        if (_kbhit()) {
            int ch = _getch();
            switch (ch) {
            case 'w':
                playerTank.dir = Direction::Up;
                MoveTank(playerTank);
                break;
            case 's':
                playerTank.dir = Direction::Down;
                MoveTank(playerTank);
                break;
            case 'a':
                playerTank.dir = Direction::Left;
                Move

