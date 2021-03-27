#!/usr/bin/env python
import sys
sys.path.insert(1, sys.argv[1])
from duels import Subscriber
import pygame
import os

game_path=os.path.abspath(os.path.dirname(__file__))
image_path=game_path+"/spritesV2/"



## global variables ================================================

screen_width = 1440 #pix
screen_height = 960 #pix

top_border = 0 #pix
left_border = 0 #pix

box_width = 48 #pix
box_height = 48 #pix



## init =============================================================

game = Subscriber()
init_msg = game.get_init()

grid_width = init_msg.width #boxes
grid_height = init_msg.height #boxes

# init pygame
pygame.init()
screen = pygame.display.set_mode((screen_width, screen_height))

# window name and icon
pygame.display.set_caption("Treasure_hunt")
pygame.display.set_icon(pygame.image.load(image_path+"icon.png"))


# loading images
background = pygame.image.load(image_path+"background.png")
sonar = pygame.image.load(image_path+"sonar.png")
bloc = pygame.image.load(image_path+"bloc.png")
treasure = pygame.image.load(image_path+"treasure.png")

# recovering init_msg
p1_x = init_msg.x1
p1_y = init_msg.y1
p1_t = init_msg.t1

p2_x = init_msg.x2
p2_y = init_msg.y2
p2_t = init_msg.t2

obstacles_x = init_msg.Xo
obstacles_y = init_msg.Yo

treasure_x = init_msg.xt
treasure_y = init_msg.yt

game.ready()


## utilitary functions =============================================

def convert_coordinates(coords):
    """converts grid coordinates to images coordinates"""

    i, j = coords

    x = left_border + i*box_width - 1
    y = top_border + j*box_height - 1

    return (x, y)



def blit_players(x1, y1, t1, x2, y2, t2):
    """generates blit sequence for players"""
    player1 = pygame.image.load(image_path+"player1_orientation_" + str(t1) + ".png")
    player2 = pygame.image.load(image_path+"player2_orientation_" + str(t2) + ".png")

    return [(player1, convert_coordinates((x1, y1))), (player2, convert_coordinates((x2, y2)))]



def blit_sonars(sonar_x, sonar_y):
    """generates blit sequence for sonars"""
    blit_sequence = []

    for k in range(len(sonar_x)):
        blit_sequence.append((sonar, convert_coordinates((sonar_x[k], sonar_y[k]))))

    return blit_sequence



def blit_blocs(obstacles_x, obstacles_y):
    """generates blit sequence for obstacles"""
    blit_sequence = []

    for k in range(len(obstacles_x)):
        blit_sequence.append((bloc, convert_coordinates((obstacles_x[k], obstacles_y[k]))))

    return blit_sequence


## main loop ========================================================

while True:
    msg = game.refresh()
    if msg.winner:
        break

    # display non changing elements
    screen.blit(background, (0,0))
    screen.blit(treasure, convert_coordinates((treasure_x, treasure_y)))
    screen.blits(blit_blocs(obstacles_x, obstacles_y))

    # recovering display info from server
    p1_x = msg.x1
    p1_y = msg.y1
    p1_t = msg.t1

    p2_x = msg.x2
    p2_y = msg.y2
    p2_t = msg.t2

    sonar_p1_x = msg.Xs1
    sonar_p1_y = msg.Ys1

    sonar_p2_x = msg.Xs2
    sonar_p2_y = msg.Ys2

    # display elements on the screen
    screen.blits(blit_sonars(sonar_p1_x, sonar_p1_y))
    screen.blits(blit_sonars(sonar_p2_x, sonar_p2_y))
    screen.blits(blit_players(p1_x, p1_y, p1_t, p2_x, p2_y, p2_t))

    pygame.display.update()

# update display from winner


if msg.winner == 1:
	game_over = pygame.image.load(image_path+"game_over_p1_wins.png")
else:
	game_over = pygame.image.load(image_path+"game_over_p2_wins.png")
	 
screen.blit(game_over, (0,0))
pygame.display.update()

pygame.time.wait(3000)
pygame.quit()
