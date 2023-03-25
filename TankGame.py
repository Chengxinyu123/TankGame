import pygame
import random

# 初始化pygame
pygame.init()

# 设置游戏窗口的尺寸和标题
width, height = 640, 480
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption('Tank War')

# 定义游戏中使用的颜色
white = (255, 255, 255)
black = (0, 0, 0)
green = (0, 255, 0)
red = (255, 0, 0)

# 定义坦克的属性
tank_width = 40
tank_height = 40
tank_speed = 5

# 定义子弹的属性
bullet_width = 10
bullet_height = 10
bullet_speed = 10

# 加载游戏中使用的图片
tank_img = pygame.image.load('tank.png')
bullet_img = pygame.image.load('bullet.png')

# 定义坦克类
class Tank(pygame.sprite.Sprite):
    def __init__(self, x, y):
        pygame.sprite.Sprite.__init__(self)
        self.image = tank_img
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        self.speed = tank_speed
        self.direction = 'up'

    def move(self):
        if self.direction == 'up':
            self.rect.y -= self.speed
        elif self.direction == 'down':
            self.rect.y += self.speed
        elif self.direction == 'left':
            self.rect.x -= self.speed
        elif self.direction == 'right':
            self.rect.x += self.speed

    def fire(self):
        bullet = Bullet(self.rect.centerx, self.rect.centery, self.direction)
        all_sprites.add(bullet)
        bullets.add(bullet)

# 定义子弹类
class Bullet(pygame.sprite.Sprite):
    def __init__(self, x, y, direction):
        pygame.sprite.Sprite.__init__(self)
        self.image = bullet_img
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        self.speed = bullet_speed
        self.direction = direction

    def update(self):
        if self.direction == 'up':
            self.rect.y -= self.speed
        elif self.direction == 'down':
            self.rect.y += self.speed
        elif self.direction == 'left':
            self.rect.x -= self.speed
        elif self.direction == 'right':
            self.rect.x += self.speed
        if self.rect.left < 0 or self.rect.right > width or self.rect.top < 0 or self.rect.bottom > height:
            self.kill()

# 创建所有精灵组
all_sprites = pygame.sprite.Group()
bullets = pygame.sprite.Group()

# 创建坦克
tank = Tank(width // 2, height // 2)
all_sprites.add(tank)

# 生成随机位置的敌人坦克
def create_enemy():
    enemy = Tank(random.randint(0, width), random.randint(0, height))
    all_sprites.add(enemy)
    return enemy

enemies = [create_enemy() for i in range(3)]

# 游戏主循环
running = True
# 添加碰撞检测和游戏结束检测
while running:
    # 处理游戏事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                tank.direction = 'up'
            elif event.key == pygame.K_DOWN:
                tank.direction = 'down'
            elif event.key == pygame.K_LEFT:
                tank.direction = 'left'
            elif event.key == pygame.K_RIGHT:
                tank.direction = 'right'
            elif event.key == pygame.K_SPACE:
                tank.fire()

    # 更新游戏状态
    all_sprites.update()

    # 检查子弹是否打中敌人坦克
    for bullet in bullets:
        hit_enemies = pygame.sprite.spritecollide(bullet, enemies, True)
        for enemy in hit_enemies:
            bullet.kill()

    # 检查敌人坦克是否碰撞到墙或玩家坦克
    for enemy in enemies:
        if pygame.sprite.collide_rect(enemy, tank):
            game_over()
        if pygame.sprite.spritecollide(enemy, walls, False):
            enemy.change_direction()

    # 检查玩家坦克是否碰撞到墙
    if pygame.sprite.spritecollide(tank, walls, False):
        tank.change_direction()

    # 绘制游戏画面
    screen.fill(white)
    all_sprites.draw(screen)
    pygame.display.flip()

# 退出pygame
pygame.quit()
